#include "bird.h"

Bird::Bird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
{
    // Set pixmap
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size = QSize(radius*2,radius*2);

    // Create Body
    b2BodyDef bodydef;
    bodydef.type = b2_dynamicBody;
    bodydef.bullet = true;
    bodydef.position.Set(x,y);
    bodydef.userData = this;
    g_body = world->CreateBody(&bodydef);
    b2CircleShape bodyshape;
    bodyshape.m_radius = radius;
    b2FixtureDef fixturedef;
    fixturedef.shape = &bodyshape;
    fixturedef.density = BIRD_DENSITY;
    fixturedef.friction = BIRD_FRICTION;
    fixturedef.restitution = BIRD_RESTITUTION;
    g_body->SetAngularDamping(3);
    g_body->CreateFixture(&fixturedef);
    g_body->SetSleepingAllowed(true);

    // Bound timer
    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));
    scene->addItem(&g_pixmap);

}

void Bird::setLinearVelocity(b2Vec2 velocity)
{
    g_body->SetLinearVelocity(velocity);
}
void Bird::setLinearVelocity(int mousex, int mousey)
{
    float posx,posy;
    if (mousex>=120)
    {
        mousex=120;
    }
    else if (mousex<=0)
    {
        mousex=0;
    }
    else if (mousey>=400)
    {
        mousey=400;
    }
    else if (mousey<=300)
    {
        mousey=300;
    }
    posx =g_size.width()/2.0f+(120-mousex)/g_windowsize.width()*g_worldsize.width();
    posy =(1.0f-g_size.height()/2.0f-mousey/g_windowsize.height())*g_worldsize.height();
    posy =(1.0f-g_size.height()/2.0f-300/g_windowsize.height())*g_worldsize.height()-posy;
    // set linear velocity
    b2Vec2 velocity(posx*2,posy*5);
    g_body->SetLinearVelocity(velocity);
}

void Bird::setposition(float x, float y)
{
    b2Vec2 pos;
    if (x>=120)
    {
        x=120;
    }
    else if (x<=0)
    {
        x=0;
    }
    else if (y>=400)
    {
        y=400;
    }
    else if (y<=300)
    {
        y=300;
    }
    pos.x = x*g_worldsize.width()/g_windowsize.width()+g_size.width()/2-1;
    pos.y =(1.0f-y/g_windowsize.height())*g_worldsize.height()-g_size.height()/2+1;
    // set g_body's pos, and not to change the rotation
    g_body->SetTransform(pos,g_body->GetAngle());
}
void Bird::special()
{

}
