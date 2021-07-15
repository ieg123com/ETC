/**
 * @file	Delegate.h
 * @brief	用于函数封装
 */
#pragma once
#include <functional>

#if _WIN64
#define DEL_PVOID(p) (void*)*(unsigned long long*)(p)
#else
#define DEL_PVOID(p) (void*)*(unsigned int*)(p)
#endif


namespace Model
{

	/** @brief 函数ID*/
	class DelegateID
	{
	public:
		const void* method;
		const void* object;
		long long	object_id;

		DelegateID() {
			method = nullptr;
			object = nullptr;
			object_id = 0;
		}

		DelegateID(const void* md, const void* obj) {
			method = md;
			object = obj;
			object_id = 0;
		}

		~DelegateID() {
			clear();
		}

		DelegateID& operator = (const DelegateID& val) {
			method = val.method;
			object = val.object;
			object_id = val.object_id;
			return *this;
		}

		bool operator == (const DelegateID& val) const {
			if (method == val.method &&
				object == val.object &&
				object_id == val.object_id)
			{
				return true;
			}
			return false;
		}

		void clear() {
			method = nullptr;
			object = nullptr;
			object_id = 0;
		}
	};
}
/** @internal */
namespace std
{
	template<>
	struct hash<Model::DelegateID>
	{
		size_t operator()(const Model::DelegateID& s) const noexcept
		{
			return hash<decltype(s.method)>()(s.method) +
				hash<decltype(s.object)>()(s.object) +
				hash<decltype(s.object_id)>()(s.object_id);
		}
	};
}

namespace Model
{
	/**
	 * @brief	函数封装，用于记录各种参数的函数。可以用于事件通知，线程不安全
	 */
	class Delegate
	{
	public:
		Delegate() {
			m_type = nullptr;
			m_func = nullptr;
			m_code_path = "null";
		}

		Delegate(Delegate&& val) noexcept {
			m_id = val.m_id;
			m_func = val.m_func;
			m_type = val.m_type;
			m_code_path = val.m_code_path;
			m_close = ::std::move(val.m_close);
			val.m_func = nullptr;
			val.m_type = nullptr;
			val.m_close = nullptr;
			val.m_code_path = "null";
		}

		template<typename ... _Types, typename _F>
		Delegate(_F&& f) {
			bind<_Types...>(f);
		}

		template<typename ... _Types, typename _F, typename _C>
		Delegate(_F&& f, _C&& c) {
			bind<_Types...>(f, c);
		}

		~Delegate() {
			clear();
		}

		void operator = (Delegate&& val) noexcept {
			m_id = val.m_id;
			m_func = val.m_func;
			m_type = val.m_type;
			m_code_path = val.m_code_path;
			m_close = ::std::move(val.m_close);
			val.m_func = nullptr;
			val.m_type = nullptr;
			val.m_close = nullptr;
			val.m_code_path = "null";
		}


		template< typename ... _Types, typename _F>
		void set(_F&& f) {
			if (!empty())
			{
				clear();
			}
			m_type = &typeid(void(_Types...));
			m_func = new std::function<void(_Types...)>(f);
			m_close = std::move([this] {
				delete (std::function<void(_Types...)>*)this->m_func;
				});
		}


		template<typename _F>
		void bind(_F&& f) {
			m_id.method = DEL_PVOID(&f);
			set(std::bind(f));
		}

		template<typename _F, typename _C>
		void bind(_F&& f, _C&& c) {
			m_id.method = DEL_PVOID(&f);
			m_id.object = c;
			set(std::bind(f, c));
		}

		template<typename _A1, typename _F>
		void bind(_F&& f) {
			m_id.method = DEL_PVOID(&f);
			set<_A1>(std::bind(f, std::placeholders::_1));
		}

		template<typename _A1, typename _F, typename _C>
		void bind(_F&& f, _C&& c) {
			m_id.method = DEL_PVOID(&f);
			m_id.object = c;
			set<_A1>(std::bind(f, c, std::placeholders::_1));
		}

		template<typename _A1, typename _A2, typename _F>
		void bind(_F&& f) {
			m_id.method = DEL_PVOID(&f);
			set<_A1, _A2>(std::bind(f, std::placeholders::_1, std::placeholders::_2));
		}

		template<typename _A1, typename _A2, typename _F, typename _C>
		void bind(_F&& f, _C&& c) {
			m_id.method = DEL_PVOID(&f);
			m_id.object = c;
			set<_A1, _A2>(std::bind(f, c, std::placeholders::_1, std::placeholders::_2));
		}

		template<typename _A1, typename _A2, typename _A3, typename _F>
		void bind(_F&& f) {
			m_id.method = DEL_PVOID(&f);
			set<_A1, _A2, _A3>(std::bind(f, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}

		template<typename _A1, typename _A2, typename _A3, typename _F, typename _C>
		void bind(_F&& f, _C&& c) {
			m_id.method = DEL_PVOID(&f);
			m_id.object = c;
			set<_A1, _A2, _A3>(std::bind(f, c, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}

		template<typename _A1, typename _A2, typename _A3, typename _A4, typename _F>
		void bind(_F&& f) {
			m_id.method = DEL_PVOID(&f);
			set<_A1, _A2, _A3, _A4>(std::bind(f, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
		}

		template<typename _A1, typename _A2, typename _A3, typename _A4, typename _F, typename _C>
		void bind(_F&& f, _C&& c) {
			m_id.method = DEL_PVOID(&f);
			m_id.object = c;
			set<_A1, _A2, _A3, _A4>(std::bind(f, c, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
		}

		template<typename _A1, typename _A2, typename _A3, typename _A4, typename _A5, typename _F>
		void bind(_F&& f) {
			m_id.method = DEL_PVOID(&f);
			set<_A1, _A2, _A3, _A4, _A5>(std::bind(f, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5));
		}

		template<typename _A1, typename _A2, typename _A3, typename _A4, typename _A5, typename _F, typename _C>
		void bind(_F&& f, _C&& c) {
			m_id.method = DEL_PVOID(&f);
			m_id.object = c;
			set<_A1, _A2, _A3, _A4, _A5>(std::bind(f, c, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5));
		}



		template<typename ... _Types>
		inline void call(_Types..._Args) const {
			//if (m_type == &typeid(void(_Types...)))
			{
				(*(std::function<void(_Types...)>*)m_func)(_Args...);
			}

		}



		bool empty()const {
			return (m_func == nullptr) ? true : false;
		}

		void clear() {
			if (m_close)
			{
				m_close();
				m_close = nullptr;
			}
			m_id.clear();
			m_func = nullptr;
			m_type = nullptr;
		}

		void set_objectid(const long long id) {
			m_id.object_id = id;
		}

		const DelegateID& id()const {
			return m_id;
		}

		void Dispose() {
			if (m_close)
			{
				m_close();
				m_close = nullptr;
			}
			m_id.clear();
			m_func = nullptr;
			m_type = nullptr;
		}

		bool IsDisposed() const {
			return (m_type == nullptr);
		}

	private:
		// 自身id 可用于hash记录
		DelegateID					m_id;
		// 记录函数类型
		const type_info* m_type;
		// 记录回调函数指针
		void* m_func;
		// 记录销毁函数
		::std::function<void(void)>	m_close;
	public:
		/** @internal 用于记录注册函数调用的位置，方便Debug调试*/
		const char* m_code_path;

	};
}