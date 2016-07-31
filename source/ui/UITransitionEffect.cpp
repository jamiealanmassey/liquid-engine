#include "UITransitionEffect.h"
#include "UIElement.h"
#include "../utilities/DeltaTime.h"

UITransitionEffect::UITransitionEffect(UIElement* element, float duration, FinishFunc finished) :
	m_FinishedCallback(finished),
	m_Element(element),
	m_Lifetime(0.0f),
	m_Duration(duration),
	m_Active(false)
{
}

UITransitionEffect::~UITransitionEffect()
{
}

void UITransitionEffect::trigger()
{
	// Reset the lifetime and activate transition effect
	resetLifetime();
	m_Active = true;
}

void UITransitionEffect::resetLifetime()
{
	// Set the transitions lifetime back to 0
	m_Lifetime = 0.0f;
}

///////////////////////////////////////////////////////////////
UITransitionTranslate::UITransitionTranslate(UIElement* element, float duration, sf::Vector2f point, FinishFunc finished) :
	UITransitionEffect(element, duration, finished),
	m_IsAbsolute(true)
{
	m_Point			 = point;
	m_PositionTarget = point;
}

UITransitionTranslate::~UITransitionTranslate()
{
}

void UITransitionTranslate::initialise()
{
}

void UITransitionTranslate::trigger()
{
	// Call down
	UITransitionEffect::trigger();

	// Update the target position
	if (!m_IsAbsolute)
		m_PositionTarget = m_Element->getPosition() + m_Point;
}

void UITransitionTranslate::update()
{
	// Add to the lifetime of the transition
	m_Lifetime += Delta;

	// See if lifetime has exceeded the duration of this effect, if it has
	// then execute callback and reset
	if (m_Lifetime >= m_Duration)
	{
		if (m_FinishedCallback)
			m_FinishedCallback();

		m_Active = false;
		resetLifetime();
	}

	// Calculate the timeslice ratio
	float ratio = (m_Lifetime / m_Duration);

	// Find difference and slice the position accordingly
	sf::Vector2f difference = (m_PositionTarget - m_Element->getPosition());
	sf::Vector2f slicedPosition = sf::Vector2f(difference.x * ratio, difference.y * ratio);
	sf::Vector2f newPosition = sf::Vector2f(m_Element->getPosition() + slicedPosition);

	// Move the UI element by the sliced position
	m_Element->setPosition(newPosition);
}
