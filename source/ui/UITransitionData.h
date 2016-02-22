#ifndef _UITRANSITIONDATA_H
#define _UITRANSITIONDATA_H

#include <iostream>
#include <SFML/Graphics.hpp>

#define TRANSITION_DATA_ID_DEFAULT -1
#define TRANSITION_DATA_ID_MOVETO   0
#define TRANSITION_DATA_ID_FADE	    1
#define TRANSITION_DATA_ID_ANIMATE  2
#define TRANSITION_DATA_ID_COLOUR   3

class TransitionData
{
public:
	TransitionData(int8_t id, float time);
	~TransitionData() {}

public:
	int8_t transition_id;
	float  transition_time;
	bool   transition_first_tick;
};

class TransitionMoveTo : public TransitionData
{
public:
	TransitionMoveTo(sf::Vector2f position, float time);
	~TransitionMoveTo() {}

public:
	sf::Vector2f transition_position;
	sf::Vector2f transition_position_first;
};

class TransitionFade : public TransitionData
{
public:
	TransitionFade(int8_t to_alpha, float time);
	~TransitionFade() {}

public:
	int8_t transition_alpha;
	int8_t transition_alpha_first;
};

class TransitionAnimate : public TransitionData
{
public:
	TransitionAnimate(std::string animation_name);
	~TransitionAnimate();

public:
	std::string transition_animation;
};

class TransitionColour : public TransitionData
{
public:
	TransitionColour(sf::Color colour, float time);
	~TransitionColour() {}

public:
	sf::Color transition_colour;
	sf::Color transition_colour_first;
};

#endif // _UITRANSITIONDATA_H
