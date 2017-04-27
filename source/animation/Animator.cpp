#include "Animator.h"
#include "../utilities/DeltaTime.h"

namespace liquid {
namespace animation {

    Animator::Animator()
    {
        mAnimationMode = eAnimationMode::ANIMATION_DEFAULT;
        mAnimationDirection = eAnimationDirection::DIRECTION_FORWARD;
        mDefaultAnimation = "";
        mCurrentAnimation = "";
        mDefaultBeginFrame = -1;
        mDefaultEndFrame = -1;
        mCurrentFrame = 0;
        mBeginFrame = 0;
        mEndFrame = 0;
    }

    Animator::Animator(AnimationParser animationParser)
    {
        for (auto anim : animationParser.getAnimationTable())
        {
            insertAnimation(anim.first, anim.second);
            mCurrentAnimation = anim.first;
        }

        mAnimationMode = eAnimationMode::ANIMATION_DEFAULT;
        mAnimationDirection = eAnimationDirection::DIRECTION_FORWARD;
        mDefaultAnimation = "";
        mDefaultBeginFrame = -1;
        mDefaultEndFrame = -1;
        mCurrentFrame = 0;
        mBeginFrame = 0;
        mEndFrame = (mAnimationTable[mCurrentAnimation].size() - 1);

        updateFrame(getAnimation(0)[0]);
    }

    Animator::~Animator()
    {}

    void Animator::update()
    {
        AnimationFrame& currentFrame = mAnimationTable[mCurrentAnimation][mCurrentFrame];

        if (currentFrame.getFrameDelay() >= 0.0f)
            mAccumulator += utilities::DELTA;

        if (mAccumulator >= currentFrame.getFrameDelay())
        {
            mAccumulator -= currentFrame.getFrameDelay();

            if (mAnimationMode == eAnimationMode::ANIMATION_DEFAULT)
                mCurrentFrame++;
            else if (mAnimationMode == eAnimationMode::ANIMATION_ONCE)
                mCurrentFrame++;
            else if (mAnimationMode == eAnimationMode::ANIMATION_REVERSE)
                mCurrentFrame--;
            else if (mAnimationMode == eAnimationMode::ANIMATION_PINGPONG)
            {
                if (mAnimationDirection == eAnimationDirection::DIRECTION_FORWARD)
                    mCurrentFrame++;
                else
                    mCurrentFrame--;
            }

            if (mAnimationMode == eAnimationMode::ANIMATION_DEFAULT && mCurrentFrame > mEndFrame)
                mCurrentFrame = mBeginFrame;
            else if (mAnimationMode == eAnimationMode::ANIMATION_REVERSE && mCurrentFrame < mBeginFrame)
                mCurrentFrame = mEndFrame;
            else if (mAnimationMode == eAnimationMode::ANIMATION_ONCE && mCurrentFrame > mEndFrame)
            {
                mCurrentFrame = mEndFrame;
                if (mDefaultAnimation != "")
                    transformAnimation(mDefaultAnimation, mDefaultBeginFrame, mDefaultEndFrame);

                return;
            }
            else if (mAnimationMode == eAnimationMode::ANIMATION_PINGPONG)
            {
                if (mAnimationDirection == eAnimationDirection::DIRECTION_FORWARD && mCurrentFrame > mEndFrame)
                    mAnimationDirection = eAnimationDirection::DIRECTION_BACKWARD;
                else if (mAnimationDirection == eAnimationDirection::DIRECTION_BACKWARD && mCurrentFrame < mBeginFrame)
                    mAnimationDirection = eAnimationDirection::DIRECTION_FORWARD;
            }

            updateFrame(mAnimationTable[mCurrentAnimation][mCurrentFrame]);
        }
    }

    void Animator::insertAnimationFrame(std::string name, AnimationFrame& frame)
    {
        mAnimationTable[name].push_back(frame);
    }

    void Animator::removeAnimationFrame(std::string name, int32_t index)
    {
        if (mAnimationTable.find(name) != mAnimationTable.end())
        {
            mAnimationTable[name].erase(mAnimationTable[name].begin() + index);
        }
    }

    void Animator::insertAnimation(std::string name, Animation animation)
    {
        if (mAnimationTable.find(name) == mAnimationTable.end())
        {
            mAnimationIndexer[mAnimationTable.size()] = name;
            mAnimationTable[name] = animation;
        }
    }

    void Animator::removeAnimation(std::string name)
    {
        AnimationTable::iterator it;
        if ((it = mAnimationTable.find(name)) != mAnimationTable.end())
            mAnimationTable.erase(it);
    }

    void Animator::removeAnimation(int32_t index)
    {
        if (index >= 0 && index < mAnimationTable.size())
            mAnimationTable.erase(mAnimationIndexer[index]);
    }

    void Animator::transformAnimation(std::string name, int32_t beginFrame, int32_t endFrame)
    {
        if (mAnimationTable.find(name) == mAnimationTable.end())
            return;

        eAnimationMode mode = eAnimationMode::ANIMATION_DEFAULT;
        bool defaultBounds = (beginFrame == -1 && endFrame == -1);
        int32_t splitString = name.find_first_of(":");
        std::string animName = name.substr(0, splitString);
        std::string animMode;

        if (splitString != -1)
        {
            animMode = name.substr(splitString + 1);
            std::transform(animMode.begin(), animMode.end(), animMode.begin(), ::tolower);

            if (animMode == "loop")
                mode = eAnimationMode::ANIMATION_DEFAULT;
            else if (animMode == "once")
                mode = eAnimationMode::ANIMATION_ONCE;
            else if (animMode == "pingpong")
                mode = eAnimationMode::ANIMATION_PINGPONG;
            else if (animMode == "reverse")
                mode = eAnimationMode::ANIMATION_REVERSE;
        }
        else
            animMode = "";

        if (defaultBounds == true)
        {
            beginFrame = 0;
            endFrame = getAnimation(animName).size() - 1;
        }

        if (animName == mCurrentAnimation && (beginFrame == mBeginFrame && endFrame == mEndFrame))
            return;

        mBeginFrame = beginFrame;
        mEndFrame = endFrame;
        mCurrentAnimation = animName;
        mCurrentFrame = beginFrame;

        (animMode == "") ? mAnimationMode = eAnimationMode::ANIMATION_DEFAULT :
                           mAnimationMode = mode;

        updateFrame(mAnimationTable[mCurrentAnimation][mCurrentFrame]);
    }

    void Animator::transformAnimationDefault(std::string name, int32_t beginFrame, int32_t endFrame)
    {
        mDefaultBeginFrame = beginFrame;
        mDefaultEndFrame = endFrame;
        mDefaultAnimation = name;
    }

    void Animator::transformAnimationMode(eAnimationMode mode)
    {
        mAnimationMode = mode;
    }

    void Animator::setVerticesPtr(std::array<liquid::utilities::Vertex2*, 4> vertices)
    {
        mVerticesPtr = vertices;
        mVerticesSet = true;

        updateFrame(getAnimation(mCurrentAnimation)[mCurrentFrame]);
    }

    const std::array<liquid::utilities::Vertex2*, 4>& Animator::getVerticesPtr() const
    {
        return mVerticesPtr;
    }

    const bool Animator::getVerticesSet() const
    {
        return mVerticesSet;
    }

    Animation& Animator::getAnimation(int32_t index)
    {
        if (mAnimationIndexer.find(index) != mAnimationIndexer.end())
            return getAnimation(mAnimationIndexer[index]);

        return Animation();
    }

    Animation& Animator::getAnimation(std::string name)
    {
        if (mAnimationTable.find(name) != mAnimationTable.end())
            return mAnimationTable[name];

        return Animation();
    }

    const Animator::eAnimationMode Animator::getAnimationMode() const
    {
        return mAnimationMode;
    }

    const Animator::eAnimationDirection Animator::getAnimationDirection() const
    {
        return mAnimationDirection;
    }

    const std::string Animator::getDefaultAnimation() const
    {
        return mDefaultAnimation;
    }

    const std::string Animator::getCurrentAnimation() const
    {
        return mCurrentAnimation;
    }

    const int32_t Animator::getDefaultBeginFrame() const
    {
        return mDefaultBeginFrame;
    }

    const int32_t Animator::getDefaultEndFrame() const
    {
        return mDefaultEndFrame;
    }

    const int32_t Animator::getBeginFrame() const
    {
        return mBeginFrame;
    }

    const int32_t Animator::getEndFrame() const
    {
        return mEndFrame;
    }

    const int32_t Animator::getCurrentFrame() const
    {
        return mCurrentFrame;
    }

    void Animator::updateFrame(AnimationFrame frame)
    {
        if (mVerticesSet == true)
        {
            float positionX = mVerticesPtr[0]->getPosition()[0];
            float positionY = mVerticesPtr[0]->getPosition()[1];
            float width = frame.getTexCoord2()[0] - frame.getTexCoord1()[0];
            float height = frame.getTexCoord3()[1] - frame.getTexCoord2()[1];

            mVerticesPtr[0]->setTexCoord(frame.getTexCoord1());
            mVerticesPtr[1]->setTexCoord(frame.getTexCoord2());
            mVerticesPtr[2]->setTexCoord(frame.getTexCoord3());
            mVerticesPtr[3]->setTexCoord(frame.getTexCoord4());

            mVerticesPtr[0]->setPosition(positionX, positionY);
            mVerticesPtr[1]->setPosition(positionX + width, positionY);
            mVerticesPtr[2]->setPosition(positionX + width, positionY + height);
            mVerticesPtr[3]->setPosition(positionX, positionY + height);
        }
    }

}}
