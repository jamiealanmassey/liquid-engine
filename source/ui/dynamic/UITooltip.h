#ifndef _UITOOLTIP_H
#define _UITOOLTIP_H

#include "../UIElement.h"
#include "../../graphics/RenderableText.h"

class UITooltip : public UIElement
{
public:
	UITooltip(UIElement* parent, std::string id, sf::Vector2f size, std::string elementName);
	~UITooltip();

	virtual void implInitialise() override;
	virtual void implUpdate()	  override;

	void instantiateFrame();
	void updateFrame();

	virtual void setPressed(bool flag) override;
	virtual void setEntered(bool flag) override;

	virtual void setPosition(const sf::Vector2f& point) override;

	void setTooltipText(const std::string text);
	void renderCallback(Renderable* renderable, sf::RenderTarget& target);

	RenderableText* getRenderableText() { return m_RenderableText; }

protected:
	RenderableText*						m_RenderableText;
	std::vector<UIElement*>				m_TooltipFrame;
	std::vector<std::vector<sf::Text*>> m_TooltipText;
	
};

#endif // _UITOOLTIP_H
