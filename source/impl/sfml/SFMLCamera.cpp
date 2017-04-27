#include "SFMLCamera.h"
#include "../../utilities/Random.h"
#include "../../utilities/DeltaTime.h"

namespace liquid {
namespace impl {

    SFMLCamera::SFMLCamera(float centreX, float centreY)
    {
        mShaking = false;
        mShakeAccumulator = 0.0f;
        mShakeRadius = 0.0f;
        mShakeAngle = 0.0f;

        setCentre({ centreX,centreY });
    }

    SFMLCamera::SFMLCamera(float centreX, float centreY, float width, float height)
    {
        mShaking = false;
        mShakeAccumulator = 0.0f;
        mShakeRadius = 0.0f;
        mShakeAngle = 0.0f;

        setCentre({ centreX, centreY });
        setDimensions({ width, height });
    }

    SFMLCamera::~SFMLCamera()
    {}

    void SFMLCamera::update()
    {
        for (uint32_t i = 0; i < 2; i++)
            mPositionTweener[i].update();

        mRotationTweener.update();
        mZoomTweener.update();

        if (mShaking && mShakeAccumulator <= mShakeDuration)
        {
            mShakeAccumulator += utilities::DELTA;
            int32_t rand = utilities::Random::instance().randomRange(0, 1);
            float radius = utilities::Random::instance().randomRange(0.f, 60.f);
            float time = mShakeAccumulator / mShakeDuration;

            (rand == 0) ? rand = -1 : 
                          rand =  1;

            mShakeRadius = mShakeRadiusBegin * (1 - time);
            mShakeAngle += (180 + (radius * rand));
            updateScreenShake();

            if (mShakeAccumulator >= mShakeDuration)
            {
                mShaking = false;
                mSFMLView.setCenter(mCentre[0], mCentre[1]);
            }
        }
    }

    void SFMLCamera::setCentre(std::array<float, 2> position)
    {
        mSFMLView.setCenter(position[0], position[1]);
        mCentre = position;
    }

    void SFMLCamera::setDimensions(std::array<float, 2> dimensions)
    {
        mSFMLView.setSize(dimensions[0], dimensions[1]);
        mDimensions = dimensions;
    }

    void SFMLCamera::setRotation(float rotation)
    {
        mSFMLView.setRotation(rotation);
        mRotation = rotation;
    }

    void SFMLCamera::setZoomFactor(float zoomFactor)
    {
        // TODO: doesn't actually work like this!
        mSFMLView.zoom(zoomFactor);
        mZoomFactor = zoomFactor;
    }

    void SFMLCamera::easePosition(std::array<float, 2> targetPosition, float duration)
    {
        for (uint32_t i = 0; i < 2; i++)
        {
            mPositionTweener[i].setInitial(mCentre[i]);
            mPositionTweener[i].setTarget(targetPosition[i]);
            mPositionTweener[i].setDuration(duration);
            mPositionTweener[i].reset();
        }  
    }

    void SFMLCamera::easeRotation(float targetRotation, float duration)
    {
        mRotationTweener.setTarget(targetRotation);
        mRotationTweener.setInitial(mRotation);
        mRotationTweener.setDuration(duration);
        mRotationTweener.reset();
    }

    void SFMLCamera::easeZoomFactor(float targetZoomFactor, float duration)
    {
        mZoomTweener.setTarget(targetZoomFactor);
        mZoomTweener.setInitial(mRotation);
        mZoomTweener.setDuration(duration);
        mZoomTweener.reset();
    }

    void SFMLCamera::shake(float duration, float radius, eShakeAxis axis)
    {
        mShaking = true;
        mShakeDuration = duration;
        mShakeAccumulator = 0.0f;
        mShakeAxis = axis;
        mShakeOffset[0] = 0.0f;
        mShakeOffset[1] = 0.0f;
        mShakeRadius = radius;
        mShakeRadiusBegin = radius;
        mShakeAngle = utilities::Random::instance().randomRange(0.f, 360.f); 

        updateScreenShake();
    }

    void SFMLCamera::updateScreenShake()
    {
        mShakeOffset[0] = std::sin(mShakeAngle) * mShakeRadius;
        mShakeOffset[1] = std::cos(mShakeAngle) * mShakeRadius;

        float cameraX = mCentre[0] + mShakeOffset[0];
        float cameraY = mCentre[1] + mShakeOffset[1];

        if (mShakeAxis == eShakeAxis::SHAKEAXIS_X)
            mSFMLView.setCenter(cameraX, mCentre[1]);
        else if (mShakeAxis == eShakeAxis::SHAKEAXIS_Y)
            mSFMLView.setCenter(mCentre[0], cameraY);
        else if (mShakeAxis == eShakeAxis::SHAKEAXIS_XY)
            mSFMLView.setCenter(cameraX, cameraY);
    }

    sf::View SFMLCamera::getSFMLView() const
    {
        return mSFMLView;
    }

}}
