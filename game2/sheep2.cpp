#include "sheep2.h"

/**
* \file sheep2.cpp
* \brief Contains the Sheep class
*/

Sheep2::Sheep2(int row, int col, QObject *parent) :
    QObject(parent)
{
    setPixmap(QPixmap("pictures/sheep.png"));
    setScale(0.15);

    m_row = row;
    m_col = col;
}

int Sheep2::getRow() {
    return m_row;
}

int Sheep2::getCol() {
    return m_col;
}
