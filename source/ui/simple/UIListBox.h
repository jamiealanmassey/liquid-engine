#ifndef _UILISTBOX_H
#define _UILISTBOX_H

#include "../UIElement.h"
#include "UIStaticLabel.h"

class UIListBox : public UIElement
{
public:
	enum eListType
	{
		SINGLE	 = 0,
		MULTIPLE = 1,
	};

public:
	UIListBox(UIElement* parent, std::string id, sf::Vector2f size, std::string elementName);
	~UIListBox();

	void implInitialise() override;
	void implUpdate()	  override;

	virtual void acceptListener(UIElement* element, int32_t eventID) override;
	virtual void setPosition(const sf::Vector2f& point)				 override;

	void addItem(std::string text);
	void setOutlineColour(sf::Color colour);
	void setCharacterSize(uint32_t size);

	bool isItemSelected(UIElement* element);
	bool isItemSelected(int32_t index);

	std::vector<UIElement*> getSelectedItems();

	void renderCallback(Renderable* renderable, sf::RenderTarget& target);

protected:
	void    updateLabelPositions();
	int32_t getSelectedIndex(UIElement* element);

protected:
	std::vector<UIStaticLabel*> m_ListItems;
	std::vector<UIElement*>		m_SelectedItems;
	sf::RectangleShape			m_FrameOutline;
	sf::Vector2f				m_Padding;
	eListType					m_ListType;
	uint32_t					m_CharacterSize;
};

#endif // _UILISTBOX_H
