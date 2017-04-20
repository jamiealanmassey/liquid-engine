#include <vector>
#include <chrono>

namespace liquid { namespace utilities {
#ifndef _DELTATIME_H
#define _DELTATIME_H

/**
 * \class DeltaTime
 *
 * \ingroup Utilities
 * \brief Defines a singleton class that can be called to smooth out movement inbetween frames
 *
 * \author Jamie Massey
 * \version 2.0
 * \date 09/04/2017
 *
 */

#define DELTA_CACHE_SIZE 40

class DeltaTime
{
private:
    /// DeltaTime Constructor
    DeltaTime();

    /// DeltaTime Destructor
    ~DeltaTime();

public:
    /// \brief Start the DeltaTime
    void start();

    /** \brief Simulates a tick of the DeltaTime (in milliseconds)
      *
      * Will simulate a tick of DeltaTime by taing the current time using the 
      * mClock variable and taking away the last tick time. Then if the last X
      * amount of frames as defined by DELTA_CACHE_SIZE have become far between
      * a correction will be attempted by averaging the delta over the cache.
      */
    void tick();

    /// \return The current delta between current and last frame (in milliseconds)
    float getDelta() const;

    /// \return Time elapsed since DeltaTime::start() was called (in milliseconds)
    float getTimeSinceStart() const;

    /// \return Instance of this class (singleton)
    static DeltaTime& instance();

protected:
    float                                          mDelta;      ///< Current delta between this and last frame (in milliseconds)
    std::vector<float>                             mDeltaCache; ///< Cache of the last X frames
    std::chrono::high_resolution_clock             mClock;      ///< Clock to be accessed to ask for current time
    std::chrono::high_resolution_clock::time_point mTickTime;   ///< Tick time point of the last frame
    std::chrono::high_resolution_clock::time_point mStartTime;  ///< Start time of the DeltaTime singleton class
};

#define DELTA DeltaTime::instance().getDelta()
#define TIME DeltaTime::instance().getTimeSinceStart()

#endif // _DELTATIME_H
}}
