#include <stdint.h>

namespace liquid { namespace events {
#ifndef _TEXTEVENTDATA_H
#define _TEXTEVENTDATA_H

/**
 * \class TextEventData
 *
 * \ingroup Events
 * \brief Structure of a text event, use for EventDispatcher
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 05/05/2017
 *
 */

class TextEventData
{
public:
    /** \brief TextEventData constructor
      * \param character Unicode uint32_t of the character entered
      */
    TextEventData(uint32_t character)
    {
        mCharacter = character;
    }

public:
    uint32_t mCharacter; ///< Unicode character entered
};

#endif // _TEXTEVENTDATA_H
}}
