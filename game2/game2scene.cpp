#include "game2scene.h"
#include <algorithm>

/**
* \file game2scene.cpp
* \brief Contains the Trap the Sheep game scene
*/

/**
* Places the items on the scene
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

    placeTiles();
    placeSheepInitial();


//    QVector< Tile* >* test = getNeighbors(tileAt(11,11));
//    qDebug()<<test->size();
//    QVector< Tile* >::iterator in;
//    for (in = test->begin(); in != test->end(); ++in)  {
//        qDebug()<< (*in)->getRow() << "," << (*in)->getCol();

//    }

}

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

void Game2Scene::placeSheepInitial() {
    int row, col;
    //place sheep on a tile that is not blocked
    Tile * sheep_tile;
    do{
        row = rand()%3 + 2;
        col = rand()%3 +3;
        sheep_tile = (m_tiles.at(row)).at(col);
    } while(sheep_tile->isBlocked());

    sheep = new Sheep2(row, col);

    sheep->setPos(sheep_tile->x(), sheep_tile->y());
    sheep_tile->setHasSheep(true);
    addItem(sheep);
}

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

void Game2Scene::resetVisited() {

}

Tile* Game2Scene::tileAt(int i, int j) {
    return (m_tiles.at(i)).at(j);
}

// reset visited before calling
//bool Game2Scene::win(Tile * tile) {
//    QVector<Tile*> * neighbors = getNeighbors(tile);
//    QVector< Tile* >::iterator neighbor;

//    for (neighbor = neighbors->begin(); neighbor != neighbors->end(); ++neighbor)  {
//        if (!(*neighbor)->isBlocked()) {
//            if ((*neighbor)->isBorder()) {
//                return false;
//            }
//            if (!(*neighbor)->isVisited()) {
//                win(*neighbor);
//            }
//        }
//    }
//    return true;
//}
