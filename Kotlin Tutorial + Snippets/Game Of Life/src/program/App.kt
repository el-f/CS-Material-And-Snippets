package program

import javafx.stage.Stage
import javafx.scene.Scene
import com.sun.javafx.application.LauncherImpl
import javafx.application.Application
import kotlin.system.exitProcess

class App : Application() {
    override fun start(primaryStage: Stage) {
        val mainView = MainView()
        primaryStage.title = "Game of Life"
        primaryStage.scene = Scene(mainView, 950.0, 855.0)
        primaryStage.setOnCloseRequest { exitProcess(0) }
        primaryStage.show()
        mainView.draw()
    }
}

fun main(args: Array<String>) {
    LauncherImpl.launchApplication(App::class.java, args)
}