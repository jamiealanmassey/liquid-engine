#ifdef SFML
#include "SFMLRenderableBatch.h"
#include "SFMLRenderer.h"

namespace liquid {
namespace impl {

    SFMLRenderableBatch::SFMLRenderableBatch(sf::Texture& texture, uint32_t defaultCapacity) :
        graphics::RenderableBatch(defaultCapacity),
        mTexture(texture)
    {
        mRenderStates.texture = &mTexture;
        mRenderStates.blendMode = sf::BlendAlpha;
        mSFMLVertices.resize(defaultCapacity * 4);
    }

    SFMLRenderableBatch::~SFMLRenderableBatch()
    {}

    void SFMLRenderableBatch::draw(graphics::Renderer* renderer)
    {
        for (uint32_t i = 0; i < mVertices.size(); i++)
        {
            if (mVertices[i]->hasChanged() == true)
            {
                convertFromVertex2(i);
                mVertices[i]->resetChanged();
            }
        }

        SFMLRenderer* sfml = static_cast<SFMLRenderer*>(renderer);
        sf::RenderWindow* window = sfml->getRenderWindow();
        window->draw(mSFMLVertices.data(), mBatchCount * 4, sf::Quads, mRenderStates);
    }

    std::array<utilities::Vertex2*, 4> SFMLRenderableBatch::nextVertices()
    {
        std::array<utilities::Vertex2*, 4> verts = RenderableBatch::nextVertices();
        sf::Vector2u size = getTextureSize();

        verts[0]->setTexCoord(0.0f, 0.0f);
        verts[1]->setTexCoord(size.x, 0.0f);
        verts[2]->setTexCoord(size.x, size.y);
        verts[3]->setTexCoord(0.0f, size.y);

        for (uint32_t i = 0; i < 4; i++)
        {
            mSFMLVertices[(mBatchCount - 1) + i].texCoords.x = verts[i]->getTexCoord()[0];
            mSFMLVertices[(mBatchCount - 1) + i].texCoords.y = verts[i]->getTexCoord()[1];
        }

        return verts;
    }

    void SFMLRenderableBatch::setBlendMode(sf::BlendMode mode)
    {
        mRenderStates.blendMode = mode;
    }

    void SFMLRenderableBatch::setShader(const sf::Shader shader)
    {
        mRenderStates.shader = &shader;
    }

    sf::Vector2u SFMLRenderableBatch::getTextureSize() const
    {
        return mTexture.getSize();
    }

    void SFMLRenderableBatch::convertFromVertex2(int32_t index)
    {
        std::array<float, 2> position = mVertices[index]->getPosition();
        std::array<float, 2> texCoords = mVertices[index]->getTexCoord();
        std::array<float, 4> colour = mVertices[index]->getColour();

        mSFMLVertices[index].position.x = position[0];
        mSFMLVertices[index].position.y = position[1];
        mSFMLVertices[index].color.r = colour[0];
        mSFMLVertices[index].color.g = colour[1];
        mSFMLVertices[index].color.b = colour[2];
        mSFMLVertices[index].color.a = colour[3];
        mSFMLVertices[index].texCoords.x = texCoords[0];
        mSFMLVertices[index].texCoords.y = texCoords[1];

        // TODO: Move this somewhere where both SFMLRenderable and SFMLRenderableBatch can get to it
        //       instead of duplicating code
        /*sf::Vertex vertex;
        std::array<float, 2> position = vert->getPosition();
        std::array<float, 2> texCoords = vert->getTexCoord();
        std::array<float, 4> colour = vert->getColour();

        vertex.position = sf::Vector2f(position[0], position[1]);
        vertex.texCoords = sf::Vector2f(texCoords[0], texCoords[1]);
        vertex.color = sf::Color(colour[0], colour[1], colour[2], colour[3]);

        return vertex;*/
    }

}}

#endif // SFML
