#ifndef _UIWINDOW_H
#define _UIWINDOW_H

#include "../UIElement.h"
#include "../simple/UIButton.h"
#include "../simple/UIStaticLabel.h"

#define WINDOW_FLAG_NO_TITLE	0x01
#define WINDOW_FLAG_TITLE		0x02
#define WINDOW_FLAG_CLOSE		0x04
#define WINDOW_FLAG_COLLAPSABLE 0x08
#define WINDOW_FLAG_RESIZE		0x10

struct WindowHeader
{
	UIStaticLabel* title;
	UIButton*	   close_button;
	UIElement*	   top_left;
	UIElement*     top_right;
	UIElement*     btm_left;
	UIElement*     btm_right;
	UIElement*     top_middle;
	UIElement*     btm_middle;
	UIElement*     left;
	UIElement*     right;
	UIElement*     content;
};

struct Window
{
	UIElement* top_left;
	UIElement* top_right;
	UIElement* btm_left;
	UIElement* btm_right;
	UIElement* top_middle;
	UIElement* btm_middle;
	UIElement* left;
	UIElement* right;
	UIElement* container;
};

class UIWindow : public UIElement
{
public:
	UIWindow(UIElement* parent, std::string id, sf::Vector2f size, std::string elementName, uint8_t windowFlags);
	~UIWindow();

	virtual void implInitialise() override;
	virtual void implUpdate()     override;

	virtual void setSize(float x, float y)			override;
	virtual void setSize(const sf::Vector2f& point) override;

	virtual void addChild(UIElement* child)    override;
	virtual void removeChild(UIElement* child) override;

	void setTitlebarText(std::string title);
	void setTitlebarColour(sf::Color colour);
	void setWindowColour(sf::Color colour);

	sf::Color getTitlebarColour() { return m_WindowHeader.top_left->getRenderable()->getColor(); }
	sf::Color getWindowColour()   { return m_Window.top_left->getRenderable()->getColor();		 }

protected:
	void releasedCallback(UIElement* element, sf::Mouse::Button button);
	void pressedCallback(UIElement* element, sf::Mouse::Button button);
	void movedCallback(UIElement* element, sf::Vector2f mouse_pos);
	void renderCallback(Renderable* renderable, sf::RenderTarget& target);
	void closeBtnReleasedCallback(UIElement* element, sf::Mouse::Button);

protected:
	void constructComparatives();
	void constructTitlebar();
	void constructWindow();
	void reconfigureTitlebar();
	void reconfigureWindow();
	void toggleElements();

protected:
	std::vector<UIElement*> m_TrackedElements;
	std::string				m_ComparativeIDs[20];
	WindowHeader			m_WindowHeader;
	Window					m_Window;
	uint8_t					m_WindowFlags;
	float					m_RootPosition;
	bool					m_AllowMovement;
	bool					m_AllowResize;
};

#endif // _UIWINDOW_H
