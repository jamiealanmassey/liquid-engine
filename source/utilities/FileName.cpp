#include "Filename.h"

FileName::FileName(std::string full_path)
{
	static std::string delims = "\\/";

	// Get path
	size_t pos = full_path.find_last_of(delims);
	m_Path	   = full_path.substr(0, pos + 1);

	// Get filename & extension
	size_t pos2 = full_path.find_last_of('.');
	m_Filename  = full_path.substr(pos + 1, (pos2 - pos - 1));
	m_Extension = full_path.substr(pos2 + 1);
}
