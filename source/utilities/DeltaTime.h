#ifndef _DELTATIME_H
#define _DELTATIME_H

#include <vector>
#include <chrono>

using namespace std::chrono;

#define DELTA_CACHE_SIZE 40

class DeltaTime
{
public:
	static DeltaTime& Instance();

	void Start();
	void Tick();

	float GetDelta()          const { return m_Delta; }
	float GetTimeSinceStart() const;

private:
	DeltaTime();
	~DeltaTime();

protected:
	float							  m_Delta;
	std::vector<float>				  m_DeltaCache;
	high_resolution_clock			  m_Clock;
	high_resolution_clock::time_point m_TickTime;
	high_resolution_clock::time_point m_StartTime;
};

#define Delta DeltaTime::Instance().GetDelta()
#define Time  DeltaTime::Instance().GetTimeSinceStart()

#endif // _DELTATIME
