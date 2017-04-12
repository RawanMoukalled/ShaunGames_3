#include "game1/game1options.h"
#include "helper.h"
#include "gui/gamemainmenu.h"
#include "game1/game1.h"
#include <QSqlQuery>

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
        m_levels[i]->setDisabled(true);
    }

    int nbOfUnlockedLevels = Game1Options::getNumberOfUnlockedLevels();
    for (int i=0; i<nbOfUnlockedLevels; ++i) {
        m_levels[i]->setEnabled(true);
    }

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

    for (QVector<QSpacerItem*>::iterator sp=m_spacerItems.begin(); sp!=m_spacerItems.end(); ++sp) {
        delete *sp;
    }
}

/**
* Returns the number of levels that the user has unlocked.
*/
int Game1Options::getNumberOfUnlockedLevels() {
    int userId = Helper::getUserId();
    if (userId != 0) {
        bool opened = Helper::shaunDB.open();
        QSqlQuery query;
        if (opened) {
            query.exec("SELECT GAME1UNLOCKEDLEVELS FROM ACCOUNT WHERE ID='"+QString::number(userId)+"'");
            query.next();

            m_numberOfUnlockedLevels = query.value(0).toInt();
        }
        Helper::shaunDB.close();
    }
    return m_numberOfUnlockedLevels;
}

/**
* Unlocks a new level if the user has just won the last unlocked level.
* Called after a user wins a certain level.
*/
void Game1Options::unlockExtraLevel(int currLevel) {
    if (m_numberOfUnlockedLevels == currLevel+1) {
        ++m_numberOfUnlockedLevels;

        int userId = Helper::getUserId();

        if (userId != 0) {
            bool opened = Helper::shaunDB.open();
            QSqlQuery query;
            if (opened) {
                query.exec("UPDATE ACCOUNT SET GAME1UNLOCKEDLEVELS = '" + QString::number(m_numberOfUnlockedLevels) +
                           "' WHERE ID = '"+ QString::number(userId) + "'");
            }
            Helper::shaunDB.close();
        }
    }
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
    QSpacerItem *sp = new QSpacerItem(100,100);
    m_spacerItems.push_back(sp);
    m_mainLayout->addItem(sp);
    m_mainLayout->addWidget(m_back);

    m_mainLayout->setAlignment(m_instructions, Qt::AlignCenter);
    m_mainLayout->setAlignment(m_back, Qt::AlignCenter);
}

/**
* Sets the layout of the level buttons.
*/
void Game1Options::setLevelLayout() {
    QSpacerItem *sp = new QSpacerItem(100,100);
    m_spacerItems.push_back(sp);
    m_levelLayout->addItem(sp,0,0,5,1);
    for (int i=0; i<5; ++i) {
        for (int j=0; j<5; ++j) {
            m_levelLayout->addWidget(m_levels[i*5+j],i,j+1);
        }
    }
    sp = new QSpacerItem(100,100);
    m_spacerItems.push_back(sp);
    m_levelLayout->addItem(sp,0,6,5,1);
}

int Game1Options::m_numberOfUnlockedLevels(1);
