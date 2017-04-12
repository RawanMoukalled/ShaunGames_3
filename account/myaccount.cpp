#include "myaccount.h"
#include "helper.h"
#include "gui/gameselection.h"
#include <QSqlQuery>

/**
* \file myaccount.cpp
* \brief Contains MyAccount class definition
*/

/**
* Initializes all buttons and labels and shows them on the
* game selection menu.
*/
MyAccount::MyAccount(QWidget *parent) :
    QWidget(parent), m_game1GameNbs(), m_game1Scores(), m_game2GameNbs(), m_game2Scores(), m_game3GameNbs(), m_game3Scores()
{
    setFixedSize(600,600);
    m_backToGamesButton = new QPushButton("Back to Games");

    bool opened = Helper::shaunDB.open();
    QSqlQuery query;
    if (opened) {
        query.exec("SELECT FIRSTNAME, LASTNAME FROM ACCOUNT WHERE ID='"+QString::number(Helper::getUserId())+"'");
        query.next();
    }
    Helper::shaunDB.close();

    m_title = new QLabel("Performance History of " + query.value(0).toString() + " " + query.value(1).toString());

    Helper::makeWidgetLarge(m_title);

    m_showGame1 = new QPushButton("Sheep Line");
    m_showGame2 = new QPushButton("Trap the Sheep");
    m_showGame3 = new QPushButton("Dots and Lines");
    m_showOverall = new QPushButton("Overall");

    Helper::makeWidgetSmall(m_backToGamesButton);
    Helper::makeWidgetSmall(m_showGame1);
    Helper::makeWidgetSmall(m_showGame2);
    Helper::makeWidgetSmall(m_showGame3);
    Helper::makeWidgetSmall(m_showOverall);

    m_backToGamesButton->setFixedWidth(300);

    m_myAccountLayout = new QGridLayout;

    m_customPlot = new QCustomPlot;

    setMyAccountLayout();
    setLayout(m_myAccountLayout);

    setConnections();
    setScoreVectors();

    m_customPlot->resize(500,500);

    showGameGraph(0);
}

/**
* Frees allocated memory.
*/
MyAccount::~MyAccount() {
    delete m_title;
    delete m_backToGamesButton;
    delete m_customPlot;
    delete m_showGame1;
    delete m_showGame2;
    delete m_showGame3;
    delete m_showOverall;
    delete m_signalMapper;
    delete m_myAccountLayout;

    for (QVector<QSpacerItem*>::iterator sp=m_spacerItems.begin(); sp!=m_spacerItems.end(); ++sp) {
        delete *sp;
    }
}

/**
* Takes the user back to the game selection menu.
* Called when the user clicks the corresponding button.
*/
void MyAccount::goToGames() {
    GameSelection *gameSelection = new GameSelection();
    gameSelection->show();
    close();
}

void MyAccount::showGameGraph(int gamenb) {
    m_customPlot->legend->setVisible(true);
    m_customPlot->clearItems();
    m_customPlot->clearGraphs();

    m_customPlot->addGraph();

    QVector<double> x,y;
    int nbOfGames;
    int min;
    int max;

    if (gamenb <= 1) {
        x = m_game1GameNbs;
        y = m_game1Scores;
        nbOfGames = m_game1GameNbs.size();
        min = m_min1;
        max = m_max1;
        m_customPlot->graph(0)->setName("Sheep Line");
    }
    else if (gamenb == 2) {
        x = m_game2GameNbs;
        y = m_game2Scores;
        nbOfGames = m_game2GameNbs.size();
        min = m_min2;
        max = m_max2;
        m_customPlot->graph(0)->setName("Trap the Sheep");
        m_customPlot->graph(0)->setPen(QPen(Qt::red));
    }
    else {
        x = m_game3GameNbs;
        y = m_game3Scores;
        nbOfGames = m_game3GameNbs.size();
        min = m_min3;
        max = m_max3;
        m_customPlot->graph(0)->setName("Dots and Lines");
        m_customPlot->graph(0)->setPen(QPen(Qt::green));
    }
    m_customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc));
    m_customPlot->graph(0)->setData(x,y);

    if (gamenb == 0) {
        nbOfGames = qMax(nbOfGames, m_game2GameNbs.size());
        nbOfGames = qMax(nbOfGames, m_game3GameNbs.size());

        m_customPlot->addGraph();
        m_customPlot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc));
        m_customPlot->graph(1)->setData(m_game2GameNbs,m_game2Scores);
        m_customPlot->graph(1)->setName("Trap the Sheep");
        m_customPlot->graph(1)->setPen(QPen(Qt::red));

        m_customPlot->addGraph();
        m_customPlot->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc));
        m_customPlot->graph(2)->setData(m_game3GameNbs,m_game3Scores);
        m_customPlot->graph(2)->setName("Dots and Lines");
        m_customPlot->graph(2)->setPen(QPen(Qt::green));

        min = m_minAll;
        max = m_maxAll;
    }

    m_customPlot->yAxis->setLabel("Score");
    m_customPlot->xAxis->setLabel("Game Number");

    m_customPlot->xAxis->setRange(0, nbOfGames+1);
    m_customPlot->yAxis->setRange(min, max);

    m_customPlot->xAxis->setAutoTickStep(false);
    m_customPlot->xAxis->setTickStep(1);
    m_customPlot->replot();

    m_myAccountLayout->addWidget(m_customPlot,4,0,1,4);
}

/**
* Connects the difficulty buttons to the new game 2.
*/
void MyAccount::setConnections() {
    QObject::connect(m_backToGamesButton, SIGNAL(clicked()), SLOT(goToGames()));

    m_signalMapper = new QSignalMapper(this);

    QObject::connect(m_showGame1, SIGNAL(clicked()), m_signalMapper, SLOT(map()));
    m_signalMapper->setMapping(m_showGame1, 1);

    QObject::connect(m_showGame2, SIGNAL(clicked()), m_signalMapper, SLOT(map()));
    m_signalMapper->setMapping(m_showGame2, 2);

    QObject::connect(m_showGame3, SIGNAL(clicked()), m_signalMapper, SLOT(map()));
    m_signalMapper->setMapping(m_showGame3, 3);

    QObject::connect(m_showOverall, SIGNAL(clicked()), m_signalMapper, SLOT(map()));
    m_signalMapper->setMapping(m_showOverall, 0);

    QObject::connect(m_signalMapper, SIGNAL(mapped(int)), this, SLOT(showGameGraph(int)));
}

/**
* Sets the overall layout of the widget.
*/
void MyAccount::setMyAccountLayout() {
    m_myAccountLayout->addWidget(m_title,0,0,1,4, Qt::AlignCenter);

    QSpacerItem *sp = new QSpacerItem(600,20);
    m_spacerItems.push_back(sp);
    m_myAccountLayout->addItem(sp,1,0,1,4);

    m_myAccountLayout->addWidget(m_showGame1,2,0);
    m_myAccountLayout->addWidget(m_showGame2,2,1);
    m_myAccountLayout->addWidget(m_showGame3,2,2);
    m_myAccountLayout->addWidget(m_showOverall,2,3);

    sp = new QSpacerItem(600,30);
    m_spacerItems.push_back(sp);
    m_myAccountLayout->addItem(sp,3,0,1,4);

    m_myAccountLayout->addWidget(m_customPlot,4,0,1,4);
    m_myAccountLayout->setRowStretch(4,30);

    sp = new QSpacerItem(600,50);
    m_spacerItems.push_back(sp);
    m_myAccountLayout->addItem(sp,5,0,1,4);

    m_myAccountLayout->addWidget(m_backToGamesButton,6,1,1,2, Qt::AlignHCenter);
}

/**
* Initializes the score vectors for all games.
*/
void MyAccount::setScoreVectors() {
    int userId = Helper::getUserId();

    QString game1Query;
    QString game2Query;
    QString game3Query;

    bool opened = Helper::shaunDB.open();
    QSqlQuery query;
    if (opened) {
        query.exec("SELECT SCORE FROM SCORE WHERE ACCOUNTID='"+QString::number(userId)+"' AND GAMENB='1'");
        query.next();
        game1Query = query.value(0).toString();

        query.exec("SELECT SCORE FROM SCORE WHERE ACCOUNTID='"+QString::number(userId)+"' AND GAMENB='2'");
        query.next();
        game2Query = query.value(0).toString();

        query.exec("SELECT SCORE FROM SCORE WHERE ACCOUNTID='"+QString::number(userId)+"' AND GAMENB='3'");
        query.next();
        game3Query = query.value(0).toString();
    }
    Helper::shaunDB.close();

    QStringList game1SplitQuery = game1Query.split(",", QString::SkipEmptyParts);
    int game1QuerySize = game1SplitQuery.size();

    if (game1QuerySize == 0) {
        m_min1 = 0;
        m_max1 = 10;
    }
    else
    {
        m_min1 = 9000;
        m_max1 = -1;
        for (int i=0; i<game1QuerySize; i++) {
            m_game1GameNbs.push_back(i+1.0);
            m_game1Scores.push_back(game1SplitQuery.at(i).toDouble());

            if (m_game1Scores[i] < m_min1) {
                m_min1 = m_game1Scores[i];
            }
            if (m_game1Scores[i] > m_max1) {
                m_max1 = m_game1Scores[i];
            }
        }

        if (game1QuerySize == 1) {
            m_min1 = m_min1 - 5;
            m_max1 = m_max1 + 5;
        }
    }

    QStringList game2SplitQuery = game2Query.split(",", QString::SkipEmptyParts);
    int game2QuerySize = game2SplitQuery.size();

    if (game2QuerySize == 0) {
        m_min2 = 0;
        m_max2 = 10;
    }
    else
    {
        m_min2 = 9000;
        m_max2 = -1;
        for (int i=0; i<game2QuerySize; i++) {
            m_game2GameNbs.push_back(i+1.0);
            m_game2Scores.push_back(game2SplitQuery.at(i).toDouble());

            if (m_game2Scores[i] < m_min2) {
                m_min2 = m_game2Scores[i];
            }
            if (m_game2Scores[i] > m_max2) {
                m_max2 = m_game2Scores[i];
            }
        }

        if (game2QuerySize == 1) {
            m_min2 = m_min2 - 5;
            m_max2 = m_max2 + 5;
        }
    }

    QStringList game3SplitQuery = game3Query.split(",", QString::SkipEmptyParts);
    int game3QuerySize = game3SplitQuery.size();

    if (game3QuerySize == 0) {
        m_min3 = 0;
        m_max3 = 10;
    }
    else
    {
        m_min3 = 9000;
        m_max3 = -1;
        for (int i=0; i<game3QuerySize; i++) {
            m_game3GameNbs.push_back(i+1.0);
            m_game3Scores.push_back(game3SplitQuery.at(i).toDouble());

            if (m_game3Scores[i] < m_min3) {
                m_min3 = m_game3Scores[i];
            }
            if (m_game3Scores[i] > m_max3) {
                m_max3 = m_game3Scores[i];
            }
        }

        if (game3QuerySize == 1) {
            m_min3 = m_min3 - 5;
            m_max3 = m_max3 + 5;
        }
    }

    m_minAll = qMin(m_min1, m_min2);
    m_minAll = qMin(m_minAll, m_min3);

    m_maxAll = qMax(m_max1, m_max2);
    m_maxAll = qMax(m_maxAll, m_max3);
}
