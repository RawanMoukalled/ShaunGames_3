#ifndef GAME3SCENE_H
#define GAME3SCENE_H

#include <QtGui>
#include "difficulty.h"
#include "game3/size.h"
#include "game3/dot.h"

class Game3Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Game3Scene(Difficulty difficulty, Size size, QObject *parent = 0);

    virtual ~Game3Scene();
    
signals:
    
public slots:

private:
    const Difficulty m_difficulty;
    const Size m_size;
    const int m_nbOfDots;
    QVector< QVector<Dot*> > m_dots;
};

#endif // GAME3SCENE_H
