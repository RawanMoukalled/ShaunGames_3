#ifndef SHEEP1_H
#define SHEEP1_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Sheep1 : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Sheep1(int number, QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // SHEEP1_H
