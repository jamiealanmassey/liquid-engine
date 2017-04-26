#include "../utilities/Vertex2.h"
#include "../parser/Parser.h"
#include "AnimationFrame.h"
#include "AnimationDefs.h"
#include "AnimationParser.h"

namespace liquid { namespace animation {
#ifndef _ANIMATOR_H
#define _ANIMATOR_H

class Animator
{
public:
    enum eAnimationMode
    {
        ANIMATION_DEFAULT = 0,
        ANIMATION_ONCE = 1,
        ANIMATION_PINGPONG = 2,
        ANIMATION_REVERSE = 3,
    };

    enum eAnimationDirection
    {
        DIRECTION_FORWARD = 0,
        DIRECTION_BACKWARD = 1,
    };

public:
    // TODO: Pass and use AnimationParser
    Animator();
    Animator(AnimationParser animationParser);
    ~Animator();

    void update();

    void insertAnimationFrame(std::string name, AnimationFrame& frame);
    void removeAnimationFrame(std::string name, int32_t index);

    void insertAnimation(std::string name, Animation animation);
    void removeAnimation(std::string name);
    void removeAnimation(int32_t index);

    void transformAnimation(std::string name, int32_t beginFrame = -1, int32_t endFrame = -1);
    void transformAnimationDefault(std::string name, int32_t beginFrame = -1, int32_t endFrame = -1);
    void transformAnimationMode(eAnimationMode mode);

    void setVerticesPtr(std::array<liquid::utilities::Vertex2*, 4> vertices);

    const std::array<liquid::utilities::Vertex2*, 4>& getVerticesPtr() const;
    const bool getVerticesSet() const;

    Animation& getAnimation(int32_t index);
    Animation& getAnimation(std::string name);

    const eAnimationMode getAnimationMode() const;
    const eAnimationDirection getAnimationDirection() const;
    const std::string getDefaultAnimation() const;
    const std::string getCurrentAnimation() const;
    const int32_t getDefaultBeginFrame() const;
    const int32_t getDefaultEndFrame() const;
    const int32_t getBeginFrame() const;
    const int32_t getEndFrame() const;
    const int32_t getCurrentFrame() const;

protected:
    void updateFrame(AnimationFrame frame);

protected:
    AnimationIndexer mAnimationIndexer;
    AnimationTable mAnimationTable;
    eAnimationMode mAnimationMode;
    eAnimationDirection mAnimationDirection;
    std::string mDefaultAnimation;
    std::string mCurrentAnimation;
    int32_t mDefaultBeginFrame;
    int32_t mDefaultEndFrame;
    int32_t mBeginFrame;
    int32_t mEndFrame;
    int32_t mCurrentFrame;
    float mAccumulator;

protected:
    std::array<liquid::utilities::Vertex2*, 4> mVerticesPtr; ///< Pointer to array of vertices, usually for transforming Renderable data
    bool                                       mVerticesSet; ///< Denotes if the Vertices pointer was ever set
};

#endif // _ANIMATOR_H
}}
