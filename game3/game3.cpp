#include "game3/game3.h"
#include "helper.h"
#include "gui/gamemainmenu.h"
#include <QSqlQuery>

/**
* \file game3.cpp
* \brief Contains the Dots and Lines game
*/

/**
* Sets the size of the window, initializes the graphic items, sets the layouts
* and connects buttons to their slots.
*/
Game3::Game3(Difficulty difficulty, Size size, bool resume, QWidget *parent) :
    QWidget(parent), m_difficulty(difficulty), m_size(size), m_justSaved(false)
{
    setFixedSize(600,600);
    m_title = new QLabel("Dots and Lines");
    m_Game3Layout = new QVBoxLayout();
    m_exit = new QPushButton("Save and Exit");

    Helper::makeWidgetLarge(m_title);
    Helper::makeWidgetSmall(m_exit);

    m_gameScene = new Game3Scene(difficulty, size, resume);
    m_gameView = new QGraphicsView;

    setGame3Layout();
    setLayout(m_Game3Layout);

    QObject::connect(m_exit, SIGNAL(clicked()), SLOT(save()));
    QObject::connect(m_gameScene, SIGNAL(done()),SLOT(endGame()));
}

/**
* Frees allocated memory.
*/
Game3::~Game3() {
    delete m_title;
    delete m_Game3Layout;
    if (m_exit != NULL) {
        delete m_exit;
    }
    else {
        delete m_goBack;
        delete m_replay;
    }
    delete m_gameView;
    delete m_gameScene;
}

/**
* Adds widgets and spaces for the layout of Dots and Lines.
*/
void Game3::setGame3Layout() {
    m_gameScene->setSceneRect(0,0,575,505);
    m_gameView->setScene(m_gameScene);
    m_gameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_gameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_Game3Layout->addWidget(m_title);
    m_Game3Layout->addWidget(m_gameView);
    m_Game3Layout->addWidget(m_exit);

    m_Game3Layout->setAlignment(m_title, Qt::AlignHCenter);
    m_Game3Layout->setAlignment(m_exit, Qt::AlignHCenter);
}

/**
* Reloads game.
*/
void Game3::replay() {
    delete m_gameScene;
    m_gameScene = new Game3Scene(m_difficulty, m_size);
    m_gameView->setScene(m_gameScene);
    m_gameScene->setSceneRect(0,0,575,505);
    m_gameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_gameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    m_Game3Layout->removeWidget(m_goBack);
    delete m_goBack;

    m_Game3Layout->removeWidget(m_replay);
    delete m_replay;

    m_exit = new QPushButton("Save and Exit");
    m_Game3Layout->addWidget(m_exit);
    m_Game3Layout->setAlignment(m_exit, Qt::AlignHCenter);
    QObject::connect(m_exit, SIGNAL(clicked()), SLOT(goToMainMenu()));
    QObject::connect(m_gameScene, SIGNAL(done()),SLOT(endGame()));
}

/**
* Removes the save and exitbutton and adds the go back and replay
* buttons along with their connections.
*/
void Game3::endGame() {
    m_goBack = new QPushButton("Go Back");
    m_replay = new QPushButton("Replay");

    m_Game3Layout->removeWidget(m_exit);
    delete m_exit;
    m_exit = NULL;

    m_Game3Layout->addWidget(m_goBack);
    m_Game3Layout->addWidget(m_replay);

    m_Game3Layout->setAlignment(m_goBack, Qt::AlignHCenter);
    m_Game3Layout->setAlignment(m_replay, Qt::AlignHCenter);

    QObject::connect(m_goBack, SIGNAL(clicked()), SLOT(goToMainMenu()));
    QObject::connect(m_replay, SIGNAL(clicked()), SLOT(replay()));
}

/**
* \brief Goes back to the Main meny of Dots and Lines.
*/
void Game3::goToMainMenu() {
    close();
    GameMainMenu *menu = new GameMainMenu(3);
    menu->show();
}

/**
* Saves and exits
*/
void Game3::save() {
    int account = Helper::getUserId();
    if (account != 0) {
        bool isUserTurn = m_gameScene->isUserTurn();
        m_gameScene->freeze();
        Helper::deleteSavedGame(3);
        m_justSaved = true;
        bool opened = Helper::shaunDB.open();
        QSqlQuery query;
        if(opened) {
            query.prepare("INSERT INTO GAME3 (ACCOUNTID, DIFFICULTY, SIZE, SCORE, USERTURN, PCBOXES, USERBOXES, MARKEDH, "
                          "MARKEDV) VALUES (:accountID, :difficulty, :size, :score, :userTurn, :pcBoxes, "
                          ":userBoxes, :markedH, :markedV)");

            query.bindValue(":accountId", account);
            query.bindValue(":difficulty", m_difficulty);
            query.bindValue(":size", m_size);
            query.bindValue(":score", m_gameScene->getScore());
            query.bindValue(":userTurn", isUserTurn);
            query.bindValue(":pcBoxes", m_gameScene->getBoxesClosedByPC());
            query.bindValue(":userBoxes", m_gameScene->getBoxesClosedByUser());
            query.bindValue(":markedH", m_gameScene->getDrawnHorizontalLines());
            query.bindValue(":markedV", m_gameScene->getDrawnVerticalLines());

            query.exec();
        }

        Helper::shaunDB.close();
    }
    goToMainMenu();
}

/**
* Deletes the saved game on close unless it is a newly saved game.
*/
void Game3::closeEvent(QCloseEvent *bar) {
    if (!m_justSaved) {
        Helper::deleteSavedGame(3);
    }
    bar->accept();
}
