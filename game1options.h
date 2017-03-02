#ifndef GAME1OPTIONS_H
#define GAME1OPTIONS_H

#include <QWidget>
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
    
signals:
    
public slots:
    /**
    * \brief Takes the user to the game main menu
    */
    void gotoGameMainMenu();

    /**
    * \brief Takes the user to game 1
    */
    void gotoGame1();
    
private:
    QLabel *m_instructions; ///< Asks the user to pick a level
    QPushButton *m_levels[25]; ///< Allow the user to pick one of the 25 levels of game 1
    QPushButton *m_back; ///< Allows the user to go back to the game main menu
    QVBoxLayout *m_mainLayout; ///< Main layout of the page
    QGridLayout *m_levelLayout; ///< Layout of the level buttons

    /**
    * \brief Sets the main layout of the widget
    */
    void setMainLayout();

    /**
    * \brief Sets the layout of the level buttons
    */
    void setLevelLayout();
};

#endif // GAME1OPTIONS_H
