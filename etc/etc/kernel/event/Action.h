#pragma once
#include <unordered_map>
#include <memory>
#include <queue>
#include "Delegate.h"
#include "GameDefinition.h"

// ���ں���ͳһ����
class Action
{
public:

	// ��Ӻ���
	void Increase(const std::shared_ptr<Delegate>& del) {
		m_delegate_enter.push(del);
	}
	// �Ƴ�����
	void Remove(const DelegateID& id) {
		m_delegate_leave.push(id);
	}
	// ����
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
		// ��ʼ�����¼�
		for (auto& item : m_all_delegate)
		{
			if (auto func = item.second.lock())
			{
				
				try {
					func->call<_Types...>(_Agrs...);
				}
				catch (std::exception & e) {
					LOG_ERROR("[{}] ���ú������ִ���!({})", func->m_code_path, e.what());
				}
				catch (...) {
					LOG_ERROR("[{}] ���ú������ִ���!(δ֪����)", func->m_code_path);
				}
			}
			else {
				Remove(item.first);
			}
		}
	}

private:
	std::unordered_map<DelegateID, std::weak_ptr<Delegate>>	m_all_delegate;

	// ��Ҫ����ĺ���
	std::queue<std::weak_ptr<Delegate>>		m_delegate_enter;
	// ��Ҫ�뿪�ĺ���
	std::queue<DelegateID>					m_delegate_leave;
};