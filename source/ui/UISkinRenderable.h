#ifndef _UISKINRENDERABLE_H
#define _UISKINRENDERABLE_H

#include "../graphics/Renderable.h"
#include <PugiXML/pugixml.hpp>
#include <map>

class UISkinRenderable : public Renderable
{
public:
	UISkinRenderable(UISkinRenderable* copy);
	UISkinRenderable(std::string texture, std::string data_xml);
	~UISkinRenderable();

	void pickElement(std::string name);
	void parseSkinData();

protected:
	std::map<std::string, sf::IntRect> m_SkinData;
	std::string						   m_SkinDataXML;
	std::string					       m_SkinTexture;
};

#endif _UISKINRENDERABLE_H
