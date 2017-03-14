#include "sheep1.h"
#include "helper.h"
#include "game1scene.h"
#include <QString>
#include <QtGui>

/**
* Sets the properties of the sheep.
*/
Sheep1::Sheep1(int number, bool inLine, QObject *parent) :
    QObject(parent), m_number(number), m_angle(0.), m_inLine(inLine), m_scene(NULL)
{
    setPixmap(QPixmap("pictures/sheep/"+QString::number(number)+".png"));
    setScale(0.10);
    setPos(500,0);

    m_timer = new QTimer(this);
}

/**
* Frees allocated memory.
*/
Sheep1::~Sheep1() {
    delete m_timer;
}

/**
* Fires sheep at an angle. Called when the user fires the cannon.
*/
void Sheep1::fire(double angle) {
    m_angle = angle;
    m_scene = scene();

    connect(m_timer, SIGNAL(timeout()), this, SLOT(firedMove()));
    m_timer->start(1);
}

/**
* Moves sheep in line by given distance.
*/
void Sheep1::moveInLine(double distance) {
    if (m_inLine) {
        double currX = x();
        double currY = y();

        if (currX == 500) {
            // if in the straight line
            if (currY <= 250-distance) {
                // if we're moving only in the straight line
                setPos(currX, currY + distance);
                return;
            }
            else {
                // if we also need to move in the circle
                setPos(currX, 250);
                distance = distance - (250 - currY);
            }
        }

        double angle = (m_angle + distance/(2*Helper::PI*200/360));

        if (angle >= 360) {
            angle = angle - 360;
        }

        setAngle(angle);

        double rAngle = Helper::toRadians(angle);
        currX = 300 + 200*cos(rAngle);
        currY = 250 + 200*sin(rAngle);

        setPos(currX, currY);
    }
}

/**
* Calculates the distance between the two in-line sheep.
*/
double Sheep1::inLineDistanceTo(const Sheep1 *other) const {
    double distance = 0;
    if (m_inLine && other->m_inLine) {
        double thisX = x();
        double thisY = y();
        double otherX = other->x();
        double otherY = other->y();

        if (thisX == 500) {
            if (otherX == 500) {
                return qAbs(thisY - otherY);
            }
            else {
                distance = 250 - thisY;
                thisY = 250;
            }
        }
        else if (otherX == 500) {
            distance = 250 - otherY;
            otherY = 250;
        }

        distance = distance + 2*Helper::PI*200/360*qAbs(m_angle-other->m_angle);
    }
    return distance;
}

/**
* Moves the sheep in the distance of the firing of the cannon.
*/
void Sheep1::firedMove() {
    Game1Scene *sc = static_cast<Game1Scene*>(m_scene);

    if (sc->collidesWithSheepInLine(this)) {
        m_timer->stop();
    }
    else {
        double newX = x() + cos(Helper::toRadians(m_angle));
        double newY = y() + sin(Helper::toRadians(m_angle));
        setPos(newX, newY);
        if (newX > 620 || newX < -35 || newY > 540 || newY < -35 ) {
            delete this;
        }
    }
}

double Sheep1::getAngle() const {
    return m_angle;
}

void Sheep1::setAngle(double angle){
    if (angle >= 360) {
        angle = angle - 360;
    }
    m_angle = angle;
}

void Sheep1::setInLine(bool inLine) {
    m_inLine = inLine;
}

bool Sheep1::isInLine() const {
    return m_inLine;
}

int Sheep1::getNumber() const {
    return m_number;
}

