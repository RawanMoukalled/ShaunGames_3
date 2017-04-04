#include "horizontalline.h"

/**
* \file horizontalline.cpp
* \brief Contains HorizontalLine class definition
*/

/**
* Sets HorizontalLine properties.
*/
HorizontalLine::HorizontalLine(Box *above, Box *under, QObject *parent) :
    Line(parent), m_above(above), m_under(under)
{
    setPixmap(QPixmap("pictures/Lines/horizontal_transparent.png"));
    setZValue(2);
}

/**
* Frees allocated memory.
*/
HorizontalLine::~HorizontalLine() {
}

/**
* Changes the object image to make it grey.
*/
void HorizontalLine::turnGrey() {
    setPixmap(QPixmap("pictures/Lines/horizontal_grey.png"));
}

/**
* Called when a line is drawn. Returns whether it is still the same player's turn.
*/
bool HorizontalLine::playTurn(bool userTurn) {
    draw();
    setPixmap(QPixmap("pictures/Lines/horizontal_red.png"));
    bool keepTurn = false;
    if (m_above != NULL) {
        m_above->setUnder();
        if (m_above->isClosed()) {
            keepTurn = true;
            if (userTurn) {
                m_above->drawBitzer();
            }
            else {
                m_above->drawShaun();
            }
        }
    }
    if (m_under != NULL) {
        m_under->setAbove();
        if (m_under->isClosed()) {
            keepTurn = true;
            if (userTurn) {
                m_under->drawBitzer();
            }
            else {
                m_under->drawShaun();
            }
        }
    }
    return keepTurn;
}
