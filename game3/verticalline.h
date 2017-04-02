#ifndef VERTICALLINE_H
#define VERTICALLINE_H

#include <QtGui>
#include "game3/box.h"

/**
* \file verticalline.h
* \brief VerticalLine class
*
* Vertical lines that delimit boxes from the left and right.
* \author Rita Aoun
* \author Rawan Moukalled
*/
class VerticalLine : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    /**
    * \brief Default constructor
    * \param left Box on left of line
    * \param right Box on right of line
    */
    explicit VerticalLine(Box *left, Box *right, QObject *parent = 0);

    /**
    * \brief Destructor
    */
    virtual ~VerticalLine();

    /**
    * \brief Makes the line grey
    */
    void turnGrey();
    
signals:
    
public slots:

private:
    Box *m_left, *m_right; ///< Line neighbors
    
};

#endif // VERTICALLINE_H
