#include "RenderableText.h"
#include "../utilities/Vectors.h"
#include "../common/ResourceManager.h"

RenderableText::RenderableText() :
	m_CharacterSize(30U),
	m_Font(nullptr),
	m_Padding(4.0f, 4.0f)
{
	initialiseColours();
}

RenderableText::RenderableText(sf::Vector2f pos, const sf::String& source, const sf::Font& font, uint32_t characterSize) :
	m_CharacterSize(characterSize),
	m_Font(&font),
	m_Padding(4.0f, 4.0f)
{
	initialiseColours();
	setString(source);
	setPosition(pos);
}

void RenderableText::setString(const std::string& source)
{
	if (m_Font == nullptr || source.empty())
		return;

	RichTextTokenizer tokenizer(source);
	parseTokens(tokenizer);
}

void RenderableText::setFont(std::string font)
{
	m_Font = ResourceManager::instance().lookupFont(font);

	for (auto line : m_TextData)
	{
		for (auto text : line)
			text.setFont(*m_Font);
	}
}

void RenderableText::setCharacterSize(uint32_t size)
{
	m_CharacterSize = size;

	for (auto line : m_TextData)
	{
		for (auto text : line)
			text.setCharacterSize(size);
	}
}

void RenderableText::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto line : m_TextData)
	{
		for (auto text : line)
			target.draw(text);
	}
}

void RenderableText::setPosition(const sf::Vector2f& point)
{
	// Set the new position
	Transformable::setPosition(point);

	// Now that we have the text position it
	if (!m_TextData.empty())
	{
		float next_x = getPosition().x;
		float next_y = getPosition().y + (m_Padding.y / 2.0f);

		for (int32_t i = 0; i < m_TextData.size(); i++)
		{
			next_x = getPosition().x + (m_Padding.x / 2.0f);

			for (int32_t x = 0; x < m_TextData[i].size(); x++)
			{
				m_TextData[i][x].setPosition(next_x, next_y);
				next_x += m_TextData[i][x].getLocalBounds().width + 2.0f;
			}

			
			next_y += m_CharacterSize;
		}
	}
}

void RenderableText::setPosition(float x, float y)
{
	// Call down to set position
	setPosition(x, y);
}

sf::FloatRect RenderableText::getLocalBounds() const
{
	float height = m_CharacterSize * m_TextData.size();
	float width  = 0.0f;

	for (auto line : m_TextData)
	{
		float next_width = 0.0f;

		for (auto text : line)
			next_width += (text.getLocalBounds().width + 2.0f);

		width = std::max(width, next_width);
	}

	sf::FloatRect bounds;
	bounds.left   = getPosition().x;
	bounds.top    = getPosition().y;
	bounds.width  = width + m_Padding.x;
	bounds.height = height + m_Padding.y;
	return bounds;
}

std::vector<sf::Text> RenderableText::getLineData(int32_t index)
{
	// Get all corresponding line texts
	std::vector<sf::Text> texts;
	for (auto text : m_TextData[index])
		texts.push_back(text);

	// Return them
	return texts;
}

std::string RenderableText::getLineText(int32_t index)
{
	// Store results and lines
	std::string result = "";
	std::vector<sf::Text> texts = getLineData(index);

	// Add to the resulting string
	for (auto text : texts)
		result += text.getString();

	// Return result
	return result;
}

void RenderableText::parseTokens(RichTextTokenizer tokenizer)
{
	// Store temporary data for the next line of text
	sf::Color	colour = sf::Color::White;
	std::string	text = "";
	bool		coloured = false;
	bool		bold = false;
	bool		italic = false;
	bool		underline = false;
	bool		found_text = false;

	// Clear all previous data and make sure we have our
	// first line
	m_TextData.clear();
	m_TextData.push_back(std::vector<sf::Text>());

	// Loop through the tokenizer until we have no tokens left
	while (!tokenizer.isEmpty())
	{
		// Find the next token
		RichTextToken next_token = tokenizer.getNextToken();
		
		// Based on token type apply operation to our temporary variables
		if (next_token.type == RichTextToken::FORMAT_BEGIN)
		{
			if (!found_text)
			{
				if (next_token.formatType == RichTextToken::COLOUR)
				{
					coloured = true;
					colour = next_token.colour;
				}
				else if (next_token.formatType == RichTextToken::BOLD)
					bold = true;
				else if (next_token.formatType == RichTextToken::ITALIC)
					italic = true;
				else if (next_token.formatType == RichTextToken::UNDERLINE)
					underline = true;
			}
			else
			{
				parseNextLine(coloured, bold, italic, underline, colour, text);

				colour = sf::Color::White;
				text = "";
				bold = italic = underline = found_text = false;
			}
		}
		else if (next_token.type == RichTextToken::FORMAT_END)
		{
			if (found_text)
			{
				parseNextLine(coloured, bold, italic, underline, colour, text);

				colour = sf::Color::White;
				text = "";
				bold = italic = underline = found_text = false;
			}
			else
			{
				colour = sf::Color::White;
				text = "";
				bold = italic = underline = found_text = false;
			}
		}
		else if (next_token.type == RichTextToken::EOL)
		{
			if (found_text)
			{
				parseNextLine(coloured, bold, italic, underline, colour, text);
				m_TextData.push_back(std::vector<sf::Text>());

				colour = sf::Color::White;
				text = "";
				bold = italic = underline = found_text = false;
			}
			else
			{
				m_TextData.push_back(std::vector<sf::Text>());
				colour = sf::Color::White;
				text = "";
				bold = italic = underline = found_text = false;
			}
		}
		else if (next_token.type == RichTextToken::TEXT)
		{
			if (!found_text)
			{
				found_text = true;
				text = next_token.text;
			}
			else
			{
				parseNextLine(coloured, bold, italic, underline, colour, text);

				colour = sf::Color::White;
				text = "";
				bold = italic = underline = found_text = false;
			}
		}
	}

	// Make sure we add the last text
	if (found_text)
		parseNextLine(coloured, bold, italic, underline, colour, text);

	// Posiiton the new text
	setPosition(getPosition());
}

void RenderableText::parseNextLine(bool coloured, bool bold, bool italic, bool underline,
									sf::Color colour, std::string text)
{
	sf::Text new_text;

	if (bold)      new_text.setStyle(new_text.getStyle() | sf::Text::Bold);
	if (italic)    new_text.setStyle(new_text.getStyle() | sf::Text::Italic);
	if (underline) new_text.setStyle(new_text.getStyle() | sf::Text::Underlined);

	new_text.setString(text);
	new_text.setColor(colour);
	new_text.setFont(*m_Font);
	new_text.setCharacterSize(m_CharacterSize);

	m_TextData[m_TextData.size()-1].push_back(new_text);
}

///////////////////////////////////////////////////////////
RichTextTokenizer::RichTextTokenizer(sf::String string)
{
	tokenize(string);
}

RichTextTokenizer::~RichTextTokenizer()
{
}

RichTextToken RichTextTokenizer::getNextToken()
{
	// Get the next token and pop it
	RichTextToken token = m_Tokens.front();
	m_Tokens.pop_front();
	return token;
}

bool RichTextTokenizer::isEmpty() const
{
	return m_Tokens.empty();
}

void RichTextTokenizer::tokenize(sf::String string)
{
	size_t prev_pos   = 0;
	size_t pos	      = 0;
	size_t prev_token = 0;

	// TODO: Syntax checking. Also probably merge eType & eFormatType again xD
	std::string str = string;

	while(1)
	{
		pos = str.find_first_of("<\n", prev_pos);

		if (pos == std::string::npos)
		{
			// Copy everything that's left into a text token and STAHP
			std::string text = str.substr(prev_token);
			if(text.length() > 0)
				m_Tokens.push_back(RichTextToken(text, RichTextToken::TEXT));

			break;
		}
		else if (str[pos] == '<')
		{
			// if ( x<i or y>4) 
			// Likely a formatting token
			// Find closing bracket
			prev_pos = pos;
			pos		 = str.find_first_of(">", prev_pos);

			RichTextToken new_token;
			if (parseFormatToken(str.substr(prev_pos + 1, pos - prev_pos - 1), new_token))
			{
				// Write text in between this token and the previous one
				std::string text = str.substr(prev_token, prev_pos - prev_token);
				if (text.length() > 0)
					m_Tokens.push_back(RichTextToken(text, RichTextToken::TEXT));

				m_Tokens.push_back(new_token);
				prev_token = (pos + 1);
			}
		}
		else if(str[pos] == '\n')
		{
			// EOL token
			m_Tokens.push_back(RichTextToken(str[pos], RichTextToken::EOL));
			prev_token = (pos + 1);
		}

		prev_pos = pos + 1;
	}
}

bool RichTextTokenizer::parseFormatToken(std::string string, RichTextToken& token)
{
	// Parse format token
	// Check if it's a closing tag
	if(string[0] == '/') 
	{
		string = string.substr(1);
		token.type = RichTextToken::FORMAT_END;
	}
	else
	{
		token.type = RichTextToken::FORMAT_BEGIN;
	}

	
	if(string[0] == 'c')
	{
		// Likely a colour token
		size_t pos = string.find(" ");
		
		if (string.substr(0, pos) != "colour")
			return false;

		token.formatType = RichTextToken::COLOUR;

		if(token.type == RichTextToken::FORMAT_BEGIN)
		{
			std::string colour_str = string.substr(pos);
			token.colour = colFromStr(colour_str);

			if (token.colour == sf::Color::Transparent)
				return false;
		}
	}
	else
	{
		// Probably <i>, <b> or <u>, should only be 1 character long
		if (string.length() != 1)
			return false;

		if (string[0] == 'i')
			token.formatType = RichTextToken::ITALIC;
		else if (string[0] == 'b')
			token.formatType = RichTextToken::BOLD;
		else if (string[0] == 'u')
			token.formatType = RichTextToken::UNDERLINE;
		else
			return false;
	}

	return true;
}
