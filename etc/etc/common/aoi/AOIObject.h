#pragma once
#include "AOIDef.h"
#include "Vector3.h"
#include "skip_list/skip_list.h"
#include <unordered_map>
#include <queue>

template<typename T>
class AOI;

// �����е�ʵ��
template<typename T>
class AOIObject
{
public:
	// ��aoi�е�����
	Vector3 position;

	T		statue;



	AOIObject() {
		m_id = 0;
		m_tag = ETagType::INVALID;
		m_insight_tag = (uint32_t)ETagType::ALL;
		m_insight_range = 20;
		m_aoi = nullptr;
	}


	// �����Լ�������ǩ
	void SetTag(const ETagType tag) {m_tag = tag;}

	// ����ܿ����ı�ǩ
	void AddInsightTag(const ETagType tag){ m_insight_tag |= (uint32_t)tag; }
	// �Ƴ��ܿ����ı�ǩ
	void RemoveInsightTag(const ETagType tag){ m_insight_tag &= ~(uint32_t)tag; }


	// ���Կ���ӵ�������ǩ�Ķ���
	bool IsInsightTag(const ETagType tag) const{ return (m_insight_tag & (uint32_t)tag); }




	// ������Ұ��Χ
	void SetInsightRange(const uint32_t val){ m_insight_range = val; }


	// ��ȡ���������ǳ���
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
	// ȡ���Լ����Կ����Ķ���
	const std::unordered_map<AOIObjectID, AOIObject<T>*>& GetInsightObject()const {
		return m_insight_obj;
	}

private:
	// ��������ӵ���Ұ��
	void AddObjectToInsight(AOIObject<T>* obj) {
		m_insight_obj.insert(std::make_pair(obj->m_id, obj));
	}

	// ���������Ұ���Ƴ�
	void RemoveObjectFromInsight(AOIObject<T>* obj) {
		m_insight_obj.erase(obj->m_id);
	}

	// ����Ұ��
	bool InInight(const AOIObject<T>* obj) const {
		return (m_insight_obj.find(obj->m_id) != m_insight_obj.end());
	}
private:
	AOIObjectID	m_id;
	// �Լ�������ǩ
	ETagType	m_tag;
	// ���ӱ�ǩ
	uint32_t	m_insight_tag;
	// ��Ұ��Χ
	uint32_t	m_insight_range;

	using pos_iterator = typename skip_list<int32_t, AOIObject<T>*>::iterator;
	
	pos_iterator m_x_pos;

	// �ҿ��Կ����Ķ���
	std::unordered_map<AOIObjectID, AOIObject<T>*> m_insight_obj;
	// �ϴο��Կ����Ķ���
	std::unordered_map<AOIObjectID, AOIObject<T>*> m_insight_obj_back;



	// �������AOI��
	AOI<T>*	m_aoi;

	friend class AOI<T>;
};


// �����
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