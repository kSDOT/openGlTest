#include "sceneglwindow.h"



void SceneGLWindow::initializeGL(){
    if(scene())
        scene()->initialize();
    }



void SceneGLWindow::paintGL(){
    if(scene())
        scene()->paint();
 }



