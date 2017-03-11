#ifndef CANNON_H
#define CANNON_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Cannon : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Cannon(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // CANNON_H
