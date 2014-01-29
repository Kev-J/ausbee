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
#include "LidarControl.h"

#include <QMessageBox>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>
#include <iostream>
#include <math.h>

LidarControl::LidarControl(QGraphicsScene *_scene)
:fd(0), scene(_scene), cursor(0), receivingFrame(false)
{
    // Init display
    drawGrid();
    drawObstacles();

    // Dimensions are in meter : 10mx10m max
    scene->setSceneRect(-5.0f,-5.0f,10.0f,10.0f);
    connect(&timerRecv, SIGNAL(timeout()), this, SLOT(receive()));
}

bool LidarControl::openTTY(QString ttyDev)
{
    struct termios options;

    // Open the tty device
    fd = open(ttyDev.toStdString().c_str(), O_RDWR);

    if (fd == -1) {
        QMessageBox::critical(0, "Error", "Unable to open port");
        return false;
    }

    // set 115200 baud
    tcgetattr(fd, &options);
    cfsetispeed(&options, B115200);
    cfsetospeed(&options, B115200);

    if (tcsetattr(fd, TCSANOW, &options) == -1 ) {
        QMessageBox::critical(0, "Error", "Unable to set options");
        return false;
    }

    receivingFrame = false;
    timerRecv.start(1); // Start timer
}

void LidarControl::closeTTY()
{
    // stop the timer
    timerRecv.stop();

    if (fd <= 0)
        return;

    // close device
    close(fd);
    fd = 0;
}

void LidarControl::receive()
{
    int bytes, ret;
    struct pollfd pfd;
    unsigned char buffer[100];

    pfd.fd = fd;
    pfd.events = POLLIN;

    ret = poll(&pfd, 1, 0);

    // If error occurs during polling
    if (ret < 0) {
        QMessageBox::critical(0, "Error", "Unable to read on serial port");
        closeTTY();
    }

    // If datas are available
    if (ret > 0) {

        // Read datas
        bytes = read(fd, &buffer, sizeof(buffer));

        if (bytes < 0) {
            QMessageBox::critical(0, "Error", "Unable to read on serial port");
            closeTTY();
        }

        for (int i = 0 ; i < bytes ; i++) {

            // Check if the start byte is receive
            if ((buffer[i] == 0xFA) && (receivingFrame == false)) {
                receivingFrame = true; // Store each byte after the start byte
                cursor = 0;
            }

            if (receivingFrame) { // Start byte reiceved
                frame[cursor] = buffer[i]; // Copy data

                if (cursor == AUSBEE_LIDAR_PICCOLO_FRAME_LENGTH) { // Receive complete
                    receivingFrame = false;
                    ausbee_lidar_parse_piccolo(frame, data); // Parse data
                    for (int j = 0 ; j < AUSBEE_LIDAR_PICCOLO_DATA_LENGTH ; j++) {
                        if ((!data[j].error) && (!data[j].strengthWarning))  { //If data is valid
                            double x, y;
                            double angleRad;

                            angleRad = data[j].angle * 2 * M_PI / 360.0; // Degree to radian conversion

                            // Get point coordinates
                            x = data[j].distance_mm*cos((float)(angleRad));
                            y = data[j].distance_mm*sin((float)(angleRad));
                            QRectF rect(x/1000,y/1000,0.01,0.01);

                            // Display point
                            if ((int)(data[j].angle) < obstacles.count()) {
                                obstacles[(int)(data[j].angle)]->setRect(rect);
                                obstacles[(int)(data[j].angle)]->setVisible(true);
                            }
                        } else {
                            // Hide point in case of error
                            if (data[j].angle < obstacles.count()) {
                                obstacles[(int)(data[j].angle)]->setVisible(false);
                            }
                        }
                    }
                }
                cursor++;
            }
        }
    }
}

void LidarControl::drawGrid()
{
    for (float f = 2.0f ; f < 10.0 ; f+=2.0f) {
        // Draw some circles
        QRectF rect(-f/2.0f, -f/2.0f, f, f);
        scene->addEllipse(rect, QPen(QColor(255,0,0)));
        scene->addLine(-5.0f, 0.0f, 5.0f, 0.0f, QPen(QColor(255,0,0)));
        scene->addLine(0.0f, -5.0f, 0.0f, 5.0f, QPen(QColor(255,0,0)));

        // Display the distance of each circle
        QString dist;
        dist.setNum(f/2.0, 'f', 1);

        QGraphicsTextItem *text = scene->addText(dist+"m", QFont("Helvetica", 20));
        text->setPos(f/2.0f, 0);
        text->setDefaultTextColor(QColor(255, 0, 0));
        text->setScale(0.01);
        text->setVisible(true);
    }
}

void LidarControl::drawObstacles()
{
    // Init each points
    for (int i = 0 ; i < 360 ; i++) {
        QRectF rect(0,0,0.01, 0.01);
        obstacles.push_back(scene->addEllipse(rect, QPen(QColor(0,255,0)), QBrush(QColor(0,255,0))));
        obstacles[i]->setVisible(false);
    }
}
