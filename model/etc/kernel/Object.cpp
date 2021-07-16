#include "Object.h"
#include "ObjectPool.h"
#include "Game.h"
#include "GlobalData.h"
#include <atomic>

namespace Model
{
	Object::Object()
	{
		RefreshObjectID();
		m_is_from_pool = false;
		m_disposed = false;

		CanEverAwake = false;
		CanEverStart = false;
		CanEverUpdate = false;
		CanEverLateUpdate = false;
		CanEverSecondsUpdate = false;

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
		Destroy();

		Game::System().RemoveSystem(shared_from_this());
		//GEvent::Clear();

		m_host.reset();
		m_obj_id = 0;


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

	void Object::RefreshObjectID()
	{
		m_obj_id = GlobalData::GetObjectID();
	}
}