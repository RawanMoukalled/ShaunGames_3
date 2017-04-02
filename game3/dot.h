#ifndef DOT_H
#define DOT_H

#include <QtGui>

class Dot : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Dot(QObject *parent = 0);

    virtual ~Dot();
    
signals:
    
public slots:
    
};

#endif // DOT_H
