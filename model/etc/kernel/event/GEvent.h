/**
 * @file	GEvent.h
 * @brief	对象事件Event
 */
#pragma once
#include <vector>
#include <unordered_set>
#include "Action.h"
#include "GameDefinition.h"

namespace Model
{
	class Object;

	/** @brief 事件id*/
	class EventID
	{
	public:
		uint32_t	type;
		DelegateID	delegate_id;
		const void* self;

		EventID() {
			type = 0;
			self = nullptr;
		}
		EventID(const uint32_t t, const DelegateID& id, const void* s) {
			type = t;
			delegate_id = id;
			self = s;
		}

		~EventID() {
			clear();
		}

		EventID& operator = (const EventID& val) {
			this->type = val.type;
			this->delegate_id = val.delegate_id;
			this->self = val.self;
			return *this;
		}

		bool operator == (const EventID& val) const {
			if (this->type == val.type &&
				this->delegate_id == val.delegate_id &&
				this->self == val.self)
			{
				return true;
			}
			return false;
		}

		void clear() {
			type = 0;
			delegate_id.clear();
			self = nullptr;
		}
	};

	/** @brief 进入的事件*/
	struct stEnteredEvent
	{
		/** @brief 事件要添加到的目标对象*/
		::std::shared_ptr<Object>	target_obj;
		/**
		* @brief 回调函数所在对象。当前对象为空时，将不能绑定对象函数
		*/
		::std::shared_ptr<Object>	self_obj;

		EventID						id;
		::std::shared_ptr<Delegate>	del;
	};

	/** @brief 离开的事件*/
	struct stLeavedEvent
	{
		/** @brief 事件所在的目标对象*/
		::std::shared_ptr<Object>	target_obj;
		/** @brief 回调函数所在对象*/
		::std::shared_ptr<Object>	self_obj;

		EventID						id;
	};
}
	namespace std
	{
		template<>
		struct hash<Model::EventID>
		{
			size_t operator()(const Model::EventID& s) const noexcept
			{
				return hash<decltype(s.type)>()(s.type) +
					hash<decltype(s.delegate_id)>()(s.delegate_id) +
					hash<decltype(s.self)>()(s.self);
			}
		};
	}

namespace Model
{
	/**
	 * @brief	事件管理，用于对象事件注册与分发
	 */
	class GEvent
	{
	public:
		GEvent();

		~GEvent();

		/**
		* @brief		添加事件
		* @param[in]	id : 事件ID
		* @param[in]	f : 接收事件的函数
		* @retval	nullptr : 注册事件失败
		* @retval	Delegate : 注册事件成功
		*/
		template<typename ... _Types, typename _E, typename _F>
		std::shared_ptr<Delegate> AddEvent(const _E id, _F&& f) {
			auto new_event = std::make_shared<Delegate>();
			new_event->bind<_Types...>(f);
			EventEnter((uint32_t)id, new_event, nullptr);
			return new_event;
		}


		template<typename ... _Types, typename _E, typename _F, typename _C>
		std::shared_ptr<Delegate> AddEvent(const _E id, _F&& f, const std::shared_ptr<_C>& obj) {
			// 事件对象必须继承 Object
			static_assert(std::is_base_of<Object, _C>::value,
				"The event object must inherit Object!");

			auto new_event = std::make_shared<Delegate>();
			new_event->bind<_Types...>(f, obj.get());
			EventEnter((uint32_t)id, new_event, obj);
			return new_event;
		}

		// 广播事件
		template<typename ... _Types, typename _E>
		void BrocastEvent(const _E id, _Types..._Agrs) {

			HandleEvent();

			auto found = m_all_event.find((uint32_t)id);
			if (found != m_all_event.end())
			{
				// 有这个事件
				auto atn = found->second;
				// 防止在下面事件调用期间，Action 被销毁
				atn->Call<_Types...>(_Agrs...);
			}
		}

		// 移除事件
		template<typename ... _Types, typename _E, typename _F>
		void RemoveEvent(const _E id, _F&& f) {
			EventLeave((uint32_t)id, DelegateID(DEL_PVOID(&f), nullptr), nullptr);
		}

		template<typename ... _Types, typename _E, typename _F, typename _C>
		void RemoveEvent(const _E id, _F&& f, const std::shared_ptr<_C>& obj) {
			// 事件对象必须继承 Object
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

		// 处理事件
		void HandleEvent();

	private:
		// 添加的事件
		std::unordered_map<uint32_t, std::shared_ptr<Action>>	m_all_event;

		std::queue<stEnteredEvent>	m_event_enter;
		std::queue<stLeavedEvent>	m_event_leave;



	private:


	private:
		// 在其他对象上注册的事件
		// 自身销毁时，事件将会失效
		std::unordered_map<EventID, std::shared_ptr<Delegate>>	m_registered_event;

		friend class EventSystem;
		friend class Object;
	};

}
#ifdef COMPILE_INT_TO_STR
#define COMPILE_TO_STR(_str) #_str
#define COMPILE_INT_TO_STR(_num) COMPILE_TO_STR(_num)
#endif

/** brief 标记事件,事件发送异常时，方便查找*/
#define MARK_EVENT ->m_code_path=__FILE__ ":" COMPILE_INT_TO_STR(__LINE__)