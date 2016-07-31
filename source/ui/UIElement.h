#ifndef _UIELEMENT_H
#define _UIELEMENT_H

#include "UIEventTable.h"
#include "UITransitionTable.h"
#include "UISkinRenderable.h"
#include "../graphics/Renderable.h"
#include <vector>

#define LISTEN_PRESSED	0
#define LISTEN_RELEASED 1
#define LISTEN_HIDE		2
#define LISTEN_SHOW		3
#define LISTEN_DESTROY	4

class GameScene;
class UIManager;
class UITooltip;

class UIElement
{
public:
	typedef std::vector<UIElement*>		   ElementList;
	typedef std::map<int32_t, ElementList> Listeners;

public:
	enum eCentreAnchor
	{
		NONE	   = 0,
		BOTH	   = 1,
		HORIZONTAL = 2,
		VERTICAL   = 3,
	};

public:
	UIElement();
	UIElement(UIElement* parent, std::string id, sf::Vector2f size, std::string elementName);
	virtual ~UIElement();

	void initialise();
	void update();

	virtual void implInitialise() {};
	virtual void implUpdate()     {};

	virtual bool acceptsFocus()		   const;
	virtual bool acceptsFocusFromKbd() const;

	virtual void setPressed(bool flag);
	virtual void setEntered(bool flag);

	virtual void addChild(UIElement* child);
	virtual void removeChild(UIElement* child);

	void listen(UIElement* element, int32_t eventID);
	void ignore(UIElement* element, int32_t eventID);

	virtual void triggerListener(int32_t eventID);
	virtual void acceptListener(UIElement* element, int32_t eventID);

	const ElementList& getChildrenConst() const;
		  ElementList& getChildren();
		  UIElement*   findChildByID(std::string id);
		  UIElement*   findChildByName(std::string elementName);
		  void		   destroyChildren();
	
	UIElement* getParent()			const;
	UIElement* getNextSibling()		const;
	UIElement* getPreviousSibling() const;

	sf::Vector2f getSize()		const { return m_Size;	    }
	sf::Vector2f getMinSize()	const { return m_SizeMin;   }
	sf::Vector2f getMaxSize()	const { return m_SizeMax;   }
	float		 getMinWidth()	const { return m_SizeMin.x; }
	float		 getMaxWidth()	const { return m_SizeMax.x; }
	float		 getMinHeight()	const { return m_SizeMin.y; }
	float		 getMaxHeight()	const { return m_SizeMax.y; }
	
	virtual void setMinSize(const sf::Vector2f& size);
	virtual void setMaxSize(const sf::Vector2f& size);
	virtual void setSize(float width, float height);
	virtual void setSize(const sf::Vector2f& size);

	sf::Vector2f getPositionAbsolute() const;
	sf::Vector2f getPosition()		   const;
	sf::IntRect  getBounds()		   const;

	void parentMoved();
	void fitElements();
	void centre(eCentreAnchor anchor = eCentreAnchor::BOTH);

	void move(float x, float y);
	void move(const sf::Vector2f& point);
	
	virtual void setPosition(const sf::Vector2f& point);
	virtual void setPosition(float x, float y);

	virtual void lowerZ();
	virtual void raiseZ();

	virtual void show();
	virtual void hide();
	virtual void enable();
	virtual void disable();

	//void attachTooltip(UITooltipCtrl* tooltip);
	void attachTooltip(std::string info, std::string font = "kenvector");
	bool removeTooltip();

	/*UITooltipCtrl* getTooltip();*/
	UITooltip*  getTooltip();
	std::string getTooltipText() const;
	std::string getID()   const;
	std::string getName() const;

	void setID(std::string id);
	void setName(std::string name);

	void close();
	void destroy();

	void setCanFocus(bool flag);
	void setCanFocusFromKbd(bool flag);
	void setCanEnter(bool flag);
	void setFocus(bool flag);

	void setTooltipFollow(bool flag);
	void setTooltipOffset(const sf::Vector2f& point);

	bool canAcceptFocus()		 const;
	bool canAcceptFocusFromKbd() const;
	bool canEnter()				 const;
	bool hasFocus()				 const;
	bool canLoseFocus()			 const;

	bool isInside(float x, float y)			 const;
	bool isInside(const sf::Vector2f& point) const;

	bool isEnabled()		  const { return m_Enabled;			 }
	bool isActive()			  const { return m_Active;			 }
	bool isPressed()		  const { return m_Pressed;			 }
	bool isEntered()		  const { return m_Entered;			 }
	bool isDestroyNextFrame() const { return m_DestroyNextFrame; }

	void setParentScene(GameScene* scene)	  { m_ParentScene = scene;     }
	void setParentManager(UIManager* manager) { m_ParentManager = manager; }

	void setPositionPressed(sf::Vector2f& point)    { m_PositionPressed = point;    }
	void setPositionPressedAbs(sf::Vector2f& point) { m_PositionPressedAbs = point; }

	UISkinRenderable* getRenderable() { return m_Renderable; }

protected:
	void setParent(UIElement* parent) 
		{ m_ParentElement = parent; }

public:
	UIEventTable	  UIEventTable;
	UITransitionTable UITransitionTable;

protected:
	bool			  m_Focused;
	bool			  m_AcceptsFocus;
	bool			  m_AcceptsFocusFromKbd;
	bool			  m_AcceptsEntered;
	bool			  m_DestroyNextFrame;
	bool			  m_RenderableExists;
	bool			  m_Enabled;
	bool			  m_Active;
	bool			  m_Pressed;
	bool			  m_Entered;
	bool			  m_WaitHide;
	bool			  m_WaitDisable;
	bool			  m_WaitDestroy;
	bool			  m_TooltipFollow;
	bool			  m_CanLoseFocus;
	sf::Vector2f	  m_Position;
	sf::Vector2f	  m_PositionAbsolute;
	sf::Vector2f	  m_Size;
	sf::Vector2f	  m_SizeMin;
	sf::Vector2f	  m_SizeMax;
	sf::Vector2f	  m_TooltipOffset;
	sf::Vector2f	  m_PositionPressed;
	sf::Vector2f	  m_PositionPressedAbs;
	std::string		  m_ID;
	std::string		  m_Name;
	UISkinRenderable* m_Renderable;
	UIElement*		  m_ParentElement;
	UIManager*		  m_ParentManager;
	UITooltip*		  m_Tooltip;
	GameScene*		  m_ParentScene;
	ElementList		  m_Children;
	Listeners		  m_Listeners;
	eCentreAnchor	  m_CentreAnchor;
	
};

#endif // _UIELEMENT_H
