#include "../tweener/Tweener.h"
#include <array>

namespace liquid { namespace graphics {
#ifndef _ICAMERA_H
#define _ICAMERA_H

/**
 * \class ICamera
 *
 * \ingroup Graphics
 * \brief Simple interface class that defines a Camera for the Renderer
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 27/04/2017
 *
 */

class ICamera
{
public:
    /// Defines on which Axis to shake the Camera
    enum eShakeAxis
    {
        SHAKEAXIS_X = 0,
        SHAKEAXIS_Y = 1,
        SHAKEAXIS_XY = 2,
    };

public:
    /// ICamera Constructor
    ICamera() {}

    /// ICamera Destructor
    ~ICamera() {}

    /// \brief Called every frame, do anything that needs updating in here
    virtual void update() = 0;

    /** \brief Pure virtual called when you want to set the Camera's position
      * \param position Array representing the position in 2D space
      */
    virtual void setCentre(std::array<float, 2> position) = 0;
    
    /** \brief Pure virtual called when you want to set the Camera's dimensions
      * \param dimensions Array representing the dimensions in 2D space
      */
    virtual void setDimensions(std::array<float, 2> dimensions) = 0;

    /** \brief Pure virtual called when you want to define the Camera's rotation
      * \param rotation Float value that represent the rotation (0 - 360)
      */
    virtual void setRotation(float rotation) = 0;

    /** \brief Pure virtual called when you want to define the Camera's zoom factor
      * \param rotation Float value that represent the zoom
      */
    virtual void setZoomFactor(float zoomFactor) = 0;

    /** \brief Pure virtual to trigger tweener::Tweener to ease to the defined position
      * \param targetPosition Array representing the position in 2D space
      * \param duration Time to get to the target in milliseconds
      */
    virtual void easePosition(std::array<float, 2> targetPosition, float duration) = 0;

    /** \brief Pure virtual to trigger tweener::Tweener to ease to the defined rotation
      * \param targetRotation Rotation to ease to
      * \param duration Time to get to the target in milliseconds
      */
    virtual void easeRotation(float targetRotation, float duration) = 0;

    /** \brief Pure virtual to trigger tweener::Tweener to ease to the defined zoom factor
      * \param targetZoomFactor Zoom factor to ease to
      * \param duration Time to get to the target in milliseconds
      */
    virtual void easeZoomFactor(float targetZoomFactor, float duration) = 0;

    /** \brief Shakes the Camera with the given characteristics for determined time
      * \param duration Duration of the screenshake in milliseconds
      * \param radius Radius in which to shake the Camera
      * \param axis Axis to shake the Camera around (X, Y or XY)
      */
    virtual void shake(float duration, float radius, eShakeAxis axis) = 0;

    /// \return Gets the Centre of the Camera
    const std::array<float, 2> getCentre() const
    {
        return mCentre;
    }

    /// \return Gets the Dimensions of the Camera
    const std::array<float, 2> getDimensions() const
    {
        return mDimensions;
    }

    /// \return Gets the Rotation of the Camera
    const float getRotation() const
    {
        return mRotation;
    }

protected:
    std::array<float, 2> mCentre;     ///< Centre of the Camera in 2D space
    std::array<float, 2> mDimensions; ///< Dimensions of the Camera in 2D space
    float                mRotation;   ///< Current rotation of the Camera
    float                mZoomFactor; ///< Current zooming factorof the Camera

protected:
    tweener::Tweener mPositionTweener[2]; ///< Position tweeners for the Camera
    tweener::Tweener mRotationTweener;    ///< Rotation tweener for the Camera
    tweener::Tweener mZoomTweener;        ///< Zoom factor tweener for the Camera
};

#endif // _ICAMERA_H
}
}
