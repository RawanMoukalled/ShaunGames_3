#include "game1scene.h"

Game1Scene::Game1Scene(QObject *parent) :
    QGraphicsScene(parent)
{
    m_cannon = new Cannon;
    m_cannon->setFlag(QGraphicsItem::ItemIsFocusable);
    m_cannon->setFocus();

    addItem(m_cannon);
}
