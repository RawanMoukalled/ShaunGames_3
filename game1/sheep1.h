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
    double getAngle() const;

    /**
    * \brief Sets the angle of the sheep in degrees
    */
    void setAngle(double angle);

    /**
    * \brief Checks whether the sheep is part of the moving line
    * \returns Whether sheep is in line
    */
    bool isInLine() const;

    /**
    * \brief Changes the status of the sheep as in or out of the moving line
    */
    void setInLine(bool inLine);

    /**
    * \brief Fires the sheep in a straight line
    */
    void fire(double angle);

    /**
    * \brief Moves the sheep in line by given distance.
    * \param distance Distance by which to move the sheep in pixels
    */
    void moveInLine(double distance);

    /**
    * \brief Returns the in-line distance between object and given sheep
    * \param other Other sheep
    * \returns Distance in pixels
    */
    double inLineDistanceTo(const Sheep1 *other) const;

    /**
    * \brief Returns the sheep number
    */
    int getNumber() const;

signals:
    
public slots:
    /**
    * \brief Moves the sheep in the direction of the firing
    */
    void firedMove();

private:
    int m_number; ///< Sheep number
    double m_angle; ///< Angle of the sheep in degrees
    bool m_inLine; ///< Specifies whether the sheep is moving in the line
    QTimer *m_timer; ///< Timer for when the sheep is fired from the cannon
    QGraphicsScene *m_scene; ///< Scene that owns the sheep
};

#endif // SHEEP1_H
