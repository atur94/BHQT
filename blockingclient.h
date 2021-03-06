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

#ifndef BLOCKINGCLIENT_H
#define BLOCKINGCLIENT_H

#include <QWidget>
#include <QDialog>
#include "fortunethread.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

using namespace std;
QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QAction;
class QComboBox;
QT_END_NAMESPACE

//! [0]
class BlockingClient : public QWidget
{
    Q_OBJECT

public:
    BlockingClient(QWidget *parent = 0);

private slots:
    void requestNewFortune();
    void showFortune(const QString &fortune);
    void displayError(int socketError, const QString &message);
    void enableGetFortuneButton();
    void whatPlane();
    void drawPlane();
    void fDraw();
    void clr();
    void drawCursors();
    void drawLine();
    void debugMode();
private:

    bool state = false;
    int xc1,yc1,xc2,yc2;
    int xlen, ylen;
    int length;
    QLabel *statusLabel;
    QLabel *surface1Label;
    QLabel *surface2Label;
    QLabel *volume;

    int sum1, sum2, vol;

    QPushButton *getFortuneButton;
    QPushButton *quitButton;
    QPushButton *cursorToggle;
    QPushButton *lineDraw;
    QDialogButtonBox *buttonBox;
    QPushButton *debug;

    std::vector<QGraphicsItem*>rects;
    QRect *display1;
    QGraphicsView *disp1;
    QGraphicsView *disp2;
    QGraphicsScene *scene1;
    QPushButton *drawButton;

    vector<QGraphicsRectItem*>rectangles;
    QComboBox *plane_choose;

    QGraphicsRectItem *rect;
    QGraphicsEllipseItem *cursor1;
    QGraphicsEllipseItem *cursor2;
    QGraphicsLineItem *line1;
    void CursorInit(int x1,int y1,int x2, int y2);
    void RemoveCursors();

    FortuneThread thread;
    QString currentFortune;

};
//! [0]

#endif
