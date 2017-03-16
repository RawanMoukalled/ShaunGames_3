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
    */
    void keyPressEvent(QKeyEvent *event);
    
signals:
    
public slots:
    
private:
};

#endif // CANNON_H
