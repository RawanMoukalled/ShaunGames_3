#ifndef GAME3SCENE_H
#define GAME3SCENE_H

#include <QtGui>
#include "difficulty.h"
#include "game3/size.h"
#include "game3/dot.h"
#include "game3/horizontalline.h"
#include "game3/verticalline.h"

class Game3Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    /**
    * \brief Constructor
    */
    explicit Game3Scene(Difficulty difficulty, Size size, QObject *parent = 0);

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
    
signals:
    
public slots:
    /**
    * \brief Computer move
    */
    void computerMove();

private:
    const Difficulty m_difficulty;
    const Size m_size;
    bool m_userTurn;
    QVector< QVector<Dot*> > m_dots;
    QVector< QVector<HorizontalLine*> > m_horizontalLines;
    QVector< QVector<VerticalLine*> > m_verticalLines;
    QVector< QVector<Box*> > m_boxes;
    QTimer *m_delay; ///< Delay on computer's turn

    QVector<Line*> m_newLines; ///< Keeps track of newly drawn lines
};

#endif // GAME3SCENE_H
