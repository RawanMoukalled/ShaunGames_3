#ifndef GAME3_H
#define GAME3_H

#include <QWidget>
#include <QtGui>

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
    explicit Game3(QWidget *parent = 0);

signals:

public slots:
    /**
    * \brief Slot to go back to the games main menu when pressing Exit
    */
    void goToMainMenu();

private:
    QLabel *m_title;
    QPushButton *m_exit;
    QVBoxLayout *m_Game3Layout;

    /**
    * \brief Sets the different graphic items in one layout for the game
    */
    void setGame3Layout();
};

#endif // Game3_H
