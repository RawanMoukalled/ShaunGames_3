#include "tile.h"
#include "game2scene.h"
#include "sheep2.h"

Tile::Tile(bool block, int row, int col, QObject *parent) :
    QObject(parent)
{
    setBlock(block);
    setScale(0.25);
    m_hasSheep = false;
    m_row = row;
    m_col = col;
    m_visited = false;
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

            Game2Scene *sc = static_cast<Game2Scene*>(scene());
            sc->resetVisited();
            Sheep2 * scene_sheep = sc->getSheep();
            if( sc->win( sc->tileAt( scene_sheep->getRow(), scene_sheep->getCol() ) ) ){
                qDebug()<<"win";
            } else {
                qDebug()<<"still losin";
            }
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
    bool border = false;
    bool right_border = (m_row % 2 == 0 && m_col == 12) || (m_row % 2 != 0 && m_col == 11);
    if(m_row == 0 || m_row == 11 || m_col == 0 || right_border) {
        border = true;
    }

    return border;
}

void Tile::setVisited(bool visit) {
    m_visited = visit;
}

bool Tile::isVisited() {
    return m_visited;
}
