#ifndef GAME1SCENE_H
#define GAME1SCENE_H

#include <QGraphicsScene>
#include <QLinkedList>
#include <QTimer>
#include <ctime>

#include "game1/cannon.h"
#include "game1/sheep1.h"

class Game1Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Game1Scene(QObject *parent = 0);
    
signals:
    
public slots:
    void move_line();
    
private:
    Cannon *m_cannon;
    QLinkedList<Sheep1*> m_sheepLine;
    Sheep1 *test;
    QTimer *m_line_timer;
};

#endif // GAME1SCENE_H
