#ifndef SHADERGLSCENE_H
#define SHADERGLSCENE_H
#include <QObject>
#include <QFile>
#include <QOpenGLShaderProgram>
#include <qopenglbuffer.h>
#include <QOpenGLContext>
#include "abstractglscene.h"
#include "sceneglwindow.h"
#include "plyreader.h"
class ShaderGLScene : public QObject,
                      public AbstractGLScene{
    Q_OBJECT
    Q_PROPERTY(qreal angle READ angle WRITE angle)
 public:
    explicit ShaderGLScene(SceneGLWindow* wnd): AbstractGLScene{wnd}, mAngle{0}
                                                { wnd->scene(this);
                                                 mInitialized = false;
                                                 initializeCubeData();}

    void initialize() override;
    void paint() override;

    qreal angle() const {return mAngle;}
    void  angle(qreal a){mAngle = a; window()->update();}
 protected:

    void initializeCubeData();
 private:
    static QString fileContent(const QString& filePath, const char* codec = nullptr);
    void paintCube(const QMatrix4x4&);
    struct ScenePoint{
        QVector3D coords;
        QVector3D normal;
        ScenePoint(const QVector3D& c = QVector3D(), const QVector3D& n = QVector3D()):
            coords{c}, normal{n}{}
    };

    qreal mAngle;
    QOpenGLShaderProgram mShader;
    QMatrix4x4 mModelMatrix;
    QMatrix4x4 mViewMatrix;
    QMatrix4x4 mProjectionMatrix;
    QVector<ScenePoint> mData;
signals:

public slots:
};

#endif // SHADERGLSCENE_H
