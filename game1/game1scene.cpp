#include "game1scene.h"


Game1Scene::Game1Scene(int level, QObject *parent) :
    QGraphicsScene(parent)
{
    m_cannon = new Cannon;
    m_cannon->setFlag(QGraphicsItem::ItemIsFocusable);
    m_cannon->setFocus();

    int yValue = 600;
    srand(time(NULL));
    for(int i = 0; i < 50; i++) {
        Sheep1 * newSheep = new Sheep1(rand()%9 + 1);
        newSheep->setPos(500, yValue);
        m_sheepLine.push_back(newSheep);        
        addItem(newSheep);
        yValue -= 44;
    }

    m_line_timer = new QTimer(this);
    connect(m_line_timer, SIGNAL(timeout()), this, SLOT(move_line()));
    m_line_timer->start(300);

    addItem(m_cannon);
}

void Game1Scene::move_line(){
    QLinkedList<Sheep1*>::iterator i;
    for (i = m_sheepLine.begin(); i != m_sheepLine.end(); ++i) {
        (*i)->setPos((*i)->x(), (*i)->y()+10);
    }
}
