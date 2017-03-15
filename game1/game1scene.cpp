#include "game1scene.h"
#include "helper.h"
#include <QtGui>
#include <QGraphicsScene>
#include <QVector>
#include <QSet>

/**
* Initializes variables and connections.
*/
Game1Scene::Game1Scene(int level, QObject *parent) :
    QGraphicsScene(parent), m_score(0)
{
    m_scoreDisplay = new QLCDNumber(4);

    m_cannon = new Cannon;
    m_cannon->setFlag(QGraphicsItem::ItemIsFocusable);
    m_cannon->setFocus();

    m_current = new Sheep1(Helper::getRandomSheepNumber(), false);
    m_current->setPos(334,247);
    m_current->setRotation(345);
    m_next = new Sheep1(Helper::getRandomSheepNumber(), false);
    m_next->setPos(285,235);

    m_barn = new Barn;

    int yValue = 0;
    int prevRand;
    int currRand = Helper::getRandomSheepNumber();

    for(int i = 0; i < 50; ++i) {
        Sheep1 *newSheep = new Sheep1(currRand, true);
        newSheep->setPos(500, yValue);
        m_sheepLine.push_back(newSheep);        
        addItem(newSheep);
        yValue -= 40;

        prevRand = currRand;
        do {
            currRand = Helper::getRandomSheepNumber();
        }
        while(prevRand+currRand == 10);
    }

    m_line_timer = new QTimer(this);
    connect(m_line_timer, SIGNAL(timeout()), this, SLOT(move_line()));

    m_line_timer->start(-29.091*level+818.182);

    addWidget(m_scoreDisplay);
    m_scoreDisplay->move(20,20);

    QPalette lcdPalette = m_scoreDisplay->palette();
    lcdPalette.setColor(QPalette::Background, QColor(170, 255, 0));
    lcdPalette.setColor(QPalette::WindowText, QColor(85, 85, 255));
    lcdPalette.setColor(QPalette::Light, QColor(255, 0, 0));
    lcdPalette.setColor(QPalette::Dark, QColor(255, 0, 0));

    m_scoreDisplay->setPalette(lcdPalette);

    addItem(m_cannon);
    addItem(m_current);
    addItem(m_next);
    addItem(m_barn);
}

/**
* Frees allocated memory.
*/
Game1Scene::~Game1Scene() {
    delete m_scoreDisplay;
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

void Game1Scene::gameOver(bool win) {
    m_gameOverPicture = new GameOver(win);

    addItem(m_gameOverPicture);

    emit Done(win);
    m_cannon->setEnabled(false);
    m_line_timer->stop();
}

/**
* Moves current sheep.
* Called when the cannon rotates.
*/
void Game1Scene::moveCurrentSheep(bool toRight) {
    double angleInDegrees = m_current->rotation();
    if (toRight) {
        angleInDegrees = angleInDegrees + 5;
    }
    else {
        angleInDegrees = angleInDegrees - 5;
    }
    m_current->setAngle(angleInDegrees+15);
    int r = 45;
    double a = Helper::toRadians(angleInDegrees);
    double x = 290 + r*cos(a);
    double y = 255 + r*sin(a);
    m_current->setPos(x,y);
    m_current->setRotation(angleInDegrees);
}

/**
* Releases the sheep and makes it move in a straight line.
*/
void Game1Scene::fireSheep() {
    Sheep1 *fired = m_current;

    m_current = m_next;
    m_next = new Sheep1(Helper::getRandomSheepNumber(), false);

    m_next->setPos(m_current->pos());
    m_next->setZValue(1);
    addItem(m_next);

    m_current->setPos(fired->pos());
    m_current->setRotation(fired->rotation());

    int angle = m_cannon->rotation();

    fired->fire(angle);
}

/**
* Returns whether the given item collides with a sheep in the line.
*/
bool Game1Scene::collidesWithSheepInLine(QGraphicsItem *item) {
    QList<QGraphicsItem*> collisionList = collidingItems(item);

    //check all the colliding items with the list
    QList<QGraphicsItem*>::iterator i;
    for (i = collisionList.begin(); i != collisionList.end(); ++i) {
        if (*i != m_cannon && *i != m_barn) {
            Sheep1 *tempSheep = static_cast<Sheep1*>(*i);
            if(tempSheep->isInLine()){
                return true;
            }
        }
    }
    return false;
}

/**
* Returns the player score for the current game.
* For each destroyed sheep, the player is awarded 10 points.
* When the player wins the game, they are awarded
            m_scoreDisplay->display(m_score); 1 point per remaining sheep in-line move.
*/
int Game1Scene::getScore() const {
    return m_score;
}

/**
* Moves the sheep in the line according to their position on the screen
*/
void Game1Scene::move_line() {
    bool separate = false;
    QVector<Sheep1*> toInsert;
    QVector<QLinkedList<Sheep1*>::iterator> insertPos;
    QSet<Sheep1*> toDelete;

    Sheep1 *last = NULL;

    //check every sheep in the line

    if (m_sheepLine.size() > 1) {
        for (QLinkedList<Sheep1*>::iterator i = m_sheepLine.end()-1; i != m_sheepLine.begin()-1; --i) {

            //Get current sheep in the line
            Sheep1 *curr = *i;

            if (i == m_sheepLine.end()-1) {
                Sheep1 *prev = *(i-1);
                if(prev->getNumber() + curr->getNumber() == 10) {
                    toDelete.insert(prev);
                    toDelete.insert(curr);
                }
            }
            else if (i == m_sheepLine.begin()) {
                Sheep1 *next = *(i+1);
                if(next->getNumber() + curr->getNumber() == 10) {
                    toDelete.insert(next);
                    toDelete.insert(curr);
                }
            }
            else {
                Sheep1 *prev = *(i-1);
                Sheep1 *next = *(i+1);
                if(prev->getNumber() + curr->getNumber() == 10) {
                    toDelete.insert(prev);
                    toDelete.insert(curr);
                }
                if(next->getNumber() + curr->getNumber() == 10) {
                    toDelete.insert(next);
                    toDelete.insert(curr);
                }
            }
        }

        for (QSet<Sheep1*>::iterator i = toDelete.begin(); i != toDelete.end(); ++i) {
            Sheep1 *del = *i;
            m_sheepLine.removeOne(del);
            removeItem(del);
            m_score = m_score + 10;
            m_scoreDisplay->display(m_score);
            last = del;
        }
    }


    //if all the sheep are gone
    if(m_sheepLine.isEmpty()) {
        addItem(last);
        do {
            last->moveInLine(10);
            m_score = m_score + 1;
            m_scoreDisplay->display(m_score);
        }
        while(collidingItems(last).empty());

        removeItem(last);
        qDeleteAll(toDelete);
        gameOver(true);
        return;
    }

    qDeleteAll(toDelete);

    for (QLinkedList<Sheep1*>::iterator i = m_sheepLine.end()-2; i != m_sheepLine.begin()-1; --i) {
        Sheep1 *curr = *i;
        Sheep1 *next = *(i+1);
        if (curr->inLineDistanceTo(next) > 41) {
            curr->setAngle(next->getAngle());
            curr->setPos(next->pos());
            curr->moveInLine(40);
        }
    }

    for (QLinkedList<Sheep1*>::iterator i = m_sheepLine.end()-1; i != m_sheepLine.begin()-1; --i) {
        Sheep1 *curr = *i;
        //check if a sheep has collided with it
        QList<QGraphicsItem*> items = this->collidingItems(curr);
        QList<QGraphicsItem*>::iterator j;


        for (j = items.begin(); j != items.end(); ++j) {
            Sheep1 *tempSheep = static_cast<Sheep1*>(*j);

            //sheep was fired
            if(!tempSheep->isInLine()) {
                separate = true;
                toInsert.append(tempSheep);
                if (i == m_sheepLine.end()-1) {
                    insertPos.append(i);
                }
                else {
                    insertPos.append(i+1);
                }
                tempSheep->setInLine(true);
            }
        }

        if (separate) {
            curr->moveInLine(40*toInsert.size()+10);
        }
        else {
            curr->moveInLine(10);
        }
    }

    int size = toInsert.size();
    for (int i = 0; i < size; ++i) {
        Sheep1 *newSheep = toInsert.at(i);
        QLinkedList<Sheep1*>::iterator pos = insertPos.at(i);

        m_sheepLine.insert(pos, newSheep);
        newSheep->setRotation(0);

        Sheep1 *prevSheep = *pos;

        newSheep->setAngle(prevSheep->getAngle());
        //newSheep->setInLine(true);
        newSheep->setPos(prevSheep->x(), prevSheep->y());
        newSheep->moveInLine(40);
    }
}

