#ifndef BARN_H
#define BARN_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Barn : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Barn(QObject *parent = 0);
    
signals:
    
public slots:
    void sheepIn();

private:
    QTimer *m_timer;
    bool m_collisionDone;

};

#endif // BARN_H
