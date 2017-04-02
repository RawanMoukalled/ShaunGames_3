#ifndef GAME3SCENE_H
#define GAME3SCENE_H

#include <QtGui>
#include "difficulty.h"
#include "game3/size.h"
#include "game3/dot.h"
#include "game3/horizontalline.h"
#include "game3/verticalline.h"

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
    QVector< QVector<Dot*> > m_dots;
    QVector< QVector<HorizontalLine*> > m_horizontalLines;
    QVector< QVector<VerticalLine*> > m_verticalLines;
    QVector< QVector<Box*> > m_boxes;
};

#endif // GAME3SCENE_H
