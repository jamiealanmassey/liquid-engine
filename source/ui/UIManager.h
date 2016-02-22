#ifndef _UIMANAGER_H
#define _UIMANAGER_H

#include "UIElement.h"
#include "../common/GameManager.h"

#include <list>

struct EventData;

class GameScene;
class UIManager
{
public:
	UIManager(GameScene* scene_ptr);
	~UIManager();

	/* Core update functions */
	void update(float delta, EventData data);
	void updateEntered(float delta, EventData data);
	void updateFocused(float delta, EventData data);

	/* Element list control functions */
	void addElement(UIElement* element);
	void addElement(std::vector<UIElement*> elements);
	void removeElement(UIElement* element);

	/* Getter Functions */
	std::vector<UIElement*> getElements() { return m_Elements; }

protected:
	std::vector<UIElement*> m_Elements;			   ///< List of elements in manager
	std::list<UIElement*>	m_EnteredElements;	   ///< List of elements entered last frame
	std::list<UIElement*>	m_EnteredElementsLast; ///< List of elements entered this frame
	UIElement*				m_FocusedElement;	   ///< Current focused element
	UIElement*				m_FocusedElementLast;  ///< Last focused element
	GameScene*				m_ParentScene;		   ///< Pointer to parent scene
};

#endif // _UIMANAGER_H
