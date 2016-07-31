#ifndef _UITRANSITIONTABLE_H
#define _UITRANSITIONTABLE_H

#include "UITransitionEffect.h"
#include <map>

#define UITRANSITION_CREATE   0
#define UITRANSITION_HIDE	  1
#define UITRANSITION_SHOW	  2
#define UITRANSITION_ENABLE   3
#define UITRANSITION_DISABLE  4
#define UITRANSITION_DESTROY  5
#define UITRANSITION_PRESSED  6
#define UITRANSITION_RELEASED 7

class UITransitionTable
{
public:
	UITransitionTable();
	~UITransitionTable();

	void update();
	void trigger(int32_t id);
	
	bool connect(int32_t id, UITransitionEffect* effect);
	bool disconnect(int32_t id);
	bool exists(int32_t id);

	bool isFinished(int32_t id);
	bool isFinishedAll();

protected:
	std::map<int32_t, UITransitionEffect*> m_TransitionTable;
};

#endif // _UITRANSITIONTABLE_H
