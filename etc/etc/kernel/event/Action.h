#pragma once
#include <unordered_map>
#include <memory>
#include <queue>
#include "Delegate.h"
#include "GameDefinition.h"

// 用于函数统一管理
class Action
{
public:

	// 添加函数
	void Increase(const std::shared_ptr<Delegate>& del) {
		m_delegate_enter.push(del);
	}
	// 移除函数
	void Remove(const DelegateID& id) {
		m_delegate_leave.push(id);
	}
	// 调用
	template<typename ... _Types>
	void Call(_Types..._Agrs){
		while (m_delegate_enter.empty() == false)
		{
			auto temp = std::move(m_delegate_enter.front());
			m_delegate_enter.pop();
			if(auto dge = temp.lock())
				m_all_delegate.insert(std::make_pair(dge->id(), temp));
		}

		while (m_delegate_leave.empty() == false)
		{
			auto id = m_delegate_leave.front();
			m_delegate_leave.pop();
			m_all_delegate.erase(id);
		}
		// 开始调用事件
		for (auto& item : m_all_delegate)
		{
			if (auto func = item.second.lock())
			{
				
				try {
					func->call<_Types...>(_Agrs...);
				}
				catch (std::exception & e) {
					LOG_ERROR("[{}] 调用函数出现错误!({})", func->m_code_path, e.what());
				}
				catch (...) {
					LOG_ERROR("[{}] 调用函数出现错误!(未知错误)", func->m_code_path);
				}
			}
			else {
				Remove(item.first);
			}
		}
	}

private:
	std::unordered_map<DelegateID, std::weak_ptr<Delegate>>	m_all_delegate;

	// 将要进入的函数
	std::queue<std::weak_ptr<Delegate>>		m_delegate_enter;
	// 将要离开的函数
	std::queue<DelegateID>					m_delegate_leave;
};