#ifndef GAME1_H
#define GAME1_H

#include <QtGui>
#include "game1/game1scene.h"

/**
* \file game1.h
* \brief Sheep Line class
*
* This is the class for the gameplay of the Sheep Line game.
* \author Rita Aoun
* \author Rawan Moukalled
*/
class Game1 : public QWidget
{
    Q_OBJECT
public:
    /**
    * \brief Constructor
    * \param level Game level
    * \param resume Whether this is a new game
    */
    explicit Game1(int level, bool resume = false, QWidget *parent = 0);

    /**
    * \brief Destructor
    */
    virtual ~Game1();

    /**
    * \brief Load new game
    * \param sameLevel Indicates if the level is the same
    */
    void loadNewGame(bool sameLevel);
    
signals:
    
public slots:
    /**
    * \brief Slot to go back to the games main menu when pressing Exit
    */
    void goToMainMenu();

    /**
    * \brief Slot to handle ending the game once it's over
    * \param win Indicates if the user has won the game
    */
    void endGame(bool win);

    /**
    * \brief Reloads the game with the same level
    */
    void replay();

    /**
    * \brief Proceed to the next level
    */
    void next();

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
    QLabel *m_title; ///< Main title of the game
    QPushButton *m_exit; ///< Button to take the user to the game main menu
    QVBoxLayout *m_game1Layout; ///< Layout for Sheep Line

    QGraphicsView *m_gameView; ///< Game view that has the game scene
    Game1Scene *m_gameScene; ///< Game1 scene

    QPushButton *m_goBack; ///< Go back to the game main menu
    QPushButton *m_replay; ///< Replay the same level
    QPushButton *m_next; ///< Proceed to the next level

    int m_level; ///<  Level selected

    bool m_justSaved; ///< Remembers whether the game has just been saved

    /**
    * \brief Sets the different graphic items in one layout for the game
    */
    void setGame1Layout();
};

#endif // GAME1_H
