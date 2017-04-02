#ifndef GAME2SCENE_H
#define GAME2SCENE_H

#include <QGraphicsScene>
#include "difficulty.h"
#include "game2/tile.h"

class Game2Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Game2Scene(Difficulty difficulty, QObject *parent = 0);

    //virtual ~Game2Scene();
    
signals:
    
public slots:

private:
    Difficulty m_difficulty; ///< Current difficulty of the scene
    int m_score; ///< Game score;
    QVector< QVector< Tile* > > m_tiles; ///< 2D Vector of the tiles making up the grid

    
};

#endif // GAME2SCENE_H
