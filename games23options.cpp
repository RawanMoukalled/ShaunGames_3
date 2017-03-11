#include "games23options.h"
#include "helper.h"
#include "game2/game2.h"
#include "game3/game3.h"
#include "gui/gamemainmenu.h"

/**
* \file games23options.cpp
* \brief Contains Games23Options class definition
*/

/**
* Initializes all buttons and text and shows them on the screen.
* Also initializes connections.
*/
Games23Options::Games23Options(int gameNumber, QWidget *parent) :
    QWidget(parent), m_gameNumber(gameNumber)
{
    setFixedSize(600,600);
    m_instructions = new QLabel("Please pick a level:");
    Helper::makeWidgetLarge(m_instructions);

    m_easy = new QPushButton("Easy");
    m_medium = new QPushButton("Medium");
    m_hard = new QPushButton("Hard");

    Helper::makeWidgetLarge(m_easy);
    m_easy->setFixedHeight(50);
    Helper::makeWidgetLarge(m_medium);
    m_medium->setFixedHeight(50);
    Helper::makeWidgetLarge(m_hard);
    m_hard->setFixedHeight(50);

    m_back = new QPushButton("Back to Game Menu");
    m_back->setFixedWidth(200);
    Helper::makeWidgetSmall(m_back);

    m_mainLayout = new QVBoxLayout;
    m_levelLayout = new QHBoxLayout;

    setMainLayout();
    setLayout(m_mainLayout);

    QObject::connect(m_easy, SIGNAL(clicked()), this, SLOT(gotoGame()));
    QObject::connect(m_medium, SIGNAL(clicked()), this, SLOT(gotoGame()));
    QObject::connect(m_hard, SIGNAL(clicked()), this, SLOT(gotoGame()));
    QObject::connect(m_back, SIGNAL(clicked()), this, SLOT(gotoGameMainMenu()));
}

/**
* Takes the user to game 2 or 3, depending on his/her initial selection.
* Called after clicking any level button.
*/
void Games23Options::gotoGame() {
    if (m_gameNumber==2) {
        Game2 *g = new Game2;
        g->show();
    }
    else {
        Game3 *g = new Game3;
        g->show();
    }
    this->close();
}

/**
* Takes the user to the game main menu that corresponds to game 2 or 3.
* Called after clicking the corresponding button.
*/
void Games23Options::gotoGameMainMenu() {
    GameMainMenu *m = new GameMainMenu(m_gameNumber);
    m->show();
    this->close();
}

/**
* Sets the overall layout of the window.
*/
void Games23Options::setMainLayout() {
    m_mainLayout->addWidget(m_instructions);
    setLevelLayout();
    m_mainLayout->addItem(m_levelLayout);
    m_mainLayout->addItem(new QSpacerItem(20,30));
    m_mainLayout->addWidget(m_back);

    m_mainLayout->setAlignment(m_instructions, Qt::AlignCenter);
    m_mainLayout->setAlignment(m_back, Qt::AlignCenter);
}

/**
* Sets the layout of the level buttons.
*/
void Games23Options::setLevelLayout() {
    m_levelLayout->addItem(new QSpacerItem(100,100));
    m_levelLayout->addWidget(m_easy);
    m_levelLayout->addItem(new QSpacerItem(20,20));
    m_levelLayout->addWidget(m_medium);
    m_levelLayout->addItem(new QSpacerItem(20,20));
    m_levelLayout->addWidget(m_hard);
    m_levelLayout->addItem(new QSpacerItem(100,100));
}
