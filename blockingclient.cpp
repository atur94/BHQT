/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>
#include <QtNetwork>

#include "blockingclient.h"
#include <QGraphicsView>
#include <QGraphicsSceneMoveEvent>

static int drawXY0[ARRAYH][ARRAYW] = {0};
static int drawXY1[ARRAYH][ARRAYW] = {0};

BlockingClient::BlockingClient(QWidget *parent)
    : QWidget(parent)
    , scene1(new QGraphicsScene())

{

    // KONFIGURACJA
    disp1 = new QGraphicsView(parent);
    disp1->setGeometry(QRect(300, 30, 300, 300));
    disp1->setMaximumSize(QSize(300, 300));

    statusLabel = new QLabel(tr(""));
    statusLabel->setWordWrap(true);

    surface1Label = new QLabel(tr("PLANE: "));
    surface2Label = new QLabel(tr("SECTION: "));
    volume = new QLabel(tr("DVOLUME: "));

    plane_choose = new QComboBox(parent);

    plane_choose->addItem("Plane 1", QVariant(1));
    plane_choose->addItem("Plane 2", QVariant(2));

    getFortuneButton = new QPushButton(tr("Connect/Scan"));
    getFortuneButton->setDefault(true);
    getFortuneButton->setEnabled(true);

    quitButton = new QPushButton(tr("Quit"));
    drawButton = new QPushButton(tr("Draw"));
    cursorToggle = new QPushButton(tr("Toggle Cursors"));
    lineDraw = new QPushButton(tr("Line"));
    debug = new QPushButton(tr("Debug"));

    buttonBox = new QDialogButtonBox;
    buttonBox->addButton(getFortuneButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);
    buttonBox->addButton(drawButton,  QDialogButtonBox::ActionRole);
    buttonBox->addButton(cursorToggle,  QDialogButtonBox::ActionRole);
    buttonBox->addButton(lineDraw, QDialogButtonBox::ActionRole);
    //DEBUG MODE.
   // buttonBox->addButton(debug, QDialogButtonBox::ActionRole);

    connect(getFortuneButton, SIGNAL(clicked()), this, SLOT(requestNewFortune()));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(plane_choose, SIGNAL(activated(int)), this, SLOT(whatPlane()));
    connect(drawButton, SIGNAL(clicked()), this, SLOT(drawPlane()));
    connect(cursorToggle, SIGNAL(clicked()), this, SLOT(drawCursors()));
    connect(lineDraw, SIGNAL(clicked()), this, SLOT(drawLine()));
    //DEBUG MODE
   // connect(debug, SIGNAL(clicked()), this, SLOT(debugMode()));

    connect(&thread, SIGNAL(newFortune(QString)),
            this, SLOT(showFortune(QString)));

    connect(&thread, SIGNAL(error(int,QString)),
            this, SLOT(displayError(int,QString)));
    connect(&thread, SIGNAL(draw()), this, SLOT(fDraw()));
    connect(&thread, SIGNAL(clrSig()),this, SLOT(clr()));


    QGridLayout *mainLayout = new QGridLayout;

    mainLayout->addWidget(buttonBox, 1, 1, 20, 20, Qt::AlignBottom|Qt::AlignCenter);

    this->disp1->setScene(scene1);
    disp1->setGeometry(0,0,250,250);
    mainLayout->addWidget(disp1, 0, 0, 0 , 0, Qt::AlignTop|Qt::AlignLeft);
    scene1->addRect(0,0, 250,250);

    thread.getScene(scene1);
    mainLayout->addWidget(plane_choose,0,18,Qt::AlignTop|Qt::AlignRight);
    mainLayout->addWidget(surface1Label,1,18);
    mainLayout->addWidget(surface2Label,2,18);
    mainLayout->addWidget(volume,3,18);
    setLayout(mainLayout);
    qDebug() << plane_choose->currentIndex();
    setWindowTitle(tr("Scanner"));
//    portLineEdit->setFocus();

}

//! [2]
void BlockingClient::requestNewFortune()
{
    getFortuneButton->setEnabled(false);
    drawButton->setEnabled(false);
    thread.requestNewFortune();
}
//! [2]

//! [3]
void BlockingClient::showFortune(const QString &nextFortune)
{
    if (nextFortune == currentFortune) {
        requestNewFortune();
        return;
    }

    currentFortune = nextFortune;
    statusLabel->setText(currentFortune);
    getFortuneButton->setEnabled(true);
    drawButton->setEnabled(true);
}


void BlockingClient::displayError(int socketError, const QString &message)
{
    switch (socketError) {
    case 1:
    default:
        QMessageBox::information(this, tr("Scanning complete"),
                                 tr("Change position of motor to scan another plane")
                                 .arg(message));
    }

    getFortuneButton->setEnabled(true);
    drawButton->setEnabled(true);
}

void BlockingClient::enableGetFortuneButton()
{
//    bool enable(!hostLineEdit->text().isEmpty() && !portLineEdit->text().isEmpty());
    getFortuneButton->setEnabled(true);
    drawButton->setEnabled(true);
}

void BlockingClient::whatPlane(){
    qDebug() << plane_choose->currentIndex();

}
void BlockingClient::drawPlane(){
    //FUNKCJA WYWOLYWANA PO ODEBRANIU WSZYSTKICH DANYCH LUB PO KLIKNIECIU PRZYCISKU DRAW
    QList<QGraphicsItem*> allGraphicsItems = scene1->items();

    allGraphicsItems.clear();
    scene1->clear();

    scene1->update(0,0,250,250);

    switch(plane_choose->currentIndex()){
    case 0:
        qDebug() << "PLANE 1 CHOOSEN";
        thread.DrawPlane(drawXY0);
        break;
    case 1:
        qDebug() << "PLANE 2 CHOOSEN";
        thread.DrawPlane(drawXY1);

        break;
    case 3:
        //DEBUG
        for(int i = 0; i < 250; i++)
           for(int j = 125; j > 50; j--)
               scene1->addRect(i,j,1,1);
        break;
    default:
        qDebug() <<"Błąd "<< plane_choose->currentIndex();
    }

}
void BlockingClient::fDraw(){
//    for(int i = 0; i < 250; i++){
//        for(int j = 0; j < 250; j++){
//            scene1->addRect(i,j,0,0);
//        }
//    }

    if(plane_choose->currentIndex() == 0){
        scene1->clear();
        scene1->update(0,0,250,250);

        thread.getData(drawXY0);
        sum1 = thread.getPoints(drawXY0);
        qDebug() << "AREA1: " << sum1 << endl;
        thread.DrawPlane(drawXY0);
    }else{

        scene1->clear();
        scene1->update(0,0,250,250);
        thread.getData(drawXY1);
        sum2 = thread.getPoints(drawXY1);
        qDebug() << "AREA2: " << sum2 << endl;
        thread.DrawPlane(drawXY1);

    }
}
void BlockingClient::clr(){
    thread.clearTab();
}

void BlockingClient::drawCursors()
{
    state = !state;
    if(!state){
        RemoveCursors();
    }else {
        CursorInit(0, 0, 0, 0);
    }
}

void BlockingClient::drawLine()
{
    QLineF line;
    if(!state){
    }else {
        xc1 = cursor1->pos().x()+5;
        yc1 = cursor1->pos().y()+5;
        xc2 = cursor2->pos().x()+5;
        yc2 = cursor2->pos().y()+5;
        line.setLine(xc1,yc1,xc2,yc2);
        line1->setLine(line);

        if(xc1 >= xc2){
            xlen = xc1 - xc2;
        }else{
            xlen = xc2 - xc1;
        }
        if(yc1 >= yc2){
            ylen = yc1 - yc2;
        }else{
            ylen = yc2 - yc1;
        }
        length = qSqrt(xlen * xlen + ylen * ylen);

        if(sum2 == 0){
            vol = sum1;
        }else {
            vol = sum1 * sum2/length;
        }
        QString label;
        label = "PLANE: "+ QString::number(sum1) +" cm^2";
        surface1Label->setText(label);
        label = "SECTION: "+ QString::number(sum2) + " cm^2";
        surface2Label->setText(label);
        label = "DVOLUME: "+ QString::number(vol)+ " cm^3";
        volume->setText(label);

        qDebug() << xc1 << yc1 << xc2 << yc2<<"LENGTH: "<< length << "VOL:"<< vol <<"SUM1:" << sum1;

    }
}

void BlockingClient::debugMode()
{
    qDebug() << "DebugMode" << endl;
    thread.debugMode();
}

void BlockingClient::CursorInit(int x1,int y1,int x2, int y2)
{

    QPen red(Qt::red);
    QPen black(Qt::black);
    black.setWidth(1);
    cursor1 = scene1->addEllipse(x1, y1, 10, 10, red);
    cursor2 = scene1->addEllipse(x2, y2, 10, 10, black);
    cursor1->setFlag(QGraphicsItem::ItemIsMovable);
    cursor2->setFlag(QGraphicsItem::ItemIsMovable);
    line1 = scene1->addLine(x1,y1,x2,y2, red);
    //WYEMITOWAĆ SYGNAŁ
    //RYSOWAĆ LINIE
}

void BlockingClient::RemoveCursors()
{
    delete cursor1;
    delete cursor2;
}


