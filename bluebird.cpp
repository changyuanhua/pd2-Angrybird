#include "bluebird.h"

bluebird::bluebird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene) : Bird(x, y, radius, timer, pixmap, world, scene){
}

void bluebird::special()
{
    g_body->SetLinearVelocity(b2Vec2(g_body->GetLinearVelocity().x,g_body->GetLinearVelocity().y+10));
}
