#ifdef SFML
#include "SFMLRenderer.h"
#include "../../graphics/Renderable.h"
#include "../../utilities/DeltaTime.h"

namespace liquid {
namespace impl {

    SFMLRenderer::SFMLRenderer(common::GameScene* sceneParent, data::Settings* settings) :
        graphics::Renderer(sceneParent)
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

        mRenderWindow = new sf::RenderWindow(mode, "Window", sf::Style::Titlebar);
    }

    SFMLRenderer::~SFMLRenderer()
    {}

    void SFMLRenderer::draw()
    {
        updateCamera();
        mRenderWindow->clear(sf::Color::Black);

        for (auto object : mRenderables)
            object->draw(this);

        Renderer::draw();

        mRenderWindow->display();
        std::string dt = std::to_string(1000.0f / utilities::DELTA);
        mRenderWindow->setTitle("Window - " + dt);
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
