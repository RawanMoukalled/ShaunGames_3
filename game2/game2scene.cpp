#include "game2scene.h"
#include <algorithm>

/**
* \file game2scene.cpp
* \brief Contains the Trap the Sheep game scene
*/

/**
* Places the items on the scene and sets the user turn
*/
Game2Scene::Game2Scene(Difficulty difficulty, QObject *parent) :
    QGraphicsScene(parent), m_difficulty(difficulty), m_score(0)
{
    //starting blocks
    if(difficulty == EASY) {
        m_block_count = 10;
    } else if(difficulty == MODERATE) {
        m_block_count = 7;
    } else if(difficulty == HARD) {
        m_block_count = 5;
    }
    m_score = 1500;
    m_scoreDisplay = new QLCDNumber(4);

    addWidget(m_scoreDisplay);
    m_scoreDisplay->move(250,480);

    QPalette lcdPalette = m_scoreDisplay->palette();
    lcdPalette.setColor(QPalette::Background, QColor(170, 255, 0));
    lcdPalette.setColor(QPalette::WindowText, QColor(85, 85, 255));
    lcdPalette.setColor(QPalette::Light, QColor(255, 0, 0));
    lcdPalette.setColor(QPalette::Dark, QColor(255, 0, 0));

    m_scoreDisplay->setPalette(lcdPalette);
    m_scoreDisplay->display(m_score);

    m_gameOverPicture = NULL;
    m_user_turn = true;

    placeTiles();
    placeSheepInitial();

    m_delay = new QTimer(this);
    connect(m_delay, SIGNAL(timeout()), this, SLOT(moveSheep()));


}

/**
* Frees allocated memory
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
}

/**
* chooses distinct random tiles to flag for blocking initially at the start of the game
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
* Places the tiles on the grid of the game
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

            if ( std::find(flagged.begin(), flagged.end(), count) != flagged.end() ) {
                tile = new Tile(true, i, j);
            } else {
                tile = new Tile(false, i, j);
            }

            tile->setPos(offset + j*left,i*top);
            row.push_back(tile);
            addItem(tile);
            count++;
        }
        even = !even;

        m_tiles.push_back(row);
    }
}

/**
* Chooses a random tile to place the sheep on at the beginning of the game
*/
void Game2Scene::placeSheepInitial() {
    int row, col;
    //place sheep on a tile that is not blocked
    Tile * sheep_tile;
    do{
        row = rand()%3 + 2;
        col = rand()%3 +3;
        sheep_tile = (m_tiles.at(row)).at(col);
    } while(sheep_tile->isBlocked());

    m_sheep = new Sheep2(sheep_tile);

    //m_sheep->setPos(sheep_tile->x(), sheep_tile->y());
    addItem(m_sheep);
}

/**
* Checks for each element in the list the block status and only
* returns the free ones
*/
QVector< Tile* > * Game2Scene::getNonBlocked(QVector<Tile*> * tiles) {
    QVector< Tile* > * unblocked = new QVector< Tile* >;

    QVector< Tile* >::iterator it;
    for(it = tiles->begin(); it != tiles->end(); ++it) {
        if(!(*it)->isBlocked()) {
            unblocked->push_back((*it));
        }
    }

    return unblocked;
}

/**
* Gets for the given tile the left, right, upper and bottom neighbors
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
      neighbors->push_back(left);
  }

  //on row with 13 columns
  if(i % 2 == 0) {
      //right
      if(j != 12) {
          right = (m_tiles.at(i)).at(j+1);
          neighbors->push_back(right);
      }


      //top right and top left
      if(i != 0) {
          topRight = (m_tiles.at(i-1)).at(j);
          neighbors->push_back(topRight);
          if(j != 0) {
              topLeft = (m_tiles.at(i-1)).at(j-1);
              neighbors->push_back(topLeft);
          }
      }

      //bottom right and bottom left
      if(i != 11) {
          if(j != 12){
            bottomRight = (m_tiles.at(i+1)).at(j);
            neighbors->push_back(bottomRight);
          }
          if(j != 0) {
            bottomLeft = (m_tiles.at(i+1)).at(j-1);
            neighbors->push_back(bottomLeft);
          }
      }
  }

  //on row with 12 columns
  else {
      //right
      if(j != 11) {
          right = (m_tiles.at(i)).at(j+1);
          neighbors->push_back(right);
      }

      //top right and top left
      if(i != 0) {
          topLeft = (m_tiles.at(i-1)).at(j);
          neighbors->push_back(topLeft);

              topRight = (m_tiles.at(i-1)).at(j+1);
              neighbors->push_back(topRight);

      }

      //bottom right and bottom left
      if(i != 11) {
          bottomLeft = (m_tiles.at(i+1)).at(j);
          neighbors->push_back(bottomLeft);

              bottomRight = (m_tiles.at(i+1)).at(j+1);
              neighbors->push_back(bottomRight);

      }
  }

  return neighbors;
}

/**
* Resets the status of the grid tiles as not visited
*/
void Game2Scene::resetVisited() {
    QVector< QVector< Tile*> >::iterator row;
    for (row = m_tiles.begin(); row != m_tiles.end(); ++row) {
        QVector< Tile*>::iterator tile;
        for (tile = (*row).begin(); tile != (*row).end(); ++tile) {
            (*tile)->setVisited(false);
        }
    }
}

/**
* Gets the tile at the given indices
*/
Tile* Game2Scene::tileAt(int i, int j) {
    return (m_tiles.at(i)).at(j);
}

/**
* Determines a win by checking if from the current sheep position
* it's possible to get to the border without encountering a blocked tile
*/
bool Game2Scene::win(Tile * tile) {
    QVector<Tile*> * neighbors = getNeighbors(tile);

    QVector< Tile* >::iterator neighbor;
    for (neighbor = neighbors->begin(); neighbor != neighbors->end(); ++neighbor)  {
        if (!(*neighbor)->isBlocked()) {
            if ((*neighbor)->isBorder()) {
                return false;
            }
            if (!(*neighbor)->isVisited()) {
                (*neighbor)->setVisited(true);
                if (!win(*neighbor)) {
                    return false;
                }
            }
        }
    }
    return true;
}

/**
* Retrieves the sheep
*/
Sheep2* Game2Scene::getSheep() {
    return m_sheep;
}

/**
* Starts the timer to delay the computer move
*/
void Game2Scene::computerTurn() {
    m_user_turn = false;
    m_delay->start(500);
}

/**
* Moves the sheep according to the difficulty when it's the
* computer's turn
*/
void Game2Scene::moveSheep() {
    if(!m_user_turn && !m_sheep->getCurrent()->isBorder()) {

        //move randomly
        if(m_difficulty == EASY) {
            //pick a random non blocked neighbor and move to it
            QVector< Tile* > * neighbors = getNonBlocked(getNeighbors(m_sheep->getCurrent()));
            int index = rand()%(neighbors->size());
            m_sheep->setCurrent(neighbors->at(index));
        }

        else if(m_difficulty == MODERATE) {


        }

        else if(m_difficulty == HARD) {


        }

        if(m_sheep->getCurrent()->isBorder()){
            //lost
            gameOver(false);
        } else {
          m_user_turn = true;
        }


    }
}

/**
* Depth first search to find the shortest path
*/
void Game2Scene::DFS() {

}

/**
* Retrieves the value that indicates if it's the user's turn
*/
bool Game2Scene::getUserTurn() {
    return m_user_turn;
}

/**
* Sets the user's turn as true or false
*/
void Game2Scene::setUserTurn(bool userTurn) {
    m_user_turn = userTurn;
}

void Game2Scene::gameOver(bool win) {
    m_gameOverPicture = new GameOver(win);
    addItem(m_gameOverPicture);
    emit Done();
}

/**
* Increments the number of blocks by one on click of a tile
*/
void Game2Scene::decrementScore() {
    m_score-=10;
    m_scoreDisplay->display(m_score);
}

/**
* Returns the score lcd
*/
QLCDNumber* Game2Scene::getScoreDisplay() {
    return m_scoreDisplay;
}

/**
* Returns the number of blocked tiles
*/
int Game2Scene::getBlockCount() {
    return m_block_count;
}
