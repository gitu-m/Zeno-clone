#include <QtWidgets>
#include <QElapsedTimer>
#include <QDebug>

#include "DigitalClock.h"

// QTime time0;
QElapsedTimer timer;

DigitalClock::DigitalClock(QWidget *parent)
    : QLCDNumber(parent)
{
    setSegmentStyle(Filled);
    // time0 = QTime::currentTime();
    timer.start();
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start(1000);

    setWindowTitle(tr("Digital Clock"));
    resize(150, 60);
}

void DigitalClock::showTime()
{
    // QTime time = QTime::currentTime() - time0;
    QString text =  QString::number(timer.elapsed()/1000);
    // if ((time.second() % 2) == 0)
    //     text[2] = ' ';
    display(text);

}

void DigitalClock::restart()
{
    timer.restart();
}
