#ifndef GAME2SCENE_H
#define GAME2SCENE_H

#include <QGraphicsScene>
#include <QtGui>
#include "difficulty.h"
#include "game2/tile.h"
#include "game2/sheep2.h"
#include "gameover.h"

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
    * Destructor
    */
    virtual ~Game2Scene();

    /**
    * \brief Sets the layout of the level buttons
    * \returns The indices of the tiles to block initially
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
    * \brief Gets the left, right, upper and lower non-blocked neighbors of the given tile
    * \param center The tile that we're getting the neighbors of
    * \returns Pointer to a vector of pointers to the neighboring tiles
    */
    QVector< Tile* > * getNeighbors(Tile * center);

    /**
    * \brief Sets all the blocks of the grid as having been unvisited
    */
    void resetVisited();

    /**
    * \brief Sets all the blocks of the grid as having infinite distance to the sheep
    */
    void resetDistances();

    /**
    * \brief Sets all the blocks of the grid as having the previous node null
    */
    void resetPrevious();

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
    * \brief delays the computer turn
    */
    void computerTurn();

    /**
    * \brief Ends the game
    * \param win whether or not the user won
    */
    void gameOver(bool win);

    /**
    * \brief Increments the number of blocks on click of a tile
    */
    void decrementScore();

    /**
    * \brief retrieves the lcd display
    * \returns the lcd display
    */
    QLCDNumber* getScoreDisplay();

    /**
    * \brief retrieves the number of blocked tiles
    * \returns number of blocked tiles
    */
    int getBlockCount();

    /**
    * \brief Finds the shortest path and returns the next tile accordingly
    */
    Tile *findNextTile();

    /**
    * \brief Computes the distances from the sheep to every other tile
    */
    void computeDistances(Tile *current);

    /**
    * \brief Retrieves the non blocked border tiles
    */
    QVector< Tile* > *getNonBlockedBorders();

    /**
    * \brief Returns the difficulty of the game
    * \returns the difficulty of the game
    */
    Difficulty getDifficulty();

    /**
    * \brief Returns the current score of the game
    * \returns the score of the game
    */
    int getScore();

    /**
    * \brief Returns a string representation of the sheep row and column
    * \returns string representing the sheep's current row and column
    */
    QString getSheepPos();

    /**
    * \brief Returns the string representation of the blocked tiles' positions
    * \returns string representing the blocked tiles' positions
    */
    QString getBlockedTilesPos();

    /**
    * \brief Adds a tile to the list of blocked tiles
    * \param tile The tile to add to the list
    */
    void addToBlockedTiles(Tile* tile);


signals:
    /**
    * \brief Signal sent to game2 to show that the game has ended
    */
    void Done();
    
public slots:
    /**
    * \brief moves the sheep according to the difficulty of the game
    */
    void moveSheep();


private:
    Difficulty m_difficulty; ///< Current difficulty of the scene
    int m_score; ///< Game score;
    QVector< QVector< Tile* > > m_tiles; ///< 2D Vector of the tiles making up the grid
    Sheep2 * m_sheep; ///< The sheep that is trying to escape
    int m_block_count; ///< number of blocks on the grid
    bool m_user_turn; ///< state of the user's turn
    QTimer *m_delay; ///< Delay on computer's turn
    GameOver *m_gameOverPicture; ///< Picture to be overlayed on the screen when game is over
    QLCDNumber *m_scoreDisplay; ///< LCD that displays the score
    QVector< Tile* > m_blockedTiles; ///< List of the blocked tiles
    
};

#endif // GAME2SCENE_H
