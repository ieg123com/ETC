#pragma once
#include "MemoryLoop.h"
#include <memory>


#define SPLIT_DATA_SIZE 1024


/** @brief 内存财富 */
class MemorySplit
{
	/** @brief 要被分割的内存记录对象 */
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
		 * @brief  添加数据
		 * @return 返回剩余长度
		 */
		size_t push_back(const void* dt, const size_t len) {
			size_t left_size = leftsize();
			if (left_size == 0) return len;
			if (left_size >= len) {
				// 可以全部添加
				memmove(end_pos, dt, len);
				end_pos += len;
				return 0;
			}
			// 无法全部添加
			memmove(end_pos, dt, left_size);
			end_pos += left_size;
			return len - left_size;
		}
		/**
		 * @brief  取出数据
		 * @return 返回剩余长度
		 */
		size_t front_pop(void* dt,const size_t len) {
			size_t size = this->size();
			if (size == 0)return len;
			if (size >= len)
			{
				// 长度够
				memmove(dt, start_pos, len);
				start_pos += len;
				return 0;
			}
			else {
				// 长度不够
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
				// 长度够
				memmove(dt, start_pos, len);
				return 0;
			}
			else {
				// 长度不够
				memmove(dt, start_pos, size);
				return len - size;
			}
		}

		size_t pop(const size_t len) {
			size_t size = this->size();
			if (size == 0)return len;
			if (size >= len)
			{
				// 长度够
				start_pos += len;
				return 0;
			}
			else {
				// 长度不够
				start_pos += size;
				return len - size;
			}
		}

		/**
		 * @brief	从所有包中取出指定长度数据
		 * @param[out]	dt : 取出后，存放的数据
		 * @param[in]	len : 需要取出的长度
		 * @warning	长度不足时，将抛出异常
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
					throw std::exception("从 SplitData 中取数据时，长度不够！");
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
					throw std::exception("从 SplitData 中取数据时，长度不够！");
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
					throw std::exception("从 SplitData 移除数据时，长度不够！");
				}
			}
		}
	};

public:
	MemorySplit();
	~MemorySplit();


	// 拆包后的数据
	std::shared_ptr<std::string> Data;

	// 添加要分割的数据
	void AddData(const char* data, const size_t len);

	bool Unpack();


private:

	void __AddData(const char* data, const size_t len);
	/**
	 * @brief	开始拆包
	 */
	bool __Unpack();


private:
	// 数据链表
	SplitData* m_list_start;
	SplitData* m_list_over;

};


