#include "HuffmanTree.hpp"
#include <string>
#include <fstream>
#include <assert.h>
#include <iostream>
#include <algorithm>
typedef long long  LongType;
struct CharInfo
{
    char _ch;//字符
    LongType _count;//出现次数
    string _code;//哈夫曼编码
    
    CharInfo operator+(const CharInfo& ch)
    {
        CharInfo ret;
        ret._count =  _count + ch._count;
        return ret;
    }
    bool operator>(const CharInfo& ch)
    {
        return _count > ch._count;
    }
    bool operator!=(const CharInfo& ch)
    {
        return _count != ch._count;
    }
};
struct ConfigInfo
{
    char _ch;//字符
    LongType _count;//出现次数
};
class FileCompress
{
    typedef HuffmanNode<CharInfo> Node;
public: 
    FileCompress()
    {
        size_t i=0;
        for(;i<256;++i)
        {
            info[i]._ch = i;
            info[i]._count = 0;
        }
    }
    /*********************
     * 功能：压缩文件
     * 参数：
     *  file:文件名
     ********************/
    void Compress(const char* file)
    {
        //1.读取文件内容，统计字符出现次数
        ifstream ifs(file);
        unsigned char ch;
        ifs>>noskipws;
        while(ifs>>ch)
        {
            cout<<int(ch)<<endl;
            ++info[ch]._count;
        }
        //2.构建哈夫曼树
        CharInfo invalid;        
        invalid._count = 0;
        HuffmanTree<CharInfo> t(info,256,invalid);
        //3.哈夫曼编码
        HuffmanCode(t.GetRoot());
        //4.压缩
        ifs.clear();
        ifs.seekg(0);
        string filename = file;
        filename += ".Huffman";
        ofstream ofs(filename.c_str());
        //4.1写入字符和字符出现的次数(解压需要重新构建树)
        ConfigInfo con;
        size_t i=0;
        for(;i<256;++i)
        {
            if(info[i]._count > 0)
            {
                con._ch = info[i]._ch;
                con._count = info[i]._count;
                ofs.write((char*)&con,sizeof(con));
            }
        }
        con._count = 0;
        ofs.write((char*)&con,sizeof(con));
        //4.2写入文件内容
        char value = 0;
        size_t pos = 0;
        while(ifs>>ch)
        {
            string& code = info[(unsigned char)ch]._code;
            size_t i=0;
            for(;i<code.size();++i)
            {
                if(code[i] == '1')
                {
                    value |= 1<<pos;
                }
                else if(code[i] == '0')
                {
                    value &= ~(1<<pos);
                }
                else 
                {
                    assert(false);
                }
                ++pos;
                if(pos == 8)
                {
                    ofs<<value;
                    pos = 0;
                    value = 0;
                }
            }
        }
        if(pos != 0)
            ofs<<value;
    }
    void HuffmanCode(Node* root)
    {
        if(root == NULL)
            return;
        //1.找到各个叶子结点
        //2.由叶子结点自下而上编码,左孩子编码0，右孩子编码1
        if(root->_lchild == NULL &&
           root->_rchild == NULL)
        {
            string& code = info[(unsigned char)root->_w._ch]._code;
            Node* parent = root->_parent;
            while(parent !=NULL)
            {
                if(parent->_lchild == root)
                {
                    code += '0';
                }
                else if(parent->_rchild == root)
                {
                    code += '1';
                }
                else 
                {
                    //出错了
                    assert(false);
                }
                root = parent;
                parent = parent->_parent;
            }
            reverse(code.begin(),code.end());
            return ;
        }
        HuffmanCode(root->_lchild);
        HuffmanCode(root->_rchild);
    }
    /*********************
     * 功能：解压文件
     * 参数：
     *  file:文件名
     ********************/
    void UnCompress(const char* file)
    {
        //1.读取字符出现次数
        ifstream ifs(file);
        ConfigInfo con;
        do
        {
            ifs.read((char*)&con,sizeof(con));
            if(con._count == 0)
                break;
            info[(unsigned char)con._ch]._count = con._count;
        }while(con._count>0);
        //2.重建哈夫曼树
        CharInfo invalid;
        invalid._count = 0;
        HuffmanTree<CharInfo> t(info,256,invalid);
        //3.解码文件内容，写入新文件
        string filename = file;
        size_t pos = filename.rfind('.');
        assert(pos != -1);
        filename.erase(pos);
        filename += ".unhuffman";
        ofstream ofs(filename.c_str());
        char ch;
        Node* root = t.GetRoot();
        size_t size = root->_w._count;
        while(ifs>>ch)
        {
            size_t i=0;
            for(;i<8;++i)
            {
                if(ch & (1<<i))
                {
                    root = root->_rchild; 
                }
                else 
                {
                    root = root->_lchild;
                }
                if(root ->_lchild == NULL&&
                   root ->_rchild == NULL)
                {
                    ofs<<root->_w._ch;
                    cout<<root->_w._ch<<":"<<int(root->_w._ch)<<endl;
                    if(--size == 0)
                    {
                        return;
                    }
                    root = t.GetRoot();
                }
            }
        }
    }
private:
    CharInfo info[256];//所有可能出现的字符，哈希直接定址法
};
