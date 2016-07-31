#ifndef _ENTITYLUA_H
#define _ENTITYLUA_H

#include <string>
#include <SFML/Graphics.hpp>

void		 luaEntityBind();
bool		 luaCheckRenderable(std::string entID);
bool		 luaCheckPhysics(std::string entID);
bool		 luaIsPointInside(std::string entID, float x, float y);
void		 luaDoEntitySleep(std::string entID);
void		 luaDoEntityWake(std::string entID);
void		 luaDoEntityKill(std::string entID);
void		 luaAttachRenderable(std::string entID, std::string texture, int32_t depth);
void		 luaSetPosition(std::string entID, float x, float y);
void		 luaAddPosition(std::string entID, float x, float y);
void		 luaAddChild(std::string entID, std::string childID);
int32_t		 luaGetEntityType(std::string entID);
int32_t		 luaGetEntityState(std::string entID);
std::string  luaGetParentSceneName(std::string entID);
std::string  luaGetParentID(std::string entID);
sf::Vector2f luaGetPosition(std::string entID);
bool		 luaHasChildren(std::string entID);

#endif // _ENTITYLUA_H
