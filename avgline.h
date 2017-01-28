#ifndef AVGLINE_H
#define AVGLINE_H

#include <QObject>
#include <QGraphicsScene>
#include <vector>
class AvgLine : public QObject
{
    Q_OBJECT
private:
    QGraphicsScene *scene;
public:
    explicit AvgLine(QObject *parent = 0);
    void getScene(QGraphicsScene *scene);
signals:

public slots:
};

#endif // AVGLINE_H
