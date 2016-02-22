#include "Button.h"
#include "../../utilities/Random.h"

#include <iostream>

Button::Button(sf::Vector2f position, std::string id) :
	UIElement(position, id),
	m_ButtonState(eButtonState::BUTTONSTATE_DEFAULT)
{
	// Set initial transitioning states
	m_TransitionState->initDefaultStates();
}

Button::~Button()
{
}

void Button::init()
{
	//f_OnReleased = std::bind(&Button::lockCallback, this, std::placeholders::_1, std::placeholders::_2);
}

void Button::onPressed(sf::Mouse::Button button)
{
	// Make sure button isn't locked and is renderable, if it is change the button state
	// to pressed, renderable animation to OnPressed and force the next state
	if (checkRenderable() && (m_ButtonState != eButtonState::BUTTONSTATE_LOCKED))
	{
		m_ButtonState = eButtonState::BUTTONSTATE_PRESSED;
		m_Renderable->changeAnimation("OnPressed");
		m_TransitionState->forceNextState("TPressed");
	}
}

void Button::onReleased(sf::Mouse::Button button)
{
	if (checkRenderable() && (m_ButtonState != eButtonState::BUTTONSTATE_LOCKED))
	{
		m_TransitionState->forceNextState("TReleased");

		if (checkEntered())
		{
			m_ButtonState = eButtonState::BUTTONSTATE_HOVER;
			m_Renderable->changeAnimation("OnEntered");
		}
		else
		{
			m_ButtonState = eButtonState::BUTTONSTATE_DEFAULT;
			m_Renderable->changeAnimation("OnDefault");
		}
	}
}

void Button::onEnter()
{
	if (checkRenderable() && !checkPressed() && (m_ButtonState != eButtonState::BUTTONSTATE_LOCKED))
	{
		m_ButtonState = eButtonState::BUTTONSTATE_HOVER;
		m_Renderable->changeAnimation("OnEntered");
	}
}

void Button::onExit()
{
	if (checkRenderable() && !checkPressed() && (m_ButtonState != eButtonState::BUTTONSTATE_LOCKED))
	{
		m_ButtonState = eButtonState::BUTTONSTATE_DEFAULT;
		m_Renderable->changeAnimation("OnDefault");
	}
}

void Button::lockButton()
{
	if (checkRenderable())
	{
		m_ButtonState = eButtonState::BUTTONSTATE_LOCKED;
		m_Renderable->changeAnimation("OnLocked");
		m_TransitionState->forceNextState("TDisabled");
	}
}

void Button::unlockButton()
{
	if (checkRenderable())
	{
		m_TransitionState->forceNextState("TEnabled");

		if (checkEntered())
		{
			m_ButtonState = eButtonState::BUTTONSTATE_HOVER;
			m_Renderable->changeAnimation("OnEntered");
		}
		else
		{
			m_ButtonState = eButtonState::BUTTONSTATE_DEFAULT;
			m_Renderable->changeAnimation("OnDefault");
		}
	}
}

void Button::lockCallback(UIElement* element, sf::Mouse::Button button)
{
	if (button == sf::Mouse::Button::Left)
	{
		if(static_cast<Button*>(element)->getButtonState() == eButtonState::BUTTONSTATE_PRESSED)
			static_cast<Button*>(element)->lockButton();
	}
}
