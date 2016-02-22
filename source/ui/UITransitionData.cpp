#include "UITransitionData.h"

TransitionData::TransitionData(int8_t id, float time) :
	transition_first_tick(true)
{
	transition_id = id;
	transition_time = time;
}

TransitionMoveTo::TransitionMoveTo(sf::Vector2f position, float time) :
	TransitionData(TRANSITION_DATA_ID_MOVETO, time),
	transition_position(position),
	transition_position_first(sf::Vector2f())
{
}

TransitionFade::TransitionFade(int8_t to_alpha, float time) :
	TransitionData(TRANSITION_DATA_ID_FADE, time),
	transition_alpha(to_alpha),
	transition_alpha_first(255)
{
}

TransitionAnimate::TransitionAnimate(std::string animation_name) :
	TransitionData(TRANSITION_DATA_ID_ANIMATE, 0.0f),
	transition_animation(animation_name)
{
}

TransitionColour::TransitionColour(sf::Color colour, float time) :
	TransitionData(TRANSITION_DATA_ID_COLOUR, time),
	transition_colour(colour),
	transition_colour_first(sf::Color())
{
}
