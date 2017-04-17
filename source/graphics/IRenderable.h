namespace liquid { namespace graphics {
#ifndef _IRENDERABLE_H
#define _IRENDERABLE_H

/**
 * \class IRenderable
 * 
 * \ingroup Graphics
 * \brief Interface class to tie togther Renderable objects
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 17/04/2017
 *
 */

class Renderer;
class IRenderable
{
public:
    /// IRenderable Constructor
    IRenderable() {}

    /// IRenderable Destructor
    ~IRenderable() {}

    /** \brief Override function for drawing
      * \param renderer Renderer you want to use for Drawing
      */
    virtual void draw(Renderer* renderer) = 0;
};

#endif // _IRENDERABLE_H
}}
