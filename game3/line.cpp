#include "line.h"
#include "game3/game3scene.h"

Line::Line(QObject *parent) :
    QObject(parent), m_drawn(false)
{
}

/**
* Called when the user clicks on the line. The function changes the states of corresponding lines and boxes.
* It then checks for a win.
*/
void Line::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    static bool firstTime(true);
    if(event->button() == Qt::LeftButton) {
        Game3Scene *s = static_cast<Game3Scene*>(scene());
        if (s->isUserTurn() && !m_drawn) {
            if (firstTime) {
                s->clearNewLines();
                firstTime = false;
            }
            s->addNewlyDrawnLine(this);
            if (!playTurn(true)) {
                firstTime = true;
                s->computerTurn();
            }
        }
    }
}

/**
* Returns whether the line has been drawn already.
*/
bool Line::isDrawn() {
    return m_drawn;
}

/**
* Sets the line as drawn.
*/
void Line::draw() {
    m_drawn = true;
}