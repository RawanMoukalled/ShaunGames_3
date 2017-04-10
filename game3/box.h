#ifndef BOX_H
#define BOX_H

#include <QtGui>

/**
* \file box.h
* \brief Box class
*
* Box objects need to be bounded by a player for them to win points.
* \author Rita Aoun
* \author Rawan Moukalled
*/
class Box : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    /**
    * \brief Default constructor
    */
    explicit Box(QObject *parent = 0);

    /**
    * \brief Destructor
    */
    virtual ~Box();

    /**
    * \brief Sets pixmap to Shaun
    */
    void drawShaun();

    /**
    * \brief Sets pixmap to Bitzer
    */
    void drawBitzer();

    /**
    * \brief Marks that the top of the box has been drawn
    */
    void setAbove();

    /**
    * \brief Marks that the left of the box has been drawn
    */
    void setLeft();

    /**
    * \brief Marks that the bottom of the box has been drawn
    */
    void setUnder();

    /**
    * \brief Marks that the right of the box has been drawn
    */
    void setRight();

    /**
    * \brief Checks if the box has been closed
    * \returns Whether the box has been closed
    */
    bool isClosed() const;

    /**
    * \brief Checks how many lines are drawn in the box
    * \returns The number of lines drawn
    */
    int numberOfLinesDrawn() const;

    /**
    * \brief Returns whether the user has closed this box
    * \returns Whether the user has closed this box
    */
    bool wasClosedByUser() const;
    
signals:
    
public slots:

private:
    bool m_above, m_left, m_under, m_right; ///< Remembers whether surrounding lines have been drawn
    bool m_closedByUser, m_closedByPC; ///< Remembers who closed the box. Both values cannot be true at the same time.
};

#endif // BOX_H
