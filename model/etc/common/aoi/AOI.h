#pragma once
#include <unordered_map>
#include "Vector3.h"
#include "AOIDef.h"
#include "AOIObject.h"



// 地图aoi
// Move 会等下一时钟周期统一刷新
// Enter、Leave 会立即刷新
template<typename T>
class AOI
{
public:
	typedef void(*call_enter)(T, const std::vector<T>&);
	typedef void(*call_leave)(T, const std::vector<T>&);

	~AOI() {
		clear();
	}

	// 实体进入场景
	AOIObject<T>* Enter(AOIObjectID id, const Vector3& vec) {
		auto obj = GetObject(id);
		if (obj != nullptr)
		{
			// 这个对象已经进入 AOI 中
			return nullptr;
		}
		else {
			// 没找到这个对象
			obj = NewObject(id);
			obj->position = vec;
		}

		AddObject(obj);

		obj->m_x_pos = m_x_axis.insert(std::make_pair(obj->position.x, obj)).first;

		// 设置对象所在aoi
		obj->m_aoi = this;

		UpdateObject(obj);

		return obj;
	}

	// 实体在场景内移动
	bool Move(AOIObjectID id, const Vector3& vec){
		auto obj = GetObject(id);
		if (obj == nullptr)
		{
			// 没找到这个对象
			return false;
		}

		obj->position = vec;

		UpdateObjectPosition(obj);

		MarkObject(obj);

		return true;
	}

	// 实体离开场景
	bool Leave(AOIObjectID id){
		auto obj = GetObject(id);
		if (obj == nullptr)
		{
			// 没找到这个对象
			return false;
		}

		m_x_axis.erase(obj->m_x_pos);
		obj->m_x_pos = nullptr;
		obj->m_aoi = nullptr;

		RemoveObject(obj);
		UnMarkObject(obj);

		UpdateObject(obj);
		
		// 删除这个对象
		DeleteObject(obj);
		return true;
	}



	// 有相同的对象
	bool IsHaveSameObject(const AOIObject<T>* obj) const {
		return (m_objs.find(obj->m_id) != m_objs.end());
	}

	// 更新标记过的对象
	void UpdateMarkedObject() {
		for (auto& item : m_changed_obj) {
			UpdateObject(item.second);
		}
		m_changed_obj.clear();
	}

	// 不会推送离开事件
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
	// 取出一个对象
	AOIObject<T>* GetObject(const AOIObjectID id)const {
		auto found = m_objs.find(id);
		if (found == m_objs.end())
		{
			return nullptr;
		}
		return found->second;
	}

public:
	// 在一定范围内，取出其他实体
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
			// 实体不在这aoi中
			return;
		}
		static skip_list<int32_t, AOIObject<T>*>::iterator axis_iter;
		const Vector3& vec = obj->position;
		int diff = 0;

		// X 轴查询
		// 向 x 轴左边
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
		// 向 x 轴右边
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
	// 添加对象
	void AddObject(AOIObject<T>* obj) {
		m_objs.insert(std::make_pair(obj->m_id, obj));
	}

	// 移除对象
	void RemoveObject(const AOIObject<T>* obj) {
		m_objs.erase(obj->m_id);
	}

	// 取出对象
	AOIObject<T>* GetObject(const AOIObjectID id) {
		auto found = m_objs.find(id);
		if (found == m_objs.end())
		{
			return nullptr;
		}
		return found->second;
	}

	// 有这个对象
	void HaveObject(const AOIObject<T>* obj) {
		return (m_objs.find(obj->m_id) != m_objs.end());
	}
	
	// 标记对象，告诉aoi模块，这个对象有变化
	void MarkObject(AOIObject<T>* obj) {
		m_changed_obj.insert(std::make_pair(obj->m_id, obj));
	}

	// 取消标记对象
	void UnMarkObject(AOIObject<T>* obj) {
		m_changed_obj.erase(obj->m_id);
	}
	
	// 新建对象
	AOIObject<T>* NewObject(const AOIObjectID id) {
		auto obj = m_obj_pool.Fetch();
		obj->m_id = id;
		return obj;
	}

	// 删除对象
	void DeleteObject(AOIObject<T>* obj) {
		m_obj_pool.Recycle(obj);
	}


	// 更新对象位置
	void UpdateObjectPosition(const AOIObject<T>* obj) {
		m_x_axis.modify(obj->m_x_pos, obj->position.x);
	}



	// 刷新对象
	void UpdateObject(AOIObject<T>* obj) {
		// 定时更新
		// 对象类型时，立即更新

		obj->m_insight_obj_back = std::move(obj->m_insight_obj);
		GetObjectsInRange(obj, obj->m_insight_obj);

		// 取出进入的实体
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


		// 取出离开的实体
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

	// 所有的对象 在 X 轴的排列
	skip_list<int32_t,AOIObject<T>*>	m_x_axis;	

	// AOI 中的全部对象
	std::unordered_map<AOIObjectID, AOIObject<T>*>	m_objs;					


	// 刷新周期内，位置有变动的实体
	std::unordered_map<AOIObjectID, AOIObject<T>*>	m_changed_obj;		
	
	std::vector<T>	m_enter_notify;
	std::vector<T>	m_leave_notify;


	// 进入回调
	call_enter	m_call_enter;
	// 离开回调
	call_leave	m_call_leave;

};