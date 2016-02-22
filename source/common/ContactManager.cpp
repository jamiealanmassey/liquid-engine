#include "ContactManager.h"
#include "Entity.h"

ContactListener::ContactListener() :
	b2ContactListener()
{
}

ContactListener::~ContactListener()
{
	// Empty callback tables
	m_CallbackTableA.clear();
	m_CallbackTableB.clear();
}

void ContactListener::BeginContact(b2Contact* contact)
{
	// Sample both entities from the fixture data
	Entity* entity_A = static_cast<Entity*>(contact->GetFixtureA()->GetUserData());
	Entity* entity_B = static_cast<Entity*>(contact->GetFixtureB()->GetUserData());

	// Store both entities types for comparison
	int32_t type_A = entity_A->getEntityType();
	int32_t type_B = entity_B->getEntityType();

	// Based on Entity types create a table search
	auto table_search = m_CallbackTableA.find(std::make_pair(type_A, type_B));

	// If we have found a match for our types call the corresponding function
	if (table_search != m_CallbackTableA.end())
	{
		auto function = table_search->second;
		function(entity_A, entity_B, contact);
	}
}

void ContactListener::EndContact(b2Contact* contact)
{
	// Sample both entities from the fixture data
	Entity* entity_A = static_cast<Entity*>(contact->GetFixtureA()->GetUserData());
	Entity* entity_B = static_cast<Entity*>(contact->GetFixtureB()->GetUserData());

	// Store both entities types for comparison
	int32_t type_A = entity_A->getEntityType();
	int32_t type_B = entity_B->getEntityType();

	// Based on Entity types create a table search
	auto table_search = m_CallbackTableB.find(std::make_pair(type_A, type_B));

	// If we have found a match for our types call the corresponding function
	if (table_search != m_CallbackTableB.end())
	{
		auto function = table_search->second;
		function(entity_A, entity_B);
	}
}

void ContactListener::ConnectBegin(int32_t type_a, int32_t type_b, ContactListener::CollisionBegin callback)
{
	// Output to console data about connecting callbacks
	std::cout << "Connecting -evtCollisionBegin- callback to ContactListener\n";
	std::cout << "EntityA: " << type_a << std::endl;
	std::cout << "EntityB: " << type_b << std::endl << std::endl;

	// Produce a pair using both types
	std::pair<int32_t, int32_t> types = std::make_pair(type_a, type_b);

	// If we haven't hit the end of the callback table we have found a match, insert
	// for callback
	if (m_CallbackTableA.find(types) == m_CallbackTableA.end())
		m_CallbackTableA.insert(std::make_pair(std::make_pair(type_a, type_b), callback));
}

void ContactListener::ConnectEnd(int32_t type_a, int32_t type_b, ContactListener::CollisionEnd callback)
{
	// Output to console data about connecting callbacks
	std::cout << "Connecting -evtCollisionEnd- callback to ContactListener\n";
	std::cout << "EntityA: " << type_a << std::endl;
	std::cout << "EntityB: " << type_b << std::endl << std::endl;

	// Produce a pair using both types
	std::pair<int32_t, int32_t> types = std::make_pair(type_a, type_b);

	// If we haven't hit the end of the callback table we have found a match, insert
	// for callback
	if (m_CallbackTableB.find(types) == m_CallbackTableB.end())
		m_CallbackTableB.insert(std::make_pair(std::make_pair(type_a, type_b), callback));
}

/////////////////////////////////////////////////////////////////////
ContactResolver::ContactResolver()
{}

ContactResolver::~ContactResolver()
{}

void ContactResolver::BeginContact(b2Contact* contact)
{
	// Sample user data passed by bodies
	void* body_user_data_A = contact->GetFixtureA()->GetBody()->GetUserData();
	void* body_user_data_B = contact->GetFixtureB()->GetBody()->GetUserData();

	// If we have found user data for both bodies then attempt to execute callback
	// functions OnBeginCollision(entity)
	if (body_user_data_A && body_user_data_B)
	{
		// Cast user data to entity types
		Entity* entity_A = static_cast<Entity*>(body_user_data_A);
		Entity* entity_B = static_cast<Entity*>(body_user_data_B);

		// If Entity A has an OnBeginCollision callback execute it
		if (entity_A->f_OnCollisionBegin)
			entity_A->f_OnCollisionBegin(entity_B, contact);

		// If Entity B has an OnBeginCollision callback execute it
		if (entity_B->f_OnCollisionBegin)
			entity_B->f_OnCollisionBegin(entity_A, contact);
	}

	// If the fixtureA has no user data stored with it but fixtureB does then we still want
	// to call fixtureB callbacks without passing an Entity
	else if (!body_user_data_A && body_user_data_B)
	{
		if (static_cast<Entity*>(body_user_data_B)->f_OnBodyCollisionBegin)
			static_cast<Entity*>(body_user_data_B)->f_OnBodyCollisionBegin(contact);
	}
}

void ContactResolver::EndContact(b2Contact* contact)
{
	// Sample user data passed by bodies
	void* body_user_data_A = contact->GetFixtureA()->GetBody()->GetUserData();
	void* body_user_data_B = contact->GetFixtureB()->GetBody()->GetUserData();

	// If we have found user data for both bodies then attempt to execute callback
	// functions OnEndCollision(entity)
	if (body_user_data_A && body_user_data_B)
	{
		// Cast user data to entity types
		Entity* entity_A = static_cast<Entity*>(body_user_data_A);
		Entity* entity_B = static_cast<Entity*>(body_user_data_B);

		// If Entity A has an OnBeginCollision callback execute it
		if (entity_A->f_OnCollisionEnd)
			entity_A->f_OnCollisionEnd(entity_B, contact);

		// If Entity B has an OnBeginCollision callback execute it
		if (entity_B->f_OnCollisionEnd)
			entity_B->f_OnCollisionEnd(entity_A, contact);
	}

	// If the fixtureA has no user data stored with it but fixtureB does then we still want
	// to call fixtureB callbacks without passing an Entity
	else if (!body_user_data_A && body_user_data_B)
	{
		if (static_cast<Entity*>(body_user_data_B)->f_OnBodyCollisionEnd)
			static_cast<Entity*>(body_user_data_B)->f_OnBodyCollisionEnd(contact);
	}
}
