#pragma once
#include <vector>
#include <unordered_set>
#include "Action.h"
#include "GameDefinition.h"


class Object;


// �¼�id
class EventID
{
public:
	uint32_t	type;
	DelegateID	delegate_id;

	EventID() {
		type = 0;
	}
	EventID(const uint32_t t, const DelegateID& id) {
		type = t;
		delegate_id = id;
	}

	~EventID() {
		clear();
	}

	EventID& operator = (const EventID& val) {
		this->type = val.type;
		this->delegate_id = val.delegate_id;
		return *this;
	}

	bool operator == (const EventID& val) const {
		if (this->type == val.type &&
			this->delegate_id == val.delegate_id)
		{
			return true;
		}
		return false;
	}

	void clear() {
		type = 0;
		delegate_id.clear();
	}
};

// ������¼�
struct stEnteredEvent
{
	// �¼�Ҫ��ӵ���Ŀ�����
	std::shared_ptr<Object>	target_obj;
	// �ص��������ڶ���
	// ��ǰ����Ϊ��ʱ�������ܰ󶨶�����
	std::shared_ptr<Object>	self_obj;

	EventID						id;
	std::shared_ptr<Delegate>	del;
};

// �뿪���¼�
struct stLeavedEvent
{
	// �¼����ڵ�Ŀ�����
	std::shared_ptr<Object>	target_obj;
	// �ص��������ڶ���
	std::shared_ptr<Object>	self_obj;

	EventID						id;
};

namespace std
{
	template<>
	struct hash<EventID>
	{
		size_t operator()(const EventID& s) const noexcept
		{
			return hash<decltype(s.type)>()(s.type) +
				hash<decltype(s.delegate_id)>()(s.delegate_id);
		}
	};
}


// �¼�����
class GEvent
{
public:
	GEvent();

	~GEvent();

	// ����¼�
	template<typename ... _Types, typename _E, typename _F>
	std::shared_ptr<Delegate> AddEvent(const _E id, _F&& f) {
		auto new_event = std::make_shared<Delegate>();
		new_event->bind<_Types...>(f);
		EventEnter((uint32_t)id, new_event, nullptr);
		return new_event;
	}


	template<typename ... _Types,typename _E, typename _F, typename _C>
	std::shared_ptr<Delegate> AddEvent(const _E id, _F&& f, const std::shared_ptr<_C>& obj) {
		// �¼��������̳� Object
		static_assert(std::is_base_of<Object, _C>::value,
			"The event object must inherit Object!");

		auto new_event = std::make_shared<Delegate>();
		new_event->bind<_Types...>(f, obj.get());
		EventEnter((uint32_t)id, new_event, obj);
		return new_event;
	}

	// �㲥�¼�
	template<typename ... _Types,typename _E>
	void BrocastEvent(const _E id, _Types..._Agrs) {

		HandleEvent();

		auto found = m_all_event.find((uint32_t)id);
		if (found != m_all_event.end())
		{
			// ������¼�
			auto atn = found->second;
			// ��ֹ�������¼������ڼ䣬Action ������
			atn->Call<_Types...>(_Agrs...);
		}
	}

	// �Ƴ��¼�
	template<typename ... _Types, typename _E, typename _F>
	void RemoveEvent(const _E id, _F&& f) {
		EventLeave((uint32_t)id, DelegateID(DEL_PVOID(&f), nullptr), nullptr);
	}

	template<typename ... _Types, typename _E, typename _F, typename _C>
	void RemoveEvent(const _E id, _F&& f, const std::shared_ptr<_C>& obj) {
		// �¼��������̳� Object
		static_assert(std::is_base_of<Object, _C>::value, 
			"The event object must inherit Object!");

		EventLeave((uint32_t)id, DelegateID(DEL_PVOID(&f), obj.get()), obj);
	}




private:
	void Clear();

	void EventEnter(const uint32_t id, const std::shared_ptr<Delegate>& del, const std::shared_ptr<Object>& obj);
	void EventLeave(const uint32_t id, const DelegateID& del_id, const std::shared_ptr<Object>& obj);

	void AddEventByDelegate(const uint32_t id, const std::shared_ptr<Delegate>& del, const std::shared_ptr<Object>& obj);

	void RemoveEventByDelegateID(const uint32_t id, const DelegateID& del_id, const std::shared_ptr<Object>& obj);

	// �����¼�
	void HandleEvent();

private:
	// ��ӵ��¼�
	std::unordered_map<uint32_t,std::shared_ptr<Action>>	m_all_event;

	std::queue<stEnteredEvent>	m_event_enter;
	std::queue<stLeavedEvent>	m_event_leave;



private:


private:
	// ������������ע����¼�
	// ��������ʱ���¼�����ʧЧ
	std::unordered_map<EventID, std::shared_ptr<Delegate>>	m_registered_event;

	friend class EventSystem;
	friend class Object;
};

#ifdef COMPILE_INT_TO_STR
#define COMPILE_TO_STR(_str) #_str
#define COMPILE_INT_TO_STR(_num) COMPILE_TO_STR(_num)
#endif

// ����¼�
// �¼������쳣ʱ���������
#define MARK_EVENT ->m_code_path=__FILE__ ":" COMPILE_INT_TO_STR(__LINE__)