#ifndef TILE_H
#define TILE_H

#include <QtGui>
#include <QMouseEvent>

/**
* \file tile.h
* \brief class for the tiles of game 2
*
* This is class for the tiles of the grid in game 2
* \author Rita Aoun
* \author Rawan Moukalled
*/
class Tile : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    /**
    * \brief Default constructor
    */
    explicit Tile(bool block, int row, int col, QObject *parent = 0);

    /**
    * \brief set the status of the tile as blocked or not
    * \param block decides if the tile is blocked or not
    */
    void setBlock(bool block);

    /**
    * \brief retrieves the blocked status of the tile
    * \returns whether or not the tile is blocked
    */
    bool isBlocked();

    /**
    * \brief what to do on the mouse press event
    * \param event the mouse press event
    */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    /**
    * \brief Destrictor
    */
    virtual ~Tile();

    /**
    * \brief sets the status of the tile as having a sheep on it or not
    * \param placed boolean status of having a sheep placed on it or not
    */
    void setHasSheep(bool placed);


    /**
    * \brief retrieves the row index of the current tile
    * \returns the row index
    */
    int getRow();

    /**
    * \brief retrieves the column index of the current tile
    * \returns the column index
    */
    int getCol();

    /**
    * \brief checks if the current tile is on the border of the grid
    * \returns the border status of the tile
    */
    bool isBorder();

    /**
    * \brief sets the status of the tile as visited or not
    * \param visit visited status of the tile
    */
    void setVisited(bool visit);

    /**
    * \brief checks if the current tile has been visited
    * \returns the visited status of the tile
    */
    bool isVisited();

    /**
    * \brief Retrieves the distance to the sheep so far
    * \returns The distance to the sheep
    */
    int getDistance();

    /**
    * \brief Sets the distance to the sheep
    * \param The distance to the sheep
    */
    void setDistance(int distance);

    /**
    * \brief Retrieves the previous tile
    * \returns The previous tile
    */
    Tile* getPrev();

    /**
    * \brief Sets the previous tile
    * \param tile The tile to be set as previous
    */
    void setTile(Tile* tile);


signals:
    
public slots:

private:
    bool m_blocked; ///< Indicates if this tile has been clicked
    bool m_hasSheep; ///< Indicates if the sheep is currently placed on it
    int m_row; ///< Indicates the row of the tile
    int m_col; ///< Indicates the column of the tile
    bool m_visited; ///< Indicates if the current tile has been visited in the search for path to border

    int m_distance; ///< Distance to the sheep
    Tile* m_prevTile;  ///< Previous tile in the distance computation

};

#endif // TILE_H
