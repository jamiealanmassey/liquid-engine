#include "UITransitionState.h"
#include "UIElement.h"
#include "../utilities/DeltaTime.h"
#include "../utilities/Random.h"

UITransitionState::UITransitionState(UIElement* parent_element) :
	m_ParentElement(parent_element),
	m_StateCurrent(""),
	m_StateLast(""),
	m_StateNext("")
{
}

UITransitionState::~UITransitionState()
{
}

void UITransitionState::initDefaultStates()
{
	// Add the 4 standard states to this transitioning element
	addState("TEnabled");
	addState("TDisabled");
	addState("TPressed");
	addState("TReleased");
}

void UITransitionState::update()
{
	// Update state ticks
	m_StateTicks += Delta;

	// Check that the current state is running first
	if (m_StatesMode[m_StateCurrent] == STATE_MODE_RUNNING)
	{
		// If it is running and has an update callback then call that function and check
		// if it has finished, if it hasn't then do nothing, otherwise if it doesn't have
		// a callback and we have a next state automatically switch to that state
		if (f_UpdateCallbacks.find(m_StateCurrent) != f_UpdateCallbacks.end() &&
			f_UpdateCallbacks[m_StateCurrent](m_ParentElement, this))
		{
			m_StatesMode[m_StateCurrent] = STATE_MODE_COMPLETE;
		}
		else if (f_FinishCallbacks.find(m_StateCurrent) != f_FinishCallbacks.end() &&
				 m_StateNext != "")
		{
			// Call finish callback on current state
			f_FinishCallbacks[m_StateCurrent](m_ParentElement, this);

			// Call helper method
			updateNextState();

			// Update the state mode for the new current mode
			if (m_StateCurrent != "")
				m_StatesMode[m_StateCurrent] = STATE_MODE_RUNNING;
		}
		else if (f_UpdateCallbacks.find(m_StateCurrent) == f_UpdateCallbacks.end() &&
				 f_FinishCallbacks.find(m_StateCurrent) == f_FinishCallbacks.end())
		{
			// Change current state mode to complete
			m_StatesMode[m_StateCurrent] = STATE_MODE_COMPLETE;
		}
	}
	else if (m_StatesMode[m_StateCurrent] == STATE_MODE_COMPLETE && m_StateNext != "")
	{
		// Update to next state if the previous is complete and it exists
		updateNextState();
	}
}

void UITransitionState::addState(std::string state_name)
{
	// If the state doesn't exist add a new state mode for it otherwise
	// output an error to the console
	if (m_StatesMode.find(state_name) == m_StatesMode.end())
	{
		// If it is the first state init the state as running so we can
		// progress, otherwise give it a state of waiting
		if (m_StatesMode.size() == 0)
		{
			m_StatesMode[state_name] = STATE_MODE_RUNNING;
			m_StateCurrent = state_name;
		}
		else 
			m_StatesMode[state_name] = STATE_MODE_WAITING;
	}
	else
		std::cout << "State " << state_name << " already exists";
}

void UITransitionState::addStateStartCallback(std::string state_name, FuncStateStart state_func)
{
	// Search map of state callbacks, if it doesn't exist add it to the map
	// otherwise output
	if (f_StartCallbacks.find(state_name) == f_StartCallbacks.end())
		f_StartCallbacks[state_name] = state_func;
	else
		std::cout << "UITransitionState start callback for state " << state_name << " already exists!\n";
}

void UITransitionState::addStateUpdateCallback(std::string state_name, FuncStateUpdate state_func)
{
	// Search map of state callbacks, if it doesn't exist add it to the map
	// otherwise output
	if (f_UpdateCallbacks.find(state_name) == f_UpdateCallbacks.end())
		f_UpdateCallbacks[state_name] = state_func;
	else
		std::cout << "UITransitionState update callback for state " << state_name << " already exists!\n";
}

void UITransitionState::addStateFinishCallback(std::string state_name, FuncStateFinish state_func)
{
	// Search map of state callbacks, if it doesn't exist add it to the map
	// otherwise output
	if (f_FinishCallbacks.find(state_name) == f_FinishCallbacks.end())
		f_FinishCallbacks[state_name] = state_func;
	else
		std::cout << "UITransitionState finish callback for state " << state_name << " already exists!\n";
}

void UITransitionState::forceNextState(std::string state)
{
	// Assign next state to variable
	m_StateNext = state;
}

void UITransitionState::forceCurrentState(std::string state)
{
	// Switch states forcing the current state
	m_StateLast	   = m_StateCurrent;
	m_StateCurrent = state;
	m_StateNext	   = "";

	// Reset state ticks
	resetStateTicks();

	// Force all states back to waiting
	for (auto state : m_StatesMode)
		state.second = STATE_MODE_WAITING;

	// Make sure the new state is running
	m_StatesMode[m_StateCurrent] = STATE_MODE_RUNNING;
	
	// If there is a start callback call it
	if (f_StartCallbacks.find(m_StateCurrent) != f_StartCallbacks.end())
		f_StartCallbacks[m_StateCurrent](m_ParentElement, this);
}

int8_t UITransitionState::getStateMode(std::string state_name)
{
	// Check state modes map, if the stored state mode already exists retrieve it
	// from the map, otherwise create a new state mode with a default state of
	// STATE_MODE_WAITING (1)
	if (m_StatesMode.find(state_name) != m_StatesMode.end())
		return m_StatesMode[state_name];
	else
	{
		addState(state_name);
		return m_StatesMode[state_name] = STATE_MODE_WAITING;
	}
}

void UITransitionState::updateNextState()
{
	// Update the current state mode, set the last state to the current state
	// and reset the next state
	m_StatesMode[m_StateCurrent] = STATE_MODE_COMPLETE;
	m_StateLast	   = m_StateCurrent;
	m_StateCurrent = m_StateNext;
	m_StateNext    = "";

	// Reset state ticks
	resetStateTicks();
}
