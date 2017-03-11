#ifndef GAME1SCENE_H
#define GAME1SCENE_H

#include <QGraphicsScene>
#include "game1/cannon.h"

class Game1Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Game1Scene(QObject *parent = 0);
    
signals:
    
public slots:
    
private:
    Cannon *m_cannon;
};

#endif // GAME1SCENE_H
