#ifndef _LIQUIDATTRIBUTE_H
#define _LIQUIDATTRIBUTE_H

#include <iostream>
#include <string>

namespace LiquidEngine
{
	struct LiquidAttribute
	{
		std::string m_UID;
		std::string m_Value;

		int32_t toInterger() { return stoi(m_Value); }
		float   toFloat()	 { return stof(m_Value); }

		bool toBoolean() 
		{
			// Check for text conversions
			if (m_Value == "true" || m_Value == "True" || m_Value == "1")
				return true;
			else if (m_Value == "false" || m_Value == "False" || m_Value == "0")
				return false;
			else
			{
				std::cout << "Attribute " << m_UID << " could not be converted to bool" << std::endl;
				return false;
			}
		}
	};
}

#endif // _LIQUIDATTRIBUTE_H
