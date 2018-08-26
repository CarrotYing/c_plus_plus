#pragma once
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
template <class W>
struct HuffmanNode
{
    HuffmanNode* _parent;
    HuffmanNode* _lchild;
    HuffmanNode* _rchild;
    W _w;
    HuffmanNode(const W& w)
        :_parent(NULL)
         ,_lchild(NULL)
         ,_rchild(NULL)
         ,_w(w)
    {}
};
template <class W>
class HuffmanTree
{
    typedef HuffmanNode<W> Node;
    struct NodeCompare
    {
        bool operator()(Node* a,Node* b) 
        {
            return a->_w > b->_w;
        }
    };
public:
    HuffmanTree(W* a,size_t size,const W& invalid)
        :_root(NULL)
    {
        priority_queue<Node*,vector<Node*>,NodeCompare> minHeap;
        size_t i=0;
        for(;i<size;++i)
        {
            if(a[i] != invalid)
            {
                minHeap.push(new Node(a[i]));
            }
        }
        while(minHeap.size()>1)
        {
            Node* lchild = minHeap.top();
            minHeap.pop();
            Node* rchild = minHeap.top();
            minHeap.pop();
            Node* parent= new Node(lchild->_w + rchild->_w);
            parent->_lchild = lchild;
            parent->_rchild = rchild;
            minHeap.push(parent);
            lchild ->_parent = parent;
            rchild ->_parent = parent;
        }
        _root = minHeap.top();
    }
    Node* GetRoot()
    {
        return _root;
    }
private:
    Node* _root;
};
