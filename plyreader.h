#ifndef PLYREADER_H
#define PLYREADER_H

#include <QObject>
#include <QVector3D>
#include <QTextStream>
#include <QVector>
#include <QIODevice>
#include <QFile>

class PLYReader : public QObject{
 public:
    struct ScenePoint{
        QVector3D coord;
        QVector3D normal;
    };



    explicit PLYReader(const QString&);
    explicit PLYReader(QIODevice*);
    inline QIODevice* device() const { return mDevice;}
    bool read();

    inline const QVector<ScenePoint> vertices() const {return mVertices;}
    inline const QVector<QVector<int>> faces() const {return mFaces;}

 protected:
    void readVertices(QTextStream&, int);
    void readFaces(QTextStream&, int);
    ScenePoint readVertex (QTextStream&);
    QVector<int> readFace (QTextStream&);

 private:
    QIODevice* mDevice;
    QVector<ScenePoint> mVertices;
    QVector<QVector<int>> mFaces;
signals:

public slots:
};

#endif // PLYREADER_H
