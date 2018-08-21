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
};
//带头结点的双向链表
template <class T>
class List
{
    typedef ListNode<T> Node;
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
