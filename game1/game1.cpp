#include "game1/game1.h"
#include "helper.h"
#include "gui/gamemainmenu.h"

/**
* \file game1.cpp
* \brief Contains the Sheep Line
*/

/**
* \brief Constructor for Sheep Line
*
* Sets the size of the window, initializes the graphic items, sets the layouts
* and connects buttons to their slots.
*/
Game1::Game1(int level, QWidget *parent) :
    QWidget(parent), m_level(level)
{
    setFixedSize(600,600);

    m_title = new QLabel("Sheep Line");
    m_game1Layout = new QVBoxLayout();
    m_exit = new QPushButton("Save and Exit");

    Helper::makeWidgetLarge(m_title);
    Helper::makeWidgetSmall(m_exit);

    m_gameScene = new Game1Scene;
    m_gameView = new QGraphicsView;

    setGame1Layout();
    setLayout(m_game1Layout);

    QObject::connect(m_exit, SIGNAL(clicked()), SLOT(goToMainMenu()));
}

/**
*brief Adds widgets and spaces for the layout of Sheep Line
*/
void Game1::setGame1Layout() {
    m_gameScene->setSceneRect(0,0,600,500);
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
* \brief Goes to the main menu of Sheep Line
*/
void Game1::goToMainMenu() {
    GameMainMenu *menu = new GameMainMenu(1);
    menu->show();
    close();
}
