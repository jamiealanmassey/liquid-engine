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

	// If the time_slice has exceeded the transition time then
	// we are done, otherwise return false
	if (state->getStateTicks() >= data->transition_time)
	{
		element->setAllowInteraction(true);
		return true;
	}

	// Sample position and time and then calculate difference of position and
	// time
	sf::Vector2f element_diff = data->transition_position - data->transition_position_first;
	float		 time_slice = state->getStateTicks();
	float		 time_diff = time_slice / data->transition_time;

	// Scale (interporlate) position difference and set new position
	// from calculation
	element_diff *= time_diff;
	element->setPosition(data->transition_position_first + element_diff);

	// Return false to indicate we are not yet done
	return false;
}

bool TransitionFuncFadeOut(UIElement* element, UITransitionState* state, TransitionFade* data)
{
	// On first tick change alpha and switch flag
	if (data->transition_first_tick)
	{
		// Sample colour and assign first alpha
		sf::Color colour = element->getRenderable()->getColor();
		colour.a = 255;

		// Flip flag and store the first setting for alpha
		data->transition_first_tick = false;
		data->transition_alpha_first = element->getRenderable()->getColor().a;

		// Disable interaction and setup the renderable to hide it
		element->setAllowInteraction(false);
		element->getRenderable()->setColor(colour);
	}

	// If the state ticks exceed transitioning time
	if (state->getStateTicks() >= data->transition_time)
	{
		// Sample colour and cap the alpha value
		sf::Color colour = element->getRenderable()->getColor();
		colour.a = 0;

		// Set the alpha of the element and re-allow interaction
		element->getRenderable()->setColor(colour);
		element->setAllowInteraction(true);
		return true;
	}

	// Take time slice and calculate difference of the time, invert the sampled
	// value and then apply that difference to the next alpha
	float time_slice = state->getStateTicks();
	float time_diff = time_slice / data->transition_time;
	float time_diff_inv = time_diff * -1;
	int8_t next_alpha = 255 * time_diff_inv;

	// Sample colour and apply next_alpha to the colour, finally pass that back
	// to the element given
	sf::Color next_colour = element->getRenderable()->getColor();
	next_colour.a		  = next_alpha;
	element->getRenderable()->setColor(next_colour);

	// Return false to indicate we are not yet done
	return false;
}

bool TransitionFuncFadeIn(UIElement* element, UITransitionState* state, TransitionFade* data)
{
	// On first tick change alpha and switch flag
	if (data->transition_first_tick)
	{
		// Sample colour and assign first alpha
		sf::Color colour = element->getRenderable()->getColor();
		colour.a = 0;

		// Flip flag and store the first setting for alpha
		data->transition_first_tick  = false;
		data->transition_alpha_first = element->getRenderable()->getColor().a;
		
		// Disable interaction and setup the renderable to hide it
		element->setAllowInteraction(false);
		element->getRenderable()->setColor(colour);
	}
	
	// If the state ticks exceed transitioning time
	if (state->getStateTicks() >= data->transition_time)
	{
		// Sample colour and cap the alpha value
		sf::Color colour = element->getRenderable()->getColor();
		colour.a = 255;

		// Set the alpha of the element and re-allow interaction
		element->getRenderable()->setColor(colour);
		element->setAllowInteraction(true);
		return true;
	}
	
	// Take time slice and calculate difference of the time, then apply that 
	// difference to the next alpha
	float time_slice  = state->getStateTicks();
	float time_diff   = time_slice / data->transition_time;
	int8_t next_alpha = 255 * time_diff;

	// Sample colour and apply next_alpha to the colour, finally pass that back
	// to the element given
	sf::Color next_colour = element->getRenderable()->getColor();
	next_colour.a		  = next_alpha;
	element->getRenderable()->setColor(next_colour);

	// Return false to indicate we are not yet done
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

bool TransitionFuncColourTo(UIElement* element, UITransitionState* state, TransitionColour* data)
{
	// On first call of the transition function change the first_tick flag and
	// sample the original colour of the element
	if (data->transition_first_tick)
	{
		// Sample variables
		data->transition_first_tick	  = false;
		data->transition_colour_first = element->getRenderable()->getColor();

		// Disabled element interaction
		element->setAllowInteraction(false);
	}

	// If state ticks exceed transition time
	if (state->getStateTicks() >= data->transition_time)
	{
		// Set colour of element to target colour and allow interaction
		// of the element again
		element->getRenderable()->setColor(data->transition_colour);
		element->setAllowInteraction(true);
		return true;
	}

	// Take time slice and calculate time difference
	float time_slice = state->getStateTicks();
	float time_diff  = time_slice / data->transition_time;

	// Calculate the colour difference based on first colour and targeted colour
	sf::Color colour_diff;
	colour_diff.r = std::fabsf(data->transition_colour.r - data->transition_colour_first.r);
	colour_diff.g = std::fabsf(data->transition_colour.g - data->transition_colour_first.g);
	colour_diff.b = std::fabsf(data->transition_colour.b - data->transition_colour_first.b);

	// Multiply the difference based on time passed
	colour_diff.r *= time_diff;
	colour_diff.g *= time_diff;
	colour_diff.b *= time_diff;

	// Store next colour and apply the colour difference
	sf::Color next_colour = data->transition_colour_first;
	next_colour -= colour_diff;

	// Min the value to make sure it doesn't exceed 255
	next_colour.r = std::min((int32_t)next_colour.r, 255);
	next_colour.g = std::min((int32_t)next_colour.g, 255);
	next_colour.b = std::min((int32_t)next_colour.b, 255);

	// Max the value to make sure it doesn't go below 0, also set the alpha
	// of the next colour to the element alpha value
	next_colour.r = std::max((int32_t)next_colour.r, 0);
	next_colour.g = std::max((int32_t)next_colour.g, 0);
	next_colour.b = std::max((int32_t)next_colour.b, 0);
	next_colour.a = element->getRenderable()->getColor().a;

	// Apply next colour and return false to indicate we are not done yet
	element->getRenderable()->setColor(next_colour);
	return false;
}
