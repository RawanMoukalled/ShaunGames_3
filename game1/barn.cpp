#include "barn.h"
#include "helper.h"
#include "game1scene.h"
#include "game1/sheep1.h"
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
        QList<QGraphicsItem*> items = scene()->collidingItems(this);

        if(!items.isEmpty()) {
            //check all the colliding items with the barn
            QList<QGraphicsItem*>::iterator i;
            for (i = items.begin(); i != items.end(); ++i) {

                Sheep1 *tempSheep = static_cast<Sheep1*>((*i));

                //game over only when sheep from the line enter, not one shot
                //from the cannon
                if(tempSheep->isInLine()){
                    m_collisionDone = true;
                    static_cast<Game1Scene*>(scene())->gameOver();
                }
            }
        }
    }
}
