#ifndef TILE_H
#define TILE_H

#include <QtGui>

class Tile : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Tile(QObject *parent = 0);

    virtual ~Tile();
    
signals:
    
public slots:
    
};

#endif // TILE_H
