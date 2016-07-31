#ifndef _UICOMBOBOX_H
#define _UICOMBOBOX_H

#include "../UIElement.h"
#include "UIButton.h"
#include "UIStaticLabel.h"

class UIComboBox : public UIElement
{
public:
	UIComboBox(UIElement* parent, std::string id, sf::Vector2f size, std::string elementName);
	~UIComboBox();

	void implInitialise() override;
	void implUpdate()	  override;

	virtual void acceptListener(UIElement* element, int32_t eventID) override;
	virtual void setPosition(const sf::Vector2f& point)				 override;

	void addSelection(std::string text);
	void setCharacterSize(uint32_t size);
	void setSelectionColour(sf::Color colour);

	void dropdownPressed(UIElement* element, sf::Mouse::Button button);
	void dropdownReleased(UIElement* element);

	void renderCallback(Renderable* renderable, sf::RenderTarget& target);
	void selectionEntered(UIElement* element);
	void selectionExited(UIElement* element);

protected:
	void dropdownOpen();
	void dropdownClose();

protected:
	std::vector<UIStaticLabel*> m_SelectionList;
	std::vector<UIElement*>		m_SelectionElements;
	UIStaticLabel*				m_CurrentSelection;
	UIButton*					m_DropdownBtn;
	UIElement*					m_InputElement;
	UIElement*					m_HeaderElement;
	UIElement*					m_FooterElement;
	uint32_t					m_CharacterSize;
	sf::Color					m_StoredColour;
	sf::Color					m_SelectionColour;
	int32_t						m_SelectionPressed;
};

#endif // _UICOMBOBOX_H
