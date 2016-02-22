#ifndef _LERPVALUE_H
#define _LERPVALUE_H

#include <SFML/Graphics.hpp>

// TODO: Extend LerpValues (quadratic, logarithmic, etc. interpolation)
// Helper struct to store particle emitter data
template<class T, class V = T>
struct LerpValue
{
	LerpValue<T, V> vary()          const;
	T               at(float ratio) const;

	T start;
	T end;
	V variant;
};

typedef LerpValue<sf::Vector2f> LerpVector;
typedef LerpValue<int32_t>		LerpInt32;
typedef LerpValue<float>		LerpFloat;
typedef LerpValue<sf::Color>    LerpColour;

#endif // _LERPVALUE_H