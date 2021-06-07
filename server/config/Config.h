#pragma once
#include <stdint.h>
#include <memory>
#include <unordered_map>
#include <string>
#include "json/ejson.h"
#include "ServerLog.h"


using ConfigId = int64_t;
using cJson = neb::CJsonObject;


class Config:
	public std::enable_shared_from_this<Config>
{
	friend class Category;
	
	virtual bool Parse(const cJson& json) = 0;
public:
	ConfigId	Id;
};

class Category
{
	using t_ptr = std::shared_ptr<Config>;
public:
	template<typename T>
	bool Load(const char* path) {
		ConfigPath = path;
		ejson json;
		if (!json.open(path))
		{
			return false;
		}
		size_t size = json.GetArraySize();
		for (int i = 0; i < size; ++i)
		{
			t_ptr cfg = std::make_shared<T>();
			if (!cfg->Parse(json[i])) {
				LOG_ERROR("加载配置出错!({})", path);
				return false;
			}
			Insert(cfg);
		}
		return true;
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

	void Remove(const ConfigId id) {
		AllConfig.erase(id);
	}


private:
	// 所有配置
	std::unordered_map<ConfigId, t_ptr>	AllConfig;

	std::string	ConfigPath;
};




class ConfigComponent
{
public:

	static ConfigComponent& Instance() {
		static ConfigComponent self;
		return self;
	}

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
	
private:

	std::unordered_map<const type_info*, std::shared_ptr<Category>> Data;


};
