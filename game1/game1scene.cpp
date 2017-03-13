#include "game1scene.h"
#include "helper.h"
#include <QDebug>
#include <QtGui>
#include <QGraphicsScene>


/**
* Initializes variables and connections.
*/
Game1Scene::Game1Scene(int level, QObject *parent) :
    QGraphicsScene(parent)
{
    m_cannon = new Cannon;
    m_cannon->setFlag(QGraphicsItem::ItemIsFocusable);
    m_cannon->setFocus();

    m_current = new Sheep1(Helper::getRandomSheepNumber(), false);
    m_current->setPos(334,247);
    m_current->setRotation(345);
    m_next = new Sheep1(Helper::getRandomSheepNumber(), false);
    m_next->setPos(285,235);

    m_barn = new Barn;

    m_stopMoving = false;

    int yValue = 0;

    srand(time(NULL));
    for(int i = 0; i < 50; i++) {
        Sheep1 * newSheep = new Sheep1(Helper::getRandomSheepNumber(), true);
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

    m_gameOverPicture = new GameOver;

    addItem(m_gameOverPicture);

    m_stopMoving = true;
    emit Done();
    m_cannon->setEnabled(false);
}

/**
* Moves current sheep.
* Called when the cannon rotates.
*/
void Game1Scene::moveCurrentSheep(bool toRight) {
    int angleInDegrees = m_current->rotation();
    if (toRight) {
        angleInDegrees = angleInDegrees + 5;
    }
    else {
        angleInDegrees = angleInDegrees - 5;
    }
    m_current->setAngle(angleInDegrees);
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
    addItem(m_next);

    m_current->setPos(fired->pos());
    m_current->setRotation(fired->rotation());

    fired->setRotation(0);

    int angle = m_cannon->rotation();

    double x = fired->x();
    double y = fired->y();

    double a = tan(Helper::toRadians(angle));
    double b = y - a*x;

    while(collidingItems(fired).empty() || collidingItems(fired).contains(m_barn) ||
          collidingItems(fired).contains(m_cannon) || collidingItems(fired).contains(m_current)) {
        if (angle < 90 || angle > 270) {
            //qDebug() << angle << a << b << x << y;
            x++;
            y = a*x+b;
        }
        else if (angle > 90 && angle < 270) {
            x--;
            y = a*x+b;
        }
        else if (angle == 90) {
            y++;
        }
        else {
            y--;
        }
        qDebug() << x << y;

        fired->setPos(x,y);

        if (x > 620 || x<-35 || y > 540 || y < -35 ) {
            delete fired;
            break;
        }

        Helper::delay(5);
    }
}

/**
* Moves the sheep in the line according to their position on the screen
*/
void Game1Scene::move_line() {

    bool separate = false;

    //check every sheep in the line
    QLinkedList<Sheep1*>::iterator i;
    int count = 0;
    if(!m_stopMoving) {
        for (i = m_sheepLine.end()-1; i != m_sheepLine.begin()-1; --i) {
            //Get current sheep in the line and its position
            Sheep1 * curr = (*i);
            int currX = curr->x();
            int currY = curr->y();

            int incrementStraight;
            int incrementCircular;

            if(!separate){
                incrementStraight = 10;
                incrementCircular = 3;
            }else{
                incrementStraight = 40;
                incrementCircular = 20;
            }


            //no collision, proceeding normally
            //straight line
            if(currX >= 500 && currY <= 250 ) {
                curr->setPos(currX, currY+incrementStraight);
            }
            //in the circular path
            else{
                int angle_degrees = (curr->getAngle() + incrementCircular) % 360;
                curr->setAngle(angle_degrees);
                double rAngle = (angle_degrees/180.0)*Helper::PI;
                double newX = 300 + 200*cos(rAngle);
                double newY = 250 + 200*sin(rAngle);

                curr->setPos(newX, newY);
            }

            //check if a sheep has collided with it
            QList<QGraphicsItem*> items = this->collidingItems(curr);
            QList<QGraphicsItem*>::iterator j;
                for (j = items.begin(); j != items.end(); ++j) {
                    Sheep1 *tempSheep = static_cast<Sheep1*>((*j));
                    //sheep was fired
                    if(!tempSheep->isInLine()) {
                        //qDebug() << curr->m_number;
                        separate = true;
                        m_line_timer->stop();
                    }
                }

            count++;
        }
    }
}
