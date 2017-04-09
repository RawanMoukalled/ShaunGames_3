#include "helper.h"
#include <ctime>
#include <QTime>

/**
* \file helper.cpp
* \brief Contains Helper class definition
*/

/**
* Makes the given widget small.
*/
void Helper::makeWidgetSmall(QWidget *widget) {
    widget->setFont(m_smallFont);
}

/**
* Makes the given widget large.
*/
void Helper::makeWidgetLarge(QWidget *widget) {
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
* Retrieves the user ID.
*/
int Helper::getUserId() {
    return m_userId;
}

/**
* Sets the user ID.
*/
void Helper::setUserId(int id) {
    m_userId = id;
}

/**
* Initializes static members.
* Called only once.
*/
void Helper::initialize() {
    if (m_uninitialized) {
        srand(time(0));
        m_uninitialized = false;
        m_smallFont.setPointSize(12);
        m_largeFont.setPointSize(18);
        shaunDB = QSqlDatabase::addDatabase("QSQLITE");//not dbConnection
        shaunDB.setDatabaseName("database/shaunDB.db");
    }
}

QSqlDatabase Helper::shaunDB(QSqlDatabase::addDatabase("QSQLITE", "shaunDB"));
QFont Helper::m_smallFont;
QFont Helper::m_largeFont;
bool Helper::m_uninitialized(true);
int Helper::m_userId(0);

