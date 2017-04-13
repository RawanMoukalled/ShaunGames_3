#ifndef GAME3SCENE_H
#define GAME3SCENE_H

#include <QtGui>
#include "difficulty.h"
#include "game3/size.h"
#include "game3/dot.h"
#include "game3/horizontalline.h"
#include "game3/verticalline.h"
#include "gameover.h"

/**
* \file game3scene.h
* \brief Game3Scene class
*
* This is the scene for game 3, Dots and Lines.
*
* \author Rita Aoun
* \author Rawan Moukalled
*/
class Game3Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    /**
    * \brief Constructor
    * \param difficulty Difficulty of the game
    * \param size Size of the game
    * \param resume Whether this is a new game
    */
    explicit Game3Scene(Difficulty difficulty, Size size, bool resume = false, QObject *parent = 0);

    /**
    * \brief Destructor
    */
    virtual ~Game3Scene();

    /**
    * \brief Computer turn
    */
    void computerTurn();

    /**
    * \brief Returns whose turn it is to play
    * \returns Whether it is the user's turn to play
    */
    bool isUserTurn();

    /**
    * \brief Remembers newly drawn line
    * \param line Newly drawn line
    */
    void addNewlyDrawnLine(Line *line);

    /**
    * \brief Clears new lines by turning them grey
    */
    void clearNewLines();

    /**
    * \brief Triggers finishing the game
    */
    void gameOver();

    /**
    * \brief Returns whether there are any moves left
    * \returns Whether there are any unmarked lines left
    */
    bool noMoreMoves();

    /**
    * \brief Declares one more box as closed by user
    */
    void closeBoxByUser();

    /**
    * \brief Declares one more box as closed by computer
    */
    void closeBoxByComputer();

    /**
    * \brief Finds and returns a non-clicked line that closes at least one box
    * \returns Non-clicked line that closes a box
    */
    Line *getLineThatClosesBox() const;

    /**
    * \brief Finds and returns a non-clicked line that does not let the user close a box
    * \returns Non-clicked line that does not let the user close a box next
    */
    Line *getSmartLine() const;

    /**
    * \brief Freezes gameplay
    */
    void freeze();

    /**
    * \brief Returns the game score
    * \returns Game score
    */
    int getScore() const;

    /**
    * \brief Returns which boxes have been closed by the user
    * \returns QString listing boxes that have been closed by the user
    */
    QString getBoxesClosedByUser() const;

    /**
    * \brief Returns which boxes have been closed by the PC
    * \returns QString listing boxes that have been closed by the PC
    */
    QString getBoxesClosedByPC() const;

    /**
    * \brief Returns which horizontal lines have already been drawn
    * \returns QString listing horizontal lines that have been drawn
    */
    QString getDrawnHorizontalLines() const;

    /**
    * \brief Returns which vertical lines have already been drawn
    * \returns QString listing vertical lines that have been drawn
    */
    QString getDrawnVerticalLines() const;
    
signals:
    /**
    * \brief Signals Game3 that the game is over
    */
    void done();
    
public slots:
    /**
    * \brief Computer move
    */
    void computerMove();

private:
    const Difficulty m_difficulty; ///< Game difficulty
    const Size m_size; ///< Number of boxes per side
    bool m_userTurn; ///< True if it's the user's turn, False if it is the computer's turn
    int m_boxesClosedByUser; ///< Number of boxes closed by user
    int m_boxesClosedByComputer; ///< Number of boxes closed by computer
    int m_score; ///< User score

    QVector< QVector<Dot*> > m_dots; ///< Dot objects
    QVector< QVector<HorizontalLine*> > m_horizontalLines; ///< Horizontal line objects
    QVector< QVector<VerticalLine*> > m_verticalLines; ///< Vertical line objects
    QVector< QVector<Box*> > m_boxes; ///< Box objects
    QTimer *m_delay; ///< Delay on computer's turn

    QVector<Line*> m_unmarkedLines; ///< Keeps track of unmarked lines so the computer chooses from them
    QVector<Line*> m_newLines; ///< Keeps track of newly drawn lines

    GameOver *m_gameOverPicture; ///< Overlayed on top of the game to show Game Over
    QLCDNumber *m_scoreDisplay; ///< Displays the game score
};

#endif // GAME3SCENE_H
