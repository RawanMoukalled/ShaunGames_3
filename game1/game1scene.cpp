#include "game1scene.h"

Game1Scene::Game1Scene(QObject *parent) :
    QGraphicsScene(parent)
{
    m_cannon = new Cannon;
    m_cannon->setFlag(QGraphicsItem::ItemIsFocusable);
    m_cannon->setFocus();
    m_cannon->setPos(300,300);

    addItem(m_cannon);
}
