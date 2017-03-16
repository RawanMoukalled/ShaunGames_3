#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QtGui>

/**
* \file gameover.h
* \brief Game Over class
*
* Image overlayed on the screen when game is over
* \author Rita Aoun
* \author Rawan Moukalled
*/
class GameOver : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    /**
    * \brief Default constructor
    */
    explicit GameOver(bool win, QObject *parent = 0);

    /**
    * \brief Destructor
    */
    virtual ~GameOver();
    
signals:
    
public slots:
    
};

#endif // GAMEOVER_H
