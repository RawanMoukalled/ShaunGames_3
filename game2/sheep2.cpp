#include "sheep2.h"

/**
* \file sheep2.cpp
* \brief Contains the Sheep class
*/

/**
* Initializes the sheep position and picture.
*/
Sheep2::Sheep2(Tile * tile, QObject *parent) :
    QObject(parent)
{
    setPixmap(QPixmap("pictures/sheep.png"));
    setScale(0.15);

    m_tile = NULL;
    setCurrent(tile);
}

/**
* Unsets current tile and sets the argument tile as current.
*/
void Sheep2::setCurrent(Tile * tile) {
    if(m_tile != NULL) {
      m_tile->setHasSheep(false);
    }
    m_tile = tile;
    m_tile->setHasSheep(true);
    this->setPos(m_tile->x(), m_tile->y());
}

/**
* Gets the current tile of the sheep.
*/
Tile* Sheep2::getCurrent() {
    return m_tile;
}

