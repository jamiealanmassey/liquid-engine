#ifndef _UIMANAGER_H
#define _UIMANAGER_H

#include <vector>
#include<list>

#include "UIElement.h"
#include "../common/GameManager.h"

struct EventData;
class GameScene;

class UIManager
{
public:
	UIManager(GameScene* scene, std::string skin, std::string skin_data);
	~UIManager();

	void update(EventData data);
	void updateEntered(EventData data);
	void updateDestroyed();

	void addElement(UIElement* element);
	void addElement(std::vector<UIElement*> elements);

	void removeElement(UIElement* element);
	void removeElement(std::string id);

	void buttonPressedCheck(UIElement* element, sf::Mouse::Button button);

	UIElement* findNextInside(UIElement* element, const sf::Vector2f& point);
	UIElement* findNextParent(UIElement* element, const sf::Vector2f& point);

	std::vector<UIElement*> getElements()		{ return m_Elements;	   }
	std::string				getSkin()			{ return m_Skin;		   }
	std::string				getSkinData()		{ return m_SkinData;	   }
	UIElement*				getFocusedElement() { return m_FocusedElement; }
	UIElement*				getEnteredElement() { return m_EnteredElement; }
	GameScene*				getParentScene()	{ return m_ParentScene;	   }

protected:
	std::vector<UIElement*> m_Elements;
	std::string				m_Skin;
	std::string				m_SkinData;
	UIElement*				m_FocusedElement;
	UIElement*				m_EnteredElement;
	GameScene*				m_ParentScene;
};

#endif // _UIMANAGER_H
