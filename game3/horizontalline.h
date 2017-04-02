#ifndef HORIZONTALLINE_H
#define HORIZONTALLINE_H

#include <QtGui>
#include "game3/box.h"

/**
* \file horizontalline.h
* \brief HorizontalLine class
*
* Horizontal lines that delimit boxes from the top and bottom.
* \author Rita Aoun
* \author Rawan Moukalled
*/
class HorizontalLine : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    /**
    * \brief Default constructor
    * \param above Box above line
    * \param under Box under line
    */
    explicit HorizontalLine(Box *above, Box *under, QObject *parent = 0);

    /**
    * \brief Destructor
    */
    virtual ~HorizontalLine();

    /**
    * \brief Makes the line grey
    */
    void turnGrey();
    
signals:
    
public slots:

private:
    Box *m_above, *m_under; ///< Line neighbors
};

#endif // HORIZONTALLINE_H
