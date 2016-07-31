// AUTHOR: Jamie Massey
// FILENAME: GameScene
//
// PURPOSE: Stores and controls a Scene holding flags for whether it should be running
//			and drawing to the screen or updating with various controls
//

#ifndef _GAMESCENE_H
#define _GAMESCENE_H

#include "LuaInstance.h"
#include "Entity.h"
#include "ContactManager.h"
#include "../graphics/Renderer.h"
#include "../ui/UIManager.h"

struct EventData;
class GameManager;
class UIManager;

class GameScene
{
public:
	GameScene(LuaInstance* lua_instance, std::string state_name = "");
	~GameScene();

	/* Helper functions for the state */
	void init();
	void updateEvents(EventData event_data);
	void update(float delta);
	void render(sf::RenderTarget& target);

	/* Override Functions for updates and init */
	virtual void implInitialise()				 {}
	virtual void implUpdate() {}

	/* Helper functions for adding Entities to the Scene */
	void addEntity(Entity* entity);
	void addEntity(std::vector<Entity*> entities);

	/* Functions to get entity by point */
	Entity* getEntityAtPoint(sf::Vector2f point);
	Entity* getEntityAtPointWithUID(sf::Vector2f point, std::string uid);
	Entity* getEntityClosestToPoint(sf::Vector2f point);
	Entity* getEntityClosestToPointWithUID(sf::Vector2f point, std::string uid);
	
	/* Entity getter functions */
	Entity*				 getEntityWithUID(std::string uid);
	std::vector<Entity*> getAllEntities();

	/* GameManager setter */
	void setGameManager(GameManager* game_mgr_ptr) { m_GameManager = game_mgr_ptr; }

	/* Flag control functions */
	void setAllowUpdate(bool flag)		  { m_AllowUpdate = flag;		 }
	void setAllowUpdateEvents(bool flag)  { m_AllowUpdateEvents = flag;	 }
	void setAllowRender(bool flag)		  { m_AllowRender = flag;		 }
	void setAllowPostProcesses(bool flag) { m_AllowPostProcesses = flag; }

	/* Helper check functions */
	bool checkAllowUpdate()		   { return m_AllowUpdate;		  }
	bool checkAllowUpdateEvents()  { return m_AllowUpdateEvents;  }
	bool checkAllowRender()		   { return m_AllowRender;		  }
	bool checkAllowPostProcesses() { return m_AllowPostProcesses; }

	/* Getter functions */
	GameManager* getGameManager() { return m_GameManager; }
	Renderer*    getRenderer()	  { return m_Renderer;    }
	UIManager*   getUIManager()	  { return m_UIManager;   }
	b2World*	 getBox2DWorld()  { return m_Box2DWorld;  }
	std::string  getStateName()	  { return m_StateName;   }

protected:
	GameManager*	 m_GameManager;		///< Pointer to LiquidEntry
	Renderer*		 m_Renderer;		///< Renderer for drawing to the screen
	UIManager*		 m_UIManager;		///< Manager for user interface
	ContactListener* m_ContactListener; ///< Contact listener for collisions
	b2World*		 m_Box2DWorld;		///< World for Box2D

protected:
	std::vector<Entity*> m_Entities;     ///< List of entities that exist in the world
	std::vector<Entity*> m_EntityBuffer; ///< Buffer for adding entities
	std::string			 m_StateName;	 ///< String identifier representing state

private:
	bool m_AllowUpdate;		   ///< Flag that denotes whether we should update the Scene
	bool m_AllowUpdateEvents;  ///< Flag that denotes whether we should update the input of the Scene
	bool m_AllowRender;		   ///< Flag that denotes whether we should render the Scene
	bool m_AllowPostProcesses; ///< Flag that denotes whether we should render the post processes of the Scene
};

#endif // _GAMESCENE_H
