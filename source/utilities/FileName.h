#ifndef _FILENAME_H
#define _FILENAME_H

#include <string>

class FileName
{
public:
	FileName(std::string full_path);
	~FileName() {}

	std::string getPath()      const { return m_Path;	   }
	std::string getFilename()  const { return m_Filename;  }
	std::string getExtension() const { return m_Extension; }
	std::string getFullPath()  const { return m_FullPath;  }

protected:
	std::string m_Path;
	std::string m_Filename;
	std::string m_Extension;
	std::string m_FullPath;
};

#endif // _FILENAME_H