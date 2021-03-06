#ifndef BLUEBIRD_H
#define BLUEBIRD_H

#include "gameitem.h"
#include "bird.h"

class bluebird : public Bird{
public:
    bluebird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    virtual void special();
};
#endif // BLUEBIRD_H
