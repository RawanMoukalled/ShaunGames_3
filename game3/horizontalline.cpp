#include "horizontalline.h"

/**
* \file horizontalline.cpp
* \brief Contains HorizontalLine class definition
*/

/**
* Sets HorizontalLine properties.
*/
HorizontalLine::HorizontalLine(Box *above, Box *under, QObject *parent) :
    QObject(parent), m_above(above), m_under(under)
{
    setPixmap(QPixmap("pictures/Lines/horizontal_red.png"));
    setZValue(2);
}

/**
* Frees allocated memory.
*/
HorizontalLine::~HorizontalLine() {
}

/**
* Changes the object image to make it grey.
*/
void HorizontalLine::turnGrey() {
    setPixmap(QPixmap("pictures/Lines/horizontal_grey.png"));
}
