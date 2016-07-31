#ifndef _RENDERABLETEXT_H
#define _RENDERABLETEXT_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <stack>
#include <list>

class RichTextTokenizer;

class RenderableText : public sf::Drawable, public sf::Transformable
{
public:
	RenderableText();
	RenderableText(sf::Vector2f pos, const sf::String& source, const sf::Font& font, uint32_t characterSize = 30U);

	void setString(const std::string& source);
	void setFont(std::string font);
	void setCharacterSize(uint32_t size);
	void clear() {}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void initialiseColours() {} // TODO

	void setPosition(const sf::Vector2f& point);
	void setPosition(float x, float y);

	sf::FloatRect getLocalBounds()  const;
	sf::FloatRect getGlobalBounds() const {} // TODO?

	sf::String getString() const {} // TODO
	sf::String getSource() const {} // TODO

	std::vector<sf::Text> getLineData(int32_t index);
	std::string			  getLineText(int32_t index);

	void setPadding(const sf::Vector2f& point) { m_Padding = point; }
	void setPadding(float x, float y) { setPadding(sf::Vector2f(x, y)); }

protected:
	void parseTokens(RichTextTokenizer tokenizer);
	void parseNextLine(bool coloured, bool bold, bool italic, bool underline, 
						sf::Color colour, std::string text);

protected:
	std::map<std::string, sf::Color>   m_ColourIndex;
	std::vector<std::vector<sf::Text>> m_TextData;
	std::vector<std::string>		   m_Source;
	std::vector<std::string>		   m_String;
	sf::FloatRect					   m_Bounds;
	sf::Vector2f					   m_Padding;
	uint32_t						   m_CharacterSize;
	const sf::Font*					   m_Font;
};

struct RichTextToken
{
	enum eType
	{
		FORMAT_BEGIN = 0,
		FORMAT_END   = 1,
		TEXT		 = 2,
		EOL			 = 3,
	};

	enum eFormatType
	{
		BOLD	  = 0,
		COLOUR	  = 1,
		ITALIC	  = 2,
		UNDERLINE = 3,
	};

	RichTextToken() {}
	RichTextToken(sf::String _text, eType _type) :
		text(_text),
		type(_type)
	{}

	sf::Color   colour;
	std::string text;
	eType	    type;
	eFormatType formatType;
};

class RichTextTokenizer
{
public:
	RichTextTokenizer(sf::String string);
	~RichTextTokenizer();

	RichTextToken getNextToken();
	bool		  isEmpty() const;

protected:
	void tokenize(sf::String string);
	bool parseFormatToken(std::string string, RichTextToken& token);

protected:
	std::list<RichTextToken> m_Tokens;
};

#endif // _RENDERABLETEXT_H
