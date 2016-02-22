#ifndef _TOGGLE_H
#define _TOGGLE_H

#include "../UIElement.h"

class Toggle : public UIElement
{
public:
	enum eToggleState
	{
		TOGGLESTATE_DEFAULT = 0,
		TOGGLESTATE_ACTIVE  = 1,
		TOGGLESTATE_HOVER   = 2,
		TOGGLESTATE_LOCKED  = 3,
	};

public:
	Toggle(sf::Vector2f position, std::string id);
	~Toggle();

	void init() override;

	/* Overrided Functions */
	void onPressed(sf::Mouse::Button button)  override;
	void onEnter()							  override;
	void onExit()							  override;

	/* Lock Control Functions */
	void lockToggle();
	void unlockToggle();

	//void lockCallback(UIElement* element, sf::Mouse::Button button);

	/* Getter Functions */
	eToggleState getToggleState()  { return m_ToggleState;								  }
	bool		 getToggleActive() { (m_ToggleState == eToggleState::TOGGLESTATE_ACTIVE); }

protected:
	eToggleState m_ToggleState; ///< Stores the current state of the toggle
	bool		 m_Toggled;     ///< Flag storing current toggled state
};

#endif // _TOGGLE_H