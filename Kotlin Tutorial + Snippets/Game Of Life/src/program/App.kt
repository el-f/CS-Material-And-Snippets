package program

import javafx.stage.Stage
import javafx.scene.Scene
import com.sun.javafx.application.LauncherImpl
import javafx.application.Application

class App : Application() {
    override fun start(primaryStage: Stage) {
        val mainView = MainView()
        val scene = Scene(mainView, 950.0, 855.0)
        primaryStage.title = "Game of Life"
        primaryStage.scene = scene
        primaryStage.show()
        mainView.draw()
    }
}

fun main(args: Array<String>) {
    LauncherImpl.launchApplication(App::class.java, args)
}