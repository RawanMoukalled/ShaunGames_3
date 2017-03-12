#include "game1scene.h"
#include "helper.h"
#include <QDebug>
#include <QtGui>


/**
* Initializes variables and connections.
*/
Game1Scene::Game1Scene(int level, QObject *parent) :
    QGraphicsScene(parent)
{
    m_cannon = new Cannon;
    m_cannon->setFlag(QGraphicsItem::ItemIsFocusable);
    m_cannon->setFocus();

    m_current = new Sheep1(Helper::getRandomSheepNumber());
    m_current->setPos(330,250);
    m_next = new Sheep1(Helper::getRandomSheepNumber());
    m_next->setPos(200,200);

    m_barn = new Barn;
    m_barn->setFlag(QGraphicsItem::ItemIsFocusable);
    m_barn->setFocus();

    m_stopMoving = false;

    //int yValue = 600;
    int yValue = 500;

    srand(time(NULL));
    for(int i = 0; i < 50; i++) {
        Sheep1 * newSheep = new Sheep1(Helper::getRandomSheepNumber());
        newSheep->setPos(500, yValue);
        m_sheepLine.push_back(newSheep);        
        addItem(newSheep);
        yValue -= 40;
    }

    m_line_timer = new QTimer(this);
    connect(m_line_timer, SIGNAL(timeout()), this, SLOT(move_line()));

    m_line_timer->start(1000.0/(level+1));

    addItem(m_cannon);
    addItem(m_current);
    addItem(m_next);
    addItem(m_barn);
}

/**
* Frees allocated memory.
*/
Game1Scene::~Game1Scene() {
    delete m_cannon;
    delete m_current;
    delete m_next;
    for (QLinkedList<Sheep1*>::iterator sheep=m_sheepLine.begin(); sheep!=m_sheepLine.end(); ++sheep) {
        delete *sheep;
    }
    delete m_line_timer;
}

void Game1Scene::mousePressEvent(QGraphicsSceneMouseEvent *) {
    m_cannon->setFocus();
}

void Game1Scene::gameOver() {
    m_stopMoving = true;
}

/**
* Moves the sheep line.
*/
void Game1Scene::move_line() {
    QLinkedList<Sheep1*>::iterator i;
    int count = 0;

    if(!m_stopMoving) {
        for (i = m_sheepLine.begin(); i != m_sheepLine.end(); ++i) {
            //Get current sheep in the line and its position
            Sheep1 * curr = (*i);
            int currX = curr->x();
            int currY = curr->y();

            if(currX >= 500 && currY <= 250 ) {
                curr->setPos(currX, currY+10);
            }

            else{
                int angle_degrees = (curr->getAngle() + 3) % 360;
                curr->setAngle(angle_degrees);
                double rAngle = (angle_degrees/180.0)*Helper::PI;
                double newX = 300 + 200*cos(rAngle);
                double newY = 250 + 200*sin(rAngle);

                curr->setPos(newX, newY);
            }
            count++;
        }
    }
}
