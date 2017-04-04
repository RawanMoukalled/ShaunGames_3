#ifndef GAME2SCENE_H
#define GAME2SCENE_H

#include <QGraphicsScene>
#include <QtGui>
#include "difficulty.h"
#include "game2/tile.h"
#include "game2/sheep2.h"

/**
* \file game2scene.h
* \brief Trap the Sheep scene class
*
* This is the scene class for the gameplay of the Trap the Sheep game.
* \author Rita Aoun
* \author Rawan Moukalled
*/
class Game2Scene : public QGraphicsScene
{
    Q_OBJECT
public:

    /**
    * \brief Default constructor
    */
    explicit Game2Scene(Difficulty difficulty, QObject *parent = 0);
    QVector<int> tilesToBlock();
    void placeTiles();
    void placeSheepInitial();
    QVector< Tile* > * getNeighbors(Tile * center);
    void resetVisited();
    Tile* tileAt(int i, int j);
    //virtual ~Game2Scene();
    bool win(Tile * tile);
    Sheep2* getSheep();
    void moveSheep();
    bool getUserTurn();
    void setUserTurn(bool userTurn);

signals:
    
public slots:

private:
    Difficulty m_difficulty; ///< Current difficulty of the scene
    int m_score; ///< Game score;
    QVector< QVector< Tile* > > m_tiles; ///< 2D Vector of the tiles making up the grid
    Sheep2 * m_sheep; ///< The sheep that is trying to escape
    int m_block_count; ///< number of blocks on the grid
    bool m_user_turn;

    
};

#endif // GAME2SCENE_H
