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
    QWidget(parent)
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

}

/**
* Frees allocated memory.
*/
Game3::~Game3() {
    delete m_title;
    delete m_Game3Layout;
    delete m_exit;
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
* \brief Goes back to the Main meny of Dots and Lines
*/
void Game3::goToMainMenu() {
    GameMainMenu *menu = new GameMainMenu(3);
    menu->show();
    close();
}
