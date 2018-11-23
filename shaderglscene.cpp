#include "shaderglscene.h"

void ShaderGLScene::initialize() {
    AbstractGLScene::initialize();
    mInitialized = true;
    glClearColor(0, 0, 0, 0);

    mShader.addShaderFromSourceCode(QOpenGLShader::Vertex,   fileContent(":/phong.vert"));
    mShader.addShaderFromSourceCode(QOpenGLShader::Fragment, fileContent(":/phong.frag"));
    mShader.link();

    mShader.bind();
    mShader.setAttributeArray("Vertex", GL_FLOAT, mData.constData(), 3, sizeof(ScenePoint));
    mShader.enableAttributeArray("Vertex");

    mShader.setAttributeArray("Normal", GL_FLOAT, &mData[0].normal, 3, sizeof(ScenePoint));
    mShader.enableAttributeArray("Normal");

    mShader.setUniformValue("mat.ka", QVector3D(0.1, 0, 0.0));
    mShader.setUniformValue("mat.kd", QVector3D(0.7, 0.0, 0.0));
    mShader.setUniformValue("mat.ks", QVector3D(1.0, 1.0, 1.0));
    mShader.setUniformValue("mat.shininess", 128.0f);

    mShader.setUniformValue("light.position", QVector3D(2, 1, 1));
    mShader.setUniformValue("light.intensity", QVector3D(1,1,1));
}

void ShaderGLScene::paint(){
    mProjectionMatrix.setToIdentity();
    qreal ratio {qreal(window()->width()) / qreal(window()->height())};
    mProjectionMatrix.perspective(90, ratio, 0.5, 40);//angle, ratio, near plane, far plane

    mViewMatrix.setToIdentity();
    QVector3D eye {0, 0, 2};
    QVector3D center {0, 0, 0};
    QVector3D up {0, 1, 0};
    mViewMatrix.lookAt(eye, center, up);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, window()->width(), window()->height());

    glEnable (GL_DEPTH_TEST);
    glEnable (GL_CULL_FACE);
    glCullFace(GL_BACK);

    mModelMatrix.setToIdentity();
    mModelMatrix.scale(2);
    mModelMatrix.rotate( 40, 0, 1, 0);
    mModelMatrix.rotate(-90, 1, 0, 0);
    QMatrix4x4 modelViewMatrix {mViewMatrix*mModelMatrix};
    paintCube(modelViewMatrix);
}


void ShaderGLScene::paintCube(const QMatrix4x4& mvMatrix){
    mShader.bind();
    mShader.setUniformValue("projectionMatrix", mProjectionMatrix);
    mShader.setUniformValue("modelViewMatrix", mvMatrix);
    mShader.setUniformValue("mvpMatrix", mProjectionMatrix*mvMatrix);
    mShader.setUniformValue("normalMatrix", mvMatrix.normalMatrix());
    const int pointCount{mData.size()};
    glDrawArrays(GL_TRIANGLES, 0, pointCount);
}

QString ShaderGLScene::fileContent(const QString& filePath, const char* codec)
{
        QFile f (filePath);
        if(!f.open(QFile::ReadOnly | QFile::Text)) return QString();
        QTextStream stream (&f);
        if(codec != 0) stream.setCodec(codec);
        return stream.readAll();
}



void ShaderGLScene::initializeCubeData(){
    PLYReader reader{":/monkey.ply"};
    if(reader.read()){
        //reconstruct faces
        const QVector<PLYReader::ScenePoint> vertices {reader.vertices()};
        const QVector<QVector<int>> faces {reader.faces()};
        foreach(QVector<int> face, faces){
            ScenePoint pt;
            for(int idx{0}; idx < face.count(); ++idx){
                int vertexId {face.at(idx)};
                PLYReader::ScenePoint scenePoint = vertices.at(vertexId);
                pt.coords = scenePoint.coord;
                pt.normal = scenePoint.normal;
                mData<<pt;
            }
        }
    }
}
