#ifndef GAME3OPTIONS_H
#define GAME3OPTIONS_H

#include <QtGui>
#include "difficulty.h"

/**
* \file game3options.h
* \brief Game3Options class
*
* This is the options page for game 3, where the user can choose the level and size with which to start the game.
* Levels are: Easy, Moderate and Hard.
*
* \author Rita Aoun
* \author Rawan Moukalled
*/
class Game3Options : public QWidget
{
    Q_OBJECT
public:
    /**
    * \brief Constructor
    */
    explicit Game3Options(QWidget *parent = 0);

    /**
    * \brief Destructor
    */
    virtual ~Game3Options();
    
signals:
    
public slots:
    /**
    * \brief Takes the user to the game main menu
    */
    void gotoGameMainMenu();

    /**
    * \brief Takes the user to game 3
    */
    void gotoGame();

    /**
    * \brief Sets the game difficulty to Easy
    */
    void setEasy();

    /**
    * \brief Sets the game difficulty to Moderate
    */
    void setModerate();

    /**
    * \brief Sets the game difficulty to Hard
    */
    void setHard();

    /**
    * \brief Sets the game size to 4x4
    */
    void setSizeFour();

    /**
    * \brief Sets the game size to 8x8
    */
    void setSizeEight();

    /**
    * \brief Sets the game size to 16x16
    */
    void setSizeSixteen();

private:
    QLabel *m_instructions; ///< Asks the user to pick a level

    Difficulty m_level;
    QPushButton *m_easy; ///< Allows the user to pick the "Easy" level
    QPushButton *m_moderate; ///< Allows the user to pick the "Medium" level
    QPushButton *m_hard; ///< Allows the user to pick the "Hard" level

    int m_size;
    QPushButton *m_sizeFour; ///< Allows the user to pick the 4x4 size
    QPushButton *m_sizeEight; ///< Allows the user to pick the 8x8 size
    QPushButton *m_sizeSixteen; ///< Allows the user to pick the 16x16 size

    QPushButton *m_play; ///< Takes the user to the game using the selected options
    QPushButton *m_back; ///< Allows the user to go back to the game main menu

    QVBoxLayout *m_mainLayout; ///< Main layout of the page
    QHBoxLayout *m_levelLayout; ///< Layout of the level buttons
    QHBoxLayout *m_sizeLayout; ///< Layout of the size buttons

    QVector<QSpacerItem*> m_spacerItems; ///< Vector of used spacer items

    /**
    * \brief Sets the main layout of the widget
    */
    void setMainLayout();

    /**
    * \brief Sets the layout of the level buttons
    */
    void setLevelLayout();

    /**
    * \brief Sets the layout of the size buttons
    */
    void setSizeLayout();
};

#endif // GAME3OPTIONS_H
