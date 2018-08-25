#include <iostream>
#include <stdlib.h>
using namespace std;

template <class T>
struct ListNode
{
    T _data;
    ListNode* _prev;
    ListNode* _next;

    ListNode(T data)
        :_data(data)
         ,_prev(NULL)
         ,_next(NULL)
    {}
    bool operator==(const ListNode& l)
    {
        return (_data==l._data && 
                _prev == l._prev &&
                _next == l._next);
    }
    bool operator!=(const ListNode& l)
    {
        return !(*this==l);
    }
};
//迭代器只是一种以统一的方式访问容器
//不关心容器底层实现
//迭代器浅拷贝即可满足需求
// iterator<T,T&,T*> 
// iterator<const T,const T&,const T*>//增强复用性 
template <class T,class Ref,class Ptr>
struct __Iterator
{
    typedef __Iterator<T,Ref,Ptr> Self;
    typedef ListNode<T> Node;
    __Iterator(Node* node)
        :_node(node)
    {}
    Self& operator++()
    {
        _node = _node->_next;
        return *this;
    }
    Self operator++(int)
    {
        Self ret(*this);
        _node = _node->_next;
        return _node;
    }
    Self& operator--()
    {
        _node = _node->_prev;
        return *this;
    }
    Self operator--(int)
    {
        Self ret(*this);
        _node = _node->_prev;
        return _node;
    }
    Ref operator*()
    {
        return _node->_data;
    }
    Ptr operator->()
    {
        return &(_node->_data);
    }
    bool operator!=(const Self& s)
    {
        return _node != s._node;
    }
    bool operator==(const Self& s)
    {
        return _node == s._node;
    }
private:
    Node* _node;
};
//带头结点的双向链表
template <class T>
class List
{
    typedef ListNode<T> Node;
public:
    typedef __Iterator<T,T&,T*> Iterator;
    typedef __Iterator<T,const T&,const T*> ConstIterator;
    Iterator begin()
    {
        return Iterator(_head->_next);
    }
    Iterator end()
    {
        return Iterator(_head);
    }
    ConstIterator begin() const
    {
        return ConstIterator(_head->_next);
    }
    ConstIterator end() const
    {
        return ConstIterator(_head);
    }
public:
    List()
        :_head(new Node(T()))
    {
        _head->_next = _head;
        _head->_prev = _head;
    }
    ~List()
    {
        Clear();
        if(_head)
        {
            delete _head;
        }
        _head = NULL;
    }
    void Clear()
    {
        Node* cur = _head->_next;
        while(cur != _head)
        {
            Node* to_delete = cur;
            cur = cur->_next;
            delete to_delete;
        }
    }
    List(const List& l)
    {
        _head = new Node(T());
        _head->_next = _head;
        _head->_prev = _head;
        Node* cur = l._head->_next;
        while(cur != l._head)
        {
            PushBack(cur->_data);
            cur = cur->_next;
        }
    }
    List* operator=(List l)
    {
        swap(this->_head,l._head);
    }
    //在pos前插入一个元素
    void Insert(Node* pos,const T& value)
    {
        Node* prev = pos->_prev;
        Node* new_node = new Node(value);

        prev->_next = new_node;
        new_node->_prev = prev;

        new_node->_next = pos;
        pos->_prev = new_node;
    }
    void Erase(Node* pos)
    {
        Node* prev = pos->_prev;
        Node* next = pos->_next;

        prev->_next = next;
        next->_prev = prev;

        delete pos;
    }
    void PushBack(const T& value)
    {
        Insert(_head,value);
    }
    void PopBack()
    {
        Erase(_head->_prev);
    }
    void PushFront(const T& value)
    {
        Insert(_head->_next,value);
    }
    void PopFront()
    {
        Erase(_head->_next);
    }
    void Print()
    {
        Node* cur = _head->_next;
        while(cur != _head)
        {
            cout<<cur->_data<<endl;
            cur = cur->_next;
        }
    }
private:
    Node* _head;
};
