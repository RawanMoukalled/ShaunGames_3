#ifndef GAMEMAINMENU_H
#define GAMEMAINMENU_H

#include <QtGui>

/**
* \file gamemainmenu.h
* \brief GameMainMenu class
*
* This is the main game menu, where the user choose between resuming a previous game or starting a new one.
* The instructions are also shown on this menu.
* \author Rita Aoun
* \author Rawan Moukalled
*/
class GameMainMenu : public QWidget
{
    Q_OBJECT
public:
    /**
    * \brief Constructor
    */
    explicit GameMainMenu(int gameChoice, QWidget *parent = 0);

    /**
    * \brief Destructor
    */
    virtual ~GameMainMenu();
    
signals:
    
public slots:
    /**
    * \brief Takes the user to the game options
    */
    void gotoGameOptions();

    /**
    * \brief Takes the user to the game selection menu
    */
    void gotoGameSelection();
    
private:
    int m_gameChoice; ///< Game choice that brought the user here
    QLabel *m_gameTitle; ///< Label that displays the game name
    QPushButton *m_back; ///< Button that takes the user back to the game selection menu
    QPushButton *m_play; ///< Button that takes the user to the new game option selection window
    QPushButton *m_resume; ///< Button that allows the user to resume last game
    QLabel *m_instructions; ///< Instructions of selected game

    QVBoxLayout *m_layout; ///< Layout of the page

    /**
    * \brief Sets the main layout of the page
    */
    void setMainLayout();
};

#endif // GAMEMAINMENU_H
