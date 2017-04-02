#include "dot.h"

/**
* \file dot.cpp
* \brief Contains Dot class definition
*/

/**
* Sets Dot properties.
*/
Dot::Dot(QObject *parent) :
    QObject(parent)
{
    setPixmap(QPixmap("pictures/Dot.png"));
    setScale(0.01);
    setZValue(3);
}

/**
* Frees allocated memory.
*/
Dot::~Dot() {
}
