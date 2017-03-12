#include "helper.h"

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

/**
* Initializes static members.
* Called only once.
*/
void Helper::initialize() {
    m_uninitialized = false;
    m_smallFont.setPointSize(12);
    m_largeFont.setPointSize(18);
}

QFont Helper::m_smallFont;
QFont Helper::m_largeFont;
bool Helper::m_uninitialized(true);

const double Helper::PI = 3.14159265;
