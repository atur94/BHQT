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

#include "fortunethread.h"
#include "dataget.h"
#include "datastruct.h"
#include "defines.h"

FortuneThread::FortuneThread(QObject *parent)
    : QThread(parent), quit(false)
{

    disp1 = new QGraphicsView();
    scene1 = new QGraphicsScene();
    dataBuffer = new Dataget();
    s = new dataStruct();
}

//! [0]
FortuneThread::~FortuneThread()
{
    mutex.lock();
    cond.wakeOne();
    mutex.unlock();
    wait();
}
//! [0]

//! [1] //! [2]
void FortuneThread::requestNewFortune()
{
//! [1]
    QMutexLocker locker(&mutex);


    this->hostName = "192.168.1.110";
    this->port = 5000;
//! [3]

    if (!isRunning())
        start();
    else
        cond.wakeOne();

}
//! [2] //! [3]

//! [4]
void FortuneThread::run()
{
    mutex.lock();
//! [4] //! [5]
    QString serverName = hostName;
    quint16 serverPort = port;

//! [5]
    QTcpSocket socket;
    gSocket = &socket;
    qint64 length;
    int xyPOS[ARRAYH][ARRAYW] = {0};
    mutex.unlock();
//! [6]
    while (1) {
        const int Timeout = 1 * 1000;


        socket.connectToHost(serverName, serverPort);
        if (!socket.waitForConnected(Timeout)) {
            emit error(socket.error(), socket.errorString());
            return;
        }
        QDataStream in(&socket);
        in.setVersion(QDataStream::Qt_4_0);
        QString fortune;


        QString string;

        do {
            if (!socket.waitForReadyRead(Timeout)) {
                dataBuffer->printOut();
                qDebug() << "END PRINT";
                dataBuffer->computeToXY();
                qDebug() << "END COMPUTE";
                dataBuffer->getData(s->data);
                qDebug() << "END GETDATA";
                dataBuffer->fillPlane(s->data);
                emit draw();
                dataBuffer->tabClear(dataBuffer->yxPOS);
                emit error(socket.error(), socket.errorString());
                return;
            }
            in.startTransaction();
            in >> fortune;
            in >> length;
            string = socket.readLine();          
            dataBuffer->setData(string);
        } while (1);

        mutex.lock();
        emit newFortune(fortune);

        cond.wait(&mutex);
        serverName = hostName;
        serverPort = port;
        mutex.unlock();

    }
//! [15]
}

void FortuneThread::readTcpData(){

}



void FortuneThread::startScan(){
    sendFlag = true;
    w++;
}

void FortuneThread::plane1(){
    plane = 1;
    qDebug() << plane;
}
void FortuneThread::plane2(){
    plane = 2;
    qDebug() << plane;
}
void FortuneThread::getData(int out[250][250]){
    for(int j = 0; j < 250; j++){
        for (int k = 0; k < 250; k++){
            out[j][k] = s->data[j][k];

         }

    }

}

void FortuneThread::getScene(QGraphicsScene *scene){
    this->scene1 = scene;
}

void FortuneThread::DrawPlane(int xyPOS[ARRAYH][ARRAYW]){
    qDebug() << "ENTERING DRAW FUNCTION";
    for(int i = 0; i < ARRAYH; i++){
        for(int j = 0; j < ARRAYW; j++){
            if(xyPOS[i][j] == 1 ) {
                scene1->addRect(i,j,1,1);
            }else {
                scene1->addRect(i,j,0,0);
            }
        }
    }
    emit clrSig();
}

void FortuneThread::clearTab(){
    for(int j = 0; j < ARRAYH; j++){
        for (int k = 0; k < ARRAYW; k++){
            s->data[j][k] = 0;

         }

    }
}
