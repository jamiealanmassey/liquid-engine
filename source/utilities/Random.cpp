#include "Random.h"

int32_t randomRange(int32_t min, int32_t max)
{
	return rand() % (max - min) + min;//((max - min) * (rand() / RAND_MAX)) + min;
}

float randomRangeF(float min, float max)
{
	return ((max - min) * ((float)rand() / RAND_MAX)) + min;
}

double randomRangeD(double min, double max)
{
	return ((max - min) * ((double)rand() / RAND_MAX)) + min;
}

sf::Vector2f randomRangeV(sf::Vector2f min, sf::Vector2f max)
{
	float rx = randomRangeF(min.x, max.x);
	float ry = randomRangeF(min.y, max.y);
	return sf::Vector2f(rx, ry);
}

sf::Vector2f randomUnitVector()
{
	float x		 = randomRangeF(-1.0f, 1.0f);
	float y		 = randomRangeF(-1.0f, 1.0f);
	float length = sqrt((x * x) + (y * y));

	if (length != 0.0f)
	{
		x /= length;
		y /= length;
	}

	return sf::Vector2f(x, y);
}
