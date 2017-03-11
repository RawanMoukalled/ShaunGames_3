#ifndef CANNON_H
#define CANNON_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>

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
    * \brief Entrance point of triggered mouse events
    * \param event Triggered event
    */
    void mouseMoveEvent(QMouseEvent *event);
    
signals:
    
public slots:
    
};

#endif // CANNON_H
