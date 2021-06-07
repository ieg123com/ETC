#pragma once
#include "AOIDef.h"
#include "Vector3.h"
#include "skip_list/skip_list.h"
#include <unordered_map>
#include <queue>

template<typename T>
class AOI;

// 场景中的实体
template<typename T>
class AOIObject
{
public:
	// 在aoi中的坐标
	Vector3 position;

	T		statue;



	AOIObject() {
		m_id = 0;
		m_tag = ETagType::INVALID;
		m_insight_tag = (uint32_t)ETagType::ALL;
		m_insight_range = 20;
		m_aoi = nullptr;
	}


	// 设置自己所属标签
	void SetTag(const ETagType tag) {m_tag = tag;}

	// 添加能看到的标签
	void AddInsightTag(const ETagType tag){ m_insight_tag |= (uint32_t)tag; }
	// 移除能看到的标签
	void RemoveInsightTag(const ETagType tag){ m_insight_tag &= ~(uint32_t)tag; }


	// 可以看到拥有这个标签的对象
	bool IsInsightTag(const ETagType tag) const{ return (m_insight_tag & (uint32_t)tag); }




	// 设置视野范围
	void SetInsightRange(const uint32_t val){ m_insight_range = val; }


	// 获取自身所在是场景
	AOI<T>* GetAOI() const { return m_aoi; }
	bool InAOI()const { return (m_aoi != nullptr); }
	
	void clear() {
		T new_statue;
		std::swap(statue, new_statue);
		m_x_pos = nullptr;
		m_insight_obj.clear();
		m_insight_obj_back.clear();
		m_aoi = nullptr;
	}
protected:
	// 取出自己可以看到的对象
	const std::unordered_map<AOIObjectID, AOIObject<T>*>& GetInsightObject()const {
		return m_insight_obj;
	}

private:
	// 将对象添加的视野中
	void AddObjectToInsight(AOIObject<T>* obj) {
		m_insight_obj.insert(std::make_pair(obj->m_id, obj));
	}

	// 将对象从视野中移除
	void RemoveObjectFromInsight(AOIObject<T>* obj) {
		m_insight_obj.erase(obj->m_id);
	}

	// 在视野中
	bool InInight(const AOIObject<T>* obj) const {
		return (m_insight_obj.find(obj->m_id) != m_insight_obj.end());
	}
private:
	AOIObjectID	m_id;
	// 自己所属标签
	ETagType	m_tag;
	// 可视标签
	uint32_t	m_insight_tag;
	// 视野范围
	uint32_t	m_insight_range;

	using pos_iterator = typename skip_list<int32_t, AOIObject<T>*>::iterator;
	
	pos_iterator m_x_pos;

	// 我可以看到的对象
	std::unordered_map<AOIObjectID, AOIObject<T>*> m_insight_obj;
	// 上次可以看到的对象
	std::unordered_map<AOIObjectID, AOIObject<T>*> m_insight_obj_back;



	// 现在这个AOI里
	AOI<T>*	m_aoi;

	friend class AOI<T>;
};


// 对象池
template<typename T>
class AOIObjectPool
{
public:
	~AOIObjectPool() {
		clear();
	}

	AOIObject<T>* Fetch() {
		AOIObject<T>* obj;
		if (m_objs.empty())
		{
			obj = new AOIObject<T>();
		}
		else {
			obj = m_objs.front();
			m_objs.pop();
			obj->clear();
		}
		return obj;
	}

	void Recycle(AOIObject<T>* obj) {
		m_objs.push(obj);
	}

	void clear() {
		while (m_objs.empty() == false)
		{
			delete m_objs.front();
			m_objs.pop();
		}
	}
private:
	std::queue<AOIObject<T>*>	m_objs;


};