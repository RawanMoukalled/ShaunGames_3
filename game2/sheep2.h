#ifndef SHEEP2_H
#define SHEEP2_H

#include <QtGui>
#include "tile.h"

/**
* \file sheep.h
* \brief Sheep class for game 2
*
* This is the sheep that we wish to trap in Game 2
* \author Rita Aoun
* \author Rawan Moukalled
*/
class Sheep2 : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:

    /**
    * \brief default constructor
    */
    explicit Sheep2(Tile * tile, QObject *parent = 0);

    /**
    * \brief sets the current tile of the sheep
    * \param tile the tile to be set as current
    */
    void setCurrent(Tile * tile);

    /**
    * \brief gets the current tile of the sheep
    * \returns the current tile
    */
    Tile* getCurrent();

    
signals:
    
public slots:

private:
    Tile * m_tile; ///< Tile that the sheep is currently on
};

#endif // SHEEP2_H
