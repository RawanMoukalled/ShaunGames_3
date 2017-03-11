#include "game3/game3.h"
#include "helper.h"
#include "gui/gamemainmenu.h"

/**
* \file game3.cpp
* \brief Contains the Dots and Lines game
*/

/**
* \brief Constructor for Dots and Lines
*
* Sets the size of the window, initializes the graphic items, sets the layouts
* and connects buttons to their slots
*/
Game3::Game3(QWidget *parent) :
    QWidget(parent)
{
    setFixedSize(600,600);
    m_title = new QLabel("Dots and Lines");
    m_Game3Layout = new QVBoxLayout();
    m_exit = new QPushButton("Save and Exit");

    Helper::makeWidgetLarge(m_title);
    Helper::makeWidgetSmall(m_exit);

    setGame3Layout();
    setLayout(m_Game3Layout);

    QObject::connect(m_exit, SIGNAL(clicked()), SLOT(goToMainMenu()));

}

/**
* \brief Adds widgets and spaces for the layout of Dots and Lines
*/

void Game3::setGame3Layout() {
    m_Game3Layout->addWidget(m_title);
    m_Game3Layout->addItem(new QSpacerItem(600,500));
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
