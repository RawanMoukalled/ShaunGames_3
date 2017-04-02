#include "game2scene.h"

Game2Scene::Game2Scene(Difficulty difficulty, QObject *parent) :
    QGraphicsScene(parent), m_difficulty(difficulty), m_score(0), m_tiles(12)
{
    //Create the tiles
    bool even = false; //to alternate between 12 and 13
    int column_size;
    double left = 44.5;
    double top = 38.5;
    int offset;

    for(int i = 0; i < 12; i++) {
        QVector< Tile* > row;
        if(!even) {
            column_size = 13;
            offset = 0;

        } else {
            column_size = 12;
            offset = 22.5;
        }

        for(int j = 0; j < column_size; j++) {
            Tile * tile = new Tile;
            tile->setPos(offset + j*left,i*top);
            row.push_back(tile);
            addItem(tile);
        }
        even = !even;
        m_tiles.push_back(row);
    }
}
