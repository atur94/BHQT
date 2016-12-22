#include "dataget.h"
#include "QWidget"
#include <string.h>
#include "QtWidgets"

Dataget::Dataget()
{
    scene = new QGraphicsScene();
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
    //6490 - 720 stopni
    //3245 - 360
    //  x  - 1


    if(angles<=3245){
        return angles = qRound(float(angles) /(3245/360)); // Obecny kąt
    }
    if(angles>3245){
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
void Dataget::getData(int out[250][250]){

    for(int i = 0; i < 250; i++){
        for (int j = 0; j < 250; j++){
            out[i][j] = yxPOS[i][j];
         }

    }
}
void Dataget::computeToXY(){
    float x,y;


    for(int angle = 0; angle < 360; angle++){
        x = qCos(qDegreesToRadians(float(angle)))*dataToCompute[angle];
        y = qSin(qDegreesToRadians(float(angle)))*dataToCompute[angle];
        x = qRound(x);
        y = qRound(y);
        yxPOS[int(x+125)][int(y+125)] = 1;
        yxPOS[int(x+125)][int(1+y+125)] = 1;
//        yxPOS[int(x+125)][int(2+y+125)] = 1;
        yxPOS[int(1+x+125)][int(y+125)] = 1;
        yxPOS[int(1+x+125)][int(1+y+125)] = 1;
//        yxPOS[int(1+x+125)][int(2+y+125)] = 1;
//        yxPOS[int(2+x+125)][int(y+125)] = 1;
//        yxPOS[int(2+x+125)][int(1+y+125)] = 1;
//        yxPOS[int(2+x+125)][int(2+y+125)] = 1;



    }
    for(int i = 0; i < 250; i++){
        for (int j = 0; j < 250; j++){
            printf("%d", yxPOS[i][j]);

         }
        printf("\n");
    }
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


void Dataget::fillPlane(int plane[250][250]){
    int copy[250][250];
    int start = 0;
    for(int q = 0; q < 250; q++) {
        for(int w = 0; w < 250; w++){
            copy[q][w] = plane[q][w];           //Tablica pomocnicza ktora pomaga w porownywaniu pikseli bez jej nadpisywania
        }
    }
    for(int i = 0; i < 250; i++) {
        if((start == 0) && 125>i){
            if((plane[i][125])||(plane[i][124])||(plane[i][123])||(plane[i][126])||(plane[i][127])) //Sprawdzanie początku i ustawienie punktu startowego
                start = !start;
        }
        if((start == 1) && 125<=i ){
            if((plane[i+1][125])||(plane[i+1][124])||(plane[i+1][126])) // od polowy sprawdzanie końca
                start = 0;
        }

        if(start == 1){
            for(int j = 126; j < 250; j++){
                if((copy[i][j] == 1)||(copy[i+3][j] == 1)||(copy[i-3][j] == 1)||(copy[i-1][j] == 1)||(copy[i+1][j] == 1)||(copy[i+2][j] == 1)||(copy[i-2][j] == 1)){
                    break;
                }
                plane[i][j] = 1;
            }
            for(int j = 125; j > 0; j--){
                if((copy[i][j] == 1)||(copy[i+3][j] == 1)||(copy[i-3][j] == 1)||(copy[i-1][j] == 1)||(copy[i+1][j] == 1)||(copy[i+2][j] == 1)||(copy[i-2][j] == 1)){
                    break;
                }
                plane[i][j] = 1;
            }
        }
    }
    start = 0;
}
void Dataget::tabClear(int tab[250][250]){
    for(int i = 0; i < 250; i++)
        for(int j = 0; j < 250; j++)
            tab[i][j] = 0;
}
