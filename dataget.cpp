#include "dataget.h"
#include "QWidget"
#include <string.h>
#include "QtWidgets"
#include <QQueue>

Dataget::Dataget()
{
    scene = new QGraphicsScene();
    for(int i = 0; i < ARRAYW; i++){
        for(int j = 0; j < ARRAYH; j++){
            yxPOS[1][j] = 0;
        }
    }

}

void Dataget::setData(QString str){
    int i = 0;
    if(str[0] == 'A'){

        angles[i] = convertToInt(str[2],str[3],str[4],str[5],str[6]);
        distances[i] = convertToInt(str[9],str[10],str[11],str[12],str[13]);
        angles[i] = convertToAngle(angles[i]);

        dataToCompute[angles[i]]=distances[i];
        qDebug() << angles[i] << distances[i] << dataToCompute[angles[i]];

        i++;

    }
}


qint16 Dataget::convertToInt(QChar p4,QChar p3,QChar p2,QChar p1,QChar p0){

    return convert(p0)+convert(p1)*10+convert(p2)*100+convert(p3)*1000+convert(p4)*10000;
}

int Dataget::convertToAngle(int angles){
    //6540 - 720 stopni
    //3245 - 360
    //  x  - 1
    int degrees720 = 6540;

    if(angles<= degrees720/2){
        return angles = qRound(float(angles) /(3245/360)); // Obecny kąt
    }
    if(angles>degrees720/2){
        return angles = 360 - qRound(float(angles-3245) /(3245/360)); // Obecny kąt
    }
    return 0;
}

qint16 Dataget::convert(QChar p){
    if(p == '0') return 0;
    if(p == '1') return 1;
    if(p == '2') return 2;
    if(p == '3') return 3;
    if(p == '4') return 4;
    if(p == '5') return 5;
    if(p == '6') return 6;
    if(p == '7') return 7;
    if(p == '8') return 8;
    if(p == '9') return 9;
    return 0;

}
void Dataget::shortData(){
    for(int i = 0; i < sizeof(angles); i++){
        if(angles[i]!=angles[i++]){
            if(dataToCompute[angles[i]] == 0){
                dataToCompute[angles[i]] = distances[i];
            }

            else if(dataToCompute[angles[i]]!=0){
                dataToCompute[angles[i]] = (dataToCompute[angles[i]]+distances[i])/2;
            }
        }

    }
    for(int i = 0; i <361; i++){
        qDebug() << i <<  dataToCompute[angles[i]];
    }
}
void Dataget::printOut(){
    for(int i = 0; i < 360; i++){
        qDebug() << i << dataToCompute[i];
    }
}
void Dataget::getData(int out[ARRAYH][ARRAYW]){

    for(int i = 0; i < ARRAYH; i++){
        for (int j = 0; j < ARRAYW; j++){
            out[i][j] = yxPOS[i][j];
         }

    }
}
void Dataget::drawPoint(int tab[ARRAYH][ARRAYW], int x, int y)
{
    tab[x][y] = 1;
}

points Dataget::setHistoryPoint(points &cords)
{
    return cords;
}

void Dataget::drawLine(int tab[ARRAYH][ARRAYW], const int x1, int y1, const int x2, const int y2) {
    // zmienne pomocnicze
    int d, dx, dy, ai, bi, xi, yi;
    int x = x1, y = y1;
    // ustalenie kierunku rysowania
    if (x1 < x2)
    {
        xi = 1;
        dx = x2 - x1;
    }
    else
    {
        xi = -1;
        dx = x1 - x2;
    }
    // ustalenie kierunku rysowania
    if (y1 < y2)
    {
        yi = 1;
        dy = y2 - y1;
    }
    else
    {
        yi = -1;
        dy = y1 - y2;
    }
    // pierwszy piksel
    drawPoint(tab, x, y);
    // oś wiodąca OX
    if (dx > dy)
    {
        ai = (dy - dx) * 2;
        bi = dy * 2;
        d = bi - dx;
        // pętla po kolejnych x
        while (x != x2)
        {
            // test współczynnika
            if (d >= 0)
            {
                x += xi;
                y += yi;
                d += ai;
            }
            else
            {
                d += bi;
                x += xi;
            }
            drawPoint(tab, x, y);
        }
    }
    // oś wiodąca OY
    else
    {
        ai = (dx - dy) * 2;
        bi = dx * 2;
        d = bi - dy;
        // pętla po kolejnych y
        while (y != y2)
        {
            // test współczynnika
            if (d >= 0)
            {
                x += xi;
                y += yi;
                d += ai;
            }
            else
            {
                d += bi;
                y += yi;
            }
            drawPoint(tab, x, y);
        }
    }
}

void Dataget::computeToXY(){
    points cords;
    points cordsLast;
    points cordsFirst;
    for(int angle = 0; angle < 360; angle++){

        cords.x = qCos(qDegreesToRadians(float(angle)))*dataToCompute[angle]+125;
        cords.y = qSin(qDegreesToRadians(float(angle)))*dataToCompute[angle]+125;
        if( angle == 0 ){
            cordsLast = cords;
            cordsFirst = cords;
        }
        drawLine(yxPOS, cords.x, cords.y, cordsLast.x, cordsLast.y);
        cordsLast = setHistoryPoint(cords);

    }
}

points Dataget::randomPoints(int tab[ARRAYH][ARRAYW], int width, int height) {
    points cords;
    cords.x = rand() % width;
    cords.y = rand() % height;
    tab[cords.x][cords.y] = 1;
    return cords;
}

void Dataget::debugMode()
{
    points cords[6];
    cords[0].x = 50;
    cords[0].y = 50;
    cords[1].x = 200;
    cords[1].y = 30;
    cords[2].x = 220;
    cords[2].y = 125;
    cords[3].x = 160;
    cords[3].y = 220;
    cords[4].x = 50;
    cords[4].y = 200;
    cords[5].x = 100;
    cords[5].y = 125;
    yxPOS[cords[0].x][cords[0].y] = 1;
    yxPOS[cords[1].x][cords[1].y] = 1;
    yxPOS[cords[2].x][cords[2].y] = 1;
    yxPOS[cords[3].x][cords[3].y] = 1;
    yxPOS[cords[4].x][cords[4].y] = 1;
    yxPOS[cords[5].x][cords[5].y] = 1;
    points Ncords, cordsLast, cordsFirst;
    for(int i = 0; i < 6; i++){
        Ncords = cords[i];
        if( i == 0 ){
            cordsLast = Ncords;
            cordsFirst = Ncords;
        }
        drawLine(yxPOS, Ncords.x, Ncords.y, cordsLast.x, cordsLast.y);
        cordsLast = setHistoryPoint(Ncords);
    }
        drawLine(yxPOS, cordsLast.x, cordsLast.y, cordsFirst.x, cordsFirst.y);
}

void Dataget::getScene(QGraphicsScene * scene){
    this->scene = scene;
    this->scene->addRect(125,125,1,1);
}

void Dataget::DrawPlane(){
    qDebug() << "ENTERING DRAW FUNCTION";
    for(int i = 0; i < 250; i++){
        for(int j = 0; j < 250; j++){
            if(yxPOS[i][j] == 1 ) {
                scene->addRect(i,j,1,1);
            }else {
                scene->addRect(i,j,0,0);
            }
        }
    }
}

void Dataget::setPoint(int tab[ARRAYH][ARRAYW], points cords)
{
    int x = cords.x;
    int y = cords.y;

    tab[x][y] = 1;
}

int Dataget::getPoint(int tab[ARRAYH][ARRAYW], points cords){
    int x = cords.x;
    int y = cords.y;
    if(tab[x][y] == 1) return 1;
    else return 0;

}

points Dataget::newPos(points cords, direction dir){
    if(dir == CLeft){
        cords.x--;
        return cords;
    }
    else if(dir == CUp){
        cords.y++;
        return cords;
    }
    else if(dir == CRight){
        cords.x++;
        return cords;
    }
    else if(dir == CDown){
        cords.y--;
        return cords;
    }
    qDebug() << "newPos. SOmething Went wrong";

}

void Dataget::fillPlane(int plane[ARRAYH][ARRAYW]){
    //ALGORYTM FLOOD-FILL Z WYKORZYSTANIEM KOLEJKI
    points cords, cordsNew;

    //USTALENIE WARTOŚCI POCZĄTKOWEJ DLA WYPEŁNIENIA
    cords.x = 125;
    cords.y = 125;
    QQueue<points> queue;
    queue.enqueue(cords);
    while(!queue.isEmpty()){
        qDebug() << "QUEUE ISNT EMPTY";
        cordsNew = queue.dequeue();
        if(getPoint(plane,cordsNew) == 0){
            setPoint(plane, cordsNew);
            queue.enqueue(newPos(cordsNew, CLeft));
            queue.enqueue(newPos(cordsNew, CRight));
            queue.enqueue(newPos(cordsNew, CDown));
            queue.enqueue(newPos(cordsNew, CUp));
        }
    }
}
void Dataget::tabClear(int tab[ARRAYH][ARRAYW]){
    for(int i = 0; i < ARRAYH; i++)
        for(int j = 0; j < ARRAYW; j++)
            tab[i][j] = 0;
}
