#include "game3scene.h"

Game3Scene::Game3Scene(Difficulty difficulty, Size size, QObject *parent) :
    QGraphicsScene(parent), m_difficulty(difficulty), m_size(size), m_dots(size+1),
    m_horizontalLines(size+1), m_verticalLines(size), m_boxes(size)
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
        firstX = 40;
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
            }
        }
    }
}

/**
* Frees allocated memory.
*/
Game3Scene::~Game3Scene() {
    for (int i=0; i<=m_size; ++i) {
        for (int j=0; j<=m_size; ++j) {
            delete m_dots[i][j];
            if (i != m_size-1) {
                delete m_horizontalLines[i][j];
            }
            if (j != m_size-1) {
                delete m_verticalLines[i][j];
            }
        }
    }
}
