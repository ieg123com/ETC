#include "AppType.h"


namespace Model
{
	EAppType Model::ToAppType(const std::string& str) {
		if (str == "Watcher")return EAppType::Watcher;
		else if (str == "Gate")return EAppType::Gate;
		else if (str == "Login")return EAppType::Login;
		else if (str == "List")return EAppType::List;
		else if (str == "Map")return EAppType::Map;
		else if (str == "Location")return EAppType::Location;
		else if (str == "AllServer")return EAppType::AllServer;
		else return EAppType::None;
	}

	bool Model::Is(const EAppType a, const EAppType b)
	{
		return (((unsigned int)a & (unsigned int)b) != 0);
	}
}