#include "Vectors.h"

#include <sstream>
#include <iostream>

using namespace std;

float lengthSq(const sf::Vector2f& v)
{
	return (v.x * v.x + v.y * v.y);
}

float length(const sf::Vector2f& v)
{
	return sqrtf(lengthSq(v));
}

float dotProduct(const sf::Vector2f& v, const sf::Vector2f& v2)
{
	return ((v.x * v2.x) + (v.y * v2.y));
}

sf::Vector2f normalize(const sf::Vector2f& v)
{
	return (v / length(v));
}

sf::Vector2f absolute(const sf::Vector2f& v)
{
	return sf::Vector2f(fabsf(v.x), fabsf(v.y));
}

float GetOrder(const sf::Vector2f& v, const sf::Vector2f& v2)
{
	// Calculate the normal and then the angle between vector 2 and the normal of vector 1
	sf::Vector2f norm1 = normalize(v);
	sf::Vector2f norm2 = normalize(v2);
	float		 dot   = dotProduct(sf::Vector2f(norm1.y, norm1.x), norm2);

	//Result
	return (dot / fabsf(dot));
}

float getAbsAngle(const sf::Vector2f& v, const sf::Vector2f& v2)
{
	// Calculate the normal and then the angle between the vectors
	sf::Vector2f norm1 = normalize(v);
	sf::Vector2f norm2 = normalize(v2);
	float        alpha = acos(dotProduct(norm1, norm2));

	// Result
	return alpha;
}

float getAngle(const sf::Vector2f& v, const sf::Vector2f& v2)
{
	// Calculate the normal and then the angle between the vectors
	sf::Vector2f norm1 = normalize(v);
	sf::Vector2f norm2 = normalize(v2);
	float        alpha = acos(dotProduct(norm1, norm2));

	// Calculate the normal and then the angle between vector 2 and the normal of vector 1
	float dot   = dotProduct(sf::Vector2f(norm1.y, norm1.x), norm2);
	float order = (dot / fabsf(dot));

	// Result
	return alpha * order;
}

sf::Vector2f projectVector(const sf::Vector2f& v, const sf::Vector2f& v2)
{
	float dot_prod  = dotProduct(v, v2);
	float length_sq = lengthSq(v2);

	return dot_prod / length_sq * v2;
}

sf::Vector2f hadamard(const sf::Vector2f& v, const sf::Vector2f& v2)
{
	return sf::Vector2f(v.x * v2.x, v.y * v2.y);
}

sf::Vector2i hadamardI(const sf::Vector2i& v, const sf::Vector2i& v2)
{
	return sf::Vector2i(v.x * v2.x, v.y * v2.y);
}

bool isZero(const sf::Vector2f& v)
{
	return v == sf::Vector2f();
}

sf::Vector2f vecFromStr(string str, eBracketStyle style, char delim)
{
	string brackets = "";
	if (style == eBracketStyle::Bracket_Round)
		brackets = "()";
	else if (style == eBracketStyle::Bracket_Square)
		brackets = "[]";
	else if (style == eBracketStyle::Bracket_Curly)
		brackets = "{}";

	// Get rid of white spaces
	string::iterator it = str.begin();
	for (; it != str.end(); it++)
	{
		if (*it == ' ')
		{
			it = str.erase(it);
			if (it == str.end())
				break;
		}
	}

	// First character must be open bracket
	// Last character must be close bracket
	if (style != eBracketStyle::Bracket_None)
	{
		if ((str[0] != brackets[0]) || (str.back() != brackets[1]))
		{
			cout << "Could not convert string \"" << str << "\" to Vector2f!" << endl;
			return sf::Vector2f();
		}

		// Remove brackets from string for easier access to the numbers
		str = str.substr(1, str.size() - 2);
	}

	// Find delimiter
	size_t pos = str.find(delim);
	if (pos == string::npos)
	{
		cout << "Could not convert string \"" << str << "\" to Vector2f!" << endl;
		return sf::Vector2f();
	}

	// Parse x & y values
	sf::Vector2f vec;
	stringstream ss(str.substr(0, pos));
	if (!(ss >> vec.x))
	{
		cout << "Could not convert string \"" << str << "\" to Vector2f!" << endl;
		return sf::Vector2f();
	}

	ss.clear(); ss.str(str.substr(pos + 1));
	if (!(ss >> vec.y))
	{
		cout << "Could not convert string \"" << str << "\" to Vector2f!" << endl;
		return sf::Vector2f();
	}

	return vec;
}

sf::Color colFromStr(string str, eBracketStyle style, char delim)
{
	string brackets = "";
	if (style == eBracketStyle::Bracket_Round)
		brackets = "()";
	else if (style == eBracketStyle::Bracket_Square)
		brackets = "[]";
	else if (style == eBracketStyle::Bracket_Curly)
		brackets = "{}";

	// Get rid of white spaces
	string::iterator it = str.begin();
	for (; it != str.end(); it++)
	{
		if (*it == ' ')
		{
			it = str.erase(it);
			if (it == str.end())
				break;
		}
	}

	// First character must be open bracket
	// Last character must be close bracket
	if (style != eBracketStyle::Bracket_None)
	{
		if ((str[0] != brackets[0]) || (str.back() != brackets[1]))
		{
			cout << "Could not convert string \"" << str << "\" to Color!" << endl;
			return sf::Color();
		}

		// Remove brackets from string for easier access to the numbers
		str = str.substr(1, str.size() - 2);
	}

	// Find rg, gb & ba delimiters
	size_t rg = str.find(delim);
	size_t gb = str.find(delim, (rg + 1));
	size_t ba = str.find(delim, (gb + 1));
	if ((rg == string::npos) || (gb == string::npos))
	{
		cout << "Could not convert string \"" << str << "\" to Color!" << endl;
		return sf::Color();
	}

	// Parse alpha value
	sf::Color    col;
	uint32_t     tmp;
	stringstream ss;

	if (ba != string::npos)
	{
		ss.str(str.substr(ba + 1));
		if (!(ss >> tmp))
		{
			cout << "Could not convert string \"" << str << "\" to Color!" << endl;
			return sf::Color();
		}
		col.a = tmp;
	}
	else
		ba = (str.length() + 1); // Makes reading in the blue component easier

								 // Parse rgb values
	ss.clear(); ss.str(str.substr(0, rg));
	if (!(ss >> tmp))
	{
		cout << "Could not convert string \"" << str << "\" to Color!" << endl;
		return sf::Color();
	}
	col.r = tmp;

	ss.clear(); ss.str(str.substr(rg + 1, (gb - rg - 1)));
	if (!(ss >> tmp))
	{
		cout << "Could not convert string \"" << str << "\" to Color!" << endl;
		return sf::Color();
	}
	col.g = tmp;

	ss.clear(); ss.str(str.substr(gb + 1, (ba - gb - 1)));
	if (!(ss >> tmp))
	{
		cout << "Could not convert string \"" << str << "\" to Color!" << endl;
		return sf::Color();
	}
	col.b = tmp;

	return col;
}
