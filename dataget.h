#ifndef DATAGET_H
#define DATAGET_H
#include <QWidget>
#define SCENE_HEIGHT 250
#define SCENE_WIDTH  250
#include <QWidget>
#include <QGraphicsScene>
#include "defines.h"

typedef struct {
    int x = 0;
    int y = 0;

}points;

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

    void drawPoint(int tab[ARRAYH][ARRAYW], int x, int y);
    points setHistoryPoint(points &cords);
    void drawLine(int tab[ARRAYH][ARRAYW], const int x1, int y1, const int x2, const int y2);
    points randomPoints(int tab[ARRAYH][ARRAYW], int width, int height);
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
