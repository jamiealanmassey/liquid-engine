#ifndef _UISELECTIONBOX_H
#define _UISELECTIONBOX_H

#include "../UIElement.h"

class UISelectionElement;
class UISelectionBox : public UIElement
{
public:
	enum eSelectionType
	{
		RADIOBOX = 0,
		CHECKBOX = 1,
	};

public:
	UISelectionBox(UIElement* parent, std::string id, sf::Vector2f size, std::string elementName, eSelectionType type);
	~UISelectionBox();

	virtual void implInitialise() override;
	virtual void implUpdate()	  override;

	virtual void setPressed(bool flag) override;
	virtual void setEntered(bool flag) override;

	virtual void acceptListener(UIElement* element, int32_t eventID) override;
	virtual void setPosition(const sf::Vector2f& point)				 override;

	void addSelection(UISelectionElement* radioBtn);
	void addSelection(std::vector<UISelectionElement*> radioBtnList);
	void setCurrentSelection(UIElement* element);
	bool isSelected(int32_t index);

	void formatBox();
	void renderCallback(Renderable* renderable, sf::RenderTarget& target);

	int32_t							 getCurrentSelection() const { return m_CurrentSelection; }
	std::vector<UISelectionElement*> getSelectionList()			 { return m_SelectionList;    }

protected:
	int32_t							 m_CurrentSelection;
	eSelectionType					 m_SelectionType;
	std::vector<UISelectionElement*> m_SelectionList;
};

#endif // _UISELECTIONBOX_H
