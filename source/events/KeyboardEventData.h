#include <stdint.h>

namespace liquid { namespace events {
#ifndef _KEYBOARDEVENTDATA_H
#define _KEYBOARDEVENTDATA_H

/**
 * \class KeyboardEventData
 *
 * \ingroup Events
 * \brief Structure of a keyboard event, use for EventDispatcher
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 09/04/2017
 *
 */

class KeyboardEventData
{
public:
    /** \brief KeyboardEventData constructor
      * \param keyCode Integer of key that was pressed
      * \param keyPressed Denotes if key was pressed down (true) or released (false)
      */
    KeyboardEventData(int32_t keyCode, bool keyPressed)
    {
        mKeyCode = keyCode;
        mKeyPressed = keyPressed;
    }

public:
    int32_t mKeyCode;    ///< Representation of key pressed as integer
    bool    mKeyPressed; ///< Denotes if the key was pressed down (true) or released (false)
};

#endif // _KEYBOARDEVENTDATA_H
}}
