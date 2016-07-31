#ifndef _UISELECTIONELEMENT_H
#define _UISELECTIONELEMENT_H

#include "../UIElement.h"
#include "UISelectionBox.h"
#include "UIStaticLabel.h"

class UISelectionElement : public UIElement
{
public:
	UISelectionElement(UIElement* parent, std::string id, sf::Vector2f size, std::string elementName);
	~UISelectionElement();

	virtual void implInitialise() override;
	virtual void implUpdate()	  override;

	virtual void setPressed(bool flag) override;
	virtual void setEntered(bool flag) override;

	void acceptListener(UIElement* element, int32_t eventID);

	void setPosition(const sf::Vector2f& point) override;
	void setText(std::string text, sf::Color colour, uint32_t size = 12U);
	void setSelectionType(UISelectionBox::eSelectionType type);

	void select();
	void deselect();

	void renderCallback(Renderable* renderable, sf::RenderTarget& target);

	bool		   isSelected()		const { return m_IsSelected;  }
	UIStaticLabel* getStaticLabel()		  { return m_RadioLabel;  }

protected:
	bool					       m_IsSelected;
	UIStaticLabel*				   m_RadioLabel;
	UISelectionBox::eSelectionType m_SelectionType;
};

#endif // _UISELECTIONELEMENT_H
