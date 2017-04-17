#include "Renderable.h"

namespace liquid {
namespace graphics {

    Renderable::Renderable(std::array<utilities::Vertex2*, 4> vertices, float layerDepth) :
        IRenderable()
    {
        mVertices = vertices;
        mLayerDepth = layerDepth;
    }

    Renderable::~Renderable()
    {} 

    void Renderable::draw(Renderer* renderer)
    {}

    float Renderable::getPositionX() const
    {
        return mVertices[0]->getPosition().at(0);
    }

    float Renderable::getPositionY() const
    {
        return mVertices[0]->getPosition().at(1);
    }

    float Renderable::getLayerDepth() const
    {
        return mLayerDepth;
    }

    void Renderable::setVertex(utilities::Vertex2 vertex, Renderable::eVertexIndex index)
    {
        mVertices[(int32_t)index] = &vertex;
    }

    utilities::Vertex2* Renderable::getVertex(Renderable::eVertexIndex index) const
    {
        return mVertices.at((int32_t)index);
    }

    const std::array<utilities::Vertex2*, 4>& Renderable::getVertices() const
    {
        return mVertices;
    }

}}
