#include "EventManager.h"

EventManager::EventManager()
{
}

EventManager::~EventManager()
{
}

void EventManager::connect(std::string listener, FuncBind func)
{
	m_FuncListeners[listener].push_back(func);
}

void EventManager::connect(std::string listener, FuncBindList funcs)
{
	for (auto func : funcs)
		m_FuncListeners[listener].push_back(func);
}

void EventManager::signal(std::string listener)
{
	if (m_FuncListeners.find(listener) != m_FuncListeners.end())
	{
		for (auto func : m_FuncListeners[listener])
			func();
	}
}

void EventManager::close(std::string listener)
{
	if (m_FuncListeners.find(listener) != m_FuncListeners.end())
		m_FuncListeners[listener].clear();
}

EventManager& EventManager::instance()
{
	static EventManager singleton;
	return singleton;
}
