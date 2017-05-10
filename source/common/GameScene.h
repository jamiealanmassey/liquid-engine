#include <vector>
#include <algorithm>
#include "Entity.h"
#include "Layer.h"
#include "../animation/Animator.h"
#include "../ui/WidgetManager.h"

namespace liquid { namespace common {
#ifndef _GAMESCENE_H
#define _GAMESCENE_H

/**
 * \class GameScene
 *
 * \ingroup Common
 * \brief Large complex container for Entities and other modules which can manage them
 *
 * \author Jamie Massey
 * \version 2.0
 * \date 04/04/2017
 *
 */

class GameScene
{
public:
    /// GameScene Constructor
    GameScene();

    /// GameScene Destructor
    ~GameScene();

    /** \brief Initialised on running of this Scene
      *
      * Called when the Scene has been officially created, usually done in
      * the GameManager class when the Scene is added to the list of working
      * scenes in the manager.
      */
    virtual void initialise();

    /** \brief Updates the game for any incoming input events from user
      *
      * This should be called every frame and will supply the program with
      * a compiled list of events that have occured and the respective data
      * pertaining to those events that've been triggered on this frame. This
      * could include events such as mouse, keyboard, gamepad input etc.
      */
    //virtual void updateEvents(/*LiquidEventData eventData*/);

    /** \brief Updates the Scene, called every frame
      *
      * Intended to be called when the game updates, this function is responsible
      * for making sure all entities and sub-modules of this scene are updated and
      * the Renderer rendered.
      */
    virtual void update(); // NOTE: Render at end of update loop, using renderer

    /** \brief Inserts a new Layer into the Scene
      * \param name std::string representation of this Layer
      * \param layerPtr Pointer to the Layer object to insert
      */
    virtual void insertLayer(std::string name, Layer* layerPtr);

    /** \brief Uses the mLayerIndexer to find the index of the layer and removes it
      * \param std::string representation of the Layer object
      */
    virtual void removeLayer(std::string name);

    /** \brief Gets the Layer with the given name
      * \return Pointer to the found layer, nullptr if not found
      */
    virtual Layer* getLayer(std::string name);

    /** \brief Find if an Entity is at the given point
      * \param x X-Coordinate to check against
      * \param y Y-Coordinate to check against
      * \return The found Entity, nullptr if none found
      *
      * Using the given point it will be checked against the Entity using the
      * Entity::isPointInside(x,y) function, where possible the function will 
      * attempt to use spatial partitioning to prune the search area.
      *
      * Note: This will only return the first found Entity at the position, 
      * dismissing any other found Entities, which may be picked at random and
      * not necessarily in any particular order.
      */
    Entity* getEntityAtPoint(float x, float y);

    /** \brief Find an Entity using their Unique ID
      * \param uid The identifier to search for
      * \return The found Entity with given ID, nullptr if none found
      *
      * Uses the given unique identifier to find an Entity in the GameScene
      */
    Entity* getEntityWithUID(std::string uid);

    void addAnimator(animation::Animator* animator);

    void setWidgetManager(ui::WidgetManager* widgetManager);

    /** \brief Denotes if the GameScene is allowed to Update
      * \param isAllowed Value to assign the flag, default: true
      */
    void setAllowUpdate(bool isAllowed = true);

    /** \brief Denotes if the GameScene is allowed to Update the Events
      * \param isAllowed Value to assign the flag, default: true
      */
    void setAllowUpdateEvents(bool isAllowed = true);

    /** \brief Denotes if the GameScene is allowed to Render anything via Renderer
      * \param isAllowed Value to assign the flag, default: true
      */
    void setAllowRenderer(bool isAllowed = true);

    /** \brief Denotes if the GameScene is allowed to apply Post-Processes
      * \param isAllowed Value to assign the flag, default: true
      */
    void setAllowPostProcesses(bool isAllowed = true);

    /** \brief Gets the current Collection of Entities in the Scene
      * \return Collection of Entities as a std::vector
      */
    std::vector<Entity*> getEntities();

    /** \brief Gets the layers associated with this GameScene
      * \return Collection of Layer objects as a std::list
      */
    std::vector<Layer*> getLayers();

    /** \brief Gets the name of the Scene
      * \return Name of the GameScene as a std::string, default: ""
      */
    std::string getSceneName() const;

    ui::WidgetManager* getWidgetManager() const;

    /** \brief Gets the Spatial Manager attached to this GameScene
      * \return Spatial object attached to this GameScene, nullptr if none
      */
    //Spatial* getSpatialManager() const;

    /** \brief Denotes if the GameScene is allowed to Update
      * \return Boolean value of True or False
      */
    bool isAllowedUpdate() const;

    /** \brief Denotes if the GameScene is allowed to Update the Events
      * \return Boolean value of True or False
      */
    bool isAllowedUpdateEvents() const;

    /** \brief Denotes if the GameScene is allowed to the Renderer and draw
      * \return Boolean value of True or False
      */
    bool isAllowedRenderer() const;

    /** \brief Denotes if the GameScene is allowed to use Post Processes
      * \return Boolean value of True or False
      */
    bool isAllowedPostProcesses() const;

protected:
    std::list<animation::Animator*> mAnimators;
    std::map<std::string, uint32_t> mLayerIndexer;
    std::vector<Layer*>             mLayers;
    std::string                     mSceneName;      ///< String identifier for the Scene
    ui::WidgetManager*              mWidgetManager;  ///< Pointer to the ui::WidgetManager class for UI management
    //Spatial*             mSpatialManager; ///< Pointer to a spatial manager used to divide and query space

private:
    bool mAllowUpdate;        ///< Flag that denotes if the scene should update
    bool mAllowUpdateEvents;  ///< Flag that denotes if the scene can react to events
    bool mAllowRenderer;      ///< Flag that denotes if we can render
    bool mAllowPostProcesses; ///< Flag that denotes if post processes can be applied
};

#endif // _GAMESCENE_H
}}
