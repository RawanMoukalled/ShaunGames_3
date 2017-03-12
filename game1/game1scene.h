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

    /**
    * \brief Adjusts focus
    */
    void mousePressEvent(QGraphicsSceneMouseEvent *);

    /**
    * \brief Moves sheep with rotating cannon
    */
    void moveCurrentSheep(bool toRight);

signals:
    
public slots:
    void move_line();
    
private:
    Cannon *m_cannon; ///< Cannon and focus of scene
    QLinkedList<Sheep1*> m_sheepLine; ///< Initial line of 50 sheep
    QTimer *m_line_timer; ///< Timer that moves the line
    Sheep1 *m_current; ///< Current sheep that will be thrown
    Sheep1 *m_next; ///< Next sheep that will be thrown
};

#endif // GAME1SCENE_H
