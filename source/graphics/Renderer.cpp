#include "Renderer.h"

namespace liquid {
namespace graphics {

    Renderer::Renderer(common::GameScene* gameSceneParent)
    {
        mGameSceneParent = gameSceneParent;
    }

    Renderer::~Renderer()
    {}

    void Renderer::addRenderable(IRenderable* renderable)
    {
        mRenderables.push_back(renderable);
    }

    void Renderer::removeRenderable(IRenderable* renderable)
    {
        std::remove(mRenderables.begin(),
                    mRenderables.end(),
                    renderable);
    }

    void Renderer::draw()
    {}

    void Renderer::addPostProcessor(PostProcessor* postProcessor)
    {
        mPostProcessors.push_back(postProcessor);
    }

    void Renderer::removePostProcessor(PostProcessor* postProcessor)
    {
        std::remove(mPostProcessors.begin(), 
                    mPostProcessors.end(), 
                    postProcessor);
    }

    void Renderer::removePostProcessor(std::string postProcessorName)
    {
        // TODO
    }

    void Renderer::removeAllPostProcessors()
    {
        for (auto processor : mPostProcessors)
            delete processor;

        mPostProcessors.clear();
    }

    std::array<float, 2> Renderer::getMousePosition()
    {
        // TODO
        return std::array<float, 2>();
    }

    common::GameScene* Renderer::getGameSceneParent()
    {
        return mGameSceneParent;
    }

    PostProcessor* Renderer::getPostProcessor(std::string postProcessorName)
    {
        // TODO
        return nullptr;
    }

    std::list<PostProcessor*>& Renderer::getPostProcessors()
    {
        return mPostProcessors;
    }

    std::list<IRenderable*>& Renderer::getRenderables()
    {
        return mRenderables;
    }

}}
