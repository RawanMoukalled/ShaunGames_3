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
    void takeSheep();

private:
    QTimer *m_timer;

};

#endif // BARN_H
