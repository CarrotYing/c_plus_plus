#pragma once
#include <stdlib.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef int DataType;
struct ListNode
{
    DataType data;
    ListNode* _next;
    ListNode* _prev;
    
    ListNode(DataType val)
        :data(val)
         ,_next(NULL)
         ,_prev(NULL)
    {}
};

class List
{
    typedef ListNode Node;
public:
    List()
       :_head(new Node(DataType())) 
    {
        _head->_next=_head;
        _head->_prev=_head;
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
        Node* cur=_head->_next;
        if(cur != _head)
        {
            Node* to_delete = cur;
            Node* prev=cur->_prev;
            Node* next=cur->_next;
            prev->_next=next;
            next->_prev=prev;
            cur = cur->_next;
            delete to_delete;
        }
    }
    List(const List& l)
    {
        _head = new Node(DataType());
        _head->_next=_head;
        _head->_prev=_head;
        Node* cur = l._head->_next;
        while(cur!=l._head)
        {
            PushBack(cur->data);
            cur = cur->_next;
        }
    }
    List& operator=(List l)
    {
        swap(_head,l._head);
        return *this;
    }
   
    void Insert(Node* pos,DataType val)
    {
        if(pos == NULL)
        {
            return ;
        }
        Node* prev = pos->_prev;
        Node* newnode = new Node(val);
        
        newnode->_next = pos;
        pos->_prev = newnode;

        prev->_next = newnode;
        newnode->_prev = prev;
    }
    void Erase(Node* pos)
    {
        Node* prev = pos->_prev;
        Node* next = pos->_next;

        prev->_next = next;
        next->_prev = prev;
        delete pos;
    }
    void PushBack(DataType val)
    {
        Insert(_head,val);
    }
    void PopBack()
    {
        Erase(_head->_prev);
    }
    void PushFront(DataType val)
    {
        Insert(_head->_next,val);
    }
    void PopFront()
    {
        Erase(_head->_next);
    }
    void Print()
    {
        Node* cur=_head->_next;
        while(cur != _head)
        {
            cout<<cur->data<<" ";
            cur = cur->_next;
        }
        cout<<endl;
    }
    Node* Find(DataType val)
    {
        Node* cur=_head->_next;
        while(cur != _head)
        {
            if(cur->data == val)
            {
                return cur;
            }
            cur = cur->_next;
        }
        return NULL;
    }
private:
    Node* _head;
};
