#include "UITransitionFuncs.h"
#include "UITransitionState.h"
#include "UIElement.h"

// -------- PREDEFINED TRANSITION STATE FUNCS ----------
bool TransitionFuncMoveTo(UIElement* element, UITransitionState* state, TransitionMoveTo* data)
{
	// On first tick sample origin position and switch flag
	if (data->transition_first_tick)
	{
 		data->transition_position_first = element->getPosition();
		data->transition_first_tick = false;

		element->setAllowInteraction(false);
	}

	// Sample position and time and then calculate difference of position and
	// time
	sf::Vector2f element_diff = data->transition_position - data->transition_position_first;
	float		 time_slice = state->getStateTicks();
	float		 time_diff = (1000.0f * time_slice) / (1000.0f * data->transition_time);

	// Scale (interporlate) position difference and set new position
	// from calculation
	element_diff *= time_diff;
	element->setPosition(data->transition_position_first + element_diff);

	// If the time_slice has exceeded the transition time then
	// we are done, otherwise return false
	if (time_slice >= data->transition_time)
	{
		element->setAllowInteraction(true);
		return true;
	}
	else
		return false;
}

bool TransitionFuncAnimate(UIElement* element, UITransitionState* state, TransitionAnimate* data)
{
	// On first tick change animation and switch flag
	if (data->transition_first_tick)
	{
		data->transition_first_tick = false;

		element->setAllowInteraction(false);
		element->getRenderable()->changeAnimation(data->transition_animation);
	}

	// Check the animation has finished, if it has return true otherwise carry on
	// animating
	if (element->getRenderable()->getCurrentFrame() == element->getRenderable()->getEndFrame())
	{
		element->setAllowInteraction(true);
		return true;
	}
	else
		return false;
}
