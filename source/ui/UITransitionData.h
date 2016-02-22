#ifndef _UITRANSITIONDATA_H
#define _UITRANSITIONDATA_H

#include <iostream>
#include <SFML/Graphics.hpp>

#define TRANSITION_DATA_ID_DEFAULT -1
#define TRANSITION_DATA_ID_MOVETO   0
#define TRANSITION_DATA_ID_FADE	    1
#define TRANSITION_DATA_ID_ANIMATE  2

struct TransitionData
{
	// Constructor for data
	TransitionData() :
		transition_first_tick(true)
	{}

	// Variables for data
	int8_t transition_id;
	float  transition_time;
	bool   transition_first_tick;
};

struct TransitionMoveTo : public TransitionData
{
	// Constructor for data
	TransitionMoveTo(sf::Vector2f position, float time) :
		TransitionData(),
		transition_position(position),
		transition_position_first(sf::Vector2f())
	{
		transition_id   = TRANSITION_DATA_ID_MOVETO;
		transition_time = time;
	}

	// Variables for data
	sf::Vector2f transition_position;
	sf::Vector2f transition_position_first;
};

struct TransitionFade : public TransitionData
{
	// Constructor for data
	TransitionFade(int8_t to_alpha, float time) :
		TransitionData(),
		transition_alpha(to_alpha),
		transition_alpha_first(255)
	{
		transition_id   = TRANSITION_DATA_ID_FADE;
		transition_time = time;
	}

	// Variables for data
	int8_t transition_alpha;
	int8_t transition_alpha_first;
};

struct TransitionAnimate : public TransitionData
{
	// Constructor for data
	TransitionAnimate(std::string animation_name) :
		TransitionData(),
		transition_animation(animation_name)
	{
		transition_id   = TRANSITION_DATA_ID_ANIMATE;
		transition_time = -1;
	}

	// Variables for data
	std::string transition_animation;
};

#endif // _UITRANSITIONDATA_H
