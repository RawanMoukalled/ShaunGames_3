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

<<<<<<< HEAD
    m_number = number;
=======
    m_timer = new QTimer(this);
>>>>>>> 9221a0f5b27b7339abf5ce1b5249e13b93811251
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
    m_angle = angle;
    m_scene = scene();

    connect(m_timer, SIGNAL(timeout()), this, SLOT(firedMove()));
    m_timer->start(2);
}

void Sheep1::firedMove() {
    Game1Scene *sc = static_cast<Game1Scene*>(m_scene);

    if (sc->collidesWithSheepInLine(this)) {
        m_timer->stop();
        setRotation(0);
    }
    else {
        double newX = x() + cos(Helper::toRadians(m_angle));
        double newY = y() + sin(Helper::toRadians(m_angle));
        setPos(newX, newY);
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
