#include "tile.h"

Tile::Tile(QObject *parent) :
    QObject(parent)
{
    setPixmap(QPixmap("pictures/tile.png"));
    setScale(0.25);
    //setPos(0,0);
}

Tile::~Tile() {

}
