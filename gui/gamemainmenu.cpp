#include "gui/gamemainmenu.h"
#include "helper.h"
#include "game1/game1options.h"
#include "game2/game2options.h"
#include "game3/game3options.h"
#include "game1/game1.h"
#include "game2/game2.h"
#include "game3/game3.h"
#include "gui/gameselection.h"
#include "difficulty.h"
#include "game3/size.h"
#include <QSqlQuery>

/**
* \file gamemainmenu.cpp
* \brief Contains GameMainMenu class definition
*/

/**
* Initializes all buttons and the game title and instructions and shows them on the screen.
* Also initializes connections.
*/
GameMainMenu::GameMainMenu(int gameChoice, QWidget *parent) :
    QWidget(parent), m_gameChoice(gameChoice)
{
    setFixedSize(600,600);
    if (gameChoice == 1) {
        m_gameTitle = new QLabel("Sheep Line");
        m_instructions = new QLabel("The farmer asked Bitzer to move the sheep flock towards "
                                    "the barnhouse. However, Shaun still wanted to play with "
                                    "his friends. Shaun, being the leader of the flock,  started "
                                    "acting naughtily by helping his fellow friends run away and "
                                    "not go into the barnhouse.  Each sheep is marked by a "
                                    "number (1 to 9). Shaun will use the cannon in the center of "
                                    "the farm to send a helper sheep to make others escape the "
                                    "line by forming pairs that add up to a 10.\n\n"
                                    "Objective: You are Shaun. Remove numbered sheep from the "
                                    "line by forming pairs that add up to 10.");
    }
    else if (gameChoice == 2) {
        m_gameTitle = new QLabel("Trap the Sheep");
        m_instructions = new QLabel("The farmer wants to trap Shaun the sheep who is giving him "
                                    "hard times. The sheep can move one step left, right and "
                                    "diagonally to find an exit. The farmer wants to trap the "
                                    "sheep and prevent it from escaping by building blocks to "
                                    "block all possible escape paths.\n\n"
                                    "Objective: You are the farmer. Click on the blocks to try "
                                    "to trap the sheep by using as few blocks as possible and do "
                                    "not let the sheep escape!");
    }
    else {
        m_gameTitle = new QLabel("Dots and Lines");
        m_instructions = new QLabel("When the farmer is taking his nap, Shaun and Bitzer get "
                                    "along and play their favorite game: dots and lines.\n\n"
                                    "Objective: This is a two-player game, where each takes turn "
                                    "adding a single horizontal or vertical line between two "
                                    "unjoined adjacent nodes. The player who closes the most "
                                    "boxes wins the game. You are Bitzer and the computer is Shaun.");
    }

    m_back = new QPushButton("Back to Game Selection Menu");
    m_play = new QPushButton("Play");
    m_resume = new QPushButton("Resume");

    int account = Helper::getUserId();
    if (account != 0) {
        bool opened = Helper::shaunDB.open();
        QSqlQuery query;
        if(opened) {
            query.exec("SELECT COUNT(*) FROM GAME"+ QString::number(m_gameChoice) +" WHERE ACCOUNTID='"+QString::number(account)+"'");
            query.next();
            if (query.value(0).toInt() == 0)
            {
                m_resume->setDisabled(true);
            }
        }
        Helper::shaunDB.close();
    }
    else {
        m_resume->setDisabled(true);
    }

    m_instructions->setWordWrap(true);

    Helper::makeWidgetSmall(m_back);
    m_back->setFixedWidth(300);
    Helper::makeWidgetLarge(m_play);
    m_play->setFixedWidth(300);
    Helper::makeWidgetLarge(m_resume);
    m_resume->setFixedWidth(300);

    Helper::makeWidgetLarge(m_gameTitle);

    m_layout = new QVBoxLayout;
    setMainLayout();
    setLayout(m_layout);

    QObject::connect(m_play, SIGNAL(clicked()), this, SLOT(gotoGameOptions()));
    QObject::connect(m_back, SIGNAL(clicked()), this, SLOT(gotoGameSelection()));
    QObject::connect(m_resume, SIGNAL(clicked()), this, SLOT(resumeSavedGame()));
}

/**
* Frees allocated memory.
*/
GameMainMenu::~GameMainMenu() {
    delete m_gameTitle;
    delete m_instructions;
    delete m_back;
    delete m_play;
    delete m_resume;
    delete m_layout;
}

/**
* Takes the user to the game option widget that corresponds to the game choice.
* Called after clicking "Play".
*/
void GameMainMenu::gotoGameOptions() {
    if (m_gameChoice == 1) {
        Game1Options *op = new Game1Options();
        op->show();
    }
    else if (m_gameChoice == 2){
        Game2Options *op = new Game2Options();
        op->show();
    }
    else {
        Game3Options *op = new Game3Options();
        op->show();
    }
    this->close();
}

/**
* Takes the user back to the game selection menu.
* Called after clicking the corresponding button.
*/
void GameMainMenu::gotoGameSelection() {
    GameSelection *selection = new GameSelection;
    selection->show();
    close();
}

/**
* Takes the user to his/her saved game.
* Called after calling resume.
*/
void GameMainMenu::resumeSavedGame() {
    bool opened = Helper::shaunDB.open();
    QSqlQuery query;
    if(opened) {
        query.exec("SELECT * FROM GAME"+ QString::number(m_gameChoice) +" WHERE ACCOUNTID='"+QString::number(Helper::getUserId())+"'");
        query.next();
    }
    Helper::shaunDB.close();

    if (m_gameChoice == 1) {
        Game1 *op = new Game1(query.value(1).toInt(), true);
        op->show();
    }
    else if (m_gameChoice == 2){
        Difficulty d = static_cast<Difficulty>(query.value(1).toInt());
        Game2 *op = new Game2(d, true);
        op->show();
    }
    else {
        Difficulty d = static_cast<Difficulty>(query.value(1).toInt());
        Size s = static_cast<Size>(query.value(2).toInt());

        Game3 *op = new Game3(d, s, true);
        op->show();
    }
    this->close();
}

/**
* Sets the page layout.
*/
void GameMainMenu::setMainLayout() {
    m_layout->addWidget(m_gameTitle);
    m_layout->addWidget(m_play);
    m_layout->addWidget(m_resume);
    m_layout->addWidget(m_back);
    m_layout->addWidget(m_instructions);

    m_layout->setAlignment(m_gameTitle, Qt::AlignHCenter);
    m_layout->setAlignment(m_play, Qt::AlignHCenter);
    m_layout->setAlignment(m_resume, Qt::AlignHCenter);
    m_layout->setAlignment(m_back, Qt::AlignHCenter);
    m_layout->setAlignment(m_instructions, Qt::AlignJustify);
}
