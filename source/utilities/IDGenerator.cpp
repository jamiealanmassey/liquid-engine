#include "IDGenerator.h"

IDGenerator::IDGenerator()
{
}

IDGenerator::~IDGenerator()
{
}

IDGenerator& IDGenerator::Instance()
{
	static IDGenerator singleton;
	return singleton;
}

std::string IDGenerator::getNextID(std::string id)
{
	std::stringstream stream;

	if (m_IDTable.find(id) == m_IDTable.end())
	{
		m_IDTable[id] = 0;
		stream << id << m_IDTable[id];
		return stream.str();
	}

	m_IDTable[id]++;
	stream << id << m_IDTable[id];
	return stream.str();
}
