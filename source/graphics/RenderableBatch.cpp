#include "RenderableBatch.h"

namespace liquid {
namespace graphics {

    RenderableBatch::RenderableBatch(uint32_t defaultCapacity) :
        IRenderable()
    {
        mCapacity = defaultCapacity;
        mBatchCount = 0;
        mVertices.reserve(defaultCapacity);
    }

    RenderableBatch::~RenderableBatch()
    {}

    void RenderableBatch::draw(Renderer* renderer)
    {}

    std::array<utilities::Vertex2*, 4> RenderableBatch::nextVertices()
    {
        std::array<utilities::Vertex2*, 4> verts;

        for (uint32_t i = 0; i < 4; i++)
        {
            utilities::Vertex2* vert = new utilities::Vertex2();
            verts[i] = vert;
            mVertices.push_back(vert);
        }

        mBatchCount++;
        return verts;
    }

    const std::vector<utilities::Vertex2*>& RenderableBatch::getVertices() const
    {
        return mVertices;
    }

}}
