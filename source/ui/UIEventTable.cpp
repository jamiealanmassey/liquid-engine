#include "UIEventTable.h"

UIEventTable::UIEventTable()
{
}

UIEventTable::~UIEventTable()
{
}

void UIEventTable::connectOnPressedEvent(std::function<void(UIElement*, sf::Mouse::Button)> func)
{
	eventOnPressed.push_back(func);
}

void UIEventTable::connectOnReleasedEvent(std::function<void(UIElement*, sf::Mouse::Button)> func)
{
	eventOnReleased.push_back(func);
}

void UIEventTable::connectOnEnteredEvent(std::function<void(UIElement*)> func)
{
	eventOnEntered.push_back(func);
}

void UIEventTable::connectOnExitedEvent(std::function<void(UIElement*)> func)
{
	eventOnExited.push_back(func);
}

void UIEventTable::connectOnFocusedEvent(std::function<void(UIElement*)> func)
{
	eventOnFocused.push_back(func);
}

void UIEventTable::connectOnFocusedFromKbdEvent(std::function<void(UIElement*)> func)
{
	eventOnFocusedFromKbd.push_back(func);
}

void UIEventTable::connectOnHideEvent(std::function<void(UIElement*)> func)
{
	eventOnHide.push_back(func);
}

void UIEventTable::connectOnShowEvent(std::function<void(UIElement*)> func)
{
	eventOnShow.push_back(func);
}

void UIEventTable::connectOnEnableEvent(std::function<void(UIElement*)> func)
{
	eventOnEnable.push_back(func);
}

void UIEventTable::connectOnDisableEvent(std::function<void(UIElement*)> func)
{
	eventOnDisable.push_back(func);
}

void UIEventTable::connectOnMovedEvent(std::function<void(UIElement*, sf::Vector2f)> func)
{
	eventOnMoved.push_back(func);
}

void UIEventTable::connectOnResizeEvent(std::function<void(UIElement*, sf::Vector2f)> func)
{
	eventOnResize.push_back(func);
}

void UIEventTable::callOnPressed(UIElement * element, sf::Mouse::Button button)
{
	if (!eventOnPressed.empty())
	{
		for (auto func : eventOnPressed)
			func(element, button);
	}
}

void UIEventTable::callOnReleased(UIElement * element, sf::Mouse::Button button)
{
	if (!eventOnReleased.empty())
	{
		for (auto func : eventOnReleased)
			func(element, button);
	}
}

void UIEventTable::callOnEntered(UIElement * element)
{
	if (!eventOnEntered.empty())
	{
		for (auto func : eventOnEntered)
			func(element);
	}
}

void UIEventTable::callOnExited(UIElement * element)
{
	if (!eventOnExited.empty())
	{
		for (auto func : eventOnExited)
			func(element);
	}
}

void UIEventTable::callOnFocused(UIElement * element)
{
	if (!eventOnFocused.empty())
	{
		for (auto func : eventOnFocused)
			func(element);
	}
}

void UIEventTable::callOnFocusedFromKbd(UIElement * element)
{
	if (!eventOnFocusedFromKbd.empty())
	{
		for (auto func : eventOnFocusedFromKbd)
			func(element);
	}
}

void UIEventTable::callOnHide(UIElement * element)
{
	if (!eventOnHide.empty())
	{
		for (auto func : eventOnHide)
			func(element);
	}
}

void UIEventTable::callOnShow(UIElement * element)
{
	if (!eventOnShow.empty())
	{
		for (auto func : eventOnShow)
			func(element);
	}
}

void UIEventTable::callOnEnable(UIElement * element)
{
	if (!eventOnEnable.empty())
	{
		for (auto func : eventOnEnable)
			func(element);
	}
}

void UIEventTable::callOnDisable(UIElement * element)
{
	if (!eventOnDisable.empty())
	{
		for (auto func : eventOnDisable)
			func(element);
	}
}

void UIEventTable::callOnMoved(UIElement * element, sf::Vector2f point)
{
	if (!eventOnMoved.empty())
	{
		for (auto func : eventOnMoved)
			func(element, point);
	}
}

void UIEventTable::callOnResize(UIElement * element, sf::Vector2f point)
{
	if (!eventOnResize.empty())
	{
		for (auto func : eventOnResize)
			func(element, point);
	}
}
