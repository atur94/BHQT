#include "avgline.h"

AvgLine::AvgLine(QObject *parent) : QObject(parent)
{

}

void AvgLine::getScene(QGraphicsScene *scene)
{
    this->scene = scene;
}

