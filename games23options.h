#ifndef GAMES23OPTIONS_H
#define GAMES23OPTIONS_H

#include <QtGui>

/**
* \file games23options.h
* \brief Games23Options class
*
* This is the options page for games 2 and 3, where the user can choose the level with which to start the game.
* Levels are: Easy, Medium and Hard.
* \author Rita Aoun
* \author Rawan Moukalled
*/
class Games23Options : public QWidget
{
    Q_OBJECT
public:
    /**
    * \brief Constructor
    */
    explicit Games23Options(int gameNumber, QWidget *parent = 0);

    /**
    * \brief Destructor
    */
    virtual ~Games23Options();
    
signals:
    
public slots:
    /**
    * \brief Takes the user to the game main menu
    */
    void gotoGameMainMenu();

    /**
    * \brief Takes the user to game 2 or 3
    */
    void gotoGame();

private:
    int m_gameNumber; ///< Selected game
    QLabel *m_instructions; ///< Asks the user to pick a level
    QPushButton *m_easy; ///< Allows the user to pick the "Easy" level
    QPushButton *m_medium; ///< Allows the user to pick the "Medium" level
    QPushButton *m_hard; ///< Allows the user to pick the "Hard" level
    QPushButton *m_back; ///< Allows the user to go back to the game main menu
    QVBoxLayout *m_mainLayout; ///< Main layout of the page
    QHBoxLayout *m_levelLayout; ///< Layout of the level buttons

    /**
    * \brief Sets the main layout of the widget
    */
    void setMainLayout();

    /**
    * \brief Sets the layout of the level buttons
    */
    void setLevelLayout();
};

#endif // GAMES23OPTIONS_H
