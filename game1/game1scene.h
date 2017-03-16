#ifndef GAME1SCENE_H
#define GAME1SCENE_H

#include <QtGui>
#include <QLinkedList>
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
    void gameOver(bool win);

    /**
    * \brief Fires the sheep
    */
    void fireSheep();

    /**
    * \brief Checks the collision list of the item for a sheep in the sheep list
    * \param item Pointer to item to check
    * \returns Whether the given item collides with a sheep in the list
    */
    bool collidesWithSheepInLine(QGraphicsItem *item);

    /**
    * \brief Returns the current player score
    * \returns Current player score
    */
    int getScore() const;

signals:
    /**
    * \brief Signals Game1 that the game is over
    */
    void Done(bool);
    
public slots:
    /**
    * \brief Move sheep in the line according to a straight line then circle
    */
    void move_line();
    
private:
    int m_level; ///< Current level of the scene
    int m_score; ///< Game score
    QLCDNumber *m_scoreDisplay; ///< Displays the game score
    Cannon *m_cannon; ///< Cannon and focus of scene
    QLinkedList<Sheep1*> m_sheepLine; ///< Initial line of 50 sheep
    QTimer *m_line_timer; ///< Timer that moves the line
    Sheep1 *m_current; ///< Current sheep that will be thrown
    Sheep1 *m_next; ///< Next sheep that will be thrown
    Barn *m_barn; ///< Barn that the sheep disappear into
    GameOver *m_gameOverPicture; ///< Overlayed on top of the game to show Game Over
};

#endif // GAME1SCENE_H
