// AUTHOR: Jamie Massey
// FILENAME: GameManager
//
// PURPOSE: Wraps and drives the GameState classes on a list/stack style container
//		    to run the game
//

#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H

#include "GameScene.h"
#include "../ui/UIManager.h"

#include <PugiXML/pugixml.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <list>
#include <vector>
#include <map>
#include <functional>
#include <sstream>

struct EventData
{
	bool key_pressed;
	bool key_released;
	bool mouse_button_pressed;
	bool mouse_button_released;
	bool joystick_button_pressed;
	bool window_lost_focus;
	bool window_gain_focus;
	bool window_closed;

	sf::Keyboard::Key data_key_pressed;
	sf::Keyboard::Key data_key_released;
	sf::Mouse::Button data_mouse_pressed;
	sf::Mouse::Button data_mouse_released;
	sf::Vector2f	  data_mouse_pressed_pos;
	sf::Vector2f	  data_mouse_released_pos;
	sf::Vector2f	  data_mouse_pos;
	uint32_t		  data_joystick_pressed;
};

struct GameSettings
{
	std::string custom_assets_folder;
	int32_t		screen_width;
	int32_t		screen_height;
	bool		fullscreen;
	bool		vsync;
	bool		particles_enabled;
	bool		tutorial_enabled;
	float		scale_gui;
	float		frame_limit;
	float		volume_master;
	float		volume_music;
	float		volume_sfx;
	float		volume_dialogue;
};

struct GameBindings
{
	std::map<std::string, sf::Keyboard::Key> m_KeyboardBinds;
	std::map<std::string, uint32_t>			 m_GamepadBinds;
};

class GameManager
{
public:
	enum eGamepadButton
	{
		A	  = 0,
		X	  = 2,
		B	  = 1,
		Y	  = 3,
		Start = 7,
		Back  = 6,
		LB	  = 4,
		RB	  = 5,
	};

public:
	GameManager(std::string game_name, std::string config_file);
	~GameManager();

	/* Functions to add states into the list */
	void addGameSceneFront(GameScene* state);
	void addGameSceneFront(std::vector<GameScene*> states);
	void addGameSceneBack(GameScene* state);
	void addGameSceneBack(std::vector<GameScene*> states);

	/* Functions to pop states from the list */
	GameScene* popGameSceneFront();
	GameScene* popGameSceneBack();

	/* Functions to peek the back and front states */
	GameScene* peekGameSceneFront();
	GameScene* peekGameSceneBack();
	GameScene* peekGameSceneByName(std::string name);

	/* Functions for core running of the game */
	void execute();
	void simulate();
	void dispose();

	/* Configuration and pre-game functions */
	void createLookupTables();
	void loadGameSettings(std::string xml_file);
	void loadGameBindings(std::string xml_file);

	sf::Keyboard::Key getKeyboardBind(std::string name);
	eGamepadButton	  getGamepadBind(std::string name);
	
	/* Misc functions */
	void	pollEventData();
	void	flushEventData();
	int32_t getNextUniqueID();

	/* Game control functions */
	void pause()  { m_SuspendGame = true;  }
	void resume() { m_SuspendGame = false; }

	/* Getter functions */
	sf::RenderWindow* getRenderWindow()		  { return m_RenderWindow; }
	EventData		  getEventData()	const { return m_EventData;    }
	GameSettings	  getGameSettings() const { return m_GameSettings; }
	GameBindings	  getGameBindings() const { return m_GameBindings; }

public:
	std::function<void(GameManager*)> f_Execute;    ///< Stores a function ptr to be called on execution
	std::function<void(GameManager*)> f_LoadConfig; ///< Stores a function ptr to be called when config is loaded

protected:
	std::list<GameScene*> m_States;     ///< List of all existing states in the game
	std::string			  m_GameName;   ///< String that stores the name of the game
	std::string			  m_ConfigFile; ///< Location of the game configuration file

protected:
	std::map<std::string, sf::Keyboard::Key> m_KeyboardLookupTable; ///< Lookup table for keyboard binds
	std::map<std::string, uint32_t>			 m_GamepadLookupTable;  ///< Lookup table for gamepad binds
	std::map<std::string, uint32_t>			 m_MouseLookupTable;	///< Lookup table for mouse binds

protected:
	sf::RenderWindow* m_RenderWindow; ///< Pointer to window which we will draw everything to
	sf::Event		  m_EventPoll;	  ///< SFML specific class to poll events
	EventData		  m_EventData;	  ///< Stores event flags and data for each frame
	GameSettings	  m_GameSettings; ///< Stores data structure defining settings
	GameBindings	  m_GameBindings; ///< Tables of input bindings

private:
	bool	m_PopNextStateFront; ///< Flag to denote whether to pop the front state next tick
	bool	m_PopNextStateBack;  ///< Flag to denote whether to pop the back state next tick
	bool	m_SuspendGame;		 ///< Flag to denote whether the game is in a state of suspension
	bool	m_GameRunning;		 ///< Flag to denote whether the game is being simulated
	int32_t m_NextUniqueID;		 ///< Counter for giving unique identifiers
};

#endif // _GAMEMANAGER_H
