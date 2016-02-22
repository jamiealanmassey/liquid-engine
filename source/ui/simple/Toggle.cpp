#include "Toggle.h"

Toggle::Toggle(sf::Vector2f position, std::string id) :
	UIElement(position, id),
	m_ToggleState(eToggleState::TOGGLESTATE_DEFAULT),
	m_Toggled(false)
{
}

Toggle::~Toggle()
{
}

void Toggle::init()
{
}

void Toggle::onPressed(sf::Mouse::Button button)
{
	if (checkRenderable() && (m_ToggleState != eToggleState::TOGGLESTATE_LOCKED))
	{
		m_Toggled = !m_Toggled;

		if (m_Toggled)
		{
			m_ToggleState = eToggleState::TOGGLESTATE_ACTIVE;
			m_Renderable->changeAnimation("OnToggled");
		}
		else
		{
			if (checkEntered())
			{
				m_ToggleState = eToggleState::TOGGLESTATE_HOVER;
				m_Renderable->changeAnimation("OnEntered");
			}
			else
			{
				m_ToggleState = eToggleState::TOGGLESTATE_DEFAULT;
				m_Renderable->changeAnimation("OnDefault");
			}
		}
	}
}

void Toggle::onEnter()
{
	if (checkRenderable() && !m_Toggled && (m_ToggleState != eToggleState::TOGGLESTATE_LOCKED))
	{
		m_ToggleState = eToggleState::TOGGLESTATE_HOVER;
		m_Renderable->changeAnimation("OnEntered");
	}
}

void Toggle::onExit()
{
	if (checkRenderable() && !m_Toggled && (m_ToggleState != eToggleState::TOGGLESTATE_LOCKED))
	{
		m_ToggleState = eToggleState::TOGGLESTATE_DEFAULT;
		m_Renderable->changeAnimation("OnDefault");
	}
}

void Toggle::lockToggle()
{
	if (checkRenderable())
	{
		m_ToggleState = eToggleState::TOGGLESTATE_LOCKED;
		m_Renderable->changeAnimation("OnLocked");
	}
}

void Toggle::unlockToggle()
{
	if (checkRenderable())
	{
		if (checkEntered() && !m_Toggled)
		{
			m_ToggleState = eToggleState::TOGGLESTATE_HOVER;
			m_Renderable->changeAnimation("OnEntered");
		}
		else if(m_Toggled)
		{
			m_ToggleState = eToggleState::TOGGLESTATE_ACTIVE;
			m_Renderable->changeAnimation("OnToggled");
		}
		else
		{
			m_ToggleState = eToggleState::TOGGLESTATE_DEFAULT;
			m_Renderable->changeAnimation("OnDefault");
		}
	}
}
