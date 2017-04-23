#include "../common/Entity.h"

namespace liquid { namespace spatial {
#ifndef _SPATIAL_H
#define _SPATIAL_H

#define SPATIAL_UNKNOWN 0x00000

/**
* \class Spatial
*
* \ingroup Spatial
* \brief Interface class that describes a Spatial Partitioning class
*
* \author Jamie Massey
* \version 2.0
* \date 23/04/2017
*
*/

class Spatial
{
public:
    /** \brief Spatial Constructor
      * \param spatialType Mask for the Spatial type, default: 0x0000
      */
    Spatial(int32_t spatialType);

    /// Spatial Destructor
    ~Spatial();

    /// \brief Virtual function for initialisation
    virtual void initialise() = 0;

    /// \brief Virtual function for disposing once done
    virtual void dispose() = 0;

    /// \brief Virtual function for updating
    virtual void update() = 0;

    /** \brief Pure virtual function for inserting a new common::Entity
      * \param entityPtr Entity to be added
      */
    virtual void insertEntity(common::Entity* entityPtr) = 0;

    /** \brief Pure virtual function for removing an common::Entity
      * \param entityPtr Entity to be removed
      */
    virtual void removeEntity(common::Entity* entityPtr) = 0;

    /** \brief Pure virtual function for querying the Spatial object
      * \param region Array representing the region to query where = (x, y, width, height)
      */
    virtual std::vector<common::Entity*> query(std::array<float, 4> region) = 0;
    
    /** \brief Pure virtual function for querying the Spatial object
      * \param region Array representing the region to query where = (x, y, width, height)
      * \param type Entity type to search for and prune data
      */
    virtual std::vector<common::Entity*> query(std::array<float, 4> region, int32_t type) = 0;

    /// \return Gets the type mask for the Spatial
    const int32_t getSpatialType() const;

protected:
    int32_t mSpatialType; ///< Stores the type mask for the Spatial Paritioning type
};

#endif // _SPATIAL_H
}}
