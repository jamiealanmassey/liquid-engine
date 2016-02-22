#ifndef _ENTITY_H
#define _ENTITY_H

#include "../graphics/Renderable.h"

#include <Box2D/Box2D.h>
#include <vector>
#include <string>
#include <functional>

#define ENTITY_TYPE_UNKNOWN 0x0000

class GameScene;
class Entity
{
public:
	enum eEntityState
	{
		ENTITYSTATE_ALIVE = 0,
		ENTITYSTATE_SLEEP = 1,
		ENTITYSTATE_DEAD  = 2,
	};

	struct TweenData
	{
		TweenData(float t)
		{
			timer	 = t;
			elapsed  = 0.0f;
			finished = false;
			func_ptr = nullptr;
		}

		float					   timer;
		float					   elapsed;
		bool					   finished;
		std::function<void(float)> func_ptr;
	};

public:
	Entity(sf::Vector2f position, std::string uid = "");
	~Entity();

	/* Core entity functions */
	void update(float delta);
	void updatePost(float delta);
	void updateTween(float delta);

	/* Inheritence implemented update */
	virtual void implInitialise() {}
	virtual void implUpdate()	  {}
	virtual void implUpdatePost() {}
	virtual void implKill()		  {}

	/* Attachment controls */
	void attachRenderable(Renderable* renderable, bool centre = true);
	void attachTweener(TweenData data);

	/* Positioning functions */
	void setPosition(sf::Vector2f pos);
	void setPosition(float x, float y);
	void addPosition(sf::Vector2f pos);
	void addPosition(float x, float y);

	/* Setter functions */
	void setGameScene(GameScene* scene) { m_ParentScene = scene; }

	/* Child/Parent functions */
	void setParent(Entity* parent);
	void addChild(Entity* child);
	void removeChild(Entity* child);

	/* Box2D Control Functions */
	void constructBox2D(b2BodyDef definition);
	void constructBox2DFixture(b2FixtureDef fixture);
	void destroyBox2D();

	/* Checker func */
	bool isPointInside(const sf::Vector2f& v, bool use_initial = false);

	/* Entity State control functions */
	void sleep() { m_EntityState = eEntityState::ENTITYSTATE_SLEEP; }
	void wake()  { m_EntityState = eEntityState::ENTITYSTATE_ALIVE; }
	void kill()  { m_EntityState = eEntityState::ENTITYSTATE_DEAD;  }

	/* Setter Functions */
	void setEntityType(int32_t type)  { m_EntityType = type; }
	void setEntityID(std::string uid) { m_UID = uid;		 }

	/* Function helpers to check what components exist */
	bool checkMoved()	   { return m_Moved;			   }
	bool checkRenderable() { return m_RenderableExists;	   }
	bool checkPhysics()	   { return m_Physics;			   }
	bool checkParent()	   { return (m_Parent != nullptr); }

	/* Function getters */
	int32_t				    getEntityType()  { return m_EntityType;   }
	GameScene*			    getParentScene() { return m_ParentScene;  }
	Renderable*			    getRenderable()  { return m_Renderable;   }
	eEntityState		    getEntityState() { return m_EntityState;  }
	sf::Vector2f		    getPosition()	 { return m_Position;	  }
	std::string			    getUID()		 { return m_UID;		  }
	Entity*				    getParent()		 { return m_Parent;		  }
	std::vector<Entity*>&   getChildren()	 { return m_Children;     }
	std::vector<TweenData>& getTweeners()	 { return m_Tweening;	  }
	b2Body*					getBox2DBody()	 { return m_Box2DBody;	  }
	b2BodyDef				getBox2DDef()	 { return m_Box2DBodyDef; }

public:
	std::function<void(Entity*, float, float)> f_SetPosition; ///< Function callback for when position is set
	std::function<void(Entity*, float, float)> f_AddPosition; ///< Function callback for when position is added to
	std::function<void(Entity*, float		)> f_Update;	  ///< Function callback which is called every tick
	std::function<void(Entity*, float		)> f_UpdatePost;  ///< Fun ction callback that is called each tick after update()
	std::function<void(Entity*				)> f_Killed;	  ///< Function callback for when Entity is destroyed
	
public:
	std::function<void(sf::Keyboard::Key)>				 f_OnKeyPressed;    ///< Function callback for when key is pressed
	std::function<void(sf::Keyboard::Key)>				 f_OnKeyReleased;   ///< Function callback for when key is released
	std::function<void(sf::Vector2f, sf::Mouse::Button)> f_OnMousePressed;  ///< Function callback for when mouse is pressed
	std::function<void(sf::Vector2f, sf::Mouse::Button)> f_OnMouseReleased; ///< Function callback for when mouse is relased

public:
	std::function<void(Entity*, b2Contact*)> f_OnCollisionBegin;	 ///< Function callback for when collision occurs
	std::function<void(Entity*, b2Contact*)> f_OnCollisionEnd;		 ///< Function callback for when collision ends
	std::function<void(b2Contact*)>			 f_OnBodyCollisionBegin; ///< Function callback for beginning of body collision
	std::function<void(b2Contact*)>			 f_OnBodyCollisionEnd;   ///< Function callback for end of body collision

protected:
	bool				   m_Moved;			   ///< Flag to denote if the Entity has moved this frame
	bool				   m_RenderableExists; ///< Flag to denote if a renderable is attatched
	bool				   m_Physics;		   ///< Flag to denote if the Entity has a physics component
	int32_t				   m_EntityType;	   ///< Type of the Entity stored as a 32-bit int flag
	GameScene*			   m_ParentScene;	   ///< Pointer to the Scene that the Entity exists in
	Renderable*			   m_Renderable;	   ///< Pointer to the renderable component
	eEntityState		   m_EntityState;	   ///< Stores the state of the Entity
	sf::Vector2f		   m_Position;		   ///< Current position of the Entity in world space
	std::string			   m_UID;			   ///< Idenitifer for the Entity
	Entity*				   m_Parent;		   ///< Parent of the Entity if it has one
	std::vector<Entity*>   m_Children;		   ///< List of children that have this Entity as a parent
	std::vector<TweenData> m_Tweening;		   ///< List of active tweens affecting this Entity
	b2Body*				   m_Box2DBody;		   ///< Box2D body for collision
	b2BodyDef			   m_Box2DBodyDef;	   ///< Box2D body definition
};

#endif // _ENTITY_H
