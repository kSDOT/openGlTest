#ifndef ABSTRACTGLSCENE_H
#define ABSTRACTGLSCENE_H
#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include <gl/GL.h>

class AbstractGLScene: protected QOpenGLFunctions{
     public:
      AbstractGLScene(QOpenGLWindow* wnd = nullptr):
        mInitialized{0}, mWin{wnd} {}
      virtual ~AbstractGLScene(){ }

      QOpenGLWindow* window() const {return mWin;}
      QOpenGLContext* context(){ return window()? window()->context() : nullptr;}
      virtual void initialize();
      virtual void paint() = 0;
     protected:
      bool mInitialized;
     private:
         QOpenGLWindow* mWin;

 };

#endif // ABSTRACTGLSCENE_H
