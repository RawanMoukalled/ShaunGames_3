#ifndef GAME1_H
#define GAME1_H

#include <QWidget>
#include <QtGui>

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
    * \brief Default constructor
    */
    explicit Game1(QWidget *parent = 0);
    
signals:
    
public slots:
    /**
    * \brief Slot to go back to the games main menu when pressing Exit
    */
    void goToMainMenu();
    
private:
    QLabel *m_title; //<Main title of the game
    QPushButton *m_exit; //<Button to take the user to the game main menu
    QVBoxLayout *m_game1Layout; //<Layout for Sheep Line

    /**
    * \brief Sets the different graphic items in one layout for the game
    */
    void setGame1Layout();
};

#endif // GAME1_H
