#pragma once
#include "MemoryLoop.h"
#include <memory>


#define SPLIT_DATA_SIZE 1024


/** @brief �ڴ�Ƹ� */
class MemorySplit
{
	/** @brief Ҫ���ָ���ڴ��¼���� */
	class SplitData:
		public MemoryObject
	{
	public:
		SplitData* next;

		char	data[SPLIT_DATA_SIZE];
		char*	start_pos;
		char*	end_pos;

		size_t size() {
			return end_pos - start_pos;
		}

		size_t sizesum() {
			size_t sum = 0;
			SplitData* child = this;
			while (child != nullptr)
			{
				sum += child->size();
				child = child->next;
			}
			return sum;
		}

		size_t leftsize() {
			return (data + sizeof(data)) - end_pos;
		}

		virtual void Awake() override {
			next = nullptr;
			start_pos = data;
			end_pos = start_pos;
		}
		/** 
		 * @brief  �������
		 * @return ����ʣ�೤��
		 */
		size_t push_back(const void* dt, const size_t len) {
			size_t left_size = leftsize();
			if (left_size == 0) return len;
			if (left_size >= len) {
				// ����ȫ�����
				memmove(end_pos, dt, len);
				end_pos += len;
				return 0;
			}
			// �޷�ȫ�����
			memmove(end_pos, dt, left_size);
			end_pos += left_size;
			return len - left_size;
		}
		/**
		 * @brief  ȡ������
		 * @return ����ʣ�೤��
		 */
		size_t front_pop(void* dt,const size_t len) {
			size_t size = this->size();
			if (size == 0)return len;
			if (size >= len)
			{
				// ���ȹ�
				memmove(dt, start_pos, len);
				start_pos += len;
				return 0;
			}
			else {
				// ���Ȳ���
				memmove(dt, start_pos, size);
				start_pos += size;
				return len - size;
			}
		}
		
		size_t front(void* dt, const size_t len) {
			size_t size = this->size();
			if (size == 0)return len;
			if (size >= len)
			{
				// ���ȹ�
				memmove(dt, start_pos, len);
				return 0;
			}
			else {
				// ���Ȳ���
				memmove(dt, start_pos, size);
				return len - size;
			}
		}

		size_t pop(const size_t len) {
			size_t size = this->size();
			if (size == 0)return len;
			if (size >= len)
			{
				// ���ȹ�
				start_pos += len;
				return 0;
			}
			else {
				// ���Ȳ���
				start_pos += size;
				return len - size;
			}
		}

		/**
		 * @brief	�����а���ȡ��ָ����������
		 * @param[out]	dt : ȡ���󣬴�ŵ�����
		 * @param[in]	len : ��Ҫȡ���ĳ���
		 * @warning	���Ȳ���ʱ�����׳��쳣
		 */
		void front_from_allpack(void* dt, const size_t len) {
			SplitData* child = this;
			size_t left_len = len;
			char* data_pos = (char*)dt;
			while (left_len != 0)
			{
				size_t size = child->front(data_pos, left_len);
				data_pos += left_len - size;
				left_len = size;
				if (size == 0)
				{
					break;
				}
				if ((child = child->next) == nullptr)
				{
					throw std::exception("�� SplitData ��ȡ����ʱ�����Ȳ�����");
				}
			}
		}

		void front_pop_from_allpack(void* dt, const size_t len) {
			SplitData* child = this;
			size_t left_len = len;
			char* data_pos = (char*)dt;
			while (left_len != 0)
			{
				size_t size = child->front_pop(data_pos, left_len);
				data_pos += left_len - size;
				left_len = size;
				if (size == 0)
				{
					break;
				}
				if ((child = child->next) == nullptr)
				{
					throw std::exception("�� SplitData ��ȡ����ʱ�����Ȳ�����");
				}
			}
		}

		void pop_from_allpack(const size_t len) {
			SplitData* child = this;
			size_t left_len = len;
			while (left_len != 0)
			{
				size_t size = child->pop(left_len);
				left_len = size;
				if (size == 0)
				{
					break;
				}
				if ((child = child->next) == nullptr)
				{
					throw std::exception("�� SplitData �Ƴ�����ʱ�����Ȳ�����");
				}
			}
		}
	};

public:
	MemorySplit();
	~MemorySplit();


	// ����������
	std::shared_ptr<std::string> Data;

	// ���Ҫ�ָ������
	void AddData(const char* data, const size_t len);

	bool Unpack();


private:

	void __AddData(const char* data, const size_t len);
	/**
	 * @brief	��ʼ���
	 */
	bool __Unpack();


private:
	// ��������
	SplitData* m_list_start;
	SplitData* m_list_over;

};


