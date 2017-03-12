#include "gui/gameselection.h"
#include "helper.h"
#include "gui/mainwidget.h"
#include "gui/gamemainmenu.h"
#include "myaccount.h"

/**
* \file gameselection.cpp
* \brief Contains GameSelection class definition
*/

/**
* Initializes all buttons and labels and shows them on the
* game selection menu.
*/
GameSelection::GameSelection(QWidget *parent) :
    QWidget(parent)
{
    setFixedSize(600,600);
    m_game1 = new QToolButton();
    m_game1->setAutoFillBackground(true);
    m_game1->setIcon(QIcon("pictures/game1.png"));
    m_game1->setIconSize(QSize(200,200));

    m_game2 = new QToolButton();
    m_game2->setAutoFillBackground(true);
    m_game2->setIcon(QIcon("pictures/game2.png"));
    m_game2->setIconSize(QSize(200,200));

    m_game3 = new QToolButton();
    m_game3->setAutoFillBackground(true);
    m_game3->setIcon(QIcon("pictures/game3.png"));
    m_game3->setIconSize(QSize(200,200));

    m_title = new QLabel("Let the Games Begin");
    Helper::makeWidgetLarge(m_title);

    m_myAccountButton = new QPushButton("My Account");

    m_logoutButton = new QPushButton("Logout");
    m_logoutButton->setAccessibleName("m_logoutButton");

    Helper::makeWidgetSmall(m_myAccountButton);
    Helper::makeWidgetSmall(m_logoutButton);

    m_gameSelectionFullLayout = new QVBoxLayout;
    m_gamesListLayout = new QGridLayout;
    m_linksListLayout = new QHBoxLayout;

    setGamesSelectionFullLayout();
    setLayout(m_gameSelectionFullLayout);

    setConnections();
}

/**
* Frees allocated memory.
*/
GameSelection::~GameSelection() {
    delete m_game1;
    delete m_game2;
    delete m_game3;
    delete m_title;
    delete m_myAccountButton;
    delete m_logoutButton;
    delete m_gamesListLayout;
    delete m_linksListLayout;
    delete m_gameSelectionFullLayout;
}

/**
* Sets the overall layout of the widget.
*/
void GameSelection::setGamesSelectionFullLayout() {
    setLinksListLayout();
    setGamesListLayout();

    m_gameSelectionFullLayout->addWidget(m_title);
    m_gameSelectionFullLayout->addItem(m_gamesListLayout);

    m_gameSelectionFullLayout->addItem(new QSpacerItem(600,50));
    m_gameSelectionFullLayout->addItem(m_linksListLayout);

    m_gameSelectionFullLayout->setAlignment(m_title, Qt::AlignHCenter);
    m_gameSelectionFullLayout->setAlignment(m_gamesListLayout, Qt::AlignHCenter);
}

/**
* Sets the layout for the navigation buttons.
*/
void GameSelection::setLinksListLayout() {
    m_linksListLayout->addWidget(m_myAccountButton);
    m_linksListLayout->addWidget(m_logoutButton);
}

/**
* Sets the layout for the game list.
*/
void GameSelection::setGamesListLayout() {
    m_gamesListLayout->addWidget(m_game1,0,0);
    m_gamesListLayout->addItem(new QSpacerItem(200,200),0,1);
    m_gamesListLayout->addWidget(m_game2,0,2);
    m_gamesListLayout->addItem(new QSpacerItem(200,200),1,0);
    m_gamesListLayout->addWidget(m_game3,1,1);
    m_gamesListLayout->addItem(new QSpacerItem(200,200),1,1);
    m_gamesListLayout->setMargin(50);
}

/**
* Takes the user back to the login widget.
* Called when the logout button is clicked.
*/
void GameSelection::goToMain() {
    MainWidget *main = new MainWidget;
    main->show();
    close();
}

/**
* Takes the user to his/her account page.
* Called when the "Account" button is clicked.
*/
void GameSelection::goToMyAccount() {
    MyAccount *account = new MyAccount;
    account->show();
    close();
}

/**
* Takes the user to game 1 when the appropriate button is clicked.
*/
void GameSelection::goToGame1() {
    GameMainMenu *game1 = new GameMainMenu(1);
    game1->show();
    close();
}

/**
* Takes the user to game 2 when the appropriate button is clicked.
*/
void GameSelection::goToGame2() {
    GameMainMenu *game2 = new GameMainMenu(2);
    game2->show();
    close();
}

/**
* Takes the user to game 3 when the appropriate button is clicked.
*/
void GameSelection::goToGame3() {
    GameMainMenu *game3 = new GameMainMenu(3);
    game3->show();
    close();
}

/**
* Sets all connections.
*/
void GameSelection::setConnections() {
    QObject::connect(m_myAccountButton, SIGNAL(clicked()), SLOT(goToMyAccount()));
    QObject::connect(m_logoutButton, SIGNAL(clicked()), SLOT(goToMain()));
    QObject::connect(m_game1, SIGNAL(clicked()), SLOT(goToGame1()));
    QObject::connect(m_game2, SIGNAL(clicked()), SLOT(goToGame2()));
    QObject::connect(m_game3, SIGNAL(clicked()), SLOT(goToGame3()));
}
