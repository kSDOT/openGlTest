#include <QGuiApplication>
#include "shaderglscene.h"
#include "sceneglwindow.h"

int main(int argc, char *argv[]){
    QGuiApplication a(argc, argv);
        SceneGLWindow window;
        QSurfaceFormat fmt;
        fmt.setSamples(16);
        window.setFormat(fmt);
        ShaderGLScene scene(&window);
        window.scene(&scene);
        scene.angle(30);
        window.resize(600, 400);
        window.show();
    return a.exec();
}

