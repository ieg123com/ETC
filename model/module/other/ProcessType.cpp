#include "ProcessType.h"


namespace Model
{
	EProcessType ToProcessType(const std::string& str)
	{
		if (str == "Server")return EProcessType::Server;
		else if (str == "Robot")return EProcessType::Robot;
		else return EProcessType::None;
	}

	std::string ToString(const EProcessType tp)
	{
		switch (tp) 
		{
		case EProcessType::Server: return "Server";
		case EProcessType::Robot: return "Robot";
		default: return "None";
		}
	}


}