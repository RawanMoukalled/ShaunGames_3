#ifndef GAME1SCENE_H
#define GAME1SCENE_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QLinkedList>
#include <cmath>
#include <QTimer>
#include "game1/cannon.h"
#include "game1/sheep1.h"

class Game1Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    /**
    * \brief Constructor
    */
    explicit Game1Scene(int level, QObject *parent = 0);

    /**
    * \brief Destructor
    */
    virtual ~Game1Scene();

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

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
