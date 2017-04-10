#include "game2scene.h"
#include <climits>
#include <QSqlQuery>
#include "helper.h"

/**
* \file game2scene.cpp
* \brief Contains Game2Scene class definition
*/

/**
* Places the items on the scene and sets the user turn.
*/
Game2Scene::Game2Scene(Difficulty difficulty, bool resume, QObject *parent) :
    QGraphicsScene(parent), m_score(0)
{
    m_difficulty = difficulty;

    if(resume) {
        bool opened = Helper::shaunDB.open();
        QSqlQuery query;
        if(opened) {
            query.exec("SELECT * FROM GAME2 WHERE ACCOUNTID='" + QString::number(Helper::getUserId()) +"'");
            query.next();
        }
        Helper::shaunDB.close();

        m_score = query.value(2).toInt();

        QString blockedtiles = query.value(5).toString();
        QStringList tilepositions = blockedtiles.split(",");
        qDebug()<<tilepositions.size();
        placeTilesResumed(tilepositions);

        QString sheeppos = query.value(4).toString();
        QStringList pos = sheeppos.split(",");
        int row = pos.at(0).toInt();
        int col = pos.at(1).toInt();
        Tile * currTile = tileAt(row, col);
        placeSheepInitialResumed(currTile);
        m_user_turn = query.value(3).toBool();
    } else {
        //starting blocks
        if(difficulty == EASY) {
            m_block_count = 10;
        } else if(difficulty == MODERATE) {
            m_block_count = 7;
        } else if(difficulty == HARD) {
            m_block_count = 5;
        }
        m_score = 1500;
        m_user_turn = true;

        placeTiles();
        placeSheepInitial();
    }

    placeLCD();
    m_gameOverPicture = NULL;

    m_delay = new QTimer(this);
    connect(m_delay, SIGNAL(timeout()), this, SLOT(moveSheep()));

    if(!m_user_turn) {
        moveSheep();
    }
}

/**
* Frees allocated memory.
*/
Game2Scene::~Game2Scene() {
    for (QVector< QVector< Tile* > >::iterator row=m_tiles.begin(); row!=m_tiles.end(); ++row) {
        for(QVector< Tile* >::iterator tile = (*row).begin(); tile!=(*row).end(); ++tile){
            delete *tile;
        }
    }

    delete m_sheep;
    delete m_delay;
    if(m_gameOverPicture != NULL) {
        delete m_gameOverPicture;
    }
    delete m_scoreDisplay;
}

void Game2Scene::placeLCD() {
    m_scoreDisplay = new QLCDNumber(4);
    addWidget(m_scoreDisplay);
    m_scoreDisplay->move(250,5);

    QPalette lcdPalette = m_scoreDisplay->palette();
    lcdPalette.setColor(QPalette::Background, QColor(170, 255, 0));
    lcdPalette.setColor(QPalette::WindowText, QColor(85, 85, 255));
    lcdPalette.setColor(QPalette::Light, QColor(255, 0, 0));
    lcdPalette.setColor(QPalette::Dark, QColor(255, 0, 0));

    m_scoreDisplay->setPalette(lcdPalette);
    m_scoreDisplay->display(m_score);
}

/**
* chooses distinct random tiles to flag for blocking initially at the start of the game.
*/
QVector<int> Game2Scene::tilesToBlock() {
    //flag some tiles as blocked initially

    int blocks = 0; //number of blocks so far
    QVector<int> flagged; //the tiles that will be initially blocked
    while(blocks < m_block_count) {
        int random = rand()%150; //tile between 0 and 149
        bool found = false;
        //search for this tile in the existing flags. If not found, flag it
        QVector<int>::iterator it;
        for (it = flagged.begin(); it != flagged.end(); ++it)  {
          if (*it == random){
            found = true;
            break;
          }
        }

        if(!found) {
            flagged.push_back(random);
            blocks++;
        }
    }

    return flagged;
}

/**
* Places the tiles on the grid of the game.
*/
void Game2Scene::placeTiles() {
    QVector<int> flagged = tilesToBlock();
    bool even = false; //to alternate between 12 and 13
    int column_size;


    double left = 44.5;
    double top = 38.5;
    int offset;

    int count = 0;

    for(int i = 0; i < 12; i++) {
        QVector< Tile* > row;
        if(!even) {
            column_size = 13;
            offset = 0;

        } else {
            column_size = 12;
            offset = 22.5;
        }


        for(int j = 0; j < column_size; j++) {
            Tile *tile;

            //if the tile is blocked
            if ( std::find(flagged.begin(), flagged.end(), count) != flagged.end() ) {
                tile = new Tile(true, i, j);
                m_blockedTiles.push_back(tile);
            } else {
                tile = new Tile(false, i, j);
            }

            tile->setPos(offset + j*left,30+i*top);
            row.push_back(tile);
            addItem(tile);
            count++;
        }
        even = !even;

        m_tiles.push_back(row);
    }
}

/**
* Places tiles with blocks loaded from previously saved game
*/
void Game2Scene::placeTilesResumed(QStringList positions) {
    bool even = false; //to alternate between 12 and 13
    int column_size;

    double left = 44.5;
    double top = 38.5;
    int offset;

    int count = 0;

    for(int i = 0; i < 12; i++) {
        QVector< Tile* > row;
        if(!even) {
            column_size = 13;
            offset = 0;

        } else {
            column_size = 12;
            offset = 22.5;
        }

        for(int j = 0; j < column_size; j++) {
            Tile *tile;

            tile = new Tile(false, i, j);

            tile->setPos(offset + j*left,30+i*top);
            row.push_back(tile);
            addItem(tile);
            count++;
        }
        even = !even;

        m_tiles.push_back(row);
    }

    //set blocks
    qDebug()<<positions.size();
    //TODO DONT FORGET TO ADD TO M_BLOCKEDTILES
}

/**
* Chooses a random tile to place the sheep on at the beginning of the game.
*/
void Game2Scene::placeSheepInitial() {
    int row, col;
    //place sheep on a tile that is not blocked
    Tile * sheep_tile;
    do{
        row = rand()%2 + 5;
        col = rand()%2 +5;
        sheep_tile = (m_tiles.at(row)).at(col);
    } while(sheep_tile->isBlocked());

    m_sheep = new Sheep2(sheep_tile);

    addItem(m_sheep);
}

/**
* Chooses a random tile to place the sheep on at the beginning of the game.
*/
void Game2Scene::placeSheepInitialResumed(Tile * tile) {
    m_sheep = new Sheep2(tile);
    addItem(m_sheep);
}

/**
* Gets the left, right, upper and bottom neighbors for the given tile.
* Memory is allocated in this function and should be freed by the caller.
*/
QVector< Tile* > * Game2Scene::getNeighbors(Tile * center) {
  QVector< Tile* > * neighbors = new QVector< Tile* >;

  int i = center->getRow();
  int j = center->getCol();

  Tile * left;
  Tile * right;
  Tile * topLeft;
  Tile * topRight;
  Tile * bottomLeft;
  Tile * bottomRight;

  if(j != 0) {
      left = (m_tiles.at(i)).at(j-1);
      if (!left->isBlocked()) {
          neighbors->push_back(left);
      }
  }


  //on row with 13 columns
  if(i % 2 == 0) {
      //right
      if(j != 12) {
          right = (m_tiles.at(i)).at(j+1);
          if (!right->isBlocked()) {
               neighbors->push_back(right);
          }
      }

      //top right and top left
      if(i != 0) {
          if (j != 12)
          {
              topRight = (m_tiles.at(i-1)).at(j);
              if (!topRight->isBlocked()) {
                    neighbors->push_back(topRight);
              }
          }
          if(j != 0) {
              topLeft = (m_tiles.at(i-1)).at(j-1);
              if (!topLeft->isBlocked()) {
                    neighbors->push_back(topLeft);
              }
          }
      }

      //bottom right and bottom left
      if(i != 11) {
          if(j != 12){
            bottomRight = (m_tiles.at(i+1)).at(j);
            if (!bottomRight->isBlocked()) {
                neighbors->push_back(bottomRight);
            }
          }
          if(j != 0) {
            bottomLeft = (m_tiles.at(i+1)).at(j-1);
            if (!bottomLeft->isBlocked()) {
                neighbors->push_back(bottomLeft);
            }
          }
      }
  }

  //on row with 12 columns
  else {
      //right
      if(j != 11) {
          right = (m_tiles.at(i)).at(j+1);
          if (!right->isBlocked()) {
                neighbors->push_back(right);
          }
      }

      //top right and top left
      if(i != 0) {
          topLeft = (m_tiles.at(i-1)).at(j);
          if(!topLeft->isBlocked()) {
                neighbors->push_back(topLeft);
          }
          topRight = (m_tiles.at(i-1)).at(j+1);
          if(!topRight->isBlocked()) {
              neighbors->push_back(topRight);
            }
      }

      //bottom right and bottom left
      if(i != 11) {
          bottomLeft = (m_tiles.at(i+1)).at(j);
          if (!bottomLeft->isBlocked()) {
              neighbors->push_back(bottomLeft);
          }

          bottomRight = (m_tiles.at(i+1)).at(j+1);
          if (!bottomRight->isBlocked()) {
              neighbors->push_back(bottomRight);
          }
      }
  }

  return neighbors;
}

/**
* Resets the status of the grid tiles as not visited.
*/
void Game2Scene::resetVisited() {
    QVector< QVector< Tile*> >::iterator row;
    for (row = m_tiles.begin(); row != m_tiles.end(); ++row) {
        QVector< Tile*>::iterator tile;
        for (tile = (*row).begin(); tile != (*row).end(); ++tile) {
            (*tile)->setVisited(false);
        }
    }
    m_sheep->getCurrent()->setVisited(true);
}

/**
* Resets the status of the grid tiles as having infinite distance to the sheep.
*/
void Game2Scene::resetDistances() {
    QVector< QVector< Tile*> >::iterator row;
    for (row = m_tiles.begin(); row != m_tiles.end(); ++row) {
        QVector< Tile*>::iterator tile;
        for (tile = (*row).begin(); tile != (*row).end(); ++tile) {
            (*tile)->setDistance(INT_MAX);
        }
    }
    m_sheep->getCurrent()->setDistance(0);
}

/**
* Resets the status of the grid tiles as having their previous tile NULL.
*/
void Game2Scene::resetPrevious() {
    QVector< QVector< Tile*> >::iterator row;
    for (row = m_tiles.begin(); row != m_tiles.end(); ++row) {
        QVector< Tile*>::iterator tile;
        for (tile = (*row).begin(); tile != (*row).end(); ++tile) {
            (*tile)->setPrev(NULL);
        }
    }
}

/**
* Gets the tile at the given indices.
*/
Tile* Game2Scene::tileAt(int i, int j) {
    return (m_tiles.at(i)).at(j);
}

/**
* Determines a win by checking if from the current sheep position
* it's possible to get to the border without encountering a blocked tile.
*/
bool Game2Scene::win(Tile * tile) {
    QVector<Tile*> * neighbors = getNeighbors(tile);

    QVector< Tile* >::iterator neighbor;
    for (neighbor = neighbors->begin(); neighbor != neighbors->end(); ++neighbor)  {
        if ((*neighbor)->isBorder()) {
            delete neighbors;
            return false;
        }
        if (!(*neighbor)->isVisited()) {
            (*neighbor)->setVisited(true);
            if (!win(*neighbor)) {
                delete neighbors;
                return false;
            }
        }
    }
    delete neighbors;
    return true;
}

/**
* Retrieves the sheep.
*/
Sheep2* Game2Scene::getSheep() {
    return m_sheep;
}

/**
* Starts the timer to delay the computer move.
*/
void Game2Scene::computerTurn() {
    m_user_turn = false;
    m_delay->start(500);
}

/**
* Moves the sheep according to the difficulty when it's the
* computer's turn.
*/
void Game2Scene::moveSheep() {
    m_delay->stop();
    Tile *next;
    //move randomly
    if(m_difficulty == EASY) {
        //pick a random non blocked neighbor and move to it
        QVector< Tile* > * neighbors = getNeighbors(m_sheep->getCurrent());
        int index = rand()%(neighbors->size());
        next = neighbors->at(index);
        delete neighbors;
    }

    else if(m_difficulty == MODERATE) {
        if (rand()%2 == 0) {
            //pick a random non blocked neighbor and move to it
            QVector< Tile* > * neighbors = getNeighbors(m_sheep->getCurrent());
            int index = rand()%(neighbors->size());
            next = neighbors->at(index);
            delete neighbors;
        }
        else {
            next = findNextTile();
        }
    }

    else {
        next = findNextTile();
    }
    m_sheep->setCurrent(next);

    if(m_sheep->getCurrent()->isBorder()){
        //lost
        gameOver(false);
    } else {
        m_user_turn = true;
    }
}

/**
* Retrieves the value that indicates if it's the user's turn.
*/
bool Game2Scene::getUserTurn() {
    return m_user_turn;
}

/**
* Sets the user's turn as true or false.
*/
void Game2Scene::setUserTurn(bool userTurn) {
    m_user_turn = userTurn;
}

/**
* Ends the game and displays the GameOver item.
*/
void Game2Scene::gameOver(bool win) {
    m_gameOverPicture = new GameOver(win);
    addItem(m_gameOverPicture);
    emit Done();
}

/**
* Increments the number of blocks by one on click of a tile.
*/
void Game2Scene::decrementScore() {
    m_score-=10;
    m_scoreDisplay->display(m_score);
}

/**
* Returns the score lcd.
*/
QLCDNumber* Game2Scene::getScoreDisplay() {
    return m_scoreDisplay;
}

/**
* Returns the number of blocked tiles.
*/
int Game2Scene::getBlockCount() {
    return m_block_count;
}

/**
* Finds the shortest path and returns the next tile accordingly.
*/
Tile *Game2Scene::findNextTile() {
    resetVisited();
    resetDistances();
    resetPrevious();
    computeDistances(m_sheep->getCurrent());

    QVector<Tile*> *borders = getNonBlockedBorders();
    Tile *min = *borders->begin();
    for (QVector<Tile*>::iterator tile=borders->begin()+1; tile!=borders->end(); ++tile) {
        if ((*tile)->getDistance() < min->getDistance()) {
            min = *tile;
        }
    }

    while (min->getPrev()->getPrev() != NULL) {
        min = min->getPrev();
    }
    delete borders;
    return min;
}

/**
* Computes the distances from the sheep to every other tile.
*/
void Game2Scene::computeDistances(Tile *current) {
    static QQueue<Tile*> queue;
    QVector<Tile*> *neighbors = getNeighbors(current);

    for (QVector< Tile* >::iterator neighbor = neighbors->begin(); neighbor != neighbors->end(); ++neighbor) {
        if (!(*neighbor)->isVisited()) {
            (*neighbor)->setVisited(true);
            (*neighbor)->setDistance(current->getDistance()+1);
            (*neighbor)->setPrev(current);
            queue.append(*neighbor);
        }
    }
    delete neighbors;
    while (!queue.empty()) {
        computeDistances(queue.dequeue());
    }
}

/**
* Retrieves the non blocked border tiles.
* Memory is allocated in this function and should be freed by the caller.
*/
QVector< Tile* > *Game2Scene::getNonBlockedBorders() {
    QVector< Tile* > *borders = new QVector<Tile*>();

    for (QVector< QVector< Tile* > >::iterator row=m_tiles.begin(); row!=m_tiles.end(); ++row) {
        for(QVector< Tile* >::iterator tile = (*row).begin(); tile!=(*row).end(); ++tile){
            if ((*tile)->isBorder()) {
                borders->push_back(*tile);
            }
        }
    }

    return borders;
}


/**
* Returns the difficulty of the game.
*/
Difficulty Game2Scene::getDifficulty() {
    return m_difficulty;
}

/**
* Returns the current score of the game.
*/
int Game2Scene::getScore() {
    return m_score;
}

/**
* Returns a string representation of the sheep row and column.
*/
QString Game2Scene::getSheepPos() {
    QString pos = QString::number(m_sheep->getCurrent()->getRow());
    pos.append(",");
    pos.append(QString::number(m_sheep->getCurrent()->getCol()));

    return pos;
}

/**
* Returns the string representation of the blocked tiles' positions.
*/
QString Game2Scene::getBlockedTilesPos() {
    QString pos = "";
    for(QVector< Tile* >::iterator it = m_blockedTiles.begin(); it != m_blockedTiles.end(); ++it) {
        pos.append(QString::number((*it)->getRow()));
        pos.append(",");
        pos.append(QString::number((*it)->getCol()));
        pos.append(",");
    }

    return pos;
}

/**
* Adds a tile to the list of blocked tiles
*/
void Game2Scene::addToBlockedTiles(Tile* tile) {
    m_blockedTiles.push_back(tile);
}
