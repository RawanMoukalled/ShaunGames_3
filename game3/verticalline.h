#ifndef VERTICALLINE_H
#define VERTICALLINE_H

#include <game3/line.h>
#include "game3/box.h"

/**
* \file verticalline.h
* \brief VerticalLine class
*
* Vertical lines that delimit boxes from the left and right.
* \author Rita Aoun
* \author Rawan Moukalled
*/
class VerticalLine : public Line
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

    /**
    * \brief Called when a line is selected
    * \param userTurn Whether it is the user's turn
    * \returns Whether it is still the player's turn
    */
    bool playTurn(bool userTurn);

    /**
    * \brief Gets the box to the left of the line
    * \returns box to the left of the line
    */
    Box* getLeft() const;

    /**
    * \brief Gets the box to the right of the line
    * \returns box to the right of the line
    */
    Box* getRight() const;

    /**
    * \brief Draws the line as grey and edits its corresponding boxes
    */
    void simpleDraw();
    
signals:
    
public slots:

private:
    Box *m_left, *m_right; ///< Line neighbors
    
};

#endif // VERTICALLINE_H
