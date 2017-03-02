#include "myaccount.h"
#include "helper.h"
#include "gameselection.h"

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

    m_performance = new QLabel();
    QPixmap img("pictures/construction.png");
    QSize size = img.size();
    size.setWidth(400);
    m_performance->setPixmap(img.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation));


    Helper::makeWidgetSmall(m_backToGamesButton);
    m_backToGamesButton->setFixedWidth(300);

    m_myAccountLayout = new QVBoxLayout;
    setMyAccountLayout();
    setLayout(m_myAccountLayout);

    QObject::connect(m_backToGamesButton, SIGNAL(clicked()), SLOT(goToGames()));
}

/**
* Sets the overall layout of the widget.
*/
void MyAccount::setMyAccountLayout() {

    m_myAccountLayout->addItem(new QSpacerItem(600,100));
    m_myAccountLayout->addWidget(m_title);
    m_myAccountLayout->addWidget(m_performance);
    m_myAccountLayout->addWidget(m_backToGamesButton);


    m_myAccountLayout->addItem(new QSpacerItem(600,100));

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
