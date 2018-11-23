#ifndef SIMPLEGLWINDOW_H
#define SIMPLEGLWINDOW_H
#include "abstractglscene.h"
#include <QObject>
//window for current scene

class AbstractGLScene;
class SceneGLWindow : public QOpenGLWindow{
    public:
        SceneGLWindow(QWindow* parent = nullptr)
            : QOpenGLWindow(NoPartialUpdate, parent),
              mScene{nullptr}{}
        ~SceneGLWindow(){}

        AbstractGLScene* scene() const{return mScene;}//get and set for member
        void scene(AbstractGLScene* aSc){mScene = aSc;}

    protected:
        void initializeGL() override;


        void paintGL() override;
    private:
        AbstractGLScene* mScene;


};

#endif // SIMPLEGLWINDOW_H
