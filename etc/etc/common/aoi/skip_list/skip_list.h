#pragma once
#include <queue>
#include <string>
#include "list_node.h"
#include "random.h"


template<typename K, typename V>
class skip_list;


template<typename K, typename V>
class skip_list_iterator
{
public:
	skip_list_iterator() {
		m_node = nullptr;
	}

	skip_list_iterator(list_node<K, V>* val) {
		m_node = val;
	}


	_NODISCARD list_node<K, V>* operator*() const noexcept {
		return m_node;
	}

	_NODISCARD list_node<K, V>* operator->() const noexcept {
		return m_node;
	}

	_NODISCARD bool operator == (const skip_list_iterator<K, V>& val)const noexcept {
		return m_node == val.m_node;
	}

	_NODISCARD bool operator != (const skip_list_iterator<K, V>& val)const noexcept {
		return m_node != val.m_node;
	}

	skip_list_iterator<K, V>& operator++() noexcept {
		m_node = m_node->next[0];
		return *this;
	}

	skip_list_iterator<K, V>& operator--() noexcept {
		m_node = m_node->prev[0];
		return *this;
	}



private:
	list_node<K, V>* m_node;

	friend class skip_list<K, V>;
};


template<typename K,typename V>
class skip_list
{
public:
	
	using iterator = skip_list_iterator<K,V>;





	skip_list() :m_rand(0x12345678) {
		m_node_level = 2;
		m_header = node_new(m_node_level);
	}

	~skip_list() {
		clear();
		node_delete(m_header);
	}

	std::pair<iterator, bool> insert(const std::pair<K, V>& val) {
		list_node<K, V>* new_node = node_new();
		new_node->key = val.first;
		new_node->value = val.second;

		return std::move(std::make_pair(add_node(new_node), true));
	}
	
	// 修改 key
	void modify(iterator iter, const K& key) {
		remove_node(iter.m_node);
		iter.m_node->key = key;
		add_node(iter.m_node);
	}

	iterator find(const K& key) {
		return find_node(key);
	}

	iterator erase(iterator del_iter) {
		iterator ret_iter(remove_node(del_iter.m_node));
		node_delete(del_iter.m_node);
		return ret_iter;
	}


	iterator begin() const {
		return iterator(m_header->next[0]);
	}

	iterator end() const {
		return iterator(nullptr);
	}

	void clear() {
		list_node<K, V>* node, *del_node;
		if (node = m_header->next[0])
		{
			while (del_node = node) {
				node = node->next[0];
				node_delete(del_node);
			}
		}

		memset(m_header->next,0, sizeof(m_header->next[0]) * m_header->level);
		m_count = 0;
	}
	

private:

	list_node<K, V>* node_new() {
		int node_level = m_rand.Skewed(m_node_level+1)+1;
		return node_new(node_level);
	}

	list_node<K, V>* node_new(const size_t level) {
		auto new_node = new list_node<K, V>(level);
		return new_node;
	}

	void node_delete(const list_node<K, V>* pnode) {
		delete pnode;
	}

	// 添加节点
	list_node<K, V>* add_node(list_node<K, V>* new_node) {

		{
			if (m_node_level < new_node->level)
			{
				// 标头节点增加高度
				m_node_level = new_node->level;
				auto new_header = node_new(m_node_level);
				// 换掉原理的节点
				replace_node(m_header, new_header);

				node_delete(m_header);
				m_header = new_header;
			}
		}


		list_node<K, V>* node = m_header;
		
		for (int i = node->level - 1; i >= 0; --i) {
			while (node->next[i] != nullptr &&
				node->next[i]->key <= new_node->key) {

				node = node->next[i];
			}
			// 记录，这个节点要插入时，每个高度的前后的节点
			if (node->key == new_node->key &&
				node != m_header)
			{
				// 有重复的key
				// 在这个节点前面插进去
				for (int hig = i; hig >= 0; --hig) 
				{
					if (hig < new_node->level)
					{
						new_node->next[hig] = node;
						new_node->prev[hig] = node->prev[hig];
					}
				}
				break;
			}
			else if(i < new_node->level)
			{
				new_node->next[i] = node->next[i];
				new_node->prev[i] = node;
			}
		}

		// 开始插入，告诉前后的节点，换人了
		for (int i = 0; i < new_node->level; ++i)
		{
			// 告诉上一个节点，下一个节点换人了
			new_node->prev[i]->next[i] = new_node;
			// 告诉下一个节点，上一个节点换人了
			if (new_node->next[i] != nullptr)
			{
				new_node->next[i]->prev[i] = new_node;
			}

		}
		

		++m_count;
		return new_node;
	}

	// 查找节点
	list_node<K, V>* find_node(const K& key) {
		list_node<K, V>* node = m_header;
		for (int i = node->level - 1; i >= 0; --i) {
			while (node->next[i] != nullptr &&
				node->next[i]->key <= key) {
				node = node->next[i];
			}
			if (node->key == key)
			{
				break;
			}
		}
		return (node->key == key) ? node : nullptr;
	}

	// 移除节点
	list_node<K, V>* remove_node(list_node<K, V>* del_node) {
		if (del_node == nullptr)
		{
			return nullptr;
		}
		list_node<K, V>* next_node = del_node->next[0];

		for (int i = 0; i < del_node->level; ++i) 
		{
			// 将节点移出
			// 告诉上一个节点，下一个节点变了
			del_node->prev[i]->next[i] = del_node->next[i];
			// 告诉下一个节点，上一个节点变了
			if (del_node->next[i] != nullptr)
			{
				del_node->next[i]->prev[i] = del_node->prev[i];
			}
			
			del_node->next[i] = nullptr;
			del_node->prev[i] = nullptr;
		}
		--m_count;
		return next_node;
	}

	// 替换节点
	void replace_node(list_node<K, V>* origin_node, list_node<K, V>* new_node) {
		for (int i = 0; i < origin_node->level; ++i)
		{
			if (i < new_node->level)
			{
				new_node->next[i] = origin_node->next[i];
				new_node->prev[i] = origin_node->prev[i];
				// 告诉下一个节点，上一个节点换人了
				if (new_node->next[i] != nullptr)
				{
					new_node->next[i]->prev[i] = new_node;
				}
			}
		}
		// 节点交接完成
	}

public:
// 	void dump_all_node() {
// 		list_node<K, V>* node = m_header;
// 		while ((node = node->next[0]) != nullptr)
// 		{
// 			dump_node(node);
// 			printf("=======================================================\n");
// 		}
// 	}
// 
// 	void dump_node(list_node<K, V>* node) {
// 		printf("node->key:%d  node->value:%d\n", node->key, node->value);
// 		for (int i = 0; i < node->level; ++i)
// 		{
// 			printf("next[%d]-key:%s  next[%d]->value:%s\n",
// 				i,
// 				(node->next[i])?std::to_string(node->next[i]->key).c_str():"null",
// 				i,
// 				(node->next[i])? node->next[i]->value.c_str():"null");
// 		}
// 	}
private:
	
	list_node<K, V>* m_header;


	// 当前节点可创建的最高等级
	size_t		m_node_level;
	// 节点数
	size_t		m_count;

	Random		m_rand;
};


