#ifndef _VECTORS_H
#define _VECTORS_H

#include <SFML/Graphics.hpp>

float lengthSq(const sf::Vector2f& v);
float length(const sf::Vector2f& v);
float dotProduct(const sf::Vector2f& v, const sf::Vector2f& v2);

sf::Vector2f normalize(const sf::Vector2f& v);
sf::Vector2f absolute(const sf::Vector2f& v);

float getOrder(const sf::Vector2f& v, const sf::Vector2f& v2);
float getAbsAngle(const sf::Vector2f& v, const sf::Vector2f& v2);
float getAngle(const sf::Vector2f& v, const sf::Vector2f& v2);

sf::Vector2f projectVector(const sf::Vector2f& v, const sf::Vector2f& v2);
sf::Vector2f hadamard(const sf::Vector2f& v, const sf::Vector2f& v2);
sf::Vector2i hadamardI(const sf::Vector2i& v, const sf::Vector2i& v2);

bool isZero(const sf::Vector2f& v);

// Generic function for converting strings to vectors
enum eBracketStyle
{
	Bracket_None = 0,
	Bracket_Round = 1,
	Bracket_Square = 2,
	Bracket_Curly = 3
};

sf::Vector2f vecFromStr(std::string str, eBracketStyle style = eBracketStyle::Bracket_Round, char delim = ',');
sf::Color    colFromStr(std::string str, eBracketStyle style = eBracketStyle::Bracket_Round, char delim = ',');

#endif // _VECTORS_H
