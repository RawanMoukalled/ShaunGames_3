#ifndef GAME1OPTIONS_H
#define GAME1OPTIONS_H

#include <QtGui>

/**
* \file game1options.h
* \brief Game1Options class
*
* This is the options page for game 1, where the user can choose the level with which to start the game.
* Only unlocked levels can be accessed.
* \author Rita Aoun
* \author Rawan Moukalled
*/
class Game1Options : public QWidget
{
    Q_OBJECT
public:
    /**
    * \brief Default constructor
    */
    explicit Game1Options(QWidget *parent = 0);

    /**
    * \brief Destructor
    */
    virtual ~Game1Options();

    /**
    * \brief Returns the number of levels in game 1 that the user has unlocked
    * \returns Number of levels
    */
    static int getNumberOfUnlockedLevels();

    /**
    * \brief Unlocks one new game 1 level if appropriate
    * \param currLevel Level that was just won
    */
    static void unlockExtraLevel(int currLevel);
    
signals:
    
public slots:
    /**
    * \brief Takes the user to the game main menu
    */
    void gotoGameMainMenu();

    /**
    * \brief Takes the user to game 1
    * \param The level of the game
    */
    void gotoGame1(int level);
    
private:
    static int m_numberOfUnlockedLevels; ///< Number of levels that the user has unlocked

    QLabel *m_instructions; ///< Asks the user to pick a level
    QPushButton *m_levels[25]; ///< Allow the user to pick one of the 25 levels of game 1
    QPushButton *m_back; ///< Allows the user to go back to the game main menu
    QVBoxLayout *m_mainLayout; ///< Main layout of the page
    QGridLayout *m_levelLayout; ///< Layout of the level buttons
    QSignalMapper *m_signalMapper; ///< Maps signals to slots to allow for level selection to be passed

    /**
    * \brief Sets the main layout of the widget
    */
    void setMainLayout();

    /**
    * \brief Sets the layout of the level buttons
    */
    void setLevelLayout();

    /**
    * \brief Sets the connections of all buttons
    */
    void setConnections();
};

#endif // GAME1OPTIONS_H
