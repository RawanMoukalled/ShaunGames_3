#include "game2scene.h"

Game2Scene::Game2Scene(Difficulty difficulty, QObject *parent) :
    QGraphicsScene(parent), m_difficulty(difficulty), m_score(0)
{

}
