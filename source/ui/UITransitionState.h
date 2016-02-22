#ifndef _UITRANSITIONSTATE_H
#define _UITRANSITIONSTATE_H

#include <functional>
#include <map>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "UITransitionData.h"
#include "UITransitionFuncs.h"

#define STATE_MODE_UNDEFINED 0
#define STATE_MODE_WAITING   1
#define STATE_MODE_RUNNING   2
#define STATE_MODE_COMPLETE  3

class UIElement;

class UITransitionState
{
public:
	typedef std::function<bool(UIElement*, UITransitionState*)>	FuncStateStart;
	typedef std::function<bool(UIElement*, UITransitionState*)> FuncStateUpdate;
	typedef std::function<void(UIElement*, UITransitionState*)>	FuncStateFinish;

	typedef std::map<std::string, FuncStateStart>				FuncStartTable;
	typedef std::map<std::string, std::vector<FuncStateUpdate>> FuncUpdateTable;
	typedef std::map<std::string, FuncStateFinish>				FuncFinishTable;

public:
	UITransitionState(UIElement* parent_element);
	~UITransitionState();

	/* Transition State Control Functions */
	void initDefaultStates();
	void update();

	/* Functions for adding different states to this transition state */
	void addState(std::string state_name);
	void addStateStartCallback(std::string state_name,  FuncStateStart state_func);
	void addStateUpdateCallback(std::string state_name, FuncStateUpdate state_func);
	void addStateFinishCallback(std::string state_name, FuncStateFinish state_func);

	/* State Modes */
	void   forceNextState(std::string state);
	void   forceCurrentState(std::string state);
	int8_t getStateMode(std::string state_name);

	/* State Control Functions */
	void resetStateTicks()	  { m_StateTicks = 0.0f;								}
	void resetStateMode()	  { m_StatesMode[m_StateCurrent] = STATE_MODE_WAITING;  }
	void terminateStateMode() { m_StatesMode[m_StateCurrent] = STATE_MODE_COMPLETE; }

	/* Getters for States */
	std::string getCurrentState()		 { return m_StateCurrent;  }
	std::string getLastState()			 { return m_StateLast;     }
	std::string getNextState()			 { return m_StateNext;     }
	UIElement*  getParentElement()		 { return m_ParentElement; }
	float		getStateTicks()    const { return m_StateTicks;	   }

private:
	/* Helper Funcs */
	void updateNextState();

private:
	FuncStartTable  f_StartCallbacks;  ///< Table of start callbacks
	FuncUpdateTable f_UpdateCallbacks; ///< Table of update callbacks
	FuncFinishTable f_FinishCallbacks; ///< Table of finish callbacks

protected:
	std::map<std::string, int8_t> m_StatesMode;	   ///< Stores the current mode of each state
	std::string				      m_StateCurrent;  ///< String identifier for the current state
	std::string					  m_StateLast;	   ///< String identifier for the last state
	std::string					  m_StateNext;	   ///< String identifier for the next state
	UIElement*					  m_ParentElement; ///< Element that owns this transition state
	float						  m_StateTicks;    ///< Duration that current state has ran
};

#endif // _UITRANSITIONSTATE_H
