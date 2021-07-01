#pragma once
#include "ObjectRef.h"
#include "ObjectFactory.h"

class Object;

template<typename T>
class ObjectRegisterAction
{
public:

	ObjectRegisterAction() {
		// Win测试获取对象名正常
		// 如Linux无法获取正确的对象名，请区分创建
 		ObjectRef::Instance().RegisterObject(((&typeid(T))->name() + 6), [](const bool from_pool)->std::shared_ptr<Object> {
 			auto obj = ObjectFactory::InternalCreate<T>(from_pool);
 			return obj;
 			});
	}

};


#define REGOBJECT(T) ObjectRegisterAction<T> ObjectRef_##T;