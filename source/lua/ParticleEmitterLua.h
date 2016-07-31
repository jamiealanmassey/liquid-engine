#ifndef _PARTICLEEMITTERLUA_H
#define _PARTICLEEMITTERLUA_H

#include <string>
#include <SFML/Graphics.hpp>

void luaParticleEmitterBind();
void luaCreateParticleEmitter(std::string id, float x, float y, std::string xml);

#endif // _PARTICLEEFFECTLUA_H
