#pragma once
#include <stdint.h>
#include <memory>
#include <unordered_map>
#include <string>
#include "etc/etc.h"
#include "other/json/cJsonHelper.h"
#include "log/ServerLog.h"



using ConfigId = int64_t;
using Json = cJSON*;


class Config:
	public std::enable_shared_from_this<Config>
{
	friend class Category;
	
	virtual bool Parse(Json json) = 0;
public:
	ConfigId	Id;

	template<typename T>
	std::shared_ptr<T> To() {
		return std::dynamic_pointer_cast<T>(shared_from_this());
	}
};

class Category
{
	using t_ptr = std::shared_ptr<Config>;
public:
	template<typename T>
	bool Load(const char* path) {
		ConfigPath = path;
		Json json = cJSON_ParseFromPath(path);
		if (!json)
		{
			return false;
		}
		bool ret = true;
		Json new_json = json->child;
		while(new_json = cJSON_Next(new_json))
		{
			t_ptr cfg = std::make_shared<T>();
			if (!cfg->Parse(new_json)) {
				LOG_ERROR("加载配置出错!({})", path);
				ret = false;
				break;
			}
			Insert(cfg);
		}
		cJSON_Delete(json);
		return ret;
	}


	void Insert(t_ptr cfg) {
		if (!AllConfig.insert(std::make_pair(cfg->Id, cfg)).second)
		{
			LOG_WARN("加载配置时,发现重复ID ({})", 
				(const char*)"null");
		}
	}

	t_ptr Get(const ConfigId id) {
		auto found = AllConfig.find(id);
		if (found == AllConfig.end())
		{
			return nullptr;
		}
		return found->second;
	}

	const std::unordered_map<ConfigId, t_ptr>& GetAllConfig() const {
		return AllConfig;
	}

	void Remove(const ConfigId id) {
		AllConfig.erase(id);
	}


private:
	// 所有配置
	std::unordered_map<ConfigId, t_ptr>	AllConfig;

	std::string	ConfigPath;
};



namespace Model
{
	class ConfigComponent :
		public Component
	{
	public:
		static ConfigComponent* Instance;

		template<typename T>
		bool Load(const char* path) {
			auto category = std::make_shared<Category>();
			if (!category->Load<T>(path))
			{
				return false;
			}
			Data.erase(&typeid(T));
			Data.insert(std::make_pair(&typeid(T), category));
			return true;
		}

		template<typename T>
		std::shared_ptr<T> Get(const ConfigId id) {
			auto found = Data.find(&typeid(T));
			if (found == Data.end())
			{
				return nullptr;
			}
			if (auto cfg = found->second->Get(id))
			{
				return std::dynamic_pointer_cast<T>(cfg);
			}
			return nullptr;
		}

		template<typename T>
		const std::unordered_map<ConfigId, std::shared_ptr<Config>>& GetAllConfig()const {
			static std::unordered_map<ConfigId, std::shared_ptr<Config>> ret_null;
			auto found = Data.find(&typeid(T));
			if (found == Data.end())
			{
				return ret_null;
			}
			return found->second->GetAllConfig();
		}

	private:

		std::unordered_map<const type_info*, std::shared_ptr<Category>> Data;


	};
}

