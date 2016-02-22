#include "PostProcessor.h"
#include "Renderer.h"

PostProcessor::PostProcessor(std::string name, Renderer* renderer) :
	m_Name(name),
	m_Enabled(true),
	m_RendererPtr(renderer)
{
	m_RenderTarget = m_RendererPtr->getWorldBuffer();
}
