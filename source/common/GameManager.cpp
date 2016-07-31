#include "GameManager.h"
#include "ResourceManager.h"
#include "../utilities/DeltaTime.h"

GameManager::GameManager() :
	m_PopNextStateFront(false),
	m_PopNextStateBack(false),
	m_SuspendGame(false),
	m_GameRunning(true),
	m_NextUniqueID(-1),
	f_Execute(nullptr),
	f_LoadConfig(nullptr)
{
	m_GameName = "";
	m_ConfigFile = "";
}

GameManager::~GameManager()
{
	dispose();
}

void GameManager::addGameSceneFront(GameScene* game_scene)
{
	// Push state to front of list
	game_scene->setGameManager(this);
	game_scene->init();
	m_States.push_front(game_scene);
}

void GameManager::addGameSceneFront(std::vector<GameScene*> game_scenes)
{
	// Add the vector of GameScene*
	for (auto scene : game_scenes)
		addGameSceneFront(scene);
}

void GameManager::addGameSceneBack(GameScene* game_scene)
{
	// Push state to front of list
	game_scene->setGameManager(this);
	game_scene->init();
	m_States.push_back(game_scene);
}

void GameManager::addGameSceneBack(std::vector<GameScene*> game_scenes)
{
	// Add the vector of GameScene*
	for (auto scene : game_scenes)
		addGameSceneBack(scene);
}

GameScene* GameManager::popGameSceneFront()
{
	// Update state flag and return state at front of list
	if (!m_States.empty())
	{
		m_PopNextStateFront = true;
		return m_States.front();
	}

	// Otherwise return nullptr
	return nullptr;
}

GameScene* GameManager::popGameSceneBack()
{
	// Update state flag and return state at back of list
	if (!m_States.empty())
	{
		m_PopNextStateBack = true;
		return m_States.back();
	}

	// Otherwise return nullptr
	return nullptr;
}

GameScene* GameManager::peekGameSceneFront()
{
	// As long as the states list isn't empty return the state sat at the front
	if (!m_States.empty())
		return m_States.front();

	// Otherwise return nullptr
	return nullptr;
}

GameScene* GameManager::peekGameSceneBack()
{
	// As long as the states list isn't empty return the state sat at the back
	if (!m_States.empty())
		return m_States.back();

	// Otherwise return nullptr
	return nullptr;
}

GameScene* GameManager::peekGameSceneByName(std::string name)
{
	// Iterate through all stored states and look for matching state name, if we find
	// one return it to the function
	for (auto scene : m_States)
	{
		if (scene->getStateName() == name)
			return scene;
	}

	// Otherwise a match was not found, return null
	return nullptr;
}

void GameManager::execute()
{
	// Produce the lookup tables and attempt to load the configuration
	createLookupTables();
	loadGameSettings("data/settings.xml");
	loadGameBindings("data/bindings.xml");

	// If there is a function ptr that exists for execution then call the fed 
	// in function for execution
	if (f_Execute)
		f_Execute(this);

	// Create new instance of the RenderWindow
	m_RenderWindow = new sf::RenderWindow(sf::VideoMode(m_GameSettings.screen_width, 
		m_GameSettings.screen_height), m_GameName, 
		(m_GameSettings.fullscreen ? sf::Style::Fullscreen : 
									 sf::Style::Close));

	// Setup render window settings
	m_RenderWindow->setFramerateLimit(m_GameSettings.frame_limit);
	m_RenderWindow->setVerticalSyncEnabled(m_GameSettings.vsync);

	// Start the DeltaTime clock
	DeltaTime::Instance().Start();

	// 
	ResourceManager::instance().initialise();

	// If we have an LuaInstance we want to initialise() it and make sure that
	// all relevant functions are registered
	if (m_LuaInstance)
		m_LuaInstance->initialise();
}

void GameManager::simulate()
{
	while (m_GameRunning)
	{
		// Make sure DeltaTime ticks
		DeltaTime::Instance().Tick();

		// Update title
		std::stringstream stream;
		stream << m_GameName << " - " << Delta;
		m_RenderWindow->setTitle(stream.str());

		// Poll new Event Data this tick
		pollEventData();

		// Provided that the game isn't suspended
		if (!m_SuspendGame)
		{
			// If the window lost focus stop updating the current Scene, also when
			// the window gains focus allow them again
			if (m_EventData.window_lost_focus)
			{
				m_States.front()->setAllowUpdate(false);
				m_States.front()->setAllowUpdateEvents(false);
			}
			else if (m_EventData.window_gain_focus)
			{
				m_States.front()->setAllowUpdate(true);
				m_States.front()->setAllowUpdateEvents(true);
			}
			else if (m_EventData.key_pressed && m_EventData.data_key_pressed == sf::Keyboard::Escape)
				m_GameRunning = false;

			// Render the state sitting at the front of the list
			m_States.front()->render(*m_RenderWindow);

			// Update the state sitting at the front of the list
			m_States.front()->updateEvents(m_EventData);
			m_States.front()->update(Delta);

			// If we need to pop the next front state and there are enough states to do
			// so then pop the state and reset the flag
			if (m_PopNextStateFront && m_States.size() > 1)
			{
				m_States.pop_front();
				m_PopNextStateFront = false;
			}
			else if (m_PopNextStateBack && m_States.size() > 1)
			{
				m_States.pop_back();
				m_PopNextStateBack = false;
			}
		}

		// If window close button was pressed exit game
		if (m_EventData.window_closed)
			m_GameRunning = false;

		// Once finished with the Event Data dispose of it for next tick
		flushEventData();
	}
}

void GameManager::dispose()
{
	// Iterate over each state and delete it
	for (auto state : m_States)
		delete state;

	// Clear the states
	m_States.clear();
}

void GameManager::createLookupTables()
{
	// Bind alphabet to keyboard
	m_KeyboardLookupTable["Q"] = sf::Keyboard::Q;
	m_KeyboardLookupTable["W"] = sf::Keyboard::W;
	m_KeyboardLookupTable["E"] = sf::Keyboard::E;
	m_KeyboardLookupTable["R"] = sf::Keyboard::R;
	m_KeyboardLookupTable["T"] = sf::Keyboard::T;
	m_KeyboardLookupTable["Y"] = sf::Keyboard::Y;
	m_KeyboardLookupTable["U"] = sf::Keyboard::U;
	m_KeyboardLookupTable["I"] = sf::Keyboard::I;
	m_KeyboardLookupTable["O"] = sf::Keyboard::O;
	m_KeyboardLookupTable["P"] = sf::Keyboard::P;
	m_KeyboardLookupTable["A"] = sf::Keyboard::A;
	m_KeyboardLookupTable["S"] = sf::Keyboard::S;
	m_KeyboardLookupTable["D"] = sf::Keyboard::D;
	m_KeyboardLookupTable["F"] = sf::Keyboard::F;
	m_KeyboardLookupTable["G"] = sf::Keyboard::G;
	m_KeyboardLookupTable["H"] = sf::Keyboard::H;
	m_KeyboardLookupTable["J"] = sf::Keyboard::J;
	m_KeyboardLookupTable["K"] = sf::Keyboard::K;
	m_KeyboardLookupTable["L"] = sf::Keyboard::L;
	m_KeyboardLookupTable["Z"] = sf::Keyboard::Z;
	m_KeyboardLookupTable["X"] = sf::Keyboard::X;
	m_KeyboardLookupTable["C"] = sf::Keyboard::C;
	m_KeyboardLookupTable["V"] = sf::Keyboard::V;
	m_KeyboardLookupTable["B"] = sf::Keyboard::B;
	m_KeyboardLookupTable["N"] = sf::Keyboard::N;
	m_KeyboardLookupTable["M"] = sf::Keyboard::M;

	// Bind misc controls to keyboard
	m_KeyboardLookupTable["ArrowLeft"]	= sf::Keyboard::Left;
	m_KeyboardLookupTable["ArrowRight"] = sf::Keyboard::Right;
	m_KeyboardLookupTable["ArrowUp"]	= sf::Keyboard::Up;
	m_KeyboardLookupTable["ArrowDown"]	= sf::Keyboard::Down;
	m_KeyboardLookupTable["LControl"]	= sf::Keyboard::LControl;
	m_KeyboardLookupTable["LShift"]		= sf::Keyboard::LShift;
	m_KeyboardLookupTable["Tab"]		= sf::Keyboard::Tab;
	m_KeyboardLookupTable["Enter"]		= sf::Keyboard::Return;
	m_KeyboardLookupTable["Numpad0"]	= sf::Keyboard::Numpad0;
	m_KeyboardLookupTable["Numpad1"]	= sf::Keyboard::Numpad1;
	m_KeyboardLookupTable["Numpad2"]	= sf::Keyboard::Numpad2;
	m_KeyboardLookupTable["Numpad3"]	= sf::Keyboard::Numpad3;
	m_KeyboardLookupTable["Numpad4"]	= sf::Keyboard::Numpad4;
	m_KeyboardLookupTable["Numpad5"]	= sf::Keyboard::Numpad5;
	m_KeyboardLookupTable["Numpad6"]	= sf::Keyboard::Numpad6;
	m_KeyboardLookupTable["Numpad7"]	= sf::Keyboard::Numpad7;
	m_KeyboardLookupTable["Numpad8"]	= sf::Keyboard::Numpad8;
	m_KeyboardLookupTable["Numpad9"]	= sf::Keyboard::Numpad9;
	m_KeyboardLookupTable["Spacebar"]   = sf::Keyboard::Space;

	// Bind numbers to keyboard
	m_KeyboardLookupTable["Num0"] = sf::Keyboard::Num0;
	m_KeyboardLookupTable["Num1"] = sf::Keyboard::Num1;
	m_KeyboardLookupTable["Num2"] = sf::Keyboard::Num2;
	m_KeyboardLookupTable["Num3"] = sf::Keyboard::Num3;
	m_KeyboardLookupTable["Num4"] = sf::Keyboard::Num4;
	m_KeyboardLookupTable["Num5"] = sf::Keyboard::Num5;
	m_KeyboardLookupTable["Num6"] = sf::Keyboard::Num6;
	m_KeyboardLookupTable["Num7"] = sf::Keyboard::Num7;
	m_KeyboardLookupTable["Num8"] = sf::Keyboard::Num8;
	m_KeyboardLookupTable["Num9"] = sf::Keyboard::Num9;

	// Bind gamepad buttons
	m_GamepadLookupTable["A"]	  = (uint32_t)eGamepadButton::A;
	m_GamepadLookupTable["X"]	  = (uint32_t)eGamepadButton::X;
	m_GamepadLookupTable["B"]	  = (uint32_t)eGamepadButton::B;
	m_GamepadLookupTable["Y"]	  = (uint32_t)eGamepadButton::Y;
	m_GamepadLookupTable["Start"] = (uint32_t)eGamepadButton::Start;
	m_GamepadLookupTable["Back"]  = (uint32_t)eGamepadButton::Back;
	m_GamepadLookupTable["LB"]	  = (uint32_t)eGamepadButton::LB;
	m_GamepadLookupTable["RB"]	  = (uint32_t)eGamepadButton::RB;

	// Bind mouse buttons
	m_MouseLookupTable["MouseLeft"]   = sf::Mouse::Left;
	m_MouseLookupTable["MouseRight"]  = sf::Mouse::Right;
	m_MouseLookupTable["MouseMiddle"] = sf::Mouse::Middle;
}

void GameManager::loadGameSettings(std::string xml_file)
{
	// Open new XML document
	pugi::xml_document settings;
	if (!settings.load_file(xml_file.c_str()))
		return;

	// Find root settings node and create iterator for it
	pugi::xml_node			settings_nd = settings.child("Settings");
	pugi::xml_node_iterator settings_it = settings_nd.begin();

	// Iterate over each setting searching for specific values to store in our
	// data structure
	for (; settings_it != settings_nd.end(); ++settings_it)
	{
		std::string id = settings_it->attribute("ID").as_string();

		if (id == "custom_assets")
			m_GameSettings.custom_assets_folder = settings_it->attribute("Value").as_string();
		else if(id == "screen_width")
			m_GameSettings.screen_width = settings_it->attribute("Value").as_int();
		else if (id == "screen_height")
			m_GameSettings.screen_height = settings_it->attribute("Value").as_int();
		else if (id == "fullscreen")
			m_GameSettings.fullscreen = settings_it->attribute("Value").as_bool();
		else if (id == "vsync")
			m_GameSettings.vsync = settings_it->attribute("Value").as_bool();
		else if (id == "particles_enabled")
			m_GameSettings.particles_enabled = settings_it->attribute("Value").as_bool();
		else if (id == "tutorial_enabled")
			m_GameSettings.tutorial_enabled = settings_it->attribute("Value").as_bool();
		else if (id == "scale_gui")
			m_GameSettings.scale_gui = settings_it->attribute("Value").as_float();
		else if (id == "frame_limit")
			m_GameSettings.frame_limit = settings_it->attribute("Value").as_float();
		else if (id == "volume_master")
			m_GameSettings.volume_master = settings_it->attribute("Value").as_float();
		else if (id == "volume_music")
			m_GameSettings.volume_music = settings_it->attribute("Value").as_float();
		else if (id == "volume_sfx")
			m_GameSettings.volume_sfx = settings_it->attribute("Value").as_float();
		else if (id == "volume_dialogue")
			m_GameSettings.volume_dialogue = settings_it->attribute("Value").as_float();
	}
}

void GameManager::loadGameBindings(std::string xml_file)
{
	// Open new XML document
	pugi::xml_document bindings;
	if (!bindings.load_file(xml_file.c_str()))
		return;

	// Locate relevant nodes and store them
	pugi::xml_node bindings_nd = bindings.child("Bindings");
	pugi::xml_node keyboard_nd = bindings_nd.child("Keyboard");
	pugi::xml_node gamepad_nd  = bindings_nd.child("Gamepad");

	// Create node iterators to search data
	pugi::xml_node_iterator keyboard_it = keyboard_nd.begin();
	pugi::xml_node_iterator gamepad_it  = gamepad_nd.begin();

	// Iterate over each keyboard entry retrieving the ID and key so that we can
	// store the data apporpriately
	for (; keyboard_it != keyboard_nd.end(); ++keyboard_it)
	{
		std::string	id  = keyboard_it->attribute("ID").as_string();
		std::string key = keyboard_it->attribute("Value").as_string();

		m_GameBindings.m_KeyboardBinds[id] = m_KeyboardLookupTable[key];
	}

	// Iterate over each gamepad entry retrieving the ID and key so that we can
	// store the data apporpriately
	for (; gamepad_it != gamepad_nd.end(); ++gamepad_it)
	{
		std::string id = gamepad_it->attribute("ID").as_string();
		std::string key = gamepad_it->attribute("Value").as_string();

		m_GameBindings.m_GamepadBinds[id] = m_GamepadLookupTable[key];
	}
}

sf::Keyboard::Key GameManager::getKeyboardBind(std::string name)
{
	// Make sure the binding first exists and if it does return it from the stored
	// bindings data structure
	if (m_GameBindings.m_KeyboardBinds.find(name) != m_GameBindings.m_KeyboardBinds.end())
		return m_GameBindings.m_KeyboardBinds[name];

	// Otherwise return an unknown key
	return sf::Keyboard::Key::Unknown;
}

GameManager::eGamepadButton GameManager::getGamepadBind(std::string name)
{
	// Make sure the binding first exists and if it does return it from the stored
	// bindings data structure
	if (m_GameBindings.m_GamepadBinds.find(name) != m_GameBindings.m_GamepadBinds.end())
		return (eGamepadButton)m_GameBindings.m_GamepadBinds[name];

	// Otherwise return an unknown button
	return (eGamepadButton)-1;
}

void GameManager::pollEventData()
{
	// Sample mouse position
	m_EventData.data_mouse_pos =
		sf::Vector2f(sf::Mouse::getPosition(*m_RenderWindow));
	
	// Poll for events
	while (m_RenderWindow->pollEvent(m_EventPoll))
	{
		if (m_EventPoll.type == sf::Event::KeyPressed)
		{
			m_EventData.key_pressed		 = true;
			m_EventData.data_key_pressed = m_EventPoll.key.code;
		}
		else if (m_EventPoll.type == sf::Event::KeyReleased)
		{
			m_EventData.key_released	  = true;
			m_EventData.data_key_released = m_EventPoll.key.code;
		}
		else if (m_EventPoll.type == sf::Event::MouseButtonPressed)
		{
			m_EventData.mouse_button_pressed = true;
			m_EventData.data_mouse_pressed   = m_EventPoll.mouseButton.button;
			// TODO: GET MOUSE POS
		}
		else if (m_EventPoll.type == sf::Event::MouseButtonReleased)
		{
			m_EventData.mouse_button_released = true;
			m_EventData.data_mouse_released   = m_EventPoll.mouseButton.button;
			// TODO: GET MOUSE POS
		}
		else if (m_EventPoll.type == sf::Event::JoystickButtonPressed)
		{
			m_EventData.joystick_button_pressed = true;
			m_EventData.data_joystick_pressed   = m_EventPoll.joystickButton.button;
		}
		else if (m_EventPoll.type == sf::Event::LostFocus)
			m_EventData.window_lost_focus = true;
		else if (m_EventPoll.type == sf::Event::GainedFocus)
			m_EventData.window_gain_focus = true;
		else if (m_EventPoll.type == sf::Event::Closed)
			m_EventData.window_closed = true;
		else if (m_EventPoll.type == sf::Event::MouseMoved)
			m_EventData.mouse_moved = true;
	}
}

void GameManager::flushEventData()
{
	// Reset all event data to factory states
	m_EventData.key_pressed				= false;
	m_EventData.key_released			= false;
	m_EventData.mouse_button_pressed	= false;
	m_EventData.mouse_button_released	= false;
	m_EventData.joystick_button_pressed = false;
	m_EventData.window_lost_focus		= false;
	m_EventData.window_gain_focus		= false;
	m_EventData.window_closed			= false;
}

int32_t GameManager::getNextUniqueID()
{
	// Increment unique ID and return it
	m_NextUniqueID++;
	return m_NextUniqueID;
}

GameManager& GameManager::instance()
{
	static GameManager singleton;
	return singleton;
}
