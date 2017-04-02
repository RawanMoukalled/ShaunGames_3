#include "game2/game2options.h"
#include "helper.h"
#include "game2/game2.h"
#include "gui/gamemainmenu.h"

/**
* \file game2options.cpp
* \brief Contains Game2Options class definition
*/

/**
* Initializes all buttons and text and shows them on the screen.
* Also initializes connections.
*/
Game2Options::Game2Options(QWidget *parent) :
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

    setConnections();
}

/**
* Frees allocated memory.
*/
Game2Options::~Game2Options() {
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
* Takes the user to game 2.
* Called after clicking any level button.
*/
void Game2Options::gotoGame(int level) {
    Game2 *g = new Game2(level);
    g->show();
    this->close();
}

/**
* Takes the user to the game main menu that corresponds to game 2.
* Called after clicking the corresponding button.
*/
void Game2Options::gotoGameMainMenu() {
    GameMainMenu *m = new GameMainMenu(2);
    m->show();
    this->close();
}

void Game2Options::setConnections() {
    m_signalMapper = new QSignalMapper(this);

    QObject::connect(m_easy, SIGNAL(clicked()), m_signalMapper, SLOT(map()));
    m_signalMapper->setMapping(m_easy, 0);

    QObject::connect(m_moderate, SIGNAL(clicked()), m_signalMapper, SLOT(map()));
    m_signalMapper->setMapping(m_easy, 1);

    QObject::connect(m_hard, SIGNAL(clicked()), m_signalMapper, SLOT(map()));
    m_signalMapper->setMapping(m_hard, 2);

    QObject::connect(m_signalMapper, SIGNAL(mapped(int)), this, SLOT(gotoGame2(int)));

    QObject::connect(m_back, SIGNAL(clicked()), this, SLOT(gotoGameMainMenu()));
}

/**
* Sets the overall layout of the window.
*/
void Game2Options::setMainLayout() {
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
void Game2Options::setLevelLayout() {
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
