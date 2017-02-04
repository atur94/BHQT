#ifndef DATAGET_H
#define DATAGET_H
#include <QWidget>
#define SCENE_HEIGHT 250
#define SCENE_WIDTH  250
#include <QWidget>
#include <QGraphicsScene>
#include "defines.h"
class Dataget
{
public:
    Dataget();
    QByteArray var;
    int dataToCompute[400];
    int angles[10000];
    int distances[10000];
    float angle[10000];
    int out[400];
    int yxPOS[ARRAYH][ARRAYW] = {0};
    int convertToAngle(int angles);
    void printOut();
    void setData(QString str);
    void getData(int out[ARRAYH][ARRAYW]);
    void shortData();
    void computeToXY();
    void debugMode();
    void DrawPlane();
    qint16 convertToInt(QChar p4,QChar p3,QChar p2,QChar p1,QChar p0);
    qint16 convert(QChar p);
    void getScene(QGraphicsScene * scene);
    void fillPlane(int plane[ARRAYH][ARRAYW]);
    void copy(int plane[ARRAYH][ARRAYW]);
    void tabClear(int tab[ARRAYH][ARRAYW]);
private:
    QGraphicsScene * scene;

};

#endif // DATAGET_H
