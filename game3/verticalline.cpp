#include "verticalline.h"
#include "game3/game3scene.h"

/**
* \file verticalline.cpp
* \brief Contains VerticalLine class definition
*/

/**
* Sets VerticalLine properties.
*/
VerticalLine::VerticalLine(Box *left, Box *right, QObject *parent) :
    Line(false, parent), m_left(left), m_right(right)
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
    Game3Scene *s = static_cast<Game3Scene*>(scene());
    if (m_left != NULL) {
        m_left->setRight();
        if (m_left->isClosed()) {
            keepTurn = true;
            if (userTurn) {
                m_left->drawBitzer();
                s->closeBoxByUser();
            }
            else {
                m_left->drawShaun();
                s->closeBoxByComputer();
            }
        }
    }
    if (m_right != NULL) {
        m_right->setLeft();
        if (m_right->isClosed()) {
            keepTurn = true;
            if (userTurn) {
                m_right->drawBitzer();
                s->closeBoxByUser();
            }
            else {
                m_right->drawShaun();
                s->closeBoxByComputer();
            }
        }
    }

    if (s->noMoreMoves()) {
        s->gameOver();
        // If it is the user's turn, keep it that way
        // Else, change turns and make it the user's turn
        return userTurn;
    }
    else {
        return keepTurn;
    }
}

/**
* Returns the box to the left of the line.
*/
Box* VerticalLine::getLeft() const {
    return m_left;
}

/**
* Returns the box to the right of the line.
*/
Box* VerticalLine::getRight() const {
    return m_right;
}

/**
* Draws the line as grey and edits its corresponding boxes.
*/
void VerticalLine::simpleDraw() {
    draw();
    if (m_left != NULL) {
        m_left->setRight();
    }
    if (m_right != NULL) {
        m_right->setLeft();
    }
    turnGrey();
}
