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
    connect(m_timer, SIGNAL(timeout()), this, SLOT(takeSheep()));
    m_timer->start(100);
}

void Barn::takeSheep() {
    if(!scene()->collidingItems(this).isEmpty()) {
        static_cast<Game1Scene*>(scene())->gameOver();
    }
}
