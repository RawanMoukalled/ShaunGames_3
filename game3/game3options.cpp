#include "game3options.h"
#include "helper.h"
#include "game3/game3.h"
#include "gui/gamemainmenu.h"

/**
* \file game3options.cpp
* \brief Contains Game3Options class definition
*/

/**
* Initializes all buttons and text and shows them on the screen.
* Also initializes connections.
*/
Game3Options::Game3Options(QWidget *parent) :
    QWidget(parent)
{
    setFixedSize(600,600);
    m_instructions = new QLabel("Please pick a level:");
    Helper::makeWidgetLarge(m_instructions);

    m_easy = new QPushButton("Easy");
    m_moderate = new QPushButton("Moderate");
    m_hard = new QPushButton("Hard");

    Helper::makeWidgetLarge(m_easy);
    m_easy->setFixedHeight(50);
    Helper::makeWidgetLarge(m_moderate);
    m_moderate->setFixedHeight(50);
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
    QObject::connect(m_moderate, SIGNAL(clicked()), this, SLOT(gotoGame()));
    QObject::connect(m_hard, SIGNAL(clicked()), this, SLOT(gotoGame()));
    QObject::connect(m_back, SIGNAL(clicked()), this, SLOT(gotoGameMainMenu()));
}

/**
* Frees allocated memory.
*/
Game3Options::~Game3Options() {
    delete m_instructions;
    delete m_easy;
    delete m_moderate;
    delete m_hard;
    delete m_back;
    delete m_mainLayout;
    delete m_levelLayout;

    for (QVector<QSpacerItem*>::iterator sp=m_spacerItems.begin(); sp!=m_spacerItems.end(); ++sp) {
        delete *sp;
    }
}

/**
* Takes the user to game 3.
* Called after clicking any level button.
*/
void Game3Options::gotoGame() {
    Game3 *g = new Game3;
    g->show();
    this->close();
}

/**
* Takes the user to the game main menu that corresponds to game 3.
* Called after clicking the corresponding button.
*/
void Game3Options::gotoGameMainMenu() {
    GameMainMenu *m = new GameMainMenu(3);
    m->show();
    this->close();
}

/**
* Sets the overall layout of the window.
*/
void Game3Options::setMainLayout() {
    m_mainLayout->addWidget(m_instructions);
    setLevelLayout();
    m_mainLayout->addItem(m_levelLayout);
    QSpacerItem *sp = new QSpacerItem(20,30);
    m_spacerItems.push_back(sp);
    m_mainLayout->addItem(sp);
    m_mainLayout->addWidget(m_back);

    m_mainLayout->setAlignment(m_instructions, Qt::AlignCenter);
    m_mainLayout->setAlignment(m_back, Qt::AlignCenter);
}

/**
* Sets the layout of the level buttons.
*/
void Game3Options::setLevelLayout() {
    QSpacerItem *sp = new QSpacerItem(100,100);
    m_spacerItems.push_back(sp);
    m_levelLayout->addItem(sp);
    m_levelLayout->addWidget(m_easy);

    sp = new QSpacerItem(20,20);
    m_spacerItems.push_back(sp);
    m_levelLayout->addItem(sp);
    m_levelLayout->addWidget(m_moderate);

    sp = new QSpacerItem(20,20);
    m_spacerItems.push_back(sp);
    m_levelLayout->addItem(sp);
    m_levelLayout->addWidget(m_hard);

    sp = new QSpacerItem(100,100);
    m_spacerItems.push_back(sp);
    m_levelLayout->addItem(sp);
}
