#ifndef SHEEP1_H
#define SHEEP1_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsScene>

/**
* \file sheep1.h
* \brief Sheep1 class
*
* Randomly numbered sheep that are used for Game 1: Sheep Line
* \author Rita Aoun
* \author Rawan Moukalled
*/
class Sheep1 : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    /**
    * \brief Constructor
    */
    explicit Sheep1(int number, bool inLine, QObject *parent = 0);

    /**
    * \brief Destructor
    */
    virtual ~Sheep1();

    /**
    * \brief Gets the angle of the sheep in degrees
    */
    int getAngle() const;
    /**
    * \brief Sets the angle of the sheep in degrees
    */
    void setAngle(int angle);

    /**
    * \brief Checks whether the sheep is part of the moving line
    */
    bool isInLine();

    /**
    * \brief Changes the status of the sheep as in or out of the moving line
    */
    void setInLine(bool inLine);

private:
    int m_angle; ///< Angle of the sheep in degrees
    bool m_inLine; ///< Specifies whether the sheep is moving in the line

    /**
    * \brief Fires the sheep in a straight line
    */
    void fire(int angle);

signals:
    
public slots:
    /**
    * \brief Moves the sheep in the direction of the firing
    */
    void firedMove();

private:
    int m_number; ///< Sheep number
    int m_angle; ///< Angle of the sheep in degrees
    bool m_inLine; ///< Specifies whether the sheep is moving in the line
    QTimer *m_timer; ///< Timer for when the sheep is fired from the cannon
    QGraphicsScene *m_scene; ///< Scene that owns the sheep
};

#endif // SHEEP1_H
