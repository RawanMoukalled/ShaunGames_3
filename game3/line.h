#ifndef LINE_H
#define LINE_H

#include <QtGui>

class Line : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    /**
    * \brief Default constructor
    */
    explicit Line(QObject *parent = 0);

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
    bool isDrawn();

    /**
    * \brief Sets the line as drawn
    */
    void draw();
    
signals:
    
public slots:

private:
    bool m_drawn; ///< Keeps track of whether the line has been clicked
};

#endif // LINE_H
