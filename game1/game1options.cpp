#include "game1/game1options.h"
#include "helper.h"
#include "gui/gamemainmenu.h"
#include "game1/game1.h"

/**
* \file game1options.cpp
* \brief Contains Game1Options class definition
*/

/**
* Initializes all buttons and text and shows them on the screen.
* Also initializes connections.
*/
Game1Options::Game1Options(QWidget *parent) :
    QWidget(parent)
{
    setFixedSize(600,600);
    m_instructions = new QLabel("Please pick a level:");
    Helper::makeWidgetLarge(m_instructions);

    for (int i=0; i<25; ++i) {
        m_levels[i] = new QPushButton(QString::number(i+1));
        m_levels[i]->setFixedSize(60,60);
        //m_levels[i]->setDisabled(true);
   }
   // m_levels[0]->setEnabled(true);

    m_back = new QPushButton("Back to Game Menu");
    m_back->setFixedWidth(200);
    Helper::makeWidgetSmall(m_back);

    m_mainLayout = new QVBoxLayout;
    m_levelLayout = new QGridLayout;

    setMainLayout();
    setLayout(m_mainLayout);
    setConnections();
}

/**
* Frees allocated memory
*/
Game1Options::~Game1Options() {
    delete m_instructions;
    for (int i=0; i<25; ++i) {
        delete m_levels[i];
    }
    delete m_back;
    delete m_mainLayout;
    delete m_levelLayout;
    delete m_signalMapper;
}

/**
* Enables the given level. Called when a user wins the previous level.
*/
void Game1Options::enable(int level) {
    m_levels[level]->setEnabled(true);
}

/**
* Takes the user to the game main menu that corresponds to game 1.
* Called after clicking the corresponding button.
*/
void Game1Options::gotoGameMainMenu() {
    GameMainMenu *op = new GameMainMenu(1);
    op->show();
    this->close();
}

/**
* Takes the user to game 1.
* Called after clicking any level button.
*/
void Game1Options::gotoGame1(int level) {
    Game1 *g1 = new Game1(level);
    g1->show();
    this->close();
}

/**
* Sets the connections of all button clicks of the widget.
*/
void Game1Options::setConnections() {
    m_signalMapper = new QSignalMapper(this);

    for (int i=0; i<25; ++i) {
        QObject::connect(m_levels[i], SIGNAL(clicked()), m_signalMapper, SLOT(map()));
        m_signalMapper->setMapping(m_levels[i], i);
    }

    QObject::connect(m_signalMapper, SIGNAL(mapped(int)), this, SLOT(gotoGame1(int)));
    QObject::connect(m_back, SIGNAL(clicked()), this, SLOT(gotoGameMainMenu()));
}

/**
* Sets the overall layout of the window.
*/
void Game1Options::setMainLayout() {
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
void Game1Options::setLevelLayout() {
    m_levelLayout->addItem(new QSpacerItem(100,100),0,0,5,1);
    for (int i=0; i<5; ++i) {
        for (int j=0; j<5; ++j) {
            m_levelLayout->addWidget(m_levels[i*5+j],i,j+1);
        }
    }
    m_levelLayout->addItem(new QSpacerItem(100,100),0,6,5,1);
}
