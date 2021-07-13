#pragma once


template<typename K, typename V>
class skip_list;

template<typename K, typename V>
class skip_list_iterator;

template<typename K, typename V>
class list_node
{
public:
	list_node(const size_t lev) {
		next = new list_node * [lev];
		prev = new list_node * [lev];
		level = lev;
		for (int i = 0; i < level; ++i)
		{
			next[i] = nullptr;
			prev[i] = nullptr;
		}
			
	}

	~list_node() {
		// 释放指针
		delete[]next;
		delete[]prev;
	}

	K	key;
	V	value;




private:
	size_t level;
	// 下一个节点 up[0]
	list_node<K,V>** next;
	// 上一个节点
	list_node<K, V>** prev;

	friend class skip_list<K, V>;
	friend class skip_list_iterator<K, V>;
};


