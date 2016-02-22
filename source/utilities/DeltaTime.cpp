#include "DeltaTime.h"

DeltaTime::DeltaTime() :
	m_Delta(0.0f)
{
	m_DeltaCache.resize(DELTA_CACHE_SIZE, 0.0f);
}

DeltaTime::~DeltaTime()
{
}

DeltaTime& DeltaTime::Instance()
{
	static DeltaTime singleton;
	return singleton;
}

void DeltaTime::Start()
{
	m_TickTime = m_StartTime = m_Clock.now();
}

void DeltaTime::Tick()
{
	// Update chache
	float delta = duration_cast<duration<float, std::milli>>(m_Clock.now() - m_TickTime).count();

	m_Delta -= m_DeltaCache[0] / (float)m_DeltaCache.size();
	m_Delta += delta / (float)m_DeltaCache.size();

	copy(m_DeltaCache.begin() + 1, m_DeltaCache.end(), m_DeltaCache.begin());
	m_DeltaCache[m_DeltaCache.size() - 1] = delta;

	//Reset clock
	m_TickTime = m_Clock.now();
}

float DeltaTime::GetTimeSinceStart() const
{
	return duration_cast<duration<float, std::milli>>(m_Clock.now() - m_StartTime).count();
}