#include "ObjectFactory.h"
#include "ObjectRef.h"
#include "Object.h"

namespace Model
{

	std::shared_ptr<Object> ObjectFactory::Create(const std::string& type_name, const bool from_pool) {
		if (auto obj = InternalCreate(type_name, from_pool))
		{
			obj->Id = IdGenerator::GenId();
			Game::Event().Awake(obj);
			Game::Event().Load(obj);
			return obj;
		}
		return nullptr;
	}

	std::shared_ptr<Object> ObjectFactory::TryCreate(const std::string& type_name, const bool from_pool)
	{
		if (auto obj = InternalCreate(type_name, from_pool))
		{
			obj->Id = IdGenerator::GenId();
			Game::Event().Awake(obj);
			Game::Event().Load(obj);
			return obj;
		}
		throw std::exception(("没找到需要创建的对象 " + type_name).c_str());
	}

	std::shared_ptr<Object> ObjectFactory::CreateWithHost(const std::shared_ptr<Object>& host, const std::string& type_name, const bool from_pool)
	{
		if (auto obj = InternalCreate(type_name, from_pool))
		{
			obj->Id = IdGenerator::GenId();
			host->AddChild(obj);
			Game::Event().Awake(obj);
			Game::Event().Load(obj);
			return obj;
		}
		return nullptr;
	}

	std::shared_ptr<Object> ObjectFactory::TryCreateWithHost(const std::shared_ptr<Object>& host, const std::string& type_name, const bool from_pool)
	{
		if (auto obj = InternalCreate(type_name, from_pool))
		{
			obj->Id = IdGenerator::GenId();
			host->AddChild(obj);
			Game::Event().Awake(obj);
			Game::Event().Load(obj);
			return obj;
		}
		throw std::exception(("没找到需要创建的对象 " + type_name).c_str());
	}

	std::shared_ptr<Object> ObjectFactory::InternalCreate(const std::string& type_name, const bool from_pool)
	{
		return ObjectRef::Instance().CreateObject(type_name);
	}

}