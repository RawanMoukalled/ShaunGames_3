#ifndef MYACCOUNT_H
#define MYACCOUNT_H

#include <QtGui>
#include "qcustomplot.h"

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

    /**
    * \brief Sets the connections for the buttons
    */
    void setConnections();



signals:

public slots:
    /**
    * \brief Goes back to the games selection menu
    */
    void goToGames();

    /**
    * \brief Displays the graph of the selected game
    * \param gamenb The number of the game
    */
    void showGameGraph(int gamenb);

private:
    QLabel *m_title; ///< Title of the page
    QPushButton *m_backToGamesButton; ///< Button to go back to the games selection window

    QVBoxLayout *m_myAccountLayout; ///< Layout of the my account page
    QLabel *m_performance; ///< Image representing the history performance of the signed in user
    QHBoxLayout *m_selectionLayout; ///< Layout of the buttons for selection

    QCustomPlot *m_customPlot; ///< Contains the plot that will be drawn
    QPushButton *m_showGame1; ///< Button to display game1 performance
    QPushButton *m_showGame2; ///< Button to display game2 performance
    QPushButton *m_showGame3; ///< Button to display game3 performance
    QPushButton *m_showOverall; ///< Button to display overall performance

    QSignalMapper *m_signalMapper; ///< Maps signals to slots to allow for game selection to be passed


    /**
    * \brief Sets the layout for the My Account page
    */
    void setMyAccountLayout();

    /**
    * \brief Sets the layout for the selection buttons
    */
    void setSelectionLayout();

};

#endif // MYACCOUNT_H
