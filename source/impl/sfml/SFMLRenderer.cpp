#ifdef SFML
#include "SFMLRenderer.h"
#include "../../utilities/DeltaTime.h"
#include "../../common/Entity.h"
#include "../../common/ResourceManager.h"
#include "../../data/TextureAtlas.h"

namespace liquid {
namespace impl {

    SFMLRenderer::SFMLRenderer(data::Settings* settings) :
        graphics::Renderer(settings)
    {
        sf::VideoMode mode;
        if (settings != nullptr)
        {
            mode.width = settings->getScreenWidth();
            mode.height = settings->getScreenHeight();
        }
        else
        {
            mode.width = 1920;
            mode.height = 1080;
        }

        mRenderBuffer = new sf::RenderTexture;
        mRenderBufferSpr = new sf::Sprite();

        mRenderBuffer->create(mode.width, mode.height);
        mRenderBufferSpr->setTexture(mRenderBuffer->getTexture());
        mRenderWindow = new sf::RenderWindow(mode, "Window", 
            settings->getFullscreen() ? sf::Style::Fullscreen : sf::Style::Titlebar);
    }

    SFMLRenderer::~SFMLRenderer()
    {}

    void SFMLRenderer::draw(common::GameScene* gameScene)
    {
        mRenderBuffer->clear(sf::Color::Black);
        mRenderWindow->clear(sf::Color::Black);

        drawPreprocess(gameScene);
        drawBatched(gameScene);

        Renderer::draw(gameScene);
        mRenderBuffer->display();
        mRenderWindow->draw(*mRenderBufferSpr);
        mRenderWindow->display();

        std::string dt = std::to_string(1000.0f / utilities::DELTA);
        mRenderWindow->setTitle("Window - " + dt);

        if (gameScene->getCamera() != nullptr)
        {
            SFMLCamera* sfmlCamera = static_cast<SFMLCamera*>(gameScene->getCamera());
            mRenderWindow->setView(sfmlCamera->getSFMLView());
        }
    }

    void SFMLRenderer::drawPreprocess(common::GameScene* gameScene)
    {
        std::vector<common::Layer*> layers = gameScene->getLayers();
        mBatchGroups.clear();
        mBatchGroups.resize(layers.size());
        int32_t layerCounter = -1;

        float x1 = 0.f, y1 = 0.f;
        float x2 = 0.f, y2 = 0.f;

        if (gameScene->getCamera() != nullptr)
        {
            common::Camera* camera = gameScene->getCamera();
            x1 = camera->getCentre()[0] - camera->getDimensions()[0];
            y1 = camera->getCentre()[1] - camera->getDimensions()[1];
            x2 = camera->getCentre()[0] + camera->getDimensions()[0];
            y2 = camera->getCentre()[1] + camera->getDimensions()[1];
        }

        for (common::Layer* layer : layers)
        {
            std::vector<common::Entity*> entities = layer->getEntities({ x1,y1,x2,y2 });
            layerCounter++;

            for (int32_t i = 0; i < entities.size(); i++)
            {
                if (entities[i]->getEntityState() != common::Entity::ENTITYSTATE_ACTIVE)
                    continue;

                std::vector<SFMLBatchGroup>::iterator it;
                int32_t atlasID = entities[i]->mAtlasID;
                int32_t shaderID = entities[i]->mShaderID;
                int32_t blendMode = entities[i]->mBlendMode;
                int32_t primitiveType = entities[i]->mPrimitiveType;

                it = std::find_if(mBatchGroups[layerCounter].begin(), mBatchGroups[layerCounter].end(),
                    std::bind(&SFMLRenderer::predicateFunc, this, std::placeholders::_1, atlasID, shaderID, blendMode, primitiveType));

                if (it == mBatchGroups[layerCounter].end())
                {
                    SFMLBatchGroup batchGroup(atlasID, shaderID, blendMode, primitiveType);
                    for (auto vertex : entities[i]->getVertices())
                        batchGroup.insertVertex(convertSFMLVertex(vertex));
                    mBatchGroups[layerCounter].push_back(batchGroup);
                }
                else
                {
                    for (auto vertex : entities[i]->getVertices())
                        (*it).insertVertex(convertSFMLVertex(vertex));
                }

                if (atlasID != -1 && mTextures.find(atlasID) == mTextures.end())
                {
                    sf::Texture texture;
                    data::TextureAtlas* atlas = nullptr;
                    atlas = common::ResourceManager<data::TextureAtlas>::getResource(atlasID);
                    texture.loadFromFile(atlas->getTexturePath());
                    mTextures[atlasID] = texture;
                }
            }
        }
    }

    void SFMLRenderer::drawBatched(common::GameScene* gameScene)
    {
        int32_t layerCount = gameScene->getLayers().size();

        for (int32_t i = 0; i < layerCount; i++)
        {
            for (int32_t b = 0; b < mBatchGroups[i].size(); b++)
            {
                sf::RenderStates states;
                std::vector<sf::Vertex> vertices;

                if (mBatchGroups[i][b].getAtlasID() != -1)
                    states.texture = &mTextures[mBatchGroups[i][b].getAtlasID()];

                states.blendMode = convertBlendMode(mBatchGroups[i][b].getBlendMode());
                vertices = mBatchGroups[i][b].getVertices();

                sf::PrimitiveType type;
                int32_t pType = mBatchGroups[i][b].getPrimitiveType();

                if (pType == 0)
                    type = sf::PrimitiveType::Quads;
                else if (pType == 1)
                    type = sf::PrimitiveType::Lines;
                else if (pType == 2)
                    type = sf::PrimitiveType::Points;
                else
                    type = sf::PrimitiveType::Quads;

                mRenderBuffer->draw(vertices.data(), vertices.size(), type, states);
            }
        }
    }

    bool SFMLRenderer::predicateFunc(SFMLBatchGroup& batch, int32_t atlasID, int32_t shaderID, int32_t blendMode, int32_t primitiveType)
    {
        return (atlasID == batch.getAtlasID() &&
                shaderID == batch.getShaderID() &&
                blendMode == batch.getBlendMode() &&
                primitiveType == batch.getPrimitiveType());
    }

    sf::Vertex SFMLRenderer::convertSFMLVertex(utilities::Vertex2* vert)
    {
        sf::Vertex vertex;
        float x = vert->getPosition()[0];
        float y = vert->getPosition()[1];

        float texCoordX = vert->getTexCoord()[0];
        float texCoordY = vert->getTexCoord()[1];

        float colourR = vert->getColour()[0];
        float colourG = vert->getColour()[1];
        float colourB = vert->getColour()[2];
        float colourA = vert->getColour()[3];

        vertex.position = sf::Vector2f(x, y);
        vertex.color = sf::Color(colourR, colourG, colourB, colourA);
        vertex.texCoords = sf::Vector2f(texCoordX, texCoordY);
        return vertex;
    }

    sf::BlendMode SFMLRenderer::convertBlendMode(int32_t blendMode)
    {
        if (blendMode == 0)
            return sf::BlendAlpha;
        else if (blendMode == 1)
            return sf::BlendAdd;
        else if (blendMode == 2)
            return sf::BlendMultiply;
        else if (blendMode == 3)
            return sf::BlendNone;
        
        return sf::BlendNone;
    }

    sf::RenderWindow* SFMLRenderer::getRenderWindow() const
    {
        return mRenderWindow;
    }

    sf::RenderTexture* SFMLRenderer::getRenderBuffer() const
    {
        return mRenderBuffer;
    }

}}

#endif // SFML
