package program

import javafx.scene.layout.VBox
import javafx.scene.transform.Affine
import javafx.application.Platform
import javafx.scene.input.KeyCode
import javafx.scene.transform.NonInvertibleTransformException
import javafx.scene.control.Slider
import javafx.event.EventHandler
import javafx.geometry.Orientation
import javafx.scene.Cursor
import javafx.scene.canvas.Canvas
import javafx.scene.control.Button
import javafx.scene.control.Label
import javafx.scene.control.Separator
import javafx.scene.input.MouseEvent
import javafx.scene.layout.HBox
import javafx.scene.paint.Color
import java.util.*
import kotlin.concurrent.schedule
import kotlin.math.floor
import kotlin.math.max
import kotlin.math.min

class MainView : VBox() {

    companion object Constants {
        const val SLOW_SPEED = 500.0
        const val FAST_SPEED = 50.0
        const val SONIC = 1.0

        const val ERASE_MODE = 0
        const val DRAW_MODE = 1
        const val TOGGLE_MODE = 2

        const val CANVAS_WIDTH = 950.0
        const val CANVAS_HEIGHT = 699.0
        const val SLIDER_WIDTH = CANVAS_WIDTH - 300.0
        const val BOX_SPACING = 10.0

        val ACTIVE_COLOR: Color = Color.RED
        val INACTIVE_COLOR: Color = Color.BLACK
        val HOVER_COLOR: Color = Color.DODGERBLUE

        val SIM_BACKGROUND_COLOR: Color = Color.LIGHTGRAY
        val SIM_CELL_COLOR: Color = Color.BLACK

        val BRUSH_SIZES = arrayOf(1, 4, 9, 16, 25)
    }

    private lateinit var simulation: Simulation
    private val affine: Affine
    private val canvas: Canvas
    private var timer: Timer
    private var editMode = DRAW_MODE
    private var currentSpeed = FAST_SPEED
    private var running = false

    private val drawIndicator = Label("D - Draw")
    private val toggleIndicator = Label("T - Toggle")
    private val eraseIndicator = Label("E - Erase")

    private var currentBrush = 0
    private val brushSizeLabel = Label("Brush Size: ${BRUSH_SIZES[currentBrush]}\t")

    init {
        timer = Timer()
        val stepButton = Button("Step")
        stepButton.onAction = EventHandler {
            simulation.step()
            draw()
        }

        val runButton = Button("Run")
        runButton.onAction = EventHandler { resume() }

        val slider = Slider()
        slider.value = currentSpeed
        slider.max = SLOW_SPEED
        slider.min = SONIC
        slider.isShowTickLabels = true
        slider.isShowTickMarks = true
        slider.valueProperty().addListener { _, _, NEW: Number -> changeSpeed(NEW) }
        slider.minWidth = SLIDER_WIDTH

        val runBox = HBox(runButton, Label("Delay Between Steps (ms) : "), slider)
        runBox.spacing = BOX_SPACING
        spacing = BOX_SPACING

        val pauseButton = Button("Pause")
        pauseButton.onAction = EventHandler { pause() }

        val resetButton = Button("Reset")
        resetButton.onAction = EventHandler {
            reset()
            draw()
        }

        val clearButton = Button("Clear")
        clearButton.onAction = EventHandler {
            simulation.clear()
            draw()
        }

        val controlButtons = HBox(pauseButton, resetButton, clearButton)
        controlButtons.spacing = 10.0

        listOf(drawIndicator, eraseIndicator, toggleIndicator).forEach {
            it.cursor = Cursor.HAND
            it.onMouseEntered = EventHandler { _ -> if (it.textFill != ACTIVE_COLOR) it.textFill = HOVER_COLOR }
            it.onMouseExited = EventHandler { updateModeIndicator() }
        }
        handleMouseAsKey(drawIndicator, KeyCode.D)
        handleMouseAsKey(eraseIndicator, KeyCode.E)
        handleMouseAsKey(toggleIndicator, KeyCode.T)


        val brushIncrease = Button("+")
        val brushDecrease = Button("-")

        brushIncrease.setOnAction { changeBrushSize(true) }
        brushDecrease.setOnAction { changeBrushSize(false) }

        val keys = HBox(
                Label("Draw Mode Keys: "),
                drawIndicator,
                eraseIndicator,
                toggleIndicator,
                Separator(Orientation.VERTICAL),
                brushSizeLabel,
                brushDecrease,
                brushIncrease
        )
        keys.spacing = BOX_SPACING

        canvas = Canvas(CANVAS_WIDTH, CANVAS_HEIGHT)
        // Using runLater to avoid thread crashes.
        canvas.onMousePressed = EventHandler { event -> Platform.runLater { handleDraw(event) } }
        canvas.onMouseDragged = EventHandler { event -> Platform.runLater { handleDraw(event) } }
        onKeyPressed = EventHandler { keyEvent -> onKeyPressed(keyEvent.code) }

        children.addAll(
                stepButton,
                controlButtons,
                runBox,
                keys,
                canvas
        )

        reset()
        println("Initialized simulation...")
        println("Height: " + simulation.height + ", Width: " + simulation.width)
        affine = Affine()
        affine.appendScale(canvas.width / simulation.width, canvas.height / simulation.height)
        updateModeIndicator()
    }

    private fun pause() {
        running = false
        timer.cancel()
    }

    private fun resume() {
        running = true
        timer.cancel()
        timer = Timer()
        timer.schedule(15, currentSpeed.toLong()) {
            // Using runLater to avoid thread crashes.
            Platform.runLater {
                simulation.step()
                draw()
            }
        }
    }

    private fun changeSpeed(speed: Number) {
        currentSpeed = speed.toDouble()
        if (running) resume() else pause()
    }

    private fun reset() {
        simulation = Simulation(Simulation.DEFAULT_STARTER)
        simulation.step()
    }

    private fun handleMouseAsKey(label: Label, kc: KeyCode) {
        label.onMousePressed = EventHandler { onKeyPressed(kc) }
    }

    private fun changeBrushSize(increase: Boolean) {
        currentBrush = if (increase) {
            min((currentBrush + 1), BRUSH_SIZES.size - 1)
        } else {
            max(currentBrush - 1, 0)
        }
        brushSizeLabel.text = "Brush Size: ${BRUSH_SIZES[currentBrush]}\t"
    }

    private fun updateModeIndicator() {
        when (editMode) {
            DRAW_MODE -> {
                drawIndicator.textFill = ACTIVE_COLOR
                eraseIndicator.textFill = INACTIVE_COLOR
                toggleIndicator.textFill = INACTIVE_COLOR
            }
            ERASE_MODE -> {
                drawIndicator.textFill = INACTIVE_COLOR
                eraseIndicator.textFill = ACTIVE_COLOR
                toggleIndicator.textFill = INACTIVE_COLOR
            }
            TOGGLE_MODE -> {
                drawIndicator.textFill = INACTIVE_COLOR
                eraseIndicator.textFill = INACTIVE_COLOR
                toggleIndicator.textFill = ACTIVE_COLOR
            }
        }
    }

    private fun onKeyPressed(keyCode: KeyCode) {
        when (keyCode) {
            KeyCode.D -> editMode = DRAW_MODE
            KeyCode.E -> editMode = ERASE_MODE
            KeyCode.T -> editMode = TOGGLE_MODE
            else -> {
            }
        }
        updateModeIndicator()
    }

    private fun handleDraw(mouseEvent: MouseEvent) {
        try {
            val simCoord = affine.inverseTransform(mouseEvent.x, mouseEvent.y)
            val simX = floor(simCoord.x).toInt()
            val simY = floor(simCoord.y).toInt()
            when (editMode) {
                ERASE_MODE -> simOperate(simY, simX) { y, x -> simulation.setDead(y, x) }
                DRAW_MODE -> simOperate(simY, simX) { y, x -> simulation.setAlive(y, x) }
                TOGGLE_MODE -> simOperate(simY, simX) { y, x -> simulation.toggleState(y, x) }
            }
            draw()
        } catch (e: NonInvertibleTransformException) {
            e.printStackTrace()
        }

    }

    private fun simOperate(y: Int, x: Int, operation: (Int, Int) -> Unit) {
        val lower: Int
        val upper: Int
        when (BRUSH_SIZES[currentBrush]) {
            1 -> operation(y, x).also { return }
            4 -> {
                lower = 0
                upper = 1
            }
            9 -> {
                lower = 1
                upper = 1
            }
            16 -> {
                lower = 1
                upper = 2
            }
            25 -> {
                lower = 2
                upper = 2
            }
            else -> return
        }
        for (i in y - lower..y + upper)
            for (j in x - lower..x + upper)
                operation(i, j)
    }

    fun draw() {
        val g = canvas.graphicsContext2D
        g.fill = SIM_BACKGROUND_COLOR
        g.fillRect(0.0, 0.0, canvas.width, canvas.width)
        g.transform = affine
        g.fill = SIM_CELL_COLOR
        for (r in 0 until simulation.height) {
            for (c in 0 until simulation.width) {
                if (simulation.getCellValue(r, c) == 1) {
                    g.fillRect(c.toDouble(), r.toDouble(), 1.0, 1.0)
                }
            }
        }
        g.lineWidth = 0.05
        g.stroke = SIM_BACKGROUND_COLOR
        var x = 0.0
        while (x <= canvas.width) {
            g.strokeLine(x, 0.0, x, canvas.width)
            x++
        }
        var y = 0.0
        while (y <= canvas.height) {
            g.strokeLine(0.0, y, canvas.height, y)
            y++
        }
    }

}