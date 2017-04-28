#include "Widget.h"
#include "WidgetManager.h"
#include "Toggle.h"
#include "../data/TextureAtlas.h"

namespace liquid { namespace ui {
#ifndef _CONTROLLIST_H
#define _CONTROLLIST_H

/**
* \class Toggle
*
* \ingroup UI
* \brief Similar to the Button class except toggles, extends the Button class
*
* \author Jamie Massey
* \version 1.0
* \date 28/04/2017
*
*/

class ControlList : public Widget
{
public:
    /// Defines what type of ControlList this is
    enum eControlType
    {
        CONTROLTYPE_SINGLE = 0,
        CONTROLTYPE_SINGLESTRICT = 1,
        CONTROLTYPE_MULTIPLE = 2,
    };

public:
    /** \brief ControlList Constructor
      * \param x Position of the Widget on the X-Axis
      * \param y Position of the Widget on the Y-Axis
      * \param textureNames Texture names to extrapolate from the stored data::TextureAtlas
      */
    ControlList(float x, float y, std::array<std::string, 2> textureNames);
    
    /// ControlList Destructor
    ~ControlList();

    /** \brief Insert a new element for this ControlList
      * \param element Element to be inserted
      */
    void insertElement(Toggle* element);

    /** \brief Remov an element from this ControlList
      * \param element Element to be removed
      */
    void removeElement(Toggle* element);

    /** \brief Sets the mTextureNames array for the interface textures
      * \param textureNames Array with two elements for the texture names
      */
    void setTextureNames(std::array<std::string, 2> textureNames);

    /** \brief Assign the eControlType of this ControlList
      * \param controlType Control type to assign
      */
    void setControlType(eControlType controlType);

    /// \brief Override Widget::handleMousePressed
    void handleMousePressed(int32_t button, float x, float y) override;

    /// \brief Override Widget::handleMouseReleased
    void handleMouseReleased(int32_t button, float x, float y) override;

    /// \brief Override Widget::handleMouseMoveds
    void handleMouseMoved(float x, float y) override;

    /// \brief Override Widget::handleKeyboardPressed
    void handleKeyboardPressed(int32_t key) override;

    /// \brief Override Widget::handleKeyboardReleased
    void handleKeyboardReleased(int32_t key) override;

protected:
    std::vector<Toggle*>       mElements;     ///< Collection of Control elements (Toggle objects)
    std::array<std::string, 2> mTextureNames; ///< Array of texture names for the data::TextureAtlas
    eControlType               mControlType;  ///< Type of Control that this ControlList is
};

#endif // _CONTROLLIST_H
}}
