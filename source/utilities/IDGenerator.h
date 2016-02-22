#ifndef _IDGENERATOR_H
#define _IDGENERATOR_H

#include <map>
#include <string>
#include <sstream>

class IDGenerator
{
public:
	IDGenerator();
	~IDGenerator();

	static IDGenerator& Instance();

	std::string getNextID(std::string id);

protected:
	std::map<std::string, int32_t> m_IDTable;
};

#endif // _IDGENERATOR_H
