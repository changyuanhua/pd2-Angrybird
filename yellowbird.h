#ifndef YELLOWBIRD_H
#define YELLOWBIRD_H

#include "gameitem.h"
#include "bird.h"

class yellowbird : public Bird{
public:
    yellowbird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    virtual void special();
};
#endif // YELLOWBIRD_H
