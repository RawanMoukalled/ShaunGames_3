#include "tile.h"

Tile::Tile(bool block, int row, int col, QObject *parent) :
    QObject(parent)
{
    setBlock(block);
    setScale(0.25);
    m_hasSheep = false;
    m_row = row;
    m_col = col;
}

Tile::~Tile() {

}

/**
* Marks tile as selected and adds border to it
*/
void Tile::setBlock(bool block) {
    m_blocked = block;
    if(!block) {
       setPixmap(QPixmap("pictures/tile.png"));
    } else {
        setPixmap(QPixmap("pictures/tile_blocked"));
    }
}

bool Tile::isBlocked() {
    return m_blocked;
}

void Tile::setHasSheep(bool placed) {
    if(placed) {
        m_hasSheep = true;
    } else {
        m_hasSheep = false;
    }
}

void Tile::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {

        if(m_hasSheep == false && m_blocked == false) {
            setBlock(true);

        }
    }
}

int Tile::getRow() {
    return m_row;
}

int Tile::getCol() {
    return m_col;
}

bool Tile::isBorder() {

}
