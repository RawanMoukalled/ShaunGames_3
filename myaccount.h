#ifndef MYACCOUNT_H
#define MYACCOUNT_H

#include <QWidget>
#include <QtGui>
#include <QGraphicsItem>

/**
* \file myaccount.h
* \brief Class representing the my account and performance history windows
*
* Menu that presents to the signed in user his history and performance statistics
* \author Rita Aoun
* \author Rawan Moukalled
*/
class MyAccount : public QWidget
{
    Q_OBJECT
public:
    /**
    * \brief Default constructor
    */
    explicit MyAccount(QWidget *parent = 0);

    /**
    * \brief Destructor
    */
    virtual ~MyAccount();
    
signals:
    
public slots:
    /**
    * \brief Goes back to the games selection menu
    */
    void goToGames();

private:
    QLabel *m_title;//<Title of the page
    QPushButton *m_backToGamesButton; //<Button to go back to the games selection window

    QVBoxLayout *m_myAccountLayout; //<Layout of the my account page
    QLabel *m_performance; //< Image representing the history performance of the signed in user

    /**
    * \brief Sets the layout for the My Account page
    */
    void setMyAccountLayout();
    
};

#endif // MYACCOUNT_H
