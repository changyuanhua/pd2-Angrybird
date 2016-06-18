#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include <Box2D/Box2D.h>
#include <gameitem.h>
#include <iostream>
class ContactListener : public b2ContactListener
{
public:
    ContactListener();
    virtual void BeginContact(b2Contact *contact);
    virtual void EndContact(b2Contact * contact);
};

#endif // CONTACTLISTENER_H
