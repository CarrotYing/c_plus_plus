#pragma once
#include <stdarg.h>
#include <malloc.h>
#include <new>
using namespace std;
typedef void(*HANDLE_FUNC)();

//一级空间配置器 
template <int inst> 
class __MallocAllocTemplate
{
	static HANDLE_FUNC __malloc_alloc_oom_handler;

	static void* oom_malloc(size_t n)
	{
		while (1)
		{
			//如果这个函数指针没设置，就真的没空间了，抛出异常 
			if (__malloc_alloc_oom_handler == 0)
			{
				throw bad_alloc();
			}
			else
			{
				//调用函数，也许能释放一些空间 
				__malloc_alloc_oom_handler();
				void* ret = malloc(n);
				if (ret)
					return ret;
			}
		}
	}

public:

	static HANDLE_FUNC SetMallocHandler(HANDLE_FUNC f)
	{
		HANDLE_FUNC old = __malloc_alloc_oom_handler;
		__malloc_alloc_oom_handler = f;

		return old;
	}
	//申请空间 
	static void* Allocate(size_t n)
	{
		void* result = malloc(n);
		if (0 == result)
			result = oom_malloc(n);
		return result;
	}
	//释放空间 
	static void Deallocate(void *p, size_t /* n */)
	{
		free(p);
	}
};




template <bool threads, int inst>
class __DefaultAllocTemplate
{
	enum { __ALIGN = 8 };
	enum { __MAX_BYTES = 128 };
	enum { __NFREELISTS = __MAX_BYTES / __ALIGN };

	union Obj {
		union Obj* _freeListLink;
	};

	// 自由链表
	static Obj * _freeList[__NFREELISTS];

	// 内存池
	static char* _startFree;
	static char* _endFree;
	static size_t _heapSize;

	static  size_t FREELIST_INDEX(size_t bytes)
	{
		return (((bytes)+__ALIGN - 1) / __ALIGN - 1);
	}

	static size_t ROUND_UP(size_t bytes)
	{
		return (((bytes)+__ALIGN - 1) & ~(__ALIGN - 1));
	}

public:
	static char* ChunkAlloc(size_t n, size_t& nobjs)
	{
		size_t totalbytes = n*nobjs;
		size_t leftbytes = _endFree - _startFree;
		if (leftbytes >= totalbytes)
		{
			cout<<"内存池有足够20个对象大小\n";

			char* ret = _startFree;
			_startFree += totalbytes;
			return ret;
		}
		else if (leftbytes >= n)
		{
			nobjs = leftbytes / n;
			cout<<"内存池只有"<<nobjs<<"个对象\n";

			totalbytes = nobjs*n;
			char* ret = _startFree;
			_startFree += totalbytes;
			return ret;
		}
		else
		{
			cout<<"内存池一个对象都不够\n";

			// 处理内存池剩余的小块内存
			if (leftbytes > 0)
			{
				size_t index = FREELIST_INDEX(leftbytes);
				((Obj*)_startFree)->_freeListLink = _freeList[index];
				_freeList[index] = (Obj*)_startFree;
			}
			
			size_t bytesToGet = nobjs*n * 2 + ROUND_UP(_heapSize >> 4);
			cout<<"向系统申请"<<bytesToGet<<" bytes到内存池\n";

			_startFree = (char*)malloc(bytesToGet);
			if (_startFree == NULL)
			{
				// 更大的自由链表中取找找
				for (size_t i = n; i < __MAX_BYTES; i+= __ALIGN)
				{
					size_t index = FREELIST_INDEX(i);
					if (_freeList[index])
					{
						Obj* obj = _freeList[index];
						_freeList[index] = obj->_freeListLink;
						_startFree = (char*)obj;
						_endFree = _startFree + i;

						return ChunkAlloc(n, nobjs);
					}
				}

				_startFree = (char*)__MallocAllocTemplate<0>::Allocate(bytesToGet);
			}

			_endFree = _startFree + bytesToGet;
			_heapSize += bytesToGet;
			return ChunkAlloc(n, nobjs);
		}
	}

	static void* Refill(size_t n)
	{
		size_t nobjs = 20;
		char* chunk = ChunkAlloc(n, nobjs);
		if (nobjs == 1)
			return chunk;

		cout<<"向系统申请到"<<nobjs<<"个内存对象，返回一个，剩下的挂起来\n";


		Obj* cur = (Obj*)(chunk + n);
		size_t index = FREELIST_INDEX(n);
		_freeList[index] = cur;

		for (size_t i = 0; i < nobjs - 2; ++i)
		{
			Obj* next =(Obj*)((char*)cur + n);
			cur->_freeListLink = next;

			cur = next;
		}

		cur->_freeListLink = NULL;

		return chunk;
	}

	static void* Allocate(size_t n)
	{
		// 大于128.调用一级空间配置器
		if (n > 128)
		{
			cout<<"向一级空间配置器申请：<<n<<\n";
			return __MallocAllocTemplate<0>::Allocate(n);
		}

			cout<<"向二级空间配置器申请："<<n<<"\n";

		size_t index = FREELIST_INDEX(n);
		if (_freeList[index] == NULL)
		{
			return Refill(ROUND_UP(n));
		}
		else
		{
			cout<<"在freelist["<<index<<"]位置取一个内存块\n";

			Obj* obj = _freeList[index];
			_freeList[index] = obj->_freeListLink;
			return obj;
		}
	}

	static void Deallocate(void* ptr, size_t n)
	{
		if (n > __MAX_BYTES)
		{
			__MallocAllocTemplate<0>::Deallocate(ptr, n);
		}
		else
		{
			size_t index = FREELIST_INDEX(n);
			cout<<"将"<<ptr<<"挂到freeList["<<index<<"]\n";

			Obj* obj = (Obj*)ptr;
			obj->_freeListLink = _freeList[index];
			_freeList[index] = obj;
		}
	}

};
//二级空间配置器的静态变量初始化 
template <bool threads, int inst>
typename __DefaultAllocTemplate<threads, inst>::Obj*
__DefaultAllocTemplate<threads, inst>::_freeList[__NFREELISTS] = { NULL };

// 内存池
template <bool threads, int inst>
char* __DefaultAllocTemplate<threads, inst>::_startFree = NULL;

template <bool threads, int inst>
char* __DefaultAllocTemplate<threads, inst>::_endFree = NULL;

template <bool threads, int inst>
size_t __DefaultAllocTemplate<threads, inst>::_heapSize = 0;



#ifdef __USE_MALLOC
	typedef __MallocAllocTemplate<0> alloc;
#else
	typedef __DefaultAllocTemplate<false, 0> alloc;
#endif // __USE_MALLOC


template<class T, class Alloc>
class SimpleAlloc {
public:
	static T* Allocate(size_t n)
	{
		return 0 == n ? 0 : (T*)Alloc::Allocate(n * sizeof (T));
	}
	static T* Allocate(void)
	{
		return (T*)Alloc::Allocate(sizeof (T));
	}
	static void Deallocate(T *p, size_t n)
	{
		if (0 != n) Alloc::Deallocate(p, n * sizeof (T));
	}
	static void Deallocate(T *p)
	{
		Alloc::Deallocate(p, sizeof (T));
	}
};
