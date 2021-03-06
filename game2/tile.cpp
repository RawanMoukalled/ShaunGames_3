#include "tile.h"
#include "game2scene.h"
#include "sheep2.h"

/**
* \file tile.cpp
* \brief Contains Tile class definition
*/

/**
* Sets the block status, scale and initializes indices.
*/
Tile::Tile(bool block, int row, int col, QObject *parent) :
    QObject(parent)
{
    setBlock(block);
    setScale(0.25);
    m_hasSheep = false;
    m_row = row;
    m_col = col;
    m_visited = false;
    m_prevTile = NULL;
}

/**
* Frees allocated memory.
*/
Tile::~Tile() {
}

/**
* Marks tile as selected and adds border to it.
*/
void Tile::setBlock(bool block) {
    m_blocked = block;
    if(!block) {
       setPixmap(QPixmap("pictures/tile.png"));
    } else {
        setPixmap(QPixmap("pictures/tile_blocked"));
    }
}

/**
* Retrieves the blocked status.
*/
bool Tile::isBlocked() {
    return m_blocked;
}

/**
* Sets the tile as having a sheep or not.
*/
void Tile::setHasSheep(bool placed) {
    if(placed) {
        m_hasSheep = true;
    } else {
        m_hasSheep = false;
    }
}

/**
* On click, places a block on the tile and checks for win status, then
* gives the turn to the computer.
*/
void Tile::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        //get the game scene
        Game2Scene *sc = static_cast<Game2Scene*>(scene());
        if(m_hasSheep == false && m_blocked == false && sc->getUserTurn()) {
            setBlock(true);
            sc->addToBlockedTiles(this);
            sc->decrementScore();

            //check if the user has won
            sc->resetVisited();
            Sheep2 * scene_sheep = sc->getSheep();
            if( sc->win( scene_sheep->getCurrent() ) ){
                sc->gameOver(true);
            } else {
                sc->computerTurn();
            }

        }
    }
}

/**
* Retrieves the row of the tile.
*/
int Tile::getRow() {
    return m_row;
}

/**
* Retrieves the column of the tile.
*/
int Tile::getCol() {
    return m_col;
}

/**
* Checks if the column is a border.
*/
bool Tile::isBorder() {
    bool border = false;
    bool right_border = (m_row % 2 == 0 && m_col == 12) || (m_row % 2 != 0 && m_col == 11);
    if(m_row == 0 || m_row == 11 || m_col == 0 || right_border) {
        border = true;
    }

    return border;
}

/**
* Sets the visited status of the tile.
*/
void Tile::setVisited(bool visit) {
    m_visited = visit;
}

/**
* Returns the visited status of the tile.
*/
bool Tile::isVisited() {
    return m_visited;
}

/**
* Retrieves the distance to the sheep so far.
*/
int Tile::getDistance() {
    return m_distance;
}

/**
* Sets the distance to the sheep.
*/
void Tile::setDistance(int distance) {
    m_distance = distance;
}

/**
* Retrieves the previous tile.
*/
Tile* Tile::getPrev() {
    return m_prevTile;
}

/**
* Sets the previous tile.
*/
void Tile::setPrev(Tile* tile) {
    m_prevTile = tile;
}
