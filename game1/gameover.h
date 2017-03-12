#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QObject>
#include <QGraphicsPixmapItem>

class GameOver : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit GameOver(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // GAMEOVER_H
