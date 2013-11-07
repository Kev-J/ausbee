/**********************************************************************
 * This file is part of LIBAUSBEE.
 * 
 * LIBAUSBEE is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * LIBAUSBEE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with LIBAUSBEE.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright 2013 (C) EIRBOT
 *
 * Authors :    Kevin JOLY <joly.kevin25@gmail.com>
 *
 **********************************************************************/
#include "MainWindow.h"

#include <QGridLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
:QWidget(parent)
{
    scene = new QGraphicsScene;

    // Init the lidar control with the QGraphicsScene to draw on
    lidarCtrl = new LidarControl(scene);

    view = new QGraphicsView(scene);
    view->setFixedSize(640, 640);
    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    
    view->setBackgroundBrush(QColor(0,0,0));

    connectBtn = new QPushButton("Connect");
    connectBtn->setCheckable(true);

    connect(connectBtn, SIGNAL(clicked(bool)), this, SLOT(connectLidar(bool)));

    // TTY path of the device connected to the lidar
    ttyDev = new QLineEdit("/dev/ttyUSB0");

    QGridLayout *mainLayout = new QGridLayout;

    mainLayout->addWidget(new QLabel("TTY device:"),0,0);
    mainLayout->addWidget(ttyDev,0,1);
    mainLayout->addWidget(connectBtn,0,2);
    mainLayout->addWidget(view,1,0,1,3);

    this->setLayout(mainLayout);
}

void MainWindow::connectLidar(bool connect)
{
    if (connect) {
        if (lidarCtrl->openTTY(ttyDev->text())) {
            ttyDev->setEnabled(false);
        } else {
            connectBtn->setChecked(false);
        }
    } else {
        lidarCtrl->closeTTY();
        ttyDev->setEnabled(true);
    }
}
