#include "LerpValue.h"
#include "Random.h"
#include "Vectors.h"

// Type-specific implementations for LerpValues
LerpVector LerpVector::vary() const
{
	// Safe-guard against division by zero
	if ((variant.x == 0.0f) && (variant.y == 0.0f))
		return *this;

	sf::Vector2f var = absolute(variant);
	var = randomRangeV(-var, var);
	return{ start + var, end + var, sf::Vector2f() };
}

sf::Vector2f LerpVector::at(float ratio) const
{
	float inv_ratio = (1.0f - ratio);
	return (inv_ratio*start + ratio*end);
}

LerpInt32 LerpInt32::vary() const
{
	// Safe-guard against division by zero
	if (variant == 0)
		return *this;

	int32_t var = randomRange(-variant, variant);
	return{ start + var, end + var, 0 };
}

int32_t LerpInt32::at(float ratio) const
{
	float inv_ratio = (1.0f - ratio);
	return (inv_ratio*start + ratio*end);
}

LerpFloat LerpFloat::vary() const
{
	// Safe-guard against division by zero
	if (variant == 0.0f)
		return *this;

	float var = fabsf(variant);
	var = randomRangeF(-var, var);
	return{ start + var, end + var, 0.0f };
}

float LerpFloat::at(float ratio) const
{
	float inv_ratio = (1.0f - ratio);
	return (inv_ratio*start + ratio*end);
}

LerpColour LerpColour::vary() const
{
	int32_t var_r, var_g, var_b, var_a;
	var_r = variant.r != 0 ? (-variant.r, variant.r) : 0;
	var_g = variant.g != 0 ? (-variant.g, variant.g) : 0;
	var_b = variant.b != 0 ? (-variant.b, variant.b) : 0;
	var_a = variant.a != 0 ? (-variant.a, variant.a) : 0;

	LerpColour res;
	res.start.r = std::max(std::min(start.r + var_r, 255), 0);
	res.start.g = std::max(std::min(start.g + var_g, 255), 0);
	res.start.b = std::max(std::min(start.b + var_b, 255), 0);
	res.start.a = std::max(std::min(start.a + var_a, 255), 0);

	res.end.r = std::max(std::min(end.r + var_r, 255), 0);
	res.end.g = std::max(std::min(end.g + var_g, 255), 0);
	res.end.b = std::max(std::min(end.b + var_b, 255), 0);
	res.end.a = std::max(std::min(end.a + var_a, 255), 0);

	res.variant = sf::Color::Transparent;
	return res;
}

sf::Color LerpColour::at(float ratio) const
{
	float inv_ratio = (1.0f - ratio);

	sf::Color res;
	res.r = inv_ratio*start.r + ratio*end.r;
	res.g = inv_ratio*start.g + ratio*end.g;
	res.b = inv_ratio*start.b + ratio*end.b;
	res.a = inv_ratio*start.a + ratio*end.a;

	return res;
}