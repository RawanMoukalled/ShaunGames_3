#include "myaccount.h"
#include "helper.h"
#include "gui/gameselection.h"


/**
* \file myaccount.cpp
* \brief Contains MyAccount class definition
*/

/**
* Initializes all buttons and labels and shows them on the
* game selection menu.
*/
MyAccount::MyAccount(QWidget *parent) :
    QWidget(parent)
{
    setFixedSize(600,600);
    m_backToGamesButton = new QPushButton("Back to Games");
    m_title = new QLabel("Performance History");

    Helper::makeWidgetLarge(m_title);

    m_showGame1 = new QPushButton("Sheep Line");
    m_showGame2 = new QPushButton("Trap the Sheep");
    m_showGame3 = new QPushButton("Dots and Lines");
    m_showOverall = new QPushButton("Overall");

    m_performance = new QLabel();
    QPixmap img("pictures/construction.png");
    QSize size = img.size();
    size.setWidth(400);
    m_performance->setPixmap(img.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    m_customPlot = NULL;


    Helper::makeWidgetSmall(m_backToGamesButton);
    Helper::makeWidgetSmall(m_showGame1);
    Helper::makeWidgetSmall(m_showGame2);
    Helper::makeWidgetSmall(m_showGame3);
    Helper::makeWidgetSmall(m_showOverall);

    m_backToGamesButton->setFixedWidth(300);

    m_myAccountLayout = new QVBoxLayout;
    m_selectionLayout = new QHBoxLayout;

    setSelectionLayout();

    setMyAccountLayout();
    setLayout(m_myAccountLayout);

    setConnections();

}

/**
* Frees allocated memory.
*/
MyAccount::~MyAccount() {
    delete m_backToGamesButton;
    delete m_title;
    delete m_performance;
    delete m_myAccountLayout;
}

void MyAccount::setSelectionLayout() {
    m_selectionLayout->addWidget(m_showGame1);
    m_selectionLayout->addWidget(m_showGame2);
    m_selectionLayout->addWidget(m_showGame3);
    m_selectionLayout->addWidget(m_showOverall);
}

/**
* Sets the overall layout of the widget.
*/
void MyAccount::setMyAccountLayout() {

    //m_myAccountLayout->addItem(new QSpacerItem(600,100));
    m_myAccountLayout->addWidget(m_title);

    m_myAccountLayout->addItem(m_selectionLayout);
    m_myAccountLayout->addWidget(m_performance);
    m_myAccountLayout->addWidget(m_backToGamesButton);


    //m_myAccountLayout->addItem(new QSpacerItem(600,100));

    m_myAccountLayout->setAlignment(m_title, Qt::AlignHCenter);

    m_myAccountLayout->setAlignment(m_performance, Qt::AlignHCenter);
    m_myAccountLayout->setAlignment(m_backToGamesButton, Qt::AlignHCenter);
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

    //QObject::connect(m_showOverall, SIGNAL(clicked()), m_signalMapper, SLOT(map()));
    //m_signalMapper->setMapping(m_hard, HARD);

    QObject::connect(m_signalMapper, SIGNAL(mapped(int)), this, SLOT(showGameGraph(int)));
}

void MyAccount::showGameGraph(int gamenb) {
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));
    m_customPlot = new QCustomPlot();
    m_customPlot->setBackground(QBrush(gradient));
    m_customPlot->clearItems();

    m_customPlot->addGraph();

    qDebug()<<"1";

    QVector<double> x,y;
    y.push_back(4);
    y.push_back(7);
    x.push_back(1);
    x.push_back(2);

    m_customPlot->graph(0)->setData(x,y);

    m_customPlot->yAxis->setLabel("Score");
    m_customPlot->xAxis->setLabel("Game Number");

    m_customPlot->xAxis->setRange(0, 10);

    m_customPlot->yAxis->setRange(0, 10);
    m_customPlot->xAxis->setBasePen(QPen(Qt::white));
    m_customPlot->xAxis->setTickPen(QPen(Qt::white));
    m_customPlot->xAxis->grid()->setVisible(true);
    m_customPlot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    m_customPlot->xAxis->setTickLabelColor(Qt::white);
    m_customPlot->xAxis->setLabelColor(Qt::white);
    m_customPlot->xAxis->setTickPen(QPen(Qt::white));
    m_customPlot->yAxis->setBasePen(QPen(Qt::white));
    m_customPlot->yAxis->setTickPen(QPen(Qt::white));
    m_customPlot->yAxis->setSubTickPen(QPen(Qt::white));
    m_customPlot->yAxis->grid()->setSubGridVisible(true);
    m_customPlot->yAxis->setTickLabelColor(Qt::white);
    m_customPlot->yAxis->setLabelColor(Qt::white);
    m_customPlot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    m_customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    m_customPlot->replot();

    qDebug()<<"2";

    m_myAccountLayout->removeWidget(m_backToGamesButton);
    m_myAccountLayout->removeWidget(m_performance);
    m_myAccountLayout->addWidget(m_customPlot);
    m_myAccountLayout->addWidget(m_backToGamesButton);
    m_myAccountLayout->setAlignment(m_backToGamesButton, Qt::AlignHCenter);

    qDebug()<<"3";
}
