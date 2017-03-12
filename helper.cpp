#include "helper.h"
#include <ctime>
#include <QTime>
#include <QCoreApplication>

/**
* \file helper.cpp
* \brief Contains Helper class definition
*/

/**
* Makes the given widget small.
*/
void Helper::makeWidgetSmall(QWidget *widget) {
    if (m_uninitialized) {
        initialize();
    }
    widget->setFont(m_smallFont);
}

/**
* Makes the given widget large.
*/
void Helper::makeWidgetLarge(QWidget *widget) {
    if (m_uninitialized) {
        initialize();
    }
    widget->setFont(m_largeFont);
}

const double Helper::PI = 3.14159265;

/**
* Converts angle from degrees to radians.
*/
double Helper::toRadians(double degrees) {
    return degrees*PI/180;
}

/**
* Returns a random sheep number between 1 and 9.
*/
int Helper::getRandomSheepNumber() {
    return rand()%9 + 1;
}

/**
* Delays execution
*/
void Helper::delay(int msec)
{
    QTime dieTime= QTime::currentTime().addMSecs(msec);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

/**
* Initializes static members.
* Called only once.
*/
void Helper::initialize() {
    srand(time(0));
    m_uninitialized = false;
    m_smallFont.setPointSize(12);
    m_largeFont.setPointSize(18);
}

QFont Helper::m_smallFont;
QFont Helper::m_largeFont;
bool Helper::m_uninitialized(true);

