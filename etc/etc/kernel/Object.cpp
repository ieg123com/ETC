#include "Object.h"
#include "ObjectPool.h"
#include "Game.h"
#include <atomic>


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

	Game::object_count++;
}

Object::~Object()
{
	Game::object_count--;
	Game::System.m_ObjectDebug.DeductObject(m_object_type.GetName());
}

void Object::Dispose() {
	if (IsDisposed())return;
	m_disposed = true;
	Destroy();

	Game::System.RemoveSystem(shared_from_this());
	GEvent::Clear();

	m_host.reset();
	m_obj_id = 0;


	if (m_is_from_pool == true)
	{
		// �ǴӶ������ȡ���Ķ���
		// ���ڰ�������ȥ
		Game::ObjPool.Recycle(shared_from_this());
	}
}

void Object::DebugIncreaseSelf()
{
	Game::System.m_ObjectDebug.IncreaseObject(m_object_type.GetName());
}

void Object::RefreshObjectID()
{
	static std::atomic<ObjectID> last_id = 0;
	last_id++;
	m_obj_id = last_id;
}