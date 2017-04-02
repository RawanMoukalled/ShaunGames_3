#ifndef GAME2_H
#define GAME2_H

#include <QtGui>
#include "difficulty.h"
#include "game2/game2scene.h"

/**
* \file game2.h
* \brief Trap the Sheep class
*
* This is the class for the gameplay of the Trap the Sheep game.
* \author Rita Aoun
* \author Rawan Moukalled
*/
class Game2 : public QWidget
{
    Q_OBJECT
public:
    /**
    * \brief Default constructor
    */
    explicit Game2(Difficulty difficulty, QWidget *parent = 0);

    /**
    * \brief Destructor
    */
    virtual ~Game2();

signals:

public slots:
    /**
    * \brief Slot to go back to the games main menu when pressing Exit
    */
    void goToMainMenu();

private:
    QLabel *m_title; ///< Game title
    QPushButton *m_exit; ///< Button to save and exit
    QVBoxLayout *m_Game2Layout; ///< Layout of widget

    QGraphicsView *m_gameView; ///< Game view that has the game scene
    Game2Scene *m_gameScene; ///< Game 2 scene

    Difficulty m_difficulty; ///< Difficulty selected

    QVector<QSpacerItem*> m_spacerItems; ///< Vector of used spacer items

    /**
    * \brief Sets the different graphic items in one layout for the game
    */
    void setGame2Layout();
};

#endif // Game2_H
