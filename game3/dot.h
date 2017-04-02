#ifndef DOT_H
#define DOT_H

#include <QtGui>

/**
* \file dot.h
* \brief Dot class
*
* Dot objects delimit the game lines.
* \author Rita Aoun
* \author Rawan Moukalled
*/
class Dot : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    /**
    * \brief Default constructor
    */
    explicit Dot(QObject *parent = 0);

    /**
    * \brief Destructor
    */
    virtual ~Dot();
    
signals:
    
public slots:
    
};

#endif // DOT_H
