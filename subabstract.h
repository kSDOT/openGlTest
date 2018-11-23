#ifndef SUBABSTRACT_H
#define SUBABSTRACT_H
#include "abstractglscene.h"
#include "sceneglwindow.h"
#include <QImage>
#include <QOpenGLTexture>
#include <QVector3D>
#include <QVector2D>
#include <QObject>
class SubAbstract: public QObject,
                   public AbstractGLScene{

    Q_OBJECT
    Q_PROPERTY(float angle READ angle WRITE angle)
    public:
        SubAbstract(SceneGLWindow* wnd):
            AbstractGLScene{wnd}, mTexture{nullptr}, mAngle{0}{ initializeCubeData();}
        ~SubAbstract() override{ delete mTexture;}

        void image(QImage aImg){mImg=aImg; if (mInitialized){initialize(); initializeTexture();}}
        QImage image(){return mImg;}

        void angle(float aAngle){mAngle = aAngle; window()->update();}
        float angle(){return mAngle;}

        void paint() override;
        void initialize() override;
    protected:
        void initializeTexture();
    private:
        void initializeCubeData();
        void paintCube();

        struct TexturedPoint{
            QVector3D mCoord;
            QVector2D mUv;
            TexturedPoint(const QVector3D& pcoord, const QVector2D& puv)
               :mCoord {pcoord}, mUv {puv}{}
        };
        QVector<TexturedPoint> mData;

        QOpenGLTexture* mTexture;
        QImage mImg;
        float mAngle;
};

#endif // SUBABSTRACT_H
