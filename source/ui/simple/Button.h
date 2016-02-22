#ifndef _BUTTON_H
#define _BUTTON_H

#include "../UIElement.h"

class Button : public UIElement
{
public:
	enum eButtonState
	{
		BUTTONSTATE_DEFAULT = 0,
		BUTTONSTATE_PRESSED = 1,
		BUTTONSTATE_HOVER = 2,
		BUTTONSTATE_LOCKED = 3,
	};

public:
	Button(sf::Vector2f position, std::string id);
	~Button();

	void init() override;

	/* Overrided Functions */
	void onPressed(sf::Mouse::Button button)  override;
	void onReleased(sf::Mouse::Button button) override;
	void onEnter()							  override;
	void onExit()							  override;

	/* Lock Control Functions */
	void lockButton();
	void unlockButton();

	void lockCallback(UIElement* element, sf::Mouse::Button button);

	/* Getter Functions */
	eButtonState getButtonState() { return m_ButtonState; }

protected:
	eButtonState m_ButtonState; ///< Stores the current state of the button
};

#endif // _BUTTON_H
