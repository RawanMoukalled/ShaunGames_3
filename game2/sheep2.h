#ifndef SHEEP2_H
#define SHEEP2_H

#include <QObject>

class Sheep2 : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Sheep2(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // SHEEP2_H
