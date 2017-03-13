#ifndef GAME1SCENE_H
#define GAME1SCENE_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QLinkedList>
#include <cmath>
#include <QTimer>
#include "game1/cannon.h"
#include "game1/sheep1.h"
#include "game1/barn.h"
#include "game1/gameover.h"

/**
* \file game1scene.h
* \brief Sheep Line class
*
* Implements the scene of Game 1: Sheep Line
* \author Rita Aoun
* \author Rawan Moukalled
*/
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

    /**
    * \brief Stops movement of the sheep and triggers finishing the game
    */
    void gameOver();

    /**
    * \brief Fires the sheep
    */
    void fireSheep();

signals:
    /**
    * \brief Signals Game1 that the game is over
    */
    void Done();
    
public slots:
    /**
    * \brief Move sheep in the line according to a straight line then circle
    */
    void move_line();
    
private:
    Cannon *m_cannon; ///< Cannon and focus of scene
    QLinkedList<Sheep1*> m_sheepLine; ///< Initial line of 50 sheep
    QTimer *m_line_timer; ///< Timer that moves the line
    Sheep1 *m_current; ///< Current sheep that will be thrown
    Sheep1 *m_next; ///< Next sheep that will be thrown
    Barn *m_barn; ///< Barn that the sheep disappear into
    bool m_stopMoving; ///< Once a sheep hits the barn, signals other sheep to stop moving
    GameOver *m_gameOverPicture; ///< Overlayed on top of the game to show Game Over
};

#endif // GAME1SCENE_H
