#ifndef _UIBUTTON_H
#define _UIBUTTON_H

#include "../UIElement.h"

class UIButton : public UIElement
{
public:
	UIButton(UIElement* parent, std::string id, sf::Vector2f size, std::string elementName);
	~UIButton();

	virtual void implInitialise() override;
	virtual void implUpdate()	  override;

	virtual void setPressed(bool flag) override;
	virtual void setEntered(bool flag) override;

	void setPosition(const sf::Vector2f& point) override;
	void setText(std::string text, sf::Color colour, uint32_t size = 12U);
	void centreText();
	void fitTextSize();

	void setDefaultElement(std::string element) { m_ButtonDefaultElement = element; }
	void setPressedElement(std::string element) { m_ButtonPressedElement = element; }
	void setDrawHover(bool flag)				{ m_DrawHover = flag;				}

	void renderEntered(Renderable* renderable, sf::RenderTarget& target);

protected:
	std::string m_ButtonDefaultElement;
	std::string m_ButtonPressedElement;
	std::string m_ButtonLockedElement;
	sf::Text*   m_ButtonText;
	bool		m_DrawHover;
};

#endif // _UIBUTTON_H
