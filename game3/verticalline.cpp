#include "verticalline.h"

/**
* \file verticalline.cpp
* \brief Contains VerticalLine class definition
*/

/**
* Sets VerticalLine properties.
*/
VerticalLine::VerticalLine(Box *left, Box *right, QObject *parent) :
    QObject(parent), m_left(left), m_right(right)
{
    setPixmap(QPixmap("pictures/Lines/vertical_red.png"));
    setZValue(2);
}

/**
* Frees allocated memory.
*/
VerticalLine::~VerticalLine() {
}

/**
* Changes the object image to make it grey.
*/
void VerticalLine::turnGrey() {
    setPixmap(QPixmap("pictures/Lines/horizontal_grey.png"));
}
