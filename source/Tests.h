#ifndef _TESTS_H
#define _TESTS_H

#include "LiquidEngine.h"
#include <cstdint>
#include <iostream>

class Tests
{
public:
    Tests() {}
    ~Tests() {}

    void lighting();
    void animation(sf::Texture& texture);
    void batchedSFMLRendering(sf::Texture& texture);
    void particles(sf::Texture& texture);
    void events();
    void navigation();
    void parserXML();
    void quadTree();
    void ai(sf::Texture& texture);

private:
    liquid::common::Entity* mEntity;
    liquid::common::ParticleEmitter* mEmitter;
};

#endif // _TESTS_H
