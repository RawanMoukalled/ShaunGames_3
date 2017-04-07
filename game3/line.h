#ifndef LINE_H
#define LINE_H

#include <QtGui>

/**
* \file line.h
* \brief Line class
*
* Line is an interface for vertical and horizontal lines.
* It implements the on-click reaction of lines and it remembers whether a line has been clicked before.
*
* \author Rita Aoun
* \author Rawan Moukalled
*/
class Line : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    /**
    * \brief Default constructor
    * \param isHorizontal Whether the line is horizontal or not (vertical)
    */
    explicit Line(bool isHorizontal, QObject *parent = 0);

    /**
    * \brief Makes the line grey
    */
    virtual void turnGrey() = 0;

    /**
    * \brief Called when the user clicks on the line
    */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    /**
    * \brief Called when a line is selected
    * \param userTurn Whether it is the user's turn
    * \returns Whether it is still the player's turn
    */
    virtual bool playTurn(bool userTurn) = 0;

    /**
    * \brief Returns whether the line has been drawn already
    * \returns Whether the line has been drawn already
    */
    bool isDrawn() const;

    /**
    * \brief Sets the line as drawn
    */
    void draw();

    /**
    * \brief Returns whether the line is horizontal or vertical
    * \returns Whether the line is horizontal
    */
    bool isHorizontal() const;
    
signals:
    
public slots:

private:
    const bool m_horizontal; ///< Whether the line is horizontal or vertical
    bool m_drawn; ///< Keeps track of whether the line has been clicked
};

#endif // LINE_H
