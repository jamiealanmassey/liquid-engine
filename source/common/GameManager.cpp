#include "GameManager.h"
#include "../utilities/DeltaTime.h"

namespace liquid {
namespace common {
    
    GameManager::GameManager()
    {
        mBindings = nullptr;
        mSettings = nullptr;
        mEventManager = nullptr;
        mRenderer = nullptr;
        mPopNextSceneFront = false;
        mPopNextSceneBack = false;
        mGameSuspended = false;
        mGameRunning = true;
    }

    GameManager::~GameManager()
    {}

    void GameManager::execute()
    {
        // TODO: Load game settings/bindings
        // TODO: Setup Context given
        // TODO: Start DeltaTime
        // TODO: Initialise the ResourceManager
        // TODO: Initialise global LUA
    }

    void GameManager::simulate()
    {
        while (mGameRunning == true)
        {
            utilities::DeltaTime::instance().tick();

            if (mGameSuspended == false)
            {
                mEventManager->updateEvents();
                mGameScenes.front()->updateEvents(); // NOTE: Required function anymore?
                mGameScenes.front()->update();
                mRenderer->draw();

                if (mPopNextSceneFront && mGameScenes.size() > 1)
                {
                    mGameScenes.pop_front();
                    mPopNextSceneFront = false;
                }
                else if (mPopNextSceneBack && mGameScenes.size() > 1)
                {
                    mGameScenes.pop_back();
                    mPopNextSceneBack = false;
                }
            }

            // TODO: Flush stale event data (?)
        }
    }

    void GameManager::terminate()
    {
        for (auto&& sc : mGameScenes)
            delete sc;

        mGameScenes.clear();
    }

    void GameManager::addGameSceneFront(GameScene* scene)
    {
        scene->initialise();
        mGameScenes.push_front(scene);
    }

    void GameManager::addGameSceneFront(std::vector<GameScene*> scenes)
    {
        for (auto sc : scenes) addGameSceneFront(sc);
    }

    void GameManager::addGameSceneBack(GameScene* scene)
    {
        scene->initialise();
        mGameScenes.push_back(scene);
    }

    void GameManager::addGameSceneBack(std::vector<GameScene*> scenes)
    {
        for (auto sc : scenes) addGameSceneBack(sc);
    }

    GameScene* GameManager::popGameSceneFront()
    {
        if (mGameScenes.empty() == false)
        {
            mPopNextSceneFront = true;
            return mGameScenes.front();
        }

        return nullptr;
    }

    GameScene* GameManager::popGameSceneBack()
    {
        if (mGameScenes.empty() == false)
        {
            mPopNextSceneBack = true;
            return mGameScenes.back();
        }

        return nullptr;
    }

    GameScene* GameManager::peekGameSceneFront() const
    {
        if (mGameScenes.empty())
            return nullptr;

        return mGameScenes.front();
    }

    GameScene* GameManager::peekGameSceneBack() const
    {
        if (mGameScenes.empty())
            return nullptr;

        return mGameScenes.back();
    }

    const GameScene* GameManager::peekGameSceneByName(std::string name) const
    {
        std::list<GameScene*>::const_iterator it =
        std::find_if(mGameScenes.begin(), mGameScenes.end(),
            [&nm = name](const GameScene* scene) {
            return scene->getSceneName() == nm;
        });

        return (*it);
    }

    GameManager& GameManager::instance()
    {
        static GameManager singleton;
        return singleton;
    }

    void GameManager::setBindingsClass(data::Bindings* bindings)
    {
        mBindings = bindings;
    }

    void GameManager::setSettingsClass(data::Settings* settings)
    {
        mSettings = settings;
    }

    void GameManager::setEventManagerClass(events::EventManager* eventManager)
    {
        mEventManager = eventManager;
    }

    void GameManager::setRendererClass(graphics::Renderer* renderer)
    {
        mRenderer = renderer;
    }

    void GameManager::setGameSuspended(bool suspended)
    {
        mGameSuspended = suspended;
    }

    void GameManager::setGameRunning(bool running)
    {
        mGameRunning = running;
    }

    data::Bindings* GameManager::getBindingsClass() const
    {
        return mBindings;
    }

    data::Settings* GameManager::getSettingsClass() const
    {
        return mSettings;
    }

}}
