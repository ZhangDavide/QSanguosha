/********************************************************************
    Copyright (c) 2013-2014 - QSanguosha-Rara

    This file is part of QSanguosha-Hegemony.

    This game is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation; either version 3.0
    of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.

    See the LICENSE file for more details.

    QSanguosha-Rara
    *********************************************************************/

#ifndef _RECORDER_H
#define _RECORDER_H

#include <QObject>
#include <QTime>
#include <QThread>
#include <QMutex>
#include <QSemaphore>
#include <QImage>
#include <QMap>

class Recorder : public QObject {
    Q_OBJECT

public:
    explicit Recorder(QObject *parent);
    bool save(const QString &filename) const;
    QList<QByteArray> getRecords() const;

public slots:
    void recordLine(const QByteArray &line);

private:
    QTime watch;
    QByteArray data;
};

class Replayer : public QThread {
    Q_OBJECT

public:
    explicit Replayer(const QString &filename, QObject *parent);

    int getDuration() const { return duration / 1000; }
    qreal getSpeed();

    QString getPath() const;

public slots:
    void uniform();
    void toggle();
    void speedUp();
    void slowDown();

protected:
    virtual void run();

private:
    QString filename;
    qreal speed;
    bool playing;
    QMutex mutex;
    QSemaphore play_sem;
    int duration;
    int pair_offset;

    struct Pair {
        int elapsed;
        QByteArray cmd;
    };
    QList<Pair> pairs;

signals:
    void command_parsed(const QByteArray &cmd);
    void elasped(int secs);
    void speed_changed(qreal speed);
};

#endif

