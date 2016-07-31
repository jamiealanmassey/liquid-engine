#ifndef _UISTATICBOX_H
#define _UISTATICBOX_H

#include "../UIElement.h"

class UIStaticBox : public UIElement
{
public:
	UIStaticBox(UIElement* parent, std::string id, sf::Vector2f size, std::string elementName);
	~UIStaticBox();

	virtual void implInitialise() override;
	virtual void implUpdate()	  override;

	virtual void setSize(float x, float y)			override;
	virtual void setSize(const sf::Vector2f& point) override;

	void setColour(sf::Color colour);

	sf::Color getColour() { return m_StaticTopLeft->getRenderable()->getColor(); }

protected:
	void reconfigure();

protected:
	UIElement* m_StaticTopLeft;
	UIElement* m_StaticTopRight;
	UIElement* m_StaticTopMiddle;
	UIElement* m_StaticBtmMiddle;
	UIElement* m_StaticLeft;
	UIElement* m_StaticRight;
	UIElement* m_StaticBtmLeft;
	UIElement* m_StaticBtmRight;
};

#endif // _UISTATICBOX_H
