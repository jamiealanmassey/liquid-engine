#include "DeltaTime.h"

namespace liquid { 
namespace utilities {

    DeltaTime::DeltaTime()
    {
        mDelta = 0.0f;
        mDeltaCache.resize(DELTA_CACHE_SIZE, 0.0f);
    }

    DeltaTime::~DeltaTime()
    {}

    void DeltaTime::start()
    {
        mTickTime = mStartTime = mClock.now();
    }

    void DeltaTime::tick()
    {
        float delta = std::chrono::duration_cast<
                      std::chrono::duration<float, std::milli>>
                      (mClock.now() - mTickTime).count();

        mDelta -= mDeltaCache[0] / (float)mDeltaCache.size();
        mDelta += delta / (float)mDeltaCache.size();

        std::copy(mDeltaCache.begin() + 1, mDeltaCache.end(), mDeltaCache.begin());
        mDeltaCache[mDeltaCache.size() - 1] = delta;
        mTickTime = mClock.now();
    }

    float DeltaTime::getDelta() const
    {
        return mDelta;
    }

    float DeltaTime::getTimeSinceStart() const
    {
        return std::chrono::duration_cast<
               std::chrono::duration<float, std::milli>>
               (mClock.now() - mStartTime).count();
    }

    DeltaTime& DeltaTime::instance()
    {
        static DeltaTime instance;
        return instance;
    }

}}
