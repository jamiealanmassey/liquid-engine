//#ifdef SFML
#include "SFMLRenderable.h"
#include "SFMLRenderer.h"

namespace liquid {
namespace impl {

SFMLRenderable::SFMLRenderable(std::array<utilities::Vertex2*, 4> vertices, sf::Texture& texture, float layerDepth) :
        graphics::Renderable(vertices, layerDepth),
        mTexture(texture)   
    {}

    SFMLRenderable::~SFMLRenderable()
    {}

    void SFMLRenderable::draw(graphics::Renderer* renderer)
    {
        SFMLRenderer* sfml = static_cast<SFMLRenderer*>(renderer);
        sf::RenderWindow* window = sfml->getRenderWindow();
        std::array<sf::Vertex, 4> converted;

        for (int32_t i = 0; i < 4; i++)
            converted[i] = convertFromVertex2(mVertices[i]);

        sf::RenderStates states;
        states.texture = &mTexture;
        window->draw(converted.data(), 4, sf::PrimitiveType::Quads, states);
    }

    sf::Vertex SFMLRenderable::convertFromVertex2(utilities::Vertex2* vert)
    {
        sf::Vertex vertex;
        std::array<float, 2> position = vert->getPosition();
        std::array<float, 2> texCoords = vert->getTexCoord();
        std::array<float, 4> colour = vert->getColour();

        vertex.position = sf::Vector2f(position[0], position[1]);
        vertex.texCoords = sf::Vector2f(texCoords[0], texCoords[1]);
        vertex.color = sf::Color(colour[0], colour[1], colour[2], colour[3]);

        return vertex;
    }

}}

//#endif // SFML
