#ifndef _CONTACTMANAGER_H
#define _CONTACTMANAGER_H

#include <Box2D/Box2D.h>
#include <functional>
#include <map>
#include <iostream>

class Entity;
class ContactListener : public b2ContactListener
{
public:
	typedef std::function<void(Entity*, Entity*, b2Contact*)>	  CollisionBegin;
	typedef std::function<void(Entity*, Entity*)>				  CollisionEnd;
	typedef std::map<std::pair<int32_t, int32_t>, CollisionBegin> CallbackTableA;
	typedef std::map<std::pair<int32_t, int32_t>, CollisionEnd>   CallbackTableB;

public:
	ContactListener();
	virtual ~ContactListener();

	/* Overrided core functions from Box2D */
	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact)   override;

	/* Collision connection functions */
	void ConnectBegin(int32_t type_a, int32_t type_b, ContactListener::CollisionBegin callback);
	void ConnectEnd(int32_t type_a, int32_t type_b, ContactListener::CollisionEnd callback);

private:
	CallbackTableA m_CallbackTableA; ///< Table of callbacks for the beginning of collisions
	CallbackTableB m_CallbackTableB; ///< Table of callbacks for end of collisions
};

class ContactResolver : public b2ContactListener
{
public:
	ContactResolver();
	~ContactResolver();

	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
};

#endif // _CONTACTMANAGER_H
