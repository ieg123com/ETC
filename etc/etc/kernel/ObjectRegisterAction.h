#pragma once
#include "ObjectRef.h"
#include "ObjectFactory.h"

class Object;

template<typename T>
class ObjectRegisterAction
{
public:

	ObjectRegisterAction() {
		// Win���Ի�ȡ����������
		// ��Linux�޷���ȡ��ȷ�Ķ������������ִ���
 		ObjectRef::Instance().RegisterObject(((&typeid(T))->name() + 6), [](const bool from_pool)->std::shared_ptr<Object> {
 			auto obj = ObjectFactory::InternalCreate<T>(from_pool);
 			return obj;
 			});
	}

};


#define REGOBJECT(T) ObjectRegisterAction<T> ObjectRef_##T;