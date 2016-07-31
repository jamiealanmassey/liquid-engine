#ifndef _UIEVENTTABLE_H
#define _UIEVENTTABLE_H

#include <functional>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>

#define MAP std::map
#define VEC std::vector
#define FNC std::function

class UIElement;
class UIEventTable
{
public:
	UIEventTable();
	~UIEventTable();

	void connectOnPressedEvent(std::function<void(UIElement*, sf::Mouse::Button)> func);
	void connectOnReleasedEvent(std::function<void(UIElement*, sf::Mouse::Button)> func);
	void connectOnEnteredEvent(std::function<void(UIElement*)> func);
	void connectOnExitedEvent(std::function<void(UIElement*)> func);
	void connectOnFocusedEvent(std::function<void(UIElement*)> func);
	void connectOnFocusedFromKbdEvent(std::function<void(UIElement*)> func);
	void connectOnHideEvent(std::function<void(UIElement*)> func);
	void connectOnShowEvent(std::function<void(UIElement*)> func);
	void connectOnEnableEvent(std::function<void(UIElement*)> func);
	void connectOnDisableEvent(std::function<void(UIElement*)> func);
	void connectOnMovedEvent(std::function<void(UIElement*, sf::Vector2f)> func);
	void connectOnResizeEvent(std::function<void(UIElement*, sf::Vector2f)> func);

	void callOnPressed(UIElement* element, sf::Mouse::Button button);
	void callOnReleased(UIElement* element, sf::Mouse::Button button);
	void callOnEntered(UIElement* element);
	void callOnExited(UIElement* element);
	void callOnFocused(UIElement* element);
	void callOnFocusedFromKbd(UIElement* element);
	void callOnHide(UIElement* element);
	void callOnShow(UIElement* element);
	void callOnEnable(UIElement* element);
	void callOnDisable(UIElement* element);
	void callOnMoved(UIElement* element, sf::Vector2f point);
	void callOnResize(UIElement* element, sf::Vector2f point);

private:
	std::vector<std::function<void(UIElement*, sf::Mouse::Button)>> eventOnPressed;
	std::vector<std::function<void(UIElement*, sf::Mouse::Button)>> eventOnReleased;
	std::vector<std::function<void(UIElement*)>>					eventOnEntered;
	std::vector<std::function<void(UIElement*)>>					eventOnExited;
	std::vector<std::function<void(UIElement*)>>					eventOnFocused;
	std::vector<std::function<void(UIElement*)>>					eventOnFocusedFromKbd;
	std::vector<std::function<void(UIElement*)>>					eventOnHide;
	std::vector<std::function<void(UIElement*)>>					eventOnShow;
	std::vector<std::function<void(UIElement*)>>					eventOnEnable;
	std::vector<std::function<void(UIElement*)>>					eventOnDisable;
	std::vector<std::function<void(UIElement*, sf::Vector2f)>>		eventOnMoved;
	std::vector<std::function<void(UIElement*, sf::Vector2f)>>		eventOnResize;
};

#endif // _UIEVENTTABLE_H
