#include "sheep1.h"
#include "helper.h"
#include "game1scene.h"
#include <QString>
#include <QtGui>

/**
* Sets the properties of the sheep.
*/
Sheep1::Sheep1(int number, bool inLine, QObject *parent) :
    QObject(parent), m_scene(NULL)
{
    m_angle = 0;

    setPixmap(QPixmap("pictures/sheep/"+QString::number(number)+".png"));
    setScale(0.10);
    setPos(500,0);

    m_inLine = inLine;

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
void Sheep1::fire(int angle) {
    setRotation(0);
    m_angle = angle;
    m_scene = scene();

    connect(m_timer, SIGNAL(timeout()), this, SLOT(firedMove()));
    if (angle == 90 || angle == 180) {
        m_timer->start(10);
    }
    else {
        m_timer->start(5);
    }
}

void Sheep1::firedMove() {
    double newX = x();
    double newY = y();

    double a = 0.;
    double b = 0.;

    if (m_angle != 90 && m_angle != 270) {
        a = tan(Helper::toRadians(m_angle));
        b = newY - a*newX;
    }

    Game1Scene *sc = static_cast<Game1Scene*>(m_scene);

    if (sc->collidesWithSheepInLine(this)) {
        m_timer->stop();
    }
    else {
        if (m_angle < 90 || m_angle > 270) {
            newX++;
            newY = a*newX+b;
        }
        else if (m_angle > 90 && m_angle < 270) {
            newX--;
            newY = a*newX+b;
        }
        else if (m_angle == 90) {
            newY++;
        }
        else {
            newY--;
        }

        setPos(newX,newY);

        if (newX > 620 || newX<-35 || newY > 540 || newY < -35 ) {
            delete this;
        }
    }
}

int Sheep1::getAngle() const {
    return m_angle;
}

void Sheep1::setAngle(int angle){
    m_angle = angle % 360;
}

void Sheep1::setInLine(bool inLine) {
    m_inLine = inLine;
}

bool Sheep1::isInLine() {
    return m_inLine;
}
