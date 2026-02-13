#pragma once

#include"Common.h"

class ThreadCache//线程缓存
{
public:
	//申请和释放内存对象
	void* Allocate(size_t size);
	void Deallocate(void* ptr, size_t size);

	//从中心缓存获取对象
	void* FetchFromCentralCache(size_t index, size_t size);

	//释放对象时候 链表过长 回收内存到中心缓存
	void ListTooLong(FreeList& list, size_t size);

private:
	FreeList _freeLists[NFREELIST];
};

// TLS thread local storage是为了fa'm'h'z
static _declspec(thread) ThreadCache* pTLSThreadCache = nullptr;
//线程TLS就像是给每个线程发的“员工个人储物柜”
//——你的东西你自己随便放、随时取，
//不用担心被同事拿错或弄乱，也不用排队等开公共柜子的锁。