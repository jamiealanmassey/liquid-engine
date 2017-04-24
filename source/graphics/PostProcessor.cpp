#include "PostProcessor.h"

namespace liquid {
namespace graphics {

    PostProcessor::PostProcessor()
    {
        mEnabled = true;
        mRendererPtr = nullptr;
        mName = "";
        mVertShader = "";
        mFragShader = "";
    }

    PostProcessor::PostProcessor(Renderer* renderer, std::string name)
    {
        mEnabled = true;
        mRendererPtr = renderer;
        mName = name;
        mVertShader = "";
        mFragShader = "";
    }

    PostProcessor::~PostProcessor()
    {}

    void PostProcessor::update()
    {}

    void PostProcessor::process()
    {}

    void PostProcessor::setEnabled(bool flag)
    {
        mEnabled = flag;
    }

    void PostProcessor::setRendererPtr(Renderer* renderer)
    {
        mRendererPtr = renderer;
    }

    void PostProcessor::setName(std::string name)
    {
        mName = name;
    }

    void PostProcessor::setVertShader(std::string vertShader)
    {
        mVertShader = vertShader;
    }

    void PostProcessor::setFragShader(std::string fragShader)
    {
        mFragShader = fragShader;
    }

    const bool PostProcessor::isEnabled() const
    {
        return mEnabled;
    }

    const Renderer* PostProcessor::getRenderer() const
    {
        return mRendererPtr;
    }

    const std::string PostProcessor::getName() const
    {
        return mName;
    }

    const std::string PostProcessor::getVertShader() const
    {
        return mVertShader;
    }

    const std::string PostProcessor::getFragShader() const
    {
        return mFragShader;
    }

}}
