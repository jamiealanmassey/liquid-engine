#include "Entity.h"
#include "../spatial/Spatial.h"

namespace liquid { namespace common {
#ifndef _LAYER_H
#define _LAYER_H

class GameScene;
class Layer
{
public:
    Layer(GameScene* parentScene);
    ~Layer();

    virtual void update();

    /** \brief Adds a new Entity to the Layer
      * \param entity Entity you wish to add to the Layer
      *
      * Inserts a new Entity into the Layer, once called this will add the Entity
      * to the mEntitiesBuffer std::vector and then any entities that you have added on
      * this frame will be inserted to the Layer at the start of the next running
      * frame.
      *
      * When the given Entity is inserted to the Layer, it will be given this Layers parent
      * scene and the Entity::initialise() function will be called on it.
      */
    virtual void insertEntity(Entity* entity);

    /** \brief Adds a collection of Entities to the Layer
      * \param entities Collection of Entities you wish to add to the Scene
      *
      * Inserts a collection of Entities into the Layer, once called this will
      * add each Entity to the mEntitiesBuffer std::vector and then any entities that you
      * have added on this frame will be inserted to the GameScene at the start of
      * the next running frame.
      *
      * When the given Entities are inserted to the Layer, they will be given this layer
      * as their parent and the Entity::initialise() function will be called on them.
      */
    virtual void insertEntity(std::vector<Entity*> entities);

    /** \brief Sets the Spatial Hash of the Layer
      * \param spatial The Spatial Partitioning method as a class
      *
      * Sets the class for partitioning the space in this Layer, you cannot
      * just pass the Spatial class, this class is simply an interface. For this to
      * work you need to pass an implemented Spatial class that implements it.
      */
    void setSpatialHash(spatial::Spatial* spatialHash);
    
    void setParentScene(GameScene* gameScene);

    spatial::Spatial* getSpatialHash() const;
    GameScene* getParentScene() const;

    std::vector<Entity*> getEntities() const;
    std::vector<Entity*> getEntities(std::array<float, 4> region);

    Entity* getEntityAtPoint(float x, float y);
    Entity* getEntityAtPoint(float x, float y, std::array<float, 4> region);
    Entity* getEntityWithID(std::string uid);
    Entity* getEntityWithID(std::string uid, std::array<float, 4> region);

protected:
    std::vector<Entity*> mEntities;       ///< Collection of Entities that exist in the Scene
    std::vector<Entity*> mEntitiesBuffer; ///< Collection buffer to slowly introduce new Entities
    spatial::Spatial*    mSpatialHash;    ///< 
    GameScene*           mParentScene;    ///< 
};

#endif // _LAYER_H
}}
