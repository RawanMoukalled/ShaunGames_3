#include "game1/game1.h"
#include "helper.h"
#include "gui/gamemainmenu.h"
#include <QSqlQuery>

/**
* \file game1.cpp
* \brief Contains the Sheep Line
*/

/**
* Sets the size of the window, initializes the graphic items, sets the layouts
* and connects buttons to their slots.
*/
Game1::Game1(int level, bool resume, QWidget *parent) :
    QWidget(parent), m_level(level), m_justSaved(false)
{
    setFixedSize(600,600);

    m_title = new QLabel("Sheep Line (Level " + QString::number(level+1) + ")");
    m_game1Layout = new QVBoxLayout();

    if (Helper::getUserId() != 0) {
        m_exit = new QPushButton("Save and Exit");
    }
    else {
        m_exit = new QPushButton("Exit");
    }

    Helper::makeWidgetLarge(m_title);
    Helper::makeWidgetSmall(m_exit);

    m_gameScene = new Game1Scene(level, resume);
    m_gameView = new QGraphicsView;

    m_next = NULL;

    setGame1Layout();
    setLayout(m_game1Layout);

    QObject::connect(m_exit, SIGNAL(clicked()), SLOT(save()));
    QObject::connect(m_gameScene, SIGNAL(Done(bool)),SLOT(endGame(bool)));

}

/**
* Frees allocated memory
*/
Game1::~Game1() {
    delete m_title;
    delete m_game1Layout;
    delete m_gameScene;
    delete m_gameView;
    if (m_exit != NULL) {
        delete m_exit;
    }
    else {
        delete m_goBack;
        delete m_replay;
        if (m_next != NULL) {
            delete m_next;
        }
    }
}

/**
* Adds widgets and spaces for the layout of Sheep Line
*/
void Game1::setGame1Layout() {
    m_gameScene->setSceneRect(0,0,575,505);
    m_gameView->setScene(m_gameScene);
    m_gameView->setBackgroundBrush(QBrush(QImage("pictures/grass.jpg").scaledToHeight(550)));
    m_gameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_gameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_game1Layout->addWidget(m_title);
    m_game1Layout->addWidget(m_gameView);
    m_game1Layout->addWidget(m_exit);

    m_game1Layout->setAlignment(m_title, Qt::AlignHCenter);
    m_game1Layout->setAlignment(m_exit, Qt::AlignHCenter);
}

/**
* Goes to the main menu of Sheep Line
*/
void Game1::goToMainMenu() {
    close();
    GameMainMenu *menu = new GameMainMenu(1);
    menu->show();
}

/**
* Removes the save and exit button and adds the go back and replay
* buttons along with their connections
*/
void Game1::endGame(bool win) {
    m_goBack = new QPushButton("Go Back");
    m_replay = new QPushButton("Replay");

    m_game1Layout->removeWidget(m_exit);
    delete m_exit;
    m_exit = NULL;

    m_game1Layout->addWidget(m_goBack);
    m_game1Layout->addWidget(m_replay);

    m_game1Layout->setAlignment(m_goBack, Qt::AlignHCenter);
    m_game1Layout->setAlignment(m_replay, Qt::AlignHCenter);

    QObject::connect(m_goBack, SIGNAL(clicked()), SLOT(goToMainMenu()));
    QObject::connect(m_replay, SIGNAL(clicked()), SLOT(replay()));

    if(win){
        m_next = new QPushButton("Continue");
        m_game1Layout->addWidget(m_next);
        m_game1Layout->setAlignment(m_next, Qt::AlignHCenter);
        QObject::connect(m_next, SIGNAL(clicked()), SLOT(next()));
    }
}

/**
* Loads a new instance of the Game1 Scene
*/
void Game1::replay() {
    loadNewGame(true);
}

/**
* Proceed to the next level
*/
void Game1::next() {
    loadNewGame(false);
}

/**
* Saves and exits
*/
void Game1::save() {
    m_gameScene->freeze();
    int account = Helper::getUserId();
    if (account != 0) {
        Helper::deleteSavedGame(1);
        m_justSaved = true;
        bool opened = Helper::shaunDB.open();
        QSqlQuery query;
        if(opened) {
            query.prepare("INSERT INTO GAME1 (ACCOUNTID, LEVEL, SCORE, CANNONANGLE, CURRSHEEP, NEXTSHEEP, LASTPOS, SHEEPLINE)"
                          "VALUES (:accountID, :level, :score, :cannonAngle, :currSheep, :nextSheep, :lastPos, :sheepLine)");

            query.bindValue(":accountId", account);
            query.bindValue(":level", m_level);
            query.bindValue(":score", m_gameScene->getScore());
            query.bindValue(":cannonAngle", m_gameScene->getCannonAngle());
            query.bindValue(":currSheep", m_gameScene->getCurrentSheepNumber());
            query.bindValue(":nextSheep", m_gameScene->getNextSheepNumber());
            query.bindValue(":lastPos", m_gameScene->getLastLinePosition());
            query.bindValue(":sheepLine", m_gameScene->getInLineSheepNumbers());

            query.exec();
        }

        Helper::shaunDB.close();
    }
    goToMainMenu();
}

/**
* \brief Deletes the saved game on close
* \param bar The event triggered
*/
void Game1::closeEvent(QCloseEvent *bar) {
    if (!m_justSaved) {
        Helper::deleteSavedGame(1);
    }
    bar->accept();
}

/**
* Loads a new game of either the same level or the next
*/
void Game1::loadNewGame(bool sameLevel) {
    if(!sameLevel) {
        m_level++;
        m_title->setText("Sheep Line (Level " + QString::number(m_level+1) + ")");
    }

    delete m_gameScene;
    m_gameScene = new Game1Scene(m_level);
    m_gameView->setScene(m_gameScene);
    m_gameScene->setSceneRect(0,0,575,505);
    m_gameView->setBackgroundBrush(QBrush(QImage("pictures/grass.jpg").scaledToHeight(550)));
    m_gameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_gameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_game1Layout->removeWidget(m_goBack);
    delete m_goBack;

    m_game1Layout->removeWidget(m_replay);
    delete m_replay;

    if(!(m_next == NULL)) {
        m_game1Layout->removeWidget(m_next);
        delete m_next;
        m_next = NULL;
    }

    m_exit = new QPushButton("Save and Exit");
    m_game1Layout->addWidget(m_exit);
    m_game1Layout->setAlignment(m_exit, Qt::AlignHCenter);
    QObject::connect(m_exit, SIGNAL(clicked()), SLOT(goToMainMenu()));
    QObject::connect(m_gameScene, SIGNAL(Done(bool)),SLOT(endGame(bool)));
}


