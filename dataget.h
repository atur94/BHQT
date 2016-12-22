#ifndef DATAGET_H
#define DATAGET_H
#include <QWidget>
#define SCENE_HEIGHT 250
#define SCENE_WIDTH  250
#include <QWidget>
#include <QGraphicsScene>
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
    int yxPOS[250][250] = {0};
    int convertToAngle(int angles);
    void printOut();
    void setData(QString str);
    void getData(int out[250][250]);
    void shortData();
    void computeToXY();
    void DrawPlane();
    qint16 convertToInt(QChar p4,QChar p3,QChar p2,QChar p1,QChar p0);
    qint16 convert(QChar p);
    void getScene(QGraphicsScene * scene);
    void fillPlane(int plane[250][250]);
    void copy(int plane[250][250]);
    void tabClear(int tab[250][250]);
private:
    QGraphicsScene * scene;

};

#endif // DATAGET_H
