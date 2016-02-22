#ifndef _RAND_H
#define _RAND_H

#include <SFML/Graphics.hpp>

int32_t		 randomRange(int32_t min, int32_t max);
float		 randomRangeF(float min, float max);
double		 randomRangeD(double min, double max);
sf::Vector2f randomRangeV(sf::Vector2f min, sf::Vector2f max);
sf::Vector2f randomUnitVector();

#endif // _RAND_H
