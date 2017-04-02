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
Game2::Game2(QWidget *parent) :
    QWidget(parent)
{
    setFixedSize(600,600);
    m_title = new QLabel("Trap the Sheep");
    m_Game2Layout = new QVBoxLayout();
    m_exit = new QPushButton("Save and Exit");

    Helper::makeWidgetLarge(m_title);
    Helper::makeWidgetSmall(m_exit);

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

    for (QVector<QSpacerItem*>::iterator sp=m_spacerItems.begin(); sp!=m_spacerItems.end(); ++sp) {
        delete *sp;
    }
}

/**
* Adds widgets and spaces for the layout of Sheep Line.
*/
void Game2::setGame2Layout() {
    m_Game2Layout->addWidget(m_title);
    m_Game2Layout->addItem(new QSpacerItem(600,500));
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
