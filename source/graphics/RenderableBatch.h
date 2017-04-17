#include <stdint.h>
#include <vector>
#include <algorithm>
#include <array>
#include "IRenderable.h"
#include "../utilities/Vertex2.h"

namespace liquid { namespace graphics {
#ifndef _RENDERABLEBATCH_H
#define _RENDERABLEBATCH_H

/**
 * \class RenderableBatch
 *
 * \ingroup Graphics
 * \brief Batches Renderable objects that share properties together to save performance
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 16/04/2017
 *
 */

class RenderableBatch : public IRenderable
{
public:
    /** \brief RenderableBatch Constructor
      * \param defaultCapacity Initial capacity of the batcher
      */
    RenderableBatch(uint32_t defaultCapacity);

    /// RenderableBatch Destructor
    ~RenderableBatch();

    /** \brief Overrie function to draw to the specified Renderer
      * \param renderer Pointer to the Renderer to use for drawing
      */
    virtual void draw(Renderer* renderer) override;

    /** \brief Generates the next batch of vertices required for drawing
      * \return Array of the Vertices for drawing the next image
      */
    virtual std::array<utilities::Vertex2*, 4> nextVertices();

    /** \brief Gets all the stored vertices
      * \return Collection of all Vertices in this batcher as std::vector
      */
    const std::vector<utilities::Vertex2*>& getVertices() const;

protected:
    std::vector<utilities::Vertex2*> mVertices;   ///< Collection of Vertices for drawing this batch
    uint32_t                         mBatchCount; ///< Number of batched objects to draw
    uint32_t                         mCapacity;   ///< Capacity of this Batch (vertices are capacity * 4)
};

#endif // _RENDERABLEBATCH_H
}}
