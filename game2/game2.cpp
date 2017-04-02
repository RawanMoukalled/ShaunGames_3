#include "game2/game2.h"
#include "helper.h"
#include "gui/gamemainmenu.h"

/**
* \file game2.cpp
* \brief Contains the Trap the Sheep game
*/

/**
* Sets the size of the window, initializes the graphic items, sets the layouts
* and connects buttons to their slots.
*/
Game2::Game2(Difficulty difficulty, QWidget *parent) :
    QWidget(parent)
{
    setFixedSize(600,600);
    m_title = new QLabel("Trap the Sheep");
    m_Game2Layout = new QVBoxLayout();
    m_exit = new QPushButton("Save and Exit");

    Helper::makeWidgetLarge(m_title);
    Helper::makeWidgetSmall(m_exit);

    m_difficulty = difficulty;
    m_gameScene = new Game2Scene(difficulty);
    m_gameView = new QGraphicsView;

    setGame2Layout();
    setLayout(m_Game2Layout);

    QObject::connect(m_exit, SIGNAL(clicked()), SLOT(goToMainMenu()));

}

/**
* Frees allocated memory.
*/
Game2::~Game2() {
    delete m_title;
    delete m_Game2Layout;
    delete m_exit;
    delete m_gameScene;
    delete m_gameView;

    for (QVector<QSpacerItem*>::iterator sp=m_spacerItems.begin(); sp!=m_spacerItems.end(); ++sp) {
        delete *sp;
    }
}

/**
* Adds widgets and spaces for the layout of Sheep Line.
*/
void Game2::setGame2Layout() {
    m_gameScene->setSceneRect(0,0,575,505);
    m_gameView->setScene(m_gameScene);
    m_gameView->setBackgroundBrush(QBrush(QImage("pictures/grass.jpg").scaledToHeight(550)));
    m_gameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_gameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_Game2Layout->addWidget(m_title);
    m_Game2Layout->addWidget(m_gameView);
    m_Game2Layout->addWidget(m_exit);

    m_Game2Layout->setAlignment(m_title, Qt::AlignHCenter);
    m_Game2Layout->setAlignment(m_exit, Qt::AlignHCenter);
}

/**
* Goes to the main menu of Sheep Line
*/
void Game2::goToMainMenu() {
    GameMainMenu *menu = new GameMainMenu(2);
    menu->show();
    close();
}
