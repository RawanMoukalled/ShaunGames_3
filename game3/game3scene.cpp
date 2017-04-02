#include "game3scene.h"

Game3Scene::Game3Scene(Difficulty difficulty, Size size, QObject *parent) :
    QGraphicsScene(parent), m_difficulty(difficulty), m_size(size), m_nbOfDots(2*pow(2.,size)+1), m_dots(m_nbOfDots)
{
    for (int i=0; i<m_nbOfDots; ++i) {
        for (int j=0; j<m_nbOfDots; ++j) {
            m_dots[i].push_back(new Dot);
            m_dots[i][j]->setPos(i*30,j*30);
            addItem(m_dots[i][j]);
        }
    }
}

Game3Scene::~Game3Scene() {
    for (int i=0; i<m_nbOfDots; ++i) {
        for (int j=0; j<m_nbOfDots; ++j) {
            delete m_dots[i][j];
        }
    }
}
