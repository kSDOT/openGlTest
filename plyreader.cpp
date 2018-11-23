#include "plyreader.h"

PLYReader::PLYReader(const QString& fileName) : mDevice { new QFile(fileName, this)}
 {  mDevice->open(QIODevice::ReadOnly | QIODevice::Text);}

PLYReader::PLYReader(QIODevice* device):mDevice{device}{}

bool PLYReader::read(){
    mVertices.clear();
    mFaces.clear();
    QTextStream stream(device());
    QString line {stream.readLine()};
    if(line!= "ply") return false;
    line = stream.readLine();
    int vertexCount{0}, faceCount{0};

    for(;line!="end_header";line = stream.readLine())
        if(line.startsWith("element")){
            QStringList args {line.split(QRegExp{"\\s+"})};
            if(args.count() < 3) break;
            if(args.at(1) == "vertex")
                vertexCount = args.at(2).toInt();
            else if( args.at(1) == "face")
                faceCount = args.at(2).toInt();
        }

    readVertices(stream, vertexCount);
    readFaces   (stream, faceCount);
    return true;

}

void PLYReader::readVertices(QTextStream& stream, int vertexCount){
    mVertices.reserve(vertexCount);
    for(int i{0}; i<vertexCount; ++i)
        mVertices<<readVertex(stream);
}

void PLYReader::readFaces(QTextStream& stream, int faceCount){
    mFaces.reserve(faceCount);
    for(int i{0}; i<faceCount; ++i)
        mFaces<<readFace(stream);
}

PLYReader::ScenePoint PLYReader::readVertex(QTextStream& stream){
    ScenePoint pt;
    float xpos, ypos, zpos;
    float nx, ny, nz;
    stream >> xpos >> ypos >> zpos >> nx >> ny >> nz;
    pt.coord  = QVector3D(xpos, ypos, zpos);
    pt.normal = QVector3D(nx, ny, nz);
    return pt;
}

QVector<int> PLYReader::readFace(QTextStream& stream){
    int cnt{}, pt{};
    stream>>cnt;
    QVector<int> face;
    face.reserve(cnt);
    for(int v{0}; v<cnt; ++v){
        stream>>pt;
        face<<pt;
    }
    return face;
}

