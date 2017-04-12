#ifndef MYACCOUNT_H
#define MYACCOUNT_H

#include <QtGui>
#include "account/qcustomplot.h"

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

    /**
    * \brief Displays the graph of the selected game
    * \param gamenb The number of the game
    */
    void showGameGraph(int gamenb);

private:
    QLabel *m_title; ///< Title of the page
    QPushButton *m_backToGamesButton; ///< Button to go back to the games selection window

    QGridLayout *m_myAccountLayout; ///< Layout of the my account page

    QCustomPlot *m_customPlot; ///< Contains the plot that will be drawn
    QPushButton *m_showGame1; ///< Button to display game1 performance
    QPushButton *m_showGame2; ///< Button to display game2 performance
    QPushButton *m_showGame3; ///< Button to display game3 performance
    QPushButton *m_showOverall; ///< Button to display overall performance

    QSignalMapper *m_signalMapper; ///< Maps signals to slots to allow for game selection to be passed

    int m_min1, m_max1; ///< Contains minimum and maximum scores for game 1
    QVector<double> m_game1GameNbs; ///< Contains game 1 game numbers
    QVector<double> m_game1Scores; ///< Contains game 1 scores

    int m_min2, m_max2; ///< Contains minimum and maximum scores for game 2
    QVector<double> m_game2GameNbs; ///< Contains game 2 game numbers
    QVector<double> m_game2Scores; ///< Contains game 2 scores

    int m_min3, m_max3; ///< Contains minimum and maximum scores for game 3
    QVector<double> m_game3GameNbs; ///< Contains game 3 game numbers
    QVector<double> m_game3Scores; ///< Contains game 3 scores

    int m_minAll, m_maxAll; ///< Contains minimum and maximum scores for all games

    QVector<QSpacerItem*> m_spacerItems; ///< Vector of used spacer items

    /**
    * \brief Sets the connections for the buttons
    */
    void setConnections();

    /**
    * \brief Sets the layout for the My Account page
    */
    void setMyAccountLayout();

    /**
    * \brief Initializes the score vectors for all games
    */
    void setScoreVectors();
};

#endif // MYACCOUNT_H
