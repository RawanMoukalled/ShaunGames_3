#ifndef SHEEP1_H
#define SHEEP1_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QString>

class Sheep1 : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    /**
    * \brief Constructor
    */
    explicit Sheep1(int number, QObject *parent = 0);

    /**
    * \brief Destructor
    */
    virtual ~Sheep1();

    int getAngle() const;
    void setAngle(int angle);

private:
    int m_angle;

signals:
    
public slots:
    
};

#endif // SHEEP1_H
