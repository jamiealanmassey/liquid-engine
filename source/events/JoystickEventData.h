#include <stdint.h>

namespace liquid { namespace events {
#ifndef _JOYSTICKEVENTDATA_H
#define _JOYSTICKEVENTDATA_H

/**
 * \class JoystickEventData
 *
 * \ingroup Events
 * \brief Structure of a joystick event, use for EventDispatcher
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 09/04/2017
 *
 */

class JoystickEventData
{
public:
    /** \brief JoystickEventData constructor
      * \param buttonCode Integer of button that was pressed
      * \param buttonPressed Denotes if button was pressed down (true) or released (false)
      */
    JoystickEventData(int32_t buttonCode, bool buttonPressed)
    {
        mButtonCode = buttonCode;
        mButtonPressed = buttonPressed;
    }

public:
    int32_t mButtonCode;    ///< Representation of button pressed as integer
    bool    mButtonPressed; ///< Denotes if the button was pressed down (true) or released (false)
};

#endif // _JOYSTICKEVENTDATA_H
}}
