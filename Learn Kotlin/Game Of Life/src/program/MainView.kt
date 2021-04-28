package program

import javafx.scene.layout.VBox
import javafx.scene.transform.Affine
import javafx.application.Platform
import javafx.scene.input.KeyCode
import javafx.scene.transform.NonInvertibleTransformException
import javafx.scene.control.Slider
import javafx.event.EventHandler
import javafx.scene.Cursor
import javafx.scene.canvas.Canvas
import javafx.scene.control.Button
import javafx.scene.control.Label
import javafx.scene.input.KeyEvent
import javafx.scene.input.MouseEvent
import javafx.scene.layout.HBox
import javafx.scene.paint.Color
import java.util.*
import kotlin.math.floor

class MainView : VBox() {

    companion object Constants {
        const val SLOW_SPEED = 500
        const val FAST_SPEED = 50
        const val SONIC = 1

        const val ERASE_MODE = 0
        const val DRAW_MODE = 1
        const val TOGGLE_MODE = 2
    }

    private lateinit var simulation: Simulation
    private val affine: Affine
    private val canvas: Canvas
    private var timer: Timer
    private var drawMode = DRAW_MODE
    private var currentSpeed = FAST_SPEED
    private var running = false
    private val drawIndicator = Label("D - Draw")
    private val toggleIndicator = Label("T - Toggle")
    private val eraseIndicator = Label("E - Erase")

    private fun pause() {
        running = false
        timer.cancel()
    }

    private fun resume() {
        timer.cancel()
        running = true
        timer = Timer()
        timer.schedule(object : TimerTask() {
            override fun run() {
                // Using runLater to avoid thread crashes.
                Platform.runLater {
                    simulation.step()
                    draw()
                }
            }
        }, 15, currentSpeed.toLong())
    }

    private fun changeSpeed(speed: Int) {
        currentSpeed = speed
        if (running) resume() else pause()
    }

    private fun reset() {
        simulation = Simulation(Simulation.DEFAULT_STARTER)
        simulation.step()
    }

    private fun handleMouseAsKey(label: Label, kc: KeyCode) {
        label.onMousePressed = EventHandler { onKeyPressed(KeyEvent(null, null, null, kc, false, false, false, false)) }
    }

    private fun updateModeIndicator() {
        when (drawMode) {
            DRAW_MODE -> {
                drawIndicator.textFill = Color.RED
                eraseIndicator.textFill = Color.BLACK
                toggleIndicator.textFill = Color.BLACK
            }
            ERASE_MODE -> {
                drawIndicator.textFill = Color.BLACK
                eraseIndicator.textFill = Color.RED
                toggleIndicator.textFill = Color.BLACK
            }
            TOGGLE_MODE -> {
                drawIndicator.textFill = Color.BLACK
                eraseIndicator.textFill = Color.BLACK
                toggleIndicator.textFill = Color.RED
            }
        }
    }

    private fun onKeyPressed(keyEvent: KeyEvent) {
        when (keyEvent.code) {
            KeyCode.D -> drawMode = DRAW_MODE
            KeyCode.E -> drawMode = ERASE_MODE
            KeyCode.T -> drawMode = TOGGLE_MODE
            else -> {}
        }
        updateModeIndicator()
    }

    private fun handleDraw(mouseEvent: MouseEvent) {
        try {
            val simCoord = affine.inverseTransform(mouseEvent.x, mouseEvent.y)
            val simX = floor(simCoord.x).toInt()
            val simY = floor(simCoord.y).toInt()
            when (drawMode) {
                ERASE_MODE -> simulation.setDead(simY, simX)
                DRAW_MODE -> simulation.setAlive(simY, simX)
                TOGGLE_MODE -> simulation.toggleState(simY, simX)
            }
            draw()
        } catch (e: NonInvertibleTransformException) {
            e.printStackTrace()
        }
    }

    fun draw() {
        val g = canvas.graphicsContext2D
        g.fill = Color.LIGHTGRAY
        g.fillRect(0.0, 0.0, canvas.width, canvas.width)
        g.transform = affine
        g.fill = Color.BLACK
        for (r in 0 until simulation.height) {
            for (c in 0 until simulation.width) {
                if (simulation.getCellValue(r, c) == 1) {
                    g.fillRect(c.toDouble(), r.toDouble(), 1.0, 1.0)
                }
            }
        }
        g.lineWidth = 0.05
        g.stroke = Color.LIGHTGRAY
        var x = 0
        while (x <= canvas.width) {
            g.strokeLine(x.toDouble(), 0.0, x.toDouble(), canvas.width)
            x++
        }
        var y = 0
        while (y <= canvas.height) {
            g.strokeLine(0.0, y.toDouble(), canvas.height, y.toDouble())
            y++
        }
    }


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
        slider.value = currentSpeed.toDouble()
        slider.max = SLOW_SPEED.toDouble()
        slider.min = SONIC.toDouble()
        slider.isShowTickLabels = true
        slider.isShowTickMarks = true
        slider.valueProperty().addListener { _, _, NEW: Number -> changeSpeed(NEW.toInt()) }
        slider.minWidth = 650.0

        val runBox = HBox(runButton, Label("Delay Between Steps (ms) : "), slider)
        runBox.spacing = 10.0
        spacing = 10.0

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

        listOf(drawIndicator, eraseIndicator, toggleIndicator).forEach { it.cursor = Cursor.HAND }
        handleMouseAsKey(drawIndicator, KeyCode.D)
        handleMouseAsKey(eraseIndicator, KeyCode.E)
        handleMouseAsKey(toggleIndicator, KeyCode.T)

        val keys = HBox(Label("Draw Mode Keys: "), drawIndicator, eraseIndicator, toggleIndicator)
        keys.spacing = 10.0

        canvas = Canvas(950.0, 708.0)
        // Using runLater to avoid thread crashes.
        canvas.onMousePressed = EventHandler { event -> Platform.runLater { handleDraw(event) } }
        canvas.onMouseDragged = EventHandler { event -> Platform.runLater { handleDraw(event) } }
        onKeyPressed = EventHandler { keyEvent -> onKeyPressed(keyEvent) }

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
}