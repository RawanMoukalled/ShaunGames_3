#include "game2/game2.h"
#include "helper.h"
#include "gui/gamemainmenu.h"
#include <QSqlQuery>
#include <QSqlError>

/**
* \file game2.cpp
* \brief Contains Game2 class definition
*/

/**
* Sets the size of the window, initializes the graphic items, sets the layouts
* and connects buttons to their slots.
*/
Game2::Game2(Difficulty difficulty, bool resume, QWidget *parent) :
    QWidget(parent), m_justSaved(false)
{
    setFixedSize(600,600);
    m_title = new QLabel("Trap the Sheep");
    m_Game2Layout = new QVBoxLayout();

    if (Helper::getUserId() != 0) {
        m_exit = new QPushButton("Save and Exit");
    }
    else {
        m_exit = new QPushButton("Exit");
    }
    Helper::makeWidgetLarge(m_title);
    Helper::makeWidgetSmall(m_exit);

    m_difficulty = difficulty;
    m_gameScene = new Game2Scene(difficulty, resume);
    m_gameView = new QGraphicsView;

    setGame2Layout();
    setLayout(m_Game2Layout);

    QObject::connect(m_exit, SIGNAL(clicked()), SLOT(save()));
    QObject::connect(m_gameScene, SIGNAL(Done()),SLOT(endGame()));

}

/**
* Frees allocated memory.
*/
Game2::~Game2() {
    delete m_title;
    delete m_Game2Layout;
    delete m_gameScene;
    delete m_gameView;

    if (m_exit != NULL) {
        delete m_exit;
    }
    else {
        delete m_goBack;
        delete m_replay;
    }
}

/**
* Adds widgets and spaces for the layout of Sheep Line.
*/
void Game2::setGame2Layout() {
    m_gameScene->setSceneRect(0,0,575,505);
    m_gameView->setScene(m_gameScene);
    m_gameView->setBackgroundBrush(QBrush(QImage("pictures/brown_bg.png").scaledToHeight(550)));
    m_gameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_gameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_Game2Layout->addWidget(m_title);
    m_Game2Layout->addWidget(m_gameView);
    m_Game2Layout->addWidget(m_exit);

    m_Game2Layout->setAlignment(m_title, Qt::AlignHCenter);
    m_Game2Layout->setAlignment(m_exit, Qt::AlignHCenter);
}

/**
* Goes to the main menu of Trap the Sheep.
*/
void Game2::goToMainMenu() {
    close();
    GameMainMenu *menu = new GameMainMenu(2);
    menu->show();
}

/**
* Reloads game.
*/
void Game2::replay() {
    delete m_gameScene;
    m_gameScene = new Game2Scene(m_difficulty, false);
    m_gameView->setScene(m_gameScene);
    m_gameScene->setSceneRect(0,0,575,505);
    m_gameView->setBackgroundBrush(QBrush(QImage("pictures/brown_bg.png").scaledToHeight(550)));
    m_gameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_gameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    m_Game2Layout->removeWidget(m_goBack);
    delete m_goBack;

    m_Game2Layout->removeWidget(m_replay);
    delete m_replay;

    if (Helper::getUserId() != 0) {
        m_exit = new QPushButton("Save and Exit");
    }
    else {
        m_exit = new QPushButton("Exit");
    }
    m_Game2Layout->addWidget(m_exit);
    m_Game2Layout->setAlignment(m_exit, Qt::AlignHCenter);
    QObject::connect(m_exit, SIGNAL(clicked()), SLOT(save()));
    QObject::connect(m_gameScene, SIGNAL(Done()),SLOT(endGame()));
}

/**
* Saves the state of the game into the database.
*/
void Game2::save() {
    //if logged in user
    if(Helper::getUserId() != 0) {
        Helper::deleteSavedGame(2);
        m_justSaved = true;
        bool opened = Helper::shaunDB.open();
        QSqlQuery query;
        if(opened) {
            query.prepare("INSERT INTO GAME2 (ACCOUNTID, DIFFICULTY, SCORE, USERTURN, SHEEPPOS, BLOCKEDTILES) VALUES (:accountid, :difficulty, :score, :userturn, :sheeppos, :blockedtiles)");

            query.bindValue(":accountid", Helper::getUserId());
            query.bindValue(":difficulty", m_gameScene->getDifficulty());
            query.bindValue(":score", m_gameScene->getScore());
            query.bindValue(":userturn", m_gameScene->getUserTurn());
            query.bindValue(":sheeppos", m_gameScene->getSheepPos());
            query.bindValue(":blockedtiles", m_gameScene->getBlockedTilesPos());

            query.exec();
       }
       Helper::shaunDB.close();
    }
    goToMainMenu();
}


/**
* \brief Deletes the saved game on close
* \param bar The event triggered
*/
void Game2::closeEvent(QCloseEvent *bar) {
    if (!m_justSaved) {
        Helper::deleteSavedGame(2);
    }
    bar->accept();
}
/**
* Removes the save and exitbutton and adds the go back and replay
* buttons along with their connections.
*/
void Game2::endGame() {
    m_goBack = new QPushButton("Go Back");
    m_replay = new QPushButton("Replay");

    m_Game2Layout->removeWidget(m_exit);
    delete m_exit;
    m_exit = NULL;

    m_Game2Layout->addWidget(m_goBack);
    m_Game2Layout->addWidget(m_replay);

    m_Game2Layout->setAlignment(m_goBack, Qt::AlignHCenter);
    m_Game2Layout->setAlignment(m_replay, Qt::AlignHCenter);

    QObject::connect(m_goBack, SIGNAL(clicked()), SLOT(goToMainMenu()));
    QObject::connect(m_replay, SIGNAL(clicked()), SLOT(replay()));
}
