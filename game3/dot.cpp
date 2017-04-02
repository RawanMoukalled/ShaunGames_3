#include "dot.h"

Dot::Dot(QObject *parent) :
    QObject(parent)
{
    setPixmap(QPixmap("pictures/Dot.png"));
    setScale(0.01);
}

Dot::~Dot() {
}
