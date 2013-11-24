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
#ifndef LIDAR_CONTROL_H
#define LIDAR_CONTROL_H

#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QTimer>
#include <AUSBEE/piccolo-lidar.h>
#include <QApplication>

class LidarControl : public QObject {
    Q_OBJECT;
    public:
        LidarControl(QGraphicsScene *_scene);
        bool openTTY(QString ttyDev);
        void closeTTY(void);
    public slots:
        void receive(void);
    private:
        void drawGrid(void);
        void drawObstacles(void);
        void clearScene(void);
    private:
        int fd;
        QGraphicsScene *scene;
        QTimer timerRecv;
        bool receivingFrame;
        int cursor;
        struct AUSBEE::Lidar::data data[4];//XXX
        unsigned char frame[AUSBEE::PiccoloLidar::FRAME_LENGTH];
        AUSBEE::PiccoloLidar lidar;
        QList<QGraphicsEllipseItem*> obstacles;
};

#endif
