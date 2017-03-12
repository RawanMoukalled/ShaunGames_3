#include "game1/game1.h"
#include "helper.h"
#include "gui/gamemainmenu.h"

#include <QDebug>
#include <QtGui>

/**
* \file game1.cpp
* \brief Contains the Sheep Line
*/

/**
* Sets the size of the window, initializes the graphic items, sets the layouts
* and connects buttons to their slots.
*/
Game1::Game1(int level, QWidget *parent) :
    QWidget(parent)
{
    setFixedSize(600,600);

    m_title = new QLabel("Sheep Line");
    m_game1Layout = new QVBoxLayout();
    m_exit = new QPushButton("Save and Exit");

    Helper::makeWidgetLarge(m_title);
    Helper::makeWidgetSmall(m_exit);

    m_level = level;
    m_gameScene = new Game1Scene(level);
    m_gameView = new QGraphicsView;

    setGame1Layout();
    setLayout(m_game1Layout);

    QObject::connect(m_exit, SIGNAL(clicked()), SLOT(goToMainMenu()));

    QObject::connect(m_gameScene, SIGNAL(Done()),SLOT(endGame()));
}

/**
* Frees allocated memory
*/
Game1::~Game1() {
    delete m_title;
    delete m_game1Layout;
    delete m_exit;
    delete m_gameScene;
    delete m_gameView;
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
    GameMainMenu *menu = new GameMainMenu(1);
    menu->show();
    close();
}

void Game1::endGame() {
    m_goBack = new QPushButton("Go Back");
    m_replay = new QPushButton("Replay");

    m_game1Layout->removeWidget(m_exit);
    delete m_exit;

    m_game1Layout->addWidget(m_goBack);
    m_game1Layout->addWidget(m_replay);

    m_game1Layout->setAlignment(m_goBack, Qt::AlignHCenter);
    m_game1Layout->setAlignment(m_replay, Qt::AlignHCenter);

    QObject::connect(m_goBack, SIGNAL(clicked()), SLOT(goToMainMenu()));
    QObject::connect(m_replay, SIGNAL(clicked()), SLOT(replay()));

}

void Game1::replay() {
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

    m_exit = new QPushButton("Save and Exit");
    m_game1Layout->addWidget(m_exit);
    m_game1Layout->setAlignment(m_exit, Qt::AlignHCenter);
    QObject::connect(m_exit, SIGNAL(clicked()), SLOT(goToMainMenu()));
    QObject::connect(m_gameScene, SIGNAL(Done()),SLOT(endGame()));
}

