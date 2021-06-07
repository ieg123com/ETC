#pragma once
#include <unordered_map>
#include "Vector3.h"
#include "AOIDef.h"
#include "AOIObject.h"



// ��ͼaoi
// Move �����һʱ������ͳһˢ��
// Enter��Leave ������ˢ��
template<typename T>
class AOI
{
public:
	typedef void(*call_enter)(T, const std::vector<T>&);
	typedef void(*call_leave)(T, const std::vector<T>&);

	~AOI() {
		clear();
	}

	// ʵ����볡��
	AOIObject<T>* Enter(AOIObjectID id, const Vector3& vec) {
		auto obj = GetObject(id);
		if (obj != nullptr)
		{
			// ��������Ѿ����� AOI ��
			return nullptr;
		}
		else {
			// û�ҵ��������
			obj = NewObject(id);
			obj->position = vec;
		}

		AddObject(obj);

		obj->m_x_pos = m_x_axis.insert(std::make_pair(obj->position.x, obj)).first;

		// ���ö�������aoi
		obj->m_aoi = this;

		UpdateObject(obj);

		return obj;
	}

	// ʵ���ڳ������ƶ�
	bool Move(AOIObjectID id, const Vector3& vec){
		auto obj = GetObject(id);
		if (obj == nullptr)
		{
			// û�ҵ��������
			return false;
		}

		obj->position = vec;

		UpdateObjectPosition(obj);

		MarkObject(obj);

		return true;
	}

	// ʵ���뿪����
	bool Leave(AOIObjectID id){
		auto obj = GetObject(id);
		if (obj == nullptr)
		{
			// û�ҵ��������
			return false;
		}

		m_x_axis.erase(obj->m_x_pos);
		obj->m_x_pos = nullptr;
		obj->m_aoi = nullptr;

		RemoveObject(obj);
		UnMarkObject(obj);

		UpdateObject(obj);
		
		// ɾ���������
		DeleteObject(obj);
		return true;
	}



	// ����ͬ�Ķ���
	bool IsHaveSameObject(const AOIObject<T>* obj) const {
		return (m_objs.find(obj->m_id) != m_objs.end());
	}

	// ���±�ǹ��Ķ���
	void UpdateMarkedObject() {
		for (auto& item : m_changed_obj) {
			UpdateObject(item.second);
		}
		m_changed_obj.clear();
	}

	// ���������뿪�¼�
	void clear() {
		m_x_axis.clear();
		m_changed_obj.clear();
		m_enter_notify.clear();
		m_leave_notify.clear();
		for (auto& item : m_objs) {
			DeleteObject(item.second);
		}
		m_objs.clear();
	}
protected:
	// ȡ��һ������
	AOIObject<T>* GetObject(const AOIObjectID id)const {
		auto found = m_objs.find(id);
		if (found == m_objs.end())
		{
			return nullptr;
		}
		return found->second;
	}

public:
	// ��һ����Χ�ڣ�ȡ������ʵ��
	void GetObjectsInRange(const AOIObjectID id, std::unordered_map<AOIObjectID, AOIObject<T>*>& set) const {
		if (auto obj = GetObject(id))
		{
			GetObjectsInRange(obj, set, obj->m_insight_range);
		}
	}
	void GetObjectsInRange(const AOIObjectID id, std::unordered_map<AOIObjectID, AOIObject<T>*>& set, const uint32_t range) const {
		if (auto obj = GetObject(id))
		{
			GetObjectsInRange(obj, set, range);
		}
	}
	void GetObjectsInRange(const AOIObject<T> * obj, std::unordered_map<AOIObjectID, AOIObject<T>*> & set) const {
		GetObjectsInRange(obj, set, obj->m_insight_range);
	}
	void GetObjectsInRange(const AOIObject<T>* obj, std::unordered_map<AOIObjectID, AOIObject<T>*>& set, const uint32_t range) const {
		if (obj->m_aoi != this)
		{
			// ʵ�岻����aoi��
			return;
		}
		static skip_list<int32_t, AOIObject<T>*>::iterator axis_iter;
		const Vector3& vec = obj->position;
		int diff = 0;

		// X ���ѯ
		// �� x �����
		if ((axis_iter = obj->m_x_pos) != m_x_axis.begin())
			--axis_iter;
		while (axis_iter != m_x_axis.begin())
		{
			diff = vec.x - axis_iter->value->position.x;
			if (diff <= range &&
				abs(vec.y - axis_iter->value->position.y) <= range)
			{
				if (obj->IsInsightTag(axis_iter->value->m_tag))
				{
					set.insert(std::make_pair(axis_iter->value->m_id, axis_iter->value));
				}
			}
			else {
				break;
			}

			--axis_iter;
		}
		// �� x ���ұ�
		if ((axis_iter = obj->m_x_pos) != m_x_axis.end())
			++axis_iter;
		while (axis_iter != m_x_axis.end())
		{
			diff = axis_iter->value->position.x - vec.x;
			if (diff <= range &&
				abs(vec.y - axis_iter->value->position.y) <= range)
			{
				if (obj->IsInsightTag(axis_iter->value->m_tag))
				{
					set.insert(std::make_pair(axis_iter->value->m_id, axis_iter->value));
				}
			}
			else {
				break;
			}
			++axis_iter;
		}
	}

private:
	// ��Ӷ���
	void AddObject(AOIObject<T>* obj) {
		m_objs.insert(std::make_pair(obj->m_id, obj));
	}

	// �Ƴ�����
	void RemoveObject(const AOIObject<T>* obj) {
		m_objs.erase(obj->m_id);
	}

	// ȡ������
	AOIObject<T>* GetObject(const AOIObjectID id) {
		auto found = m_objs.find(id);
		if (found == m_objs.end())
		{
			return nullptr;
		}
		return found->second;
	}

	// ���������
	void HaveObject(const AOIObject<T>* obj) {
		return (m_objs.find(obj->m_id) != m_objs.end());
	}
	
	// ��Ƕ��󣬸���aoiģ�飬��������б仯
	void MarkObject(AOIObject<T>* obj) {
		m_changed_obj.insert(std::make_pair(obj->m_id, obj));
	}

	// ȡ����Ƕ���
	void UnMarkObject(AOIObject<T>* obj) {
		m_changed_obj.erase(obj->m_id);
	}
	
	// �½�����
	AOIObject<T>* NewObject(const AOIObjectID id) {
		auto obj = m_obj_pool.Fetch();
		obj->m_id = id;
		return obj;
	}

	// ɾ������
	void DeleteObject(AOIObject<T>* obj) {
		m_obj_pool.Recycle(obj);
	}


	// ���¶���λ��
	void UpdateObjectPosition(const AOIObject<T>* obj) {
		m_x_axis.modify(obj->m_x_pos, obj->position.x);
	}



	// ˢ�¶���
	void UpdateObject(AOIObject<T>* obj) {
		// ��ʱ����
		// ��������ʱ����������

		obj->m_insight_obj_back = std::move(obj->m_insight_obj);
		GetObjectsInRange(obj, obj->m_insight_obj);

		// ȡ�������ʵ��
		auto& insight_obj = obj->m_insight_obj;
		auto& insight_obj_back = obj->m_insight_obj_back;
		for (auto& item : insight_obj)
		{
			if (insight_obj_back.find(item.first) == insight_obj_back.end())
			{
				m_enter_notify.push_back(item.second->statue);
				item.second->AddObjectToInsight(obj);
			}
		}


		// ȡ���뿪��ʵ��
		for (auto& item : insight_obj_back)
		{
			if (insight_obj.find(item.first) == insight_obj.end())
			{
				m_leave_notify.push_back(item.second->statue);
				item.second->RemoveObjectFromInsight(obj);
			}
		}

		if (m_call_enter&& !m_enter_notify.empty())
		{
			m_call_enter(obj->statue, m_enter_notify);
		}

		if (m_call_leave && !m_leave_notify.empty())
		{

			m_call_leave(obj->statue, m_leave_notify);
			
		}

		m_enter_notify.clear();
		m_leave_notify.clear();
	}

private:

	AOIObjectPool<T>	m_obj_pool;

	// ���еĶ��� �� X �������
	skip_list<int32_t,AOIObject<T>*>	m_x_axis;	

	// AOI �е�ȫ������
	std::unordered_map<AOIObjectID, AOIObject<T>*>	m_objs;					


	// ˢ�������ڣ�λ���б䶯��ʵ��
	std::unordered_map<AOIObjectID, AOIObject<T>*>	m_changed_obj;		
	
	std::vector<T>	m_enter_notify;
	std::vector<T>	m_leave_notify;


	// ����ص�
	call_enter	m_call_enter;
	// �뿪�ص�
	call_leave	m_call_leave;

};