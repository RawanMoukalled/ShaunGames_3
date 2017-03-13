#ifndef BARN_H
#define BARN_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

/**
* \file barn.h
* \brief Barn class
*
* Barn that terminates the game once a sheep from the line reaches it
* \author Rita Aoun
* \author Rawan Moukalled
*/
class Barn : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    /**
    * \brief Default constructor
    */
    explicit Barn(QObject *parent = 0);

    /**
    * \brief Destructor
    */
    virtual ~Barn();
    
signals:
    
public slots:
    /**
    * \brief Triggers the end of the game once a sheep collides with the barn
    */
    void sheepIn();

private:
    QTimer *m_timer; ///< Timer to keep checking for collisions
    bool m_collisionDone; ///< Boolean to check if the collision happened

};

#endif // BARN_H
