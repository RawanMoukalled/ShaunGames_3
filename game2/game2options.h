#ifndef GAME2OPTIONS_H
#define GAME2OPTIONS_H

#include <QtGui>

/**
* \file game2options.h
* \brief Game2Options class
*
* This is the options page for game 2, where the user can choose the level with which to start the game.
* Levels are: Easy, Moderate and Hard.
* \author Rita Aoun
* \author Rawan Moukalled
*/
class Game2Options : public QWidget
{
    Q_OBJECT
public:
    /**
    * \brief Constructor
    */
    explicit Game2Options(QWidget *parent = 0);

    /**
    * \brief Destructor
    */
    virtual ~Game2Options();
    
signals:
    
public slots:
    /**
    * \brief Takes the user to the game main menu
    */
    void gotoGameMainMenu();

    /**
    * \brief Takes the user to game 2
    */
    void gotoGame();

private:
    QLabel *m_instructions; ///< Asks the user to pick a level
    QPushButton *m_easy; ///< Allows the user to pick the "Easy" level
    QPushButton *m_moderate; ///< Allows the user to pick the "Medium" level
    QPushButton *m_hard; ///< Allows the user to pick the "Hard" level
    QPushButton *m_back; ///< Allows the user to go back to the game main menu
    QVBoxLayout *m_mainLayout; ///< Main layout of the page
    QHBoxLayout *m_levelLayout; ///< Layout of the level buttons

    QVector<QSpacerItem*> m_spacerItems; ///< Vector of used spacer items

    /**
    * \brief Sets the main layout of the widget
    */
    void setMainLayout();

    /**
    * \brief Sets the layout of the level buttons
    */
    void setLevelLayout();
};

#endif // GAME2OPTIONS_H
