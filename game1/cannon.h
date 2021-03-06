#ifndef CANNON_H
#define CANNON_H

#include <QtGui>

/**
* \file cannon.h
* \brief Cannon class
*
* Cannon objects rotate with mouse movements, and fire sheep on click.
* \author Rita Aoun
* \author Rawan Moukalled
*/
class Cannon : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    /**
    * \brief Default constructor
    */
    explicit Cannon(QObject *parent = 0);

    /**
    * \brief Destructor
    */
    virtual ~Cannon();

    /**
    * \brief Entrance point of triggered key events
    * \param event The event that has been triggered
    */
    void keyPressEvent(QKeyEvent *event);

    /**
    * \brief Rotates the cannon
    * \param toTheRight Whether the movement should be to the right or to the left
    */
    void rotateCannon(bool toTheRight);
    
signals:
    
public slots:
    
private:
};

#endif // CANNON_H
