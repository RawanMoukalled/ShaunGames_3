#ifndef GAMESELECTION_H
#define GAMESELECTION_H

#include <QtGui>

/**
* \file gameselection.h
* \brief Game selection menu class
*
* Game selection menu, where the user can select one of the three
* games available.
* \author Rita Aoun
* \author Rawan Moukalled
*/

class GameSelection : public QWidget
{
    Q_OBJECT
public:
    /**
    * \brief Default constructor
    */
    explicit GameSelection(QWidget *parent = 0);

    /**
    * \brief Destructor
    */
    virtual ~GameSelection();
    
signals:
    
public slots:

    /**
    * \brief Takes the user from the game selection menu to the My Account page
    */
    void goToMyAccount();

    /**
    * \brief Takes the user from the game selection menu to the main welcome window
    */
    void goToMain();

    /**
    * \brief Takes the user from the game selection menu to the Sheep Line game
    */
    void goToGame1();

    /**
    * \brief Takes the user from the game selection menu to the Trap the Sheep game
    */
    void goToGame2();

    /**
    * \brief Takes the user from the game selection menu to the Dots and Lines game
    */
    void goToGame3();

private:
    QToolButton *m_game1; //<Button for selecting Game1
    QToolButton *m_game2; //<Button for selecting Game2
    QToolButton *m_game3; //<Button for selecting Game3

    QLabel *m_title; //<Title of the page

    QPushButton *m_logoutButton; //<Button to log out of the application
    QPushButton *m_myAccountButton; //<Button to go to the My Account page

    QVBoxLayout *m_gameSelectionFullLayout; //<Layout of the full game selection menu
    QGridLayout *m_gamesListLayout; //<Layout of the buttons representing the games
    QHBoxLayout *m_linksListLayout; //<Layout of the log out and my account buttons

    /**
    * \brief Sets the layout for the full game selection menu
    */
    void setGamesSelectionFullLayout();

    /**
    * \brief Sets the layout for the log out and my account buttons
    */
    void setLinksListLayout();

    /**
    * \brief Sets the layout for the game buttons
    */
    void setGamesListLayout();

    /**
    * \brief Connects the button clicks of the game selection menu to their respective slots
    */
    void setConnections();
};

#endif // GAMESELECTION_H
