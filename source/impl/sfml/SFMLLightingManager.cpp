#include "SFMLLightingManager.h"
#include "SFMLRenderer.h"
#include "../../common/GameManager.h"
#include "../../graphics/Renderer.h"

namespace liquid {
namespace impl {

    SFMLLightingManager::SFMLLightingManager(data::Settings* settings, std::array<float, 4> ambientColour) :
        LightingManager(ambientColour)
    {
        float screenWidth = settings->getScreenWidth();
        float screenHeight = settings->getScreenHeight();

        mAcummulationBuffer = new sf::RenderTexture();
        mAcummulationBuffer->create(screenWidth, screenHeight);
    }

    SFMLLightingManager::~SFMLLightingManager()
    {
        delete mAcummulationBuffer;
    }

    void SFMLLightingManager::draw(graphics::Renderer* renderer)
    {
        if (getLightCount() == 0)
            return;

        mAcummulationBuffer->clear(sf::Color(mAmbientColour[0], mAmbientColour[1], 
                                             mAmbientColour[2], mAmbientColour[3]));

        for (int32_t i = 0; i < mLights.size(); i++)
        {
            std::array<float, 2> lightPosition = mLights[i]->getLightPosition();
            std::vector<utilities::Vertex2> geom = mLights[i]->getLightGeometry();
            sf::VertexArray vertexArray;
            vertexArray.setPrimitiveType(sf::TrianglesFan);

            for (int32_t z = 0; z < geom.size(); z++)
            {
                sf::Vertex vertex;
                vertex.position.x = geom[z].getPosition()[0];
                vertex.position.y = geom[z].getPosition()[1];
                vertex.color.r = geom[z].getColour()[0];
                vertex.color.g = geom[z].getColour()[1];
                vertex.color.b = geom[z].getColour()[2];
                vertex.color.a = geom[z].getColour()[3];
                vertexArray.append(vertex);
            }
            
            sf::RenderStates states;
            states.blendMode = sf::BlendMode(sf::BlendMode::One, sf::BlendMode::One);
            states.transform.translate(lightPosition[0], lightPosition[1]);
            mAcummulationBuffer->draw(vertexArray, states);
        }

        SFMLRenderer* sfmlRenderer = static_cast<SFMLRenderer*>(renderer);
        sfmlRenderer->getRenderWindow()->draw(sf::Sprite(mAcummulationBuffer->getTexture()),
            sf::RenderStates(sf::BlendMode(sf::BlendMode::Zero, sf::BlendMode::SrcColor)));
    }

}}
