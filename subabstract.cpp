#include "subabstract.h"


void SubAbstract::initializeTexture(){
    mTexture = new QOpenGLTexture{mImg.mirrored()};
    mTexture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    mTexture->setMagnificationFilter(QOpenGLTexture::Linear);
    }

void SubAbstract::paintCube(){
   if(mTexture)
       mTexture->bind();
   glEnable(GL_TEXTURE_2D);
   glBegin(GL_QUADS);
        for(int i {0}; i<mData.size(); ++i){
            const TexturedPoint& pt {mData.at(i)};
            glTexCoord2d(pt.mUv.x(), pt.mUv.y());
            glVertex3f(pt.mCoord.x(), pt.mCoord.y(), pt.mCoord.z());
        }
   glEnd();
   glDisable(GL_TEXTURE_2D);
}

void SubAbstract::initialize(){
    AbstractGLScene::initialize();
    mInitialized = true;
    if(!mImg.isNull())
        initializeTexture();
    glClearColor(1, 1, 1, 1);
    glShadeModel (GL_SMOOTH);

}

void SubAbstract::paint(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, window()->width(), window()->height());
    glLoadIdentity();

    glRotatef(mAngle, 1.0, 0.0, 0.0);
    glRotatef(45, 0.0, 1.0, 0.0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    paintCube();
}

void SubAbstract::initializeCubeData(){

    mData = {
            // FRONT FACE
            {{-0.5, -0.5, 0.5}, {0, 0}}, {{ 0.5, -0.5, 0.5}, {1, 0}},
            {{ 0.5, 0.5, 0.5}, {1, 1}}, {{-0.5, 0.5, 0.5}, {0, 1}},
            // TOP FACE
            {{-0.5, 0.5, 0.5}, {0, 0}}, {{ 0.5, 0.5, 0.5}, {1, 0}},
            {{ 0.5, 0.5, -0.5}, {1, 1}}, {{-0.5, 0.5, -0.5}, {0, 1}},
            // BACK FACE
            {{-0.5, 0.5, -0.5}, {0, 0}}, {{ 0.5, 0.5, -0.5}, {1, 0}},
            {{ 0.5, -0.5, -0.5}, {1, 1}}, {{-0.5, -0.5, -0.5}, {0, 1}},
            // BOTTOM FACE
            {{-0.5, -0.5, -0.5}, {0, 0}}, {{ 0.5, -0.5, -0.5}, {1, 0}},
            {{ 0.5, -0.5, 0.5}, {1, 1}}, {{-0.5, -0.5, 0.5}, {0, 1}},
            // LEFT FACE
            {{-0.5, -0.5, -0.5}, {0, 0}}, {{-0.5, -0.5, 0.5}, {1, 0}},
            {{-0.5, 0.5, 0.5}, {1, 1}}, {{-0.5, 0.5, -0.5}, {0, 1}},
            // RIGHT FACE
            {{ 0.5, -0.5, 0.5}, {0, 0}}, {{ 0.5, -0.5, -0.5}, {1, 0}},
            {{ 0.5, 0.5, -0.5}, {1, 1}}, {{ 0.5, 0.5, 0.5}, {0, 1}},
            };
}
