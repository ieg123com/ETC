#include "Object.h"
#include "ObjectPool.h"
#include "Game.h"
#include "GlobalData.h"
#include "IdGenerator.h"
#include <atomic>

namespace Model
{
	Object::Object()
	{
		m_is_from_pool = false;
		m_disposed = false;

		Game::object_count()++;
	}

	Object::~Object()
	{
		Game::object_count()--;
		if (Game::Stopping == false)
			Game::System().m_ObjectDebug.DeductObject(m_object_type.GetName());
	}


	void Object::Dispose() {
		if (IsDisposed())return;
		m_disposed = true;

		// 清理Children对象
		auto children = std::move(Children);
		for (auto& item : children)
		{
			item.second->Dispose();
		}
		children.clear();
		// 将自己从父对象移除
		if (m_host)m_host->RemoveChild(Self());

		// 发送销毁事件
		Game::Event().Destroy(shared_from_this());
		Game::Event().RemoveObject(shared_from_this());

		m_host.reset();
		m_instance_id = 0;
		Id = 0;


		if (m_is_from_pool == true)
		{
			// 是从对象池中取出的对象
			// 现在把它还回去
			Game::ObjPool().Recycle(shared_from_this());
		}
	}

	void Object::DebugIncreaseSelf()
	{
		Game::System().m_ObjectDebug.IncreaseObject(m_object_type.GetName());
	}

	void Object::__RefreshInstanceId()
	{
		m_instance_id = IdGenerator::Instance->GenerateInstanceId();
	}
}