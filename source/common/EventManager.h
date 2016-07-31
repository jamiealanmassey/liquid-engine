#ifndef _EVENTMANAGER_H
#define _EVENTMANAGER_H

#include <functional>
#include <string>
#include <map>
#include <vector>

class EventManager
{
public:
	typedef std::function<void()>				FuncBind;
	typedef std::vector<FuncBind>				FuncBindList;
	typedef std::map<std::string, FuncBindList> FuncListeners;

public:
	EventManager();
	~EventManager();

	void connect(std::string listener, FuncBind func);
	void connect(std::string listener, FuncBindList funcs);

	void signal(std::string listener);
	void close(std::string listener);

	static EventManager& instance();

protected:
	FuncListeners m_FuncListeners;
};

#endif // _EVENTMANAGER_H
