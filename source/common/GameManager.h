#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <time.h>
#include <cstdlib>
#include "GameScene.h"
#include "../data/Bindings.h"
#include "../data/Settings.h"
#include "../events/EventManager.h"
#include "../graphics/Renderer.h"

namespace liquid { namespace common {
#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H

/**
 * \class GameManager
 *
 * \ingroup Common
 * \brief Large controller that manages the flow of the game (Singleton class)
 *
 * \author Jamie Massey
 * \version 2.0
 * \date 04/04/2017
 *
 */

// TODO: Create LiquidDataEvent class to pass event data
// TODO: In Data, implement Settings and Bindings classes
// TODO: Create Context class that can be used to create a Window for any rendering API
class GameScene;
class GameManager
{
public:
    /// GameManager Constructor
    GameManager();

    /// GameManager Destructor
    ~GameManager();

    /** \brief Executes the GameManager
      *
      * The purpose of this method is to setup most of the important subsystems that 
      * the engine provides. Therefore, as this is a singleton class, you should make
      * sure to call this method in your main() function before adding any GameScene
      * instances or attempting to run any other code on this class.
      */
    void execute();

    /** \brief Simulates the entire game by managing GameScenes in mGameScenes
      * 
      * Tasked with simulation of the game this method is the main body where all
      * subsystems are updated and the Scenes are managed. This method also passes and
      * processes input events and makes sure that DeltaTime is updated.
      *
      * You only need to call this method once in your main() function, but make sure
      * that GameManager::execute() has been called first.
      */
    void simulate();

    /// Called when the game has finished running, cleaning up resources
    void terminate();

    /** \brief Insert a GameScene to the front of the stack
      * \param scene GameScene you want to insert
      *
      * Adds a GameScene to the front of the mGameScene std::list variable, as it is
      * inserted the GameScene::initialise() method is also called.
      */
    void addGameSceneFront(GameScene* scene);

    /** \brief Insert a collection of GameScene's to the front of the stack
      * \param scenes Collection of GameScene's you want to insert
      *
      * Inserts a collection GameScene to the front of the mGameScene std::list variable,
      * each added scene has GameScene::initialise called on it.
      */
    void addGameSceneFront(std::vector<GameScene*> scenes);

    /** \brief Insert a GameScene to the back of the stack
      * \param scene GameScene you want to insert
      *
      * Adds a GameScene to the back of the mGameScene std::list variable, as it is
      * inserted the GameScene::initialise() method is also called.
      */
    void addGameSceneBack(GameScene* scene);

    /** \brief Insert a collection of GameScene's to the back of the stack
      * \param scenes Collection of GameScene's you want to insert
      *
      * Inserts a collection GameScene to the back of the mGameScene std::list variable,
      * each added scene has GameScene::initialise called on it.
      */
    void addGameSceneBack(std::vector<GameScene*> scenes);

    /** \brief Pops the GameScene at the front of mGameScenes
      * \return returns the GameScene at the front, nullptr if no scene
      */
    GameScene* popGameSceneFront();

    /** \brief Pops the GameScene at the back of mGameScenes
      * \return returns the GameScene at the back, nullptr if no scene
      */
    GameScene* popGameSceneBack();

    /** \brief Peeks at the GameScene at the front of mGameScenes
      * \return returns the GameScene at the front, nullptr if no scene
      */
    GameScene* peekGameSceneFront() const;

    /** \brief Peeks at the GameScene at the back of mGameScenes
      * \return returns the GameScene at the back, nullptr if no scene
      */
    GameScene* peekGameSceneBack() const;

    /** \brief Peeks at the GameScene with the given std::string
      * \param name Name of desired GameScene as std::string
      * \return returns the found GameScene, nullptr if no scene
      */
    const GameScene* peekGameSceneByName(std::string name) const;

    /** \brief Gets the instance of this class (singleton)
      * \return Pointer to the on instance of this class in memory
      */
    static GameManager& instance();

    /** \brief Sets the instance of the Bindings class
      * \param bindings Pointer to the Bindings class you want to set
      */
    void setBindingsClass(data::Bindings* bindings);

    /** \brief Sets the instance of the Settings class
      * \param bindings Pointer to the Settings class you want to set
      */
    void setSettingsClass(data::Settings* settings);

    /** \brief Sets the instance of the EventManager class
      * \param eventManager Pointer to the EventManager class you want to set
      */
    void setEventManagerClass(events::EventManager* eventManager);

    /** \brief Sets the instance of the Renderer class
      * \param eventManager Pointer to the Renderer class you want to set
      */
    void setRendererClass(graphics::Renderer* renderer);

    /// \return Pointer to the EventManager class being used
    events::EventManager* getEventManagerClass() const;

    /// \return Pointer to the Renderer class being used
    graphics::Renderer* getRendererClass() const;

    /** \brief Suspends the game based on passed value
      * \param suspend Boolean, true suspends the game, false resumes
      */
    void setGameSuspended(bool suspend);

    /** \brief Denotes if the game is running, if set to false terminates next frame
    * \param running Setting this to false will terminate the game next frame
    */
    void setGameRunning(bool running);

    /// \return Gets the set bindings class, nullptr if none
    data::Bindings* getBindingsClass() const;

    /// \return Gets the set settings class, nullptr if none
    data::Settings* getSettingsClass() const;

protected:
    std::list<GameScene*> mGameScenes;   ///< A list of all running game scenes, active or not
    data::Bindings*       mBindings;     ///< Pointer to an instance of the Bindings class
    data::Settings*       mSettings;     ///< Pointer to an intsance of the Settings class
    events::EventManager* mEventManager; ///< Pointer to an instance of the EventManager class
    graphics::Renderer*   mRenderer;     ///< Pointer to an instance of the Renderer class

private:
    bool mPopNextSceneFront; ///< Flag denotes if the front scene should be popped next frame
    bool mPopNextSceneBack;  ///< Flag denotes if the bac scene should be popped next frame
    bool mGameSuspended;     ///< Flag denotes if the game should be suspended in its current state
    bool mGameRunning;       ///< Flag denotes if the game is being simulated, set to false to terminate
};

#endif // _GAMEMANAGER_H
}}
