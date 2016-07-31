#ifndef _UISLIDER_H
#define _UISLIDER_H

#include "../UIElement.h"

class UISlider : public UIElement
{
public:
	enum eSliderType
	{
		SLIDER_HORIZONTAL = 0,
		SLIDER_VERTICAL   = 1,
	};

public:
	UISlider(UIElement* parent, std::string id, sf::Vector2f size, std::string elementName);
	~UISlider();

	virtual void implInitialise() override;
	virtual void implUpdate()	  override;

	virtual void setPressed(bool flag) override;
	virtual void setEntered(bool flag) override;

	void setPosition(const sf::Vector2f& point) override;

	void setSliderType(eSliderType type);
	void movedCallback(UIElement* element, sf::Vector2f mouse_pos);
	void renderCallback(Renderable* renderable, sf::RenderTarget& target);

	float getRatio() { return m_Ratio; }

protected:
	UIElement*  m_Element;
	UIElement*  m_Pointer;
	eSliderType m_Type;
	float	    m_Ratio;
};

#endif // _UISLIDER_H
