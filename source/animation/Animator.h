#include "../utilities/Vertex2.h"
#include "../parser/Parser.h"
#include "AnimationFrame.h"
#include "AnimationDefs.h"
#include "AnimationParser.h"

namespace liquid { namespace animation {
#ifndef _ANIMATOR_H
#define _ANIMATOR_H

/**
 * \class Animator
 *
 * \ingroup Animation
 * \brief Uses the given Animation data to manipulate the attached vertices by changing the texture region
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 26/04/2017
 *
 */

class Animator
{
public:
    /// Denotes the mode of animation
    enum eAnimationMode
    {
        ANIMATION_DEFAULT = 0,
        ANIMATION_ONCE = 1,
        ANIMATION_PINGPONG = 2,
        ANIMATION_REVERSE = 3,
    };

    /// Denotes the direction of the animation
    enum eAnimationDirection
    {
        DIRECTION_FORWARD = 0,
        DIRECTION_BACKWARD = 1,
    };

public:
    /// Animator Constructor
    Animator();

    /** \brief Animator Constructor
      * \param animationParser Pre-parsed animation data to use
      */
    Animator(AnimationParser animationParser);

    /// Animator Destructor
    ~Animator();

    /// \brief Call every frame step to update the Animator, and therefore the Animation
    void update();

    /** \brief Insert a new AnimationFrame to the specified Animation
      * \param name Name of the Animation to use reprsented as an std::string
      * \param frame AnimationFrame to insert
      */
    void insertAnimationFrame(std::string name, AnimationFrame& frame);

    /** \brief Removes an AnimationFrame from the specified Animation
      * \param name Name of the Animation to use reprsented as an std::string
      * \param frame AnimationFrame to remove
      */
    void removeAnimationFrame(std::string name, int32_t index);

    /** \brief Insert a new Animation to the Animator
      * \param name Name of the Animation to add reprsented as an std::string
      * \param animation Animation to insert to the Animator
      */
    void insertAnimation(std::string name, Animation animation);

    /** \brief Removes an Animation from the Animator
      * \param name Name of the Animation to remove reprsented as an std::string
      */
    void removeAnimation(std::string name);

    /** \brief Removes an Animation from the Animator
      * \param index Index of the Animation to remove, utilised by mAnimationIndexer
      */
    void removeAnimation(int32_t index);

    /** \brief Change the currently running Animation
      * \param name Name of the Animation to switch to
      * \param beginFrame Frame index to start at
      * \param endFram Frame index to end on
      */
    void transformAnimation(std::string name, int32_t beginFrame = -1, int32_t endFrame = -1);

    /** \brief Simplistic method to change the currently running Animation
      * \param name Name of the Animation to switch to
      * \param beginFrame Frame index to start at
      * \param endFram Frame index to end on
      */
    void transformAnimationDefault(std::string name, int32_t beginFrame = -1, int32_t endFrame = -1);
    
    /** \brief Sets the eAnimationMode to use
      * \param mode Mode to switch to
      */
    void transformAnimationMode(eAnimationMode mode);

    /** \brief Assign vertices to use for traversing frames via texture coordinates
      * \param vertices Array of utilities::Vertex2 pointers
      */
    void setVerticesPtr(std::array<liquid::utilities::Vertex2*, 4> vertices);

    /// \return Gets the std::array of utilities::Vertex2 pointers
    const std::array<liquid::utilities::Vertex2*, 4>& getVerticesPtr() const;

    /// \return True if the Vertices for this Animator have been set, otherwise false
    const bool getVerticesSet() const;

    /** \brief Gets an Animation from the specified index via mAnimationIndexer
      * \param index Index of the Animation to get
      * \return Animation data of found Animation, Animation() if not found
      */
    Animation& getAnimation(int32_t index);

    /** \brief Gets an Animation from the specified name
      * \param name Name of the Animation represented by an std::string
      * \return Animation data of found Animation, Animation() if not found
      */
    Animation& getAnimation(std::string name);

    /// \return Gets the current Animation mode
    const eAnimationMode getAnimationMode() const;

    /// \return Gets the current Animation direction
    const eAnimationDirection getAnimationDirection() const;

    /// \return Gets the name of the default Animation as a std::string
    const std::string getDefaultAnimation() const;

    /// \return Gets the name of the current Animation as a std::string
    const std::string getCurrentAnimation() const;

    /// \return Gets the mDefaultBeginFrame value to start at
    const int32_t getDefaultBeginFrame() const;

    /// \return Gets the mDefaultEndFrame value to end with
    const int32_t getDefaultEndFrame() const;

    /// \return Gets the beginning frame of the Animation
    const int32_t getBeginFrame() const;

    /// \return Gets the end frame of the Animation
    const int32_t getEndFrame() const;

    /// \return Gets the current frame index of the Animation
    const int32_t getCurrentFrame() const;

protected:
    /** \brief Uses the given frame to update the texture coordinates of the Vertices
      * \param frame Next frame to use for the Animation
      */
    void updateFrame(AnimationFrame frame);

protected:
    AnimationIndexer    mAnimationIndexer;   ///< Indexing data to map a number to each Animation stored in mAnimationTable
    AnimationTable      mAnimationTable;     ///< Table storage of key-pair values to Animation data where (std::string, Animation)
    eAnimationMode      mAnimationMode;      ///< Denotes the mode of the animation
    eAnimationDirection mAnimationDirection; ///< Denotes the direction of the animation
    std::string         mDefaultAnimation;   ///< Name of the default Animation as std::string
    std::string         mCurrentAnimation;   ///< Name of the current Animation as std::string
    int32_t             mDefaultBeginFrame;  ///< Default beginning frame
    int32_t             mDefaultEndFrame;    ///< Default end frame
    int32_t             mBeginFrame;         ///< Beginning frame of the current Animation
    int32_t             mEndFrame;           ///< Ending frame of the current Animation
    int32_t             mCurrentFrame;       ///< Current frame index of the Animation
    float               mAccumulator;        ///< Accumulating time for the Animator in milliseconds

protected:
    std::array<liquid::utilities::Vertex2*, 4> mVerticesPtr; ///< Pointer to array of vertices, usually for transforming Renderable data
    bool                                       mVerticesSet; ///< Denotes if the Vertices pointer was ever set
};

#endif // _ANIMATOR_H
}}
