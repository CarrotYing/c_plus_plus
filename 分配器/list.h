#pragma once
#include "Alloc.h"

template<class T>
struct  ListNode
{
	T _data;
	ListNode<T>* _next;
	ListNode<T>* _prev;
};

template<class T, class Ref, class Ptr>
struct __ListIterator
{
	typedef ListNode<T> Node;
	typedef __ListIterator<T, T&, T*> Self;
	Node* _node;

	__ListIterator(Node* node)
		:_node(node)
	{}

	Ref operator*()
	{
		return _node->_data;
	}

	Self& operator++()
	{
		_node = _node->_next;

		return *this;
	}

	bool operator != (const Self& s)
	{
		return _node != s._node;
	}
};

template<class T, class Alloc = alloc>
class List
{
	typedef ListNode<T> Node;
	typedef SimpleAlloc<Node, Alloc> ListNodeAlloctor;
public:
	typedef __ListIterator<T, T&, T*> Iterator;

	Node* BuyNode(const T& x)
	{
		Node* node = ListNodeAlloctor::Allocate();
		node->_next = NULL;
		node->_prev = NULL;
		//node->_data = x;
		new(&node->_data)T(x);

		return node;
	}
	
	void DestoryNode(Node* node)
	{
		node->_data.~T();
		ListNodeAlloctor::Deallocate(node);
	}

	List()
		:_head(BuyNode(T()))
	{
		_head->_next = _head;
		_head->_prev = _head;
	}

	~List()
	{
		Clear();
		DestoryNode(_head);
		_head = NULL;
	}

	void Clear()
	{
		Iterator it = Begin();
		while (it != End())
		{
			Iterator cur = it;
			++it;
			DestoryNode(cur._node);
		}

		_head->_next = _head;
		_head->_prev = _head;
	}

	Iterator Begin()
	{
		return _head->_next;
	}

	Iterator End()
	{
		return _head;
	}

	void PushBack(const T& x)
	{
		Insert(End(), x);
	}

	void Insert(Iterator pos, const T& x)
	{
		Node* cur = pos._node;
		Node* prev = cur->_prev;
		Node* newnode = BuyNode(x);

		prev->_next = newnode;
		newnode->_prev = prev;
		newnode->_next = cur;
		cur->_prev = newnode;
	}

private:
	Node* _head;
};
