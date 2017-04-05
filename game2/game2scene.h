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

    /**
    * \brief Sets the layout of the level buttons
    * \returns the indices of the tiles to block initially
    */
    QVector<int> tilesToBlock();

    /**
    * \brief Places the tiles to create the full grid
    */
    void placeTiles();

    /**
    * \brief places the sheep on a random unblocked tile at the beginning of the game
    */
    void placeSheepInitial();

    /**
    * \brief gets the left, right, upper and lower neighbors of the given tile
    * \param center the tile that we're getting the neighbors of
    * \returns pointer to a vector of pointers to the neighboring tiles
    */
    QVector< Tile* > * getNeighbors(Tile * center);

    /**
    * \brief sets all the blocks of the grid as having been unvisited
    */
    void resetVisited();

    /**
    * \brief retrieves the tile from the grid at the indices given
    * \param i the row of the tile
    * \param j the column of the tile
    * \returns pointer to the tile at the indices
    */
    Tile* tileAt(int i, int j);

    /**
    * \brief determines if the user sucessfully trapped the sheep
    * \param tile the tile to check the neighbors of
    * \returns the state of the game if win or loss
    */
    bool win(Tile * tile);

    /**
    * \brief gets the sheep of the game
    * \returns the sheep of the game
    */
    Sheep2* getSheep();

    /**
    * \brief moves the sheep according to the difficulty of the game
    */
    void moveSheep();

    /**
    * \brief retrieves whether or not it is the user's turn
    * \returns boolean indicating if it's the user's turn
    */
    bool getUserTurn();

    /**
    * \brief sets the turn of the user
    * \param userTurn whether or not it's the user's turn
    */
    void setUserTurn(bool userTurn);

    /**
    * \brief filters the given list of the blocked tiles
    * \param tiles the list of tiles
    * \returns list of non blocked tiles
    */
    QVector< Tile* > * getNonBlocked(QVector< Tile* > * tiles);


    //virtual ~Game2Scene();

signals:
    
public slots:

private:
    Difficulty m_difficulty; ///< Current difficulty of the scene
    int m_score; ///< Game score;
    QVector< QVector< Tile* > > m_tiles; ///< 2D Vector of the tiles making up the grid
    Sheep2 * m_sheep; ///< The sheep that is trying to escape
    int m_block_count; ///< number of blocks on the grid
    bool m_user_turn; ///< state of the user's turn

    
};

#endif // GAME2SCENE_H
