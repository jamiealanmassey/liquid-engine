#ifndef _UIELEMENT_H
#define _UIELEMENT_H

#include "UITransitionState.h"
#include "../graphics/Renderable.h"

class GameScene;
class UIElement
{
public:
	enum eAnchor
	{
		ANCHOR_NONE   = 0,
		ANCHOR_LEFT	  = 1,
		ANCHOR_MIDDLE = 2,
		ANCHOR_RIGHT  = 3,
		ANCHOR_TOP	  = 4,
		ANCHOR_BOTTOM = 5,
		ANCHOR_CENTRE = 6,
	};

public:
	UIElement(sf::Vector2f position, std::string id = "");
	~UIElement();

	/* Core UIElement Functions */
	virtual void init()				 {								}
	virtual void update(float delta) { m_TransitionState->update(); }
	
	/* Positioning Functions */
	void setPosition(sf::Vector2f position);
	void setPosition(float x, float y);
	void setPositionRelative(sf::Vector2f position);
	void setPositionRelative(float x, float y);

	/* Misc Functions */
	void alignElement();
	void attachRenderable(Renderable* renderable);

	/* Child control functions */
	void addChild(UIElement* child);
	void addChild(std::vector<UIElement*> children);
	void removeChild(UIElement* child);

	void destroy() { m_DestroyNextFrame = true; }

	/* Overridable actions for when an event occurs */
	virtual void onPressed(sf::Mouse::Button button)  {}
	virtual void onReleased(sf::Mouse::Button button) {}
	virtual void onEnter()							  {}
	virtual void onExit()							  {}
	virtual void onFocus()							  {}
	virtual void onDefocus()						  {}

	/* Setter Functions */
	void setEntered(bool flag)		    { m_Entered = flag;			 }
	void setFocused(bool flag)		    { m_Focused = flag;			 }
	void setPressed(bool flag)			{ m_Pressed = flag;			 }
	void setAllowInteraction(bool flag) { m_AllowInteraction = flag; }
	void setAnchor(eAnchor anchor)		{ m_Anchor = anchor;		 }
	void setParent(UIElement* element)  { m_Parent = element;		 }
	void setGameScene(GameScene* scene) { m_ParentScene = scene;	 }

	/* Checking Functions */
	bool checkEntered()			 const { return m_Entered;		    }
	bool checkFocused()			 const { return m_Focused;		    }
	bool checkPressed()			 const { return m_Pressed;		    }
	bool checkAllowInteraction() const { return m_AllowInteraction; }
	bool checkRenderable()		 const { return m_RenderableExists; }
	bool checkToDestroy()	     const { return m_DestroyNextFrame; }

	/* Getter Functions */
	sf::Vector2f			getPosition()		  const { return m_Position;		 }
	sf::Vector2f			getPositionRelative() const { return m_PositionRelative; }
	eAnchor					getAnchor()			  const { return m_Anchor;			 }
	Renderable*				getRenderable()				{ return m_Renderable;		 }
	GameScene*				getParentScene()			{ return m_ParentScene;		 }
	UIElement*				getParent()					{ return m_Parent;			 }
	std::vector<UIElement*> getChildren()				{ return m_Children;		 }

public:
	std::function<void(UIElement*, sf::Mouse::Button)> f_OnPressed;  ///< Function callback for when mouse button is pressed
	std::function<void(UIElement*, sf::Mouse::Button)> f_OnReleased; ///< Function callback for when mouse button is released
	std::function<void(UIElement*)>					   f_OnEntered;  ///< Function callback for when cursor enters element
	std::function<void(UIElement*)>					   f_OnExit;	 ///< Function callback for when cursor leaves element
	std::function<void(UIElement*)>					   f_OnFocus;	 ///< Function callback for when element is focused
	std::function<void(UIElement*)>					   f_OnDefocus;  ///< Function callback for when element is defocused

protected:
	bool					m_Entered;			///< Flag to denote whether element has been entered
	bool					m_Focused;			///< Flag to denote whether element has been focused
	bool					m_Pressed;			///< Flag to denote if button is being pressed
	bool					m_AllowInteraction; ///< Flag for allowing interaction
	bool					m_RenderableExists; ///< Flag to denote if renderable exists
	bool					m_DestroyNextFrame; ///< Flag stating whether to destroy element
	sf::Vector2f			m_Position;			///< Stored position of element
	sf::Vector2f			m_PositionRelative; ///< Relative position of element to parent
	eAnchor					m_Anchor;			///< Anchor enumerator for positioning element in parent
	Renderable*				m_Renderable;		///< Renderable component to element
	GameScene*				m_ParentScene;		///< Pointer to parent scene
	UIElement*				m_Parent;			///< Parent of element
	UITransitionState*		m_TransitionState;	///< Transition state of the element
	std::vector<UIElement*> m_Children;			///< List of children to this element
	std::string				m_UID;				///< Unique identifier for element
};

#endif // _UIELEMENT_H
 