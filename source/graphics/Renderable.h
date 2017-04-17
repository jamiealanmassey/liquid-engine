#include <array>
#include "Renderer.h"
#include "IRenderable.h"
#include "../utilities/Vertex2.h"

namespace liquid { namespace graphics {
#ifndef _RENDERABLE_H
#define _RENDERABLE_H

/**
 * \class Renderable
 *
 * \ingroup Graphics
 * \brief Defines a way to Render something to the Renderer context
 *
 * \author Jamie Massey
 * \version 2.0
 * \date 16/04/2017
 *
 */

class Renderable : public IRenderable
{
public:
    enum eVertexIndex
    {
        VERTEX_TOPLEFT  = 0,
        VERTEX_TOPRIGHT = 1,
        VERTEX_BTMLEFT  = 2,
        VERTEX_BTMRIGHT = 3,
    };

public:
    /// Renderable Constructor
    Renderable(std::array<utilities::Vertex2*, 4> vertices, float layerDepth = 1.0f);

    /// Renderable Destructor
    ~Renderable();

    /** \brief Virtual function for drawing to the Renderer 
      * \param renderer Renderer to draw to
      */
    virtual void draw(Renderer* renderer) override;

    /// \return X-coordinate as a floating point number
    float getPositionX() const;

    /// \return Y-coordinate as a floating point number
    float getPositionY() const;
    
    /// \return Layer depth as a floating point number
    float getLayerDepth() const;

    /** \brief Set the Vertex at this index
      * \param vertex The Vertex2 to set
      * \param index The index where to set the Vertex
      */
    virtual void setVertex(utilities::Vertex2 vertex, eVertexIndex index);

    /** \brief Get the Vertex at specified index
      * \param index Index to get Vertex from
      * \return The found Vertex
      */
    utilities::Vertex2* getVertex(eVertexIndex index) const;

    /// \return All Vertices for this Renderable
    const std::array<utilities::Vertex2*, 4>& getVertices() const;

protected:
    std::array<utilities::Vertex2*, 4> mVertices; ///< Array of Vertices for this Renderable
    float                              mLayerDepth;  ///< Layer depth, where lower is higher
};

#endif // _RENDERABLE_H
}}
