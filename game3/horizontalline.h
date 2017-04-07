#ifndef HORIZONTALLINE_H
#define HORIZONTALLINE_H

#include "game3/line.h"
#include "game3/box.h"

/**
* \file horizontalline.h
* \brief HorizontalLine class
*
* Horizontal lines that delimit boxes from the top and bottom.
* \author Rita Aoun
* \author Rawan Moukalled
*/
class HorizontalLine : public Line
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

    /**
    * \brief Called when a line is selected
    * \param userTurn Whether it is the user's turn
    * \returns Whether it is still the player's turn
    */
    bool playTurn(bool userTurn);

    /**
    * \brief Gets the box above the line
    * \returns box above the line
    */
    Box* getAbove();

    /**
    * \brief Gets the box under the line
    * \returns box under the line
    */
    Box* getUnder();
    
signals:
    
public slots:

private:
    Box *m_above, *m_under; ///< Line neighbors
};

#endif // HORIZONTALLINE_H
