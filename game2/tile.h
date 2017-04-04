#ifndef TILE_H
#define TILE_H

#include <QtGui>
#include <QMouseEvent>

class Tile : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Tile(bool block, int row, int col, QObject *parent = 0);
    void setBlock(bool block);
    bool isBlocked();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual ~Tile();
    void setHasSheep(bool placed);
    int getRow();
    int getCol();
    bool isBorder();


signals:
    
public slots:

private:
    bool m_blocked; ///< Indicates if this tile has been clicked
    bool m_hasSheep; ///< Indicates if the sheep is currently placed on it
    int m_row; ///< Indicates the row of the tile
    int m_col; ///< Indicates the column of the tile
};

#endif // TILE_H
