#include "game3/game3.h"
#include "helper.h"
#include "gui/gamemainmenu.h"

/**
* \file game3.cpp
* \brief Contains the Dots and Lines game
*/

/**
* Sets the size of the window, initializes the graphic items, sets the layouts
* and connects buttons to their slots
*/
Game3::Game3(Difficulty difficulty, Size size, QWidget *parent) :
    QWidget(parent), m_difficulty(difficulty), m_size(size)
{
    setFixedSize(600,600);
    m_title = new QLabel("Dots and Lines");
    m_Game3Layout = new QVBoxLayout();
    m_exit = new QPushButton("Save and Exit");

    Helper::makeWidgetLarge(m_title);
    Helper::makeWidgetSmall(m_exit);

    m_gameScene = new Game3Scene(difficulty, size);
    m_gameView = new QGraphicsView;

    setGame3Layout();
    setLayout(m_Game3Layout);

    QObject::connect(m_exit, SIGNAL(clicked()), SLOT(goToMainMenu()));
    QObject::connect(m_gameScene, SIGNAL(done()),SLOT(endGame()));
}

/**
* Frees allocated memory.
*/
Game3::~Game3() {
    delete m_title;
    delete m_Game3Layout;
    if (m_exit != NULL) {
        delete m_exit;
    }
    else {
        delete m_goBack;
        delete m_replay;
    }
    delete m_gameView;
    delete m_gameScene;
}

/**
* Adds widgets and spaces for the layout of Dots and Lines.
*/
void Game3::setGame3Layout() {
    m_gameScene->setSceneRect(0,0,575,505);
    m_gameView->setScene(m_gameScene);
    //m_gameView->setBackgroundBrush(QBrush(QImage("pictures/grass.jpg").scaledToHeight(550)));
    m_gameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_gameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_Game3Layout->addWidget(m_title);
    m_Game3Layout->addWidget(m_gameView);
    m_Game3Layout->addWidget(m_exit);

    m_Game3Layout->setAlignment(m_title, Qt::AlignHCenter);
    m_Game3Layout->setAlignment(m_exit, Qt::AlignHCenter);
}

/**
* Reloads game
*/
void Game3::replay() {
    delete m_gameScene;
    m_gameScene = new Game3Scene(m_difficulty, m_size);
    m_gameView->setScene(m_gameScene);
    m_gameScene->setSceneRect(0,0,575,505);
    m_gameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_gameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    m_Game3Layout->removeWidget(m_goBack);
    delete m_goBack;

    m_Game3Layout->removeWidget(m_replay);
    delete m_replay;

    m_exit = new QPushButton("Save and Exit");
    m_Game3Layout->addWidget(m_exit);
    m_Game3Layout->setAlignment(m_exit, Qt::AlignHCenter);
    QObject::connect(m_exit, SIGNAL(clicked()), SLOT(goToMainMenu()));
    QObject::connect(m_gameScene, SIGNAL(done()),SLOT(endGame()));
}

/**
* Removes the save and exitbutton and adds the go back and replay
* buttons along with their connections
*/
void Game3::endGame() {
    m_goBack = new QPushButton("Go Back");
    m_replay = new QPushButton("Replay");

    m_Game3Layout->removeWidget(m_exit);
    delete m_exit;
    m_exit = NULL;

    m_Game3Layout->addWidget(m_goBack);
    m_Game3Layout->addWidget(m_replay);

    m_Game3Layout->setAlignment(m_goBack, Qt::AlignHCenter);
    m_Game3Layout->setAlignment(m_replay, Qt::AlignHCenter);

    QObject::connect(m_goBack, SIGNAL(clicked()), SLOT(goToMainMenu()));
    QObject::connect(m_replay, SIGNAL(clicked()), SLOT(replay()));
}

/**
* \brief Goes back to the Main meny of Dots and Lines
*/
void Game3::goToMainMenu() {
    GameMainMenu *menu = new GameMainMenu(3);
    menu->show();
    close();
}
