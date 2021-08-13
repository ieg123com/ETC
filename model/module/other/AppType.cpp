#include "AppType.h"


namespace Model
{
	EAppType Model::ToAppType(const std::string& str) {
		if (str == "Manager")return EAppType::Manager;
		else if (str == "Gate")return EAppType::Gate;
		else if (str == "Login")return EAppType::Login;
		else if (str == "List")return EAppType::List;
		else if (str == "Map")return EAppType::Map;
		else if (str == "Location")return EAppType::Location;
		else return EAppType::None;
	}

	bool Model::Is(const EAppType a, const EAppType b)
	{
		return (((unsigned int)a & (unsigned int)b) != 0);
	}
}