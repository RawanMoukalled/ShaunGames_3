#include "verticalline.h"

/**
* \file verticalline.cpp
* \brief Contains VerticalLine class definition
*/

/**
* Sets VerticalLine properties.
*/
VerticalLine::VerticalLine(Box *left, Box *right, QObject *parent) :
    Line(parent), m_left(left), m_right(right)
{
    setPixmap(QPixmap("pictures/Lines/vertical_transparent.png"));
    setZValue(2);
}

/**
* Frees allocated memory.
*/
VerticalLine::~VerticalLine() {
}

/**
* Changes the object image to make it grey.
*/
void VerticalLine::turnGrey() {
    setPixmap(QPixmap("pictures/Lines/vertical_grey.png"));
}

/**
* Called when a line is drawn. Returns whether it is still the same player's turn.
*/
bool VerticalLine::playTurn(bool userTurn) {
    draw();
    setPixmap(QPixmap("pictures/Lines/vertical_red.png"));
    bool keepTurn = false;
    if (m_left != NULL) {
        m_left->setRight();
        if (m_left->isClosed()) {
            keepTurn = true;
            if (userTurn) {
                m_left->drawBitzer();
            }
            else {
                m_left->drawShaun();
            }
        }
    }
    if (m_right != NULL) {
        m_right->setLeft();
        if (m_right->isClosed()) {
            keepTurn = true;
            if (userTurn) {
                m_right->drawBitzer();
            }
            else {
                m_right->drawShaun();
            }
        }
    }
    return keepTurn;
}

