#include "UITransitionTable.h"

UITransitionTable::UITransitionTable()
{
}

UITransitionTable::~UITransitionTable()
{
}

void UITransitionTable::update()
{
	// Create an iterator for the table
	std::map<int32_t, UITransitionEffect*>::iterator itr 
		= m_TransitionTable.begin();

	// Go through the table first checking if the transition effect is active
	// and if it is update it
	for (; itr != m_TransitionTable.end(); ++itr)
	{
		if ((*itr).second->isActive())
			(*itr).second->update();
	}
}

void UITransitionTable::trigger(int32_t id)
{
	// Trigger the transition with this id
	m_TransitionTable[id]->trigger();
}

bool UITransitionTable::connect(int32_t id, UITransitionEffect* effect)
{
	// See if the id already exists, if it does return false
	if (m_TransitionTable.find(id) != m_TransitionTable.end())
		return false;

	// Assign the effect to this id slot
	m_TransitionTable[id] = effect;
	return true;
}

bool UITransitionTable::disconnect(int32_t id)
{
	// Search for the transition with this id, if the key exists then
	// erase it and return true
	if (m_TransitionTable.find(id) != m_TransitionTable.end())
	{
		delete m_TransitionTable[id];
		m_TransitionTable.erase(id);
		return true;
	}

	// Key was not found
	return true;
}

bool UITransitionTable::exists(int32_t id)
{
	// See if the transition effect exists and if it does return true
	if (m_TransitionTable.find(id) != m_TransitionTable.end())
		return true;
	else
		return false;
}

bool UITransitionTable::isFinished(int32_t id)
{
	return !m_TransitionTable[id]->isActive();
}

bool UITransitionTable::isFinishedAll()
{
	int32_t count = 0;
	std::map<int32_t, UITransitionEffect*>::iterator itr = m_TransitionTable.begin();

	for (; itr != m_TransitionTable.end(); ++itr)
		count += !(*itr).second->isActive();

	return (count == 0);
}
