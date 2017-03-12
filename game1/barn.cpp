#include "barn.h"
#include "helper.h"
#include "game1scene.h"
#include <QGraphicsScene>
#include <QList>

Barn::Barn(QObject *parent) :
    QObject(parent)
{
    this->setPixmap(QPixmap("pictures/barn.png"));
    setPos(350,30);
    setScale(0.04);

    m_timer = new  QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(sheepIn()));
    m_timer->start(100);

    m_collisionDone = false;
}

void Barn::sheepIn() {

    if(!m_collisionDone) {
        if(!scene()->collidingItems(this).isEmpty()) {
            m_collisionDone = true;
            static_cast<Game1Scene*>(scene())->gameOver();
        }
    }
}
