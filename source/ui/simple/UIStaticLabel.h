#ifndef _UISTATICLABEL_H
#define _UISTATICLABEL_H

#include "../UIElement.h"

class UIStaticLabel : public UIElement
{
public:
	UIStaticLabel(UIElement* parent, std::string id, std::string elementName);
	~UIStaticLabel();

	virtual void implInitialise() override;
	virtual void implUpdate()	  override;

	virtual void setPosition(const sf::Vector2f& point) override;

	void setText(std::string text, sf::Color colour, uint32_t size = 12U);
	void setFont(std::string font);

	void renderCallback(Renderable* renderable, sf::RenderTarget& target);

	sf::Text*	getStaticText() { return m_StaticText;				}
	std::string getFontName()	{ return m_FontName;				}
	std::string getText()		{ return m_StaticText->getString(); }

protected:
	sf::Text*	m_StaticText;
	std::string m_FontName;
};

#endif // _UISTATICLABEL_H
