#include <stdint.h>

namespace liquid { namespace events {
#ifndef _MOUSEEVENTDATA_H
#define _MOUSEEVENTDATA_H

/**
 * \class MouseEventData
 *
 * \ingroup Events
 * \brief Structure of a mouse event, use for EventDispatcher
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 09/04/2017
 *
 */

class MouseEventData
{
public:
    /** \brief MouseEventData constructor
      * \param mouseButton Integer of button on mouse pressed
      * \param positionX Float representation of where pressed on X-Axis
      * \param positionY Float representation of where pressed on Y-Axis
      * \param pressed Denotes if mouse was pressed down (true) or released (false)
      */
    MouseEventData(int32_t mouseButton, float positionX, float positionY, bool pressed)
    {
        mMouseButton = mouseButton;
        mPositionX = positionX;
        mPositionY = positionY;
        mPressed = pressed;
    }

public:
    int32_t mMouseButton; ///< Representation of mouse button pressed as integer
    float   mPositionX;   ///< Position of the mouse X-Coordinate at time of the event
    float   mPositionY;   ///< Position of the mouse Y-Coordinate at time of the event
    bool    mPressed;     ///< Denotes if the mouse was pressed down (true) or released (false)
};

#endif // _MOUSEEVENTDATA_H
}}
