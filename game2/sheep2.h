#ifndef SHEEP2_H
#define SHEEP2_H

#include <QtGui>

class Sheep2 : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Sheep2(int row, int col, QObject *parent = 0);
    int getRow();
    int getCol();
    
signals:
    
public slots:

private:
    int m_row; ///< The row that the sheep is currently on
    int m_col; ///< The column that the sheep is currently on
    
};

#endif // SHEEP2_H
