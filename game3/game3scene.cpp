#include "game3scene.h"

/**
* \file game3scene.cpp
* \brief Contains Game3Scene class definition
*/

/**
* Initializes the difficulty, size, dots, lines and boxes of the game.
*/
Game3Scene::Game3Scene(Difficulty difficulty, Size size, QObject *parent) :
    QGraphicsScene(parent), m_difficulty(difficulty), m_size(size), m_userTurn(true), m_boxesClosedByUser(0),
    m_boxesClosedByComputer(0), m_score(0), m_dots(size+1), m_horizontalLines(size+1), m_verticalLines(size), m_boxes(size),
    m_unmarkedLines(), m_newLines()
{
    int firstX, firstY;
    if (size == FOURBYFOUR) {
        firstX = 230;
        firstY = 180;
    }
    else if (size == EIGHTBYEIGHT){
        firstX = 170;
        firstY = 130;
    }
    else {
        firstX = 60;
        firstY = 10;
    }

    for (int i=0; i<size; ++i) {
        for (int j=0; j<size; ++j) {
            m_boxes[i].push_back(new Box);
            m_boxes[i][j]->setPos(firstX+j*30,firstY+i*30);
            addItem(m_boxes[i][j]);
        }
    }

    for (int i=0; i<=size; ++i) {
        for (int j=0; j<=size; ++j) {
            m_dots[i].push_back(new Dot);
            m_dots[i][j]->setPos(firstX+j*30,firstY+i*30);
            addItem(m_dots[i][j]);

            if (j != size) {
                if (i == 0) {
                    m_horizontalLines[i].push_back(new HorizontalLine(NULL, m_boxes[0][j]));
                }
                else if (i < size) {
                    m_horizontalLines[i].push_back(new HorizontalLine(m_boxes[i-1][j], m_boxes[i][j]));
                }
                else {
                    m_horizontalLines[i].push_back(new HorizontalLine(m_boxes[i-1][j], NULL));
                }
                m_horizontalLines[i][j]->setPos(firstX+7+j*30,firstY+4+i*30);
                addItem(m_horizontalLines[i][j]);
                m_unmarkedLines.push_back(m_horizontalLines[i][j]);
            }

            if (i != size) {
                if (j == 0) {
                    m_verticalLines[i].push_back(new VerticalLine(NULL, m_boxes[i][j]));
                }
                else if (j < size) {
                    m_verticalLines[i].push_back(new VerticalLine(m_boxes[i][j-1], m_boxes[i][j]));
                }
                else {
                    m_verticalLines[i].push_back(new VerticalLine(m_boxes[i][j-1], NULL));
                }
                m_verticalLines[i][j]->setPos(firstX+5+j*30,firstY+4+i*30);
                addItem(m_verticalLines[i][j]);
                m_unmarkedLines.push_back(m_verticalLines[i][j]);
            }
        }
    }

    m_delay = new QTimer(this);
    connect(m_delay, SIGNAL(timeout()), this, SLOT(computerMove()));

    m_scoreDisplay = new QLCDNumber(4);
    addWidget(m_scoreDisplay);
    m_scoreDisplay->move(5,20);

    QPalette lcdPalette = m_scoreDisplay->palette();
    lcdPalette.setColor(QPalette::Background, QColor(170, 255, 0));
    lcdPalette.setColor(QPalette::WindowText, QColor(85, 85, 255));
    lcdPalette.setColor(QPalette::Light, QColor(255, 0, 0));
    lcdPalette.setColor(QPalette::Dark, QColor(255, 0, 0));

    m_scoreDisplay->setPalette(lcdPalette);
}

/**
* Frees allocated memory.
*/
Game3Scene::~Game3Scene() {
    for (int i=0; i<m_size; ++i) {
        for (int j=0; j<m_size; ++j) {
            delete m_boxes[i][j];
        }
    }
    for (int i=0; i<=m_size; ++i) {
        for (int j=0; j<=m_size; ++j) {
            delete m_dots[i][j];
            if (j != m_size) {
                delete m_horizontalLines[i][j];
            }
            if (i != m_size) {
                delete m_verticalLines[i][j];
            }
        }
    }
    delete m_delay;
    delete m_scoreDisplay;
    delete m_gameOverPicture;
}

/**
* Starts a delay to call computerMove().
*/
void Game3Scene::computerTurn() {
    m_userTurn = false;
    m_delay->start(1000);
}

/**
* Returns whether it is the user's turn to play.
*/
bool Game3Scene::isUserTurn() {
    return m_userTurn;
}

/**
* Picks a line to select according to difficulty, and plays the turn.
*/
void Game3Scene::computerMove() {
    m_delay->stop();
    static bool firstTime(true);
    if (firstTime) {
        clearNewLines();
        firstTime = false;
    }
    Line *line;
    if (m_difficulty == EASY) {
        line = m_unmarkedLines[rand() % m_unmarkedLines.size()];
    }
    else if (m_difficulty == MODERATE) {
        line = getLineThatClosesBox();
        if (line == NULL) {
            line = m_unmarkedLines[rand() % m_unmarkedLines.size()];
        }
    }
    else {
        line = getLineThatClosesBox();
        if (line == NULL) {
            line = getSmartLine();
            if (line == NULL) {
                line = m_unmarkedLines[rand() % m_unmarkedLines.size()];
            }
        }
    }

    addNewlyDrawnLine(line);
    if (line->playTurn(false)) {
        computerTurn();
    }
    else {
        m_userTurn = true;
        firstTime = true;
    }
}

/**
* Remembers newly drawn line so it can be turned grey later.
* Also removes the line from the list of unmarked lines.
*/
void Game3Scene::addNewlyDrawnLine(Line *line) {
    m_newLines.push_back(line);
    int i = m_unmarkedLines.indexOf(line);
    m_unmarkedLines.remove(i);
}

/**
* Clears new lines by turning them grey and removing them from the vector.
*/
void Game3Scene::clearNewLines() {
    for (QVector<Line*>::iterator it = m_newLines.begin(); it != m_newLines.end(); ++it) {
        (*it)->turnGrey();
    }
    m_newLines.erase(m_newLines.begin(), m_newLines.end());
}

/**
* Ends the game.
*/
void Game3Scene::gameOver() {
    m_gameOverPicture = new GameOver(m_boxesClosedByUser > m_boxesClosedByComputer);
    addItem(m_gameOverPicture);

    emit done();
}

/**
* Returns whether there are any unmarked lines left.
*/
bool Game3Scene::noMoreMoves() {
    return m_unmarkedLines.empty();
}

/**
* Declares one more box as closed by user.
*/
void Game3Scene::closeBoxByUser() {
    ++m_boxesClosedByUser;
    m_score = m_score + 100;
    m_scoreDisplay->display(m_score);
}

/**
* Declares one more box as closed by computer.
*/
void Game3Scene::closeBoxByComputer() {
    ++m_boxesClosedByComputer;
}

/**
* Finds and returns a non-clicked line that closes at least one box.
* Returns NULL if not found.
*/
Line *Game3Scene::getLineThatClosesBox() {
    QVector<Line*> potentialLines;
    for (QVector<Line*>::iterator it = m_unmarkedLines.begin(); it != m_unmarkedLines.end(); ++it) {
        if ((*it)->isHorizontal()) {
            HorizontalLine *line = static_cast<HorizontalLine*>(*it);
            Box *above = line->getAbove();
            Box *under = line->getUnder();
            if (above != NULL && above->numberOfLinesDrawn() == 3) {
                potentialLines.push_back(line);
            }
            else if (under != NULL && under->numberOfLinesDrawn() == 3) {
                potentialLines.push_back(line);
            }
        }
        else {
            VerticalLine *line = static_cast<VerticalLine*>(*it);
            Box *left = line->getLeft();
            Box *right = line->getRight();
            if (left != NULL && left->numberOfLinesDrawn() == 3) {
                potentialLines.push_back(line);
            }
            else if (right != NULL && right->numberOfLinesDrawn() == 3) {
                potentialLines.push_back(line);
            }
        }
    }
    if (potentialLines.empty()) {
        return NULL;
    }
    else {
        int size = potentialLines.size();
        return potentialLines.at(rand() % size);
    }
}

/**
* Finds and returns a non-clicked line that does not let the user close a box.
* It does so by checking that the returned line is not the third line to be drawn around any box.
* If such a line is not found, it returns NULL.
*/
Line *Game3Scene::getSmartLine() {
    QVector<Line*> potentialLines;
    for (QVector<Line*>::iterator it = m_unmarkedLines.begin(); it != m_unmarkedLines.end(); ++it) {
        if ((*it)->isHorizontal()) {
            HorizontalLine *line = static_cast<HorizontalLine*>(*it);
            Box *above = line->getAbove();
            Box *under = line->getUnder();
            if ((above == NULL || above->numberOfLinesDrawn() < 2) && (under == NULL || under->numberOfLinesDrawn() < 2)) {
                potentialLines.push_back(line);
            }
        }
        else {
            VerticalLine *line = static_cast<VerticalLine*>(*it);
            Box *left = line->getLeft();
            Box *right = line->getRight();
            if ((left == NULL || left->numberOfLinesDrawn() < 2) && (right == NULL || right->numberOfLinesDrawn() < 2)) {
                potentialLines.push_back(line);
            }
        }
    }
    if (potentialLines.empty()) {
        return NULL;
    }
    else {
        int size = potentialLines.size();
        return potentialLines.at(rand() % size);
    }
}
