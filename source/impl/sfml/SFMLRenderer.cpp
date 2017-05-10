#ifdef SFML
#include "SFMLRenderer.h"
#include "../../graphics/Renderable.h"
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

        mRenderWindow = new sf::RenderWindow(mode, "Window", 
            settings->getFullscreen() ? sf::Style::Fullscreen : sf::Style::Titlebar);
    }

    SFMLRenderer::~SFMLRenderer()
    {}

    void SFMLRenderer::draw(common::GameScene* gameScene)
    {
        updateCamera();
        mRenderWindow->clear(sf::Color::Black);

        //std::vector<common::Entity*> entities = gameScene->getEntities();
        //std::vector<sf::Vertex> sfmlVertices(entities.size() * 4);

        drawPreprocess(gameScene);
        drawBatched(gameScene);

        //mRenderWindow->draw(sfmlVertices.data(), entities.size() * 4, sf::PrimitiveType::Quads, mStates);

        /*for (auto object : mRenderables)
            object->draw(this);*/

        //Renderer::draw();

        mRenderWindow->display();
        std::string dt = std::to_string(1000.0f / utilities::DELTA);
        mRenderWindow->setTitle("Window - " + dt);
    }

    void SFMLRenderer::drawPreprocess(common::GameScene* gameScene)
    {
        std::vector<common::Layer*> layers = gameScene->getLayers();
        mBatchGroups.clear();
        mBatchGroups.resize(layers.size());
        int32_t layerCounter = -1;

        for (common::Layer* layer : layers)
        {
            float x1 = mCamera->getCentre()[0] - mCamera->getDimensions()[0];
            float y1 = mCamera->getCentre()[1] - mCamera->getDimensions()[1];
            float x2 = mCamera->getCentre()[0] + mCamera->getDimensions()[0];
            float y2 = mCamera->getCentre()[1] + mCamera->getDimensions()[1];

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

                it = std::find_if(mBatchGroups[layerCounter].begin(), mBatchGroups[layerCounter].end(),
                    std::bind(&SFMLRenderer::predicateFunc, this, std::placeholders::_1, atlasID, shaderID, blendMode));

                if (it == mBatchGroups[layerCounter].end())
                {
                    SFMLBatchGroup batchGroup(atlasID, shaderID, blendMode);
                    std::array<utilities::Vertex2*, 4> verts = entities[i]->getVerticesPtr();
                    batchGroup.insertVertex(convertSFMLVertex(verts[0]));
                    batchGroup.insertVertex(convertSFMLVertex(verts[1]));
                    batchGroup.insertVertex(convertSFMLVertex(verts[2]));
                    batchGroup.insertVertex(convertSFMLVertex(verts[3]));
                    mBatchGroups[layerCounter].push_back(batchGroup);
                }
                else
                {
                    std::array<utilities::Vertex2*, 4> verts = entities[i]->getVerticesPtr();
                    (*it).insertVertex(convertSFMLVertex(verts[0]));
                    (*it).insertVertex(convertSFMLVertex(verts[1]));
                    (*it).insertVertex(convertSFMLVertex(verts[2]));
                    (*it).insertVertex(convertSFMLVertex(verts[3]));
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

                states.texture = &mTextures[mBatchGroups[i][b].getAtlasID()];
                states.blendMode = convertBlendMode(mBatchGroups[i][b].getBlendMode());
                vertices = mBatchGroups[i][b].getVertices();

                mRenderWindow->draw(vertices.data(), vertices.size(), sf::PrimitiveType::Quads, states);
            }
        }
    }

    bool SFMLRenderer::predicateFunc(SFMLBatchGroup& batch, int32_t atlasID, int32_t shaderID, int32_t blendMode)
    {
        return (atlasID == batch.getAtlasID() &&
                shaderID == batch.getShaderID() &&
                blendMode == batch.getBlendMode());
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

    void SFMLRenderer::setCamera(graphics::ICamera* camera)
    {
        Renderer::setCamera(camera);
        SFMLCamera* sfmlCamera = static_cast<SFMLCamera*>(camera);
        mRenderWindow->setView(sfmlCamera->getSFMLView());
    }

    sf::RenderWindow* SFMLRenderer::getRenderWindow() const
    {
        return mRenderWindow;
    }

    void SFMLRenderer::updateCamera() const
    {
        if (mCamera != nullptr)
        {
            SFMLCamera* sfmlCamera = static_cast<SFMLCamera*>(mCamera);
            mRenderWindow->setView(sfmlCamera->getSFMLView());
        }
    }

}}

#endif // SFML
