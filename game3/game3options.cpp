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
    QWidget(parent), m_level(NO_DIFFICULTY), m_size(NO_SIZE)
{
    setFixedSize(600,600);
    m_instructions = new QLabel("Please pick a level:");
    Helper::makeWidgetLarge(m_instructions);

    m_easy = new QPushButton("Easy");
    m_moderate = new QPushButton("Moderate");
    m_hard = new QPushButton("Hard");

    m_sizeFour = new QPushButton("4x4");
    m_sizeEight = new QPushButton("8x8");
    m_sizeSixteen = new QPushButton("16x16");

    Helper::makeWidgetLarge(m_easy);
    m_easy->setFixedHeight(50);
    Helper::makeWidgetLarge(m_moderate);
    m_moderate->setFixedHeight(50);
    Helper::makeWidgetLarge(m_hard);
    m_hard->setFixedHeight(50);

    Helper::makeWidgetLarge(m_sizeFour);
    m_sizeFour->setFixedHeight(50);
    Helper::makeWidgetLarge(m_sizeEight);
    m_sizeEight->setFixedHeight(50);
    Helper::makeWidgetLarge(m_sizeSixteen);
    m_sizeSixteen->setFixedHeight(50);

    m_play = new QPushButton("Play");
    m_play->setDisabled(true);
    Helper::makeWidgetLarge(m_play);
    m_play->setFixedHeight(50);

    m_back = new QPushButton("Back to Game Menu");
    m_back->setFixedWidth(200);
    Helper::makeWidgetSmall(m_back);

    m_mainLayout = new QVBoxLayout;
    m_levelLayout = new QHBoxLayout;
    m_sizeLayout = new QHBoxLayout;

    setMainLayout();
    setLayout(m_mainLayout);

    QObject::connect(m_easy, SIGNAL(clicked()), this, SLOT(setEasy()));
    QObject::connect(m_moderate, SIGNAL(clicked()), this, SLOT(setModerate()));
    QObject::connect(m_hard, SIGNAL(clicked()), this, SLOT(setHard()));

    QObject::connect(m_sizeFour, SIGNAL(clicked()), this, SLOT(setSizeFour()));
    QObject::connect(m_sizeEight, SIGNAL(clicked()), this, SLOT(setSizeEight()));
    QObject::connect(m_sizeSixteen, SIGNAL(clicked()), this, SLOT(setSizeSixteen()));

    QObject::connect(m_play, SIGNAL(clicked()), this, SLOT(gotoGame()));
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
    delete m_sizeFour;
    delete m_sizeEight;
    delete m_sizeSixteen;
    delete m_play;
    delete m_back;
    delete m_mainLayout;
    delete m_levelLayout;
    delete m_sizeLayout;

    for (QVector<QSpacerItem*>::iterator sp=m_spacerItems.begin(); sp!=m_spacerItems.end(); ++sp) {
        delete *sp;
    }
}

/**
* Takes the user to game 3.
* Called after clicking any level button.
*/
void Game3Options::gotoGame() {
    Game3 *g = new Game3(m_level, m_size);
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
* Sets the game difficulty to Easy.
* Called after clicking the corresponding button.
*/
void Game3Options::setEasy() {
    m_easy->setDisabled(true);
    m_moderate->setEnabled(true);
    m_hard->setEnabled(true);
    m_level = EASY;

    if (m_size != NO_SIZE)  {
        m_play->setEnabled(true);
    }
}

/**
* Sets the game difficulty to Moderate.
* Called after clicking the corresponding button.
*/
void Game3Options::setModerate() {
    m_moderate->setDisabled(true);
    m_easy->setEnabled(true);
    m_hard->setEnabled(true);
    m_level = MODERATE;

    if (m_size != NO_SIZE)  {
        m_play->setEnabled(true);
    }
}

/**
* Sets the game difficulty to Hard.
* Called after clicking the corresponding button.
*/
void Game3Options::setHard() {
    m_hard->setDisabled(true);
    m_easy->setEnabled(true);
    m_moderate->setEnabled(true);
    m_level = HARD;

    if (m_size != NO_SIZE)  {
        m_play->setEnabled(true);
    }
}

/**
* Sets the game size to 4x4.
* Called after clicking the corresponding button.
*/
void Game3Options::setSizeFour() {
    m_sizeFour->setDisabled(true);
    m_sizeEight->setEnabled(true);
    m_sizeSixteen->setEnabled(true);
    m_size = FOURBYFOUR;

    if (m_level != NO_DIFFICULTY)  {
        m_play->setEnabled(true);
    }
}

/**
* Sets the game size to 8x8.
* Called after clicking the corresponding button.
*/
void Game3Options::setSizeEight() {
    m_sizeEight->setDisabled(true);
    m_sizeFour->setEnabled(true);
    m_sizeSixteen->setEnabled(true);
    m_size = EIGHTBYEIGHT;

    if (m_level != NO_DIFFICULTY)  {
        m_play->setEnabled(true);
    }
}

/**
* Sets the game size to 16x16.
* Called after clicking the corresponding button.
*/
void Game3Options::setSizeSixteen() {
    m_sizeSixteen->setDisabled(true);
    m_sizeEight->setEnabled(true);
    m_sizeFour->setEnabled(true);
    m_size = SIXTEENBYSIXTEEN;

    if (m_level != NO_DIFFICULTY)  {
        m_play->setEnabled(true);
    }
}

/**
* Sets the overall layout of the window.
*/
void Game3Options::setMainLayout() {
    m_mainLayout->addWidget(m_instructions);
    setLevelLayout();
    m_mainLayout->addItem(m_levelLayout);

    setSizeLayout();
    m_mainLayout->addItem(m_sizeLayout);

    m_mainLayout->addWidget(m_play);

    QSpacerItem *sp = new QSpacerItem(20,30);
    m_spacerItems.push_back(sp);
    m_mainLayout->addItem(sp);
    m_mainLayout->addWidget(m_back);

    m_mainLayout->setAlignment(m_instructions, Qt::AlignCenter);
    m_mainLayout->setAlignment(m_play, Qt::AlignCenter);
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

/**
* Sets the layout of the size buttons.
*/
void Game3Options::setSizeLayout() {
    QSpacerItem *sp = new QSpacerItem(100,100);
    m_spacerItems.push_back(sp);
    m_sizeLayout->addItem(sp);
    m_sizeLayout->addWidget(m_sizeFour);

    sp = new QSpacerItem(20,20);
    m_spacerItems.push_back(sp);
    m_sizeLayout->addItem(sp);
    m_sizeLayout->addWidget(m_sizeEight);

    sp = new QSpacerItem(20,20);
    m_spacerItems.push_back(sp);
    m_sizeLayout->addItem(sp);
    m_sizeLayout->addWidget(m_sizeSixteen);

    sp = new QSpacerItem(100,100);
    m_spacerItems.push_back(sp);
    m_sizeLayout->addItem(sp);
}
