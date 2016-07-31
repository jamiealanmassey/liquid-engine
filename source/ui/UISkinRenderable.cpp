#include "UISkinRenderable.h"
#include "../utilities/Logger.h"

UISkinRenderable::UISkinRenderable(UISkinRenderable* copy) :
	Renderable(copy->m_SkinTexture)
{
	m_SkinData    = copy->m_SkinData;
	m_SkinDataXML = copy->m_SkinDataXML;
	m_SkinTexture = copy->m_SkinTexture;
}

UISkinRenderable::UISkinRenderable(std::string texture, std::string skin_data) :
	Renderable(texture),
	m_SkinDataXML(skin_data)
{
	parseSkinData();
}

UISkinRenderable::~UISkinRenderable()
{
	m_SkinData.clear();
}

void UISkinRenderable::pickElement(std::string name)
{
	// Provided the skin data with that name exists clip the sprite
	if (m_SkinData.find(name) != m_SkinData.end() && m_Textured)
	{
		clipSprite(m_SkinData[name]);
		m_SkinTexture = name;
	}
	else
		Logger::instance().message("Could not locate " + name + " texture element in UISkinRenderable", Logger::eType::LOG_ERROR);
}

void UISkinRenderable::parseSkinData()
{
	// Open up the document data in a new pugi document
	pugi::xml_document skin_data;
	if (!skin_data.load_file(m_SkinDataXML.c_str()))
		return;

	// Find the root node and iteratively go through each child node that
	// exists harvesting data
	pugi::xml_node root = skin_data.child("SkinData");
	for (pugi::xml_node_iterator nodes = root.begin(); nodes != root.end(); ++nodes)
	{
		// Find required information for the region
		std::string name = nodes->child("Name").attribute("value").as_string();
		int32_t local_x  = nodes->child("LocalX").attribute("value").as_int();
		int32_t local_y  = nodes->child("LocalY").attribute("value").as_int();
		int32_t width	 = nodes->child("Width").attribute("value").as_int();
		int32_t height	 = nodes->child("Height").attribute("value").as_int();

		// Store the new Skin element
		sf::IntRect region = sf::IntRect(local_x, local_y, width, height);
		m_SkinData[name] = region;
	}
}
