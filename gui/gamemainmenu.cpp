#include "gui/gamemainmenu.h"
#include "helper.h"
#include "game1/game1options.h"
#include "games23options.h"
#include "gui/gameselection.h"

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
                                    "boxes wins the game.");
    }

    m_back = new QPushButton("Back to Game Selection Menu");
    m_play = new QPushButton("Play");
    m_resume = new QPushButton("Resume");
    m_resume->setDisabled(true);

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
    else {
        Games23Options *op = new Games23Options(m_gameChoice);
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
