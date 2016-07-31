#ifndef _RENDERABLELUA_H
#define _RENDERABLELUA_H

#include <string>
#include <SFML/Graphics.hpp>

void		 luaRenderableBind();
void		 luaChangeAnimation(std::string entID, std::string name, int32_t begin, int32_t end);
void		 luaChangeDefaultAnimation(std::string entID, std::string name, int32_t begin, int32_t end);
void		 luaChangeAnimationMode(std::string entID, int32_t mode);
void		 luaUpdateRotation(std::string entID, float angle);
void		 luaSetRenderableActive(std::string entID, bool flag);
float		 luaFaceTarget(std::string entID, float x, float y);
bool		 luaCheckTextured(std::string entID);
bool		 luaCheckAnimated(std::string entID);
bool		 luaCheckShaded(std::string entID);
bool		 luaCheckCentred(std::string entID);
int32_t		 luaGetSceneDepth(std::string entID);
int32_t		 luaGetDefaultStartFrame(std::string entID);
int32_t		 luaGetDefaultEndFrame(std::string entID);
int32_t		 luaGetCurrentFrame(std::string entID);
int32_t		 luaGetStartFrame(std::string entID);
int32_t		 luaGetEndFrame(std::string entID);
std::string  luaGetTexturePath(std::string entID);
std::string  luaGetAnimationPath(std::string entID);
sf::Vector2f luaGetDimensions(std::string entID);


#endif // _RENDERABLELUA_H
