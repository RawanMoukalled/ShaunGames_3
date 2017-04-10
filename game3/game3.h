#ifndef GAME3_H
#define GAME3_H

#include <QtGui>
#include "difficulty.h"
#include "game3/size.h"
#include "game3/game3scene.h"

/**
* \file game3.h
* \brief Dots and Lines class
*
* This is the class for the gameplay of the Dots and Lines game.
* \author Rita Aoun
* \author Rawan Moukalled
*/
class Game3 : public QWidget
{
    Q_OBJECT
public:
    /**
    * \brief Default constructor
    */
    explicit Game3(Difficulty difficulty, Size size, bool resume = false, QWidget *parent = 0);

    /**
    * \brief Destrucor
    */
    virtual ~Game3();

signals:

public slots:
    /**
    * \brief Removes save and exit button and adds replay and back buttons
    */
    void endGame();

    /**
    * \brief Removes save and exit button and adds replay and back buttons
    */
    void replay();

    /**
    * \brief Slot to go back to the games main menu when pressing Exit
    */
    void goToMainMenu();

    /**
    * \brief Saves and exits
    */
    void save();

    /**
    * \brief Deletes the saved game on close
    * \param bar The event triggered
    */
    void closeEvent(QCloseEvent *bar);

private:
    const Difficulty m_difficulty; ///< Difficulty of the game in the scene
    const Size m_size; ///< Size of the game in the scene
    QLabel *m_title; ///< Game title
    QPushButton *m_exit; ///< Button to save and exit
    QVBoxLayout *m_Game3Layout; ///< Layout of widget

    QGraphicsView *m_gameView; ///< Game view that has the game scene
    Game3Scene *m_gameScene; ///< Game3 scene

    QPushButton *m_goBack; ///< Button to go back to game menu
    QPushButton *m_replay; ///< Button to replay the game

    bool m_justSaved; ///< Remembers whether a new game has just been saved

    /**
    * \brief Sets the different graphic items in one layout for the game
    */
    void setGame3Layout();
};

#endif // Game3_H
