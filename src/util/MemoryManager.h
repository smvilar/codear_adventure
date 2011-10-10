#ifndef FORAGERS_MEMORYMANAGER_H
#define FORAGERS_MEMORYMANAGER_H
//----------------------------------------------------------------------------//
//#define USE_MEMORY_MANAGER
//----------------------------------------------------------------------------//
#ifndef USE_MEMORY_MANAGER
//----------------------------------------------------------------------------//
#define NEW			new
#define DELETE		delete
//----------------------------------------------------------------------------//
#else // USE_MEMORY_MANAGER
//----------------------------------------------------------------------------//
#include "DllExport.h"
#include "core/Types.h"
//----------------------------------------------------------------------------//
namespace foragers
{
//----------------------------------------------------------------------------//
class ENGINE_API MemoryManager
{
private:
	struct Block
	{
		size_t Size;
		const char* File;
		u32 Line;
		bool IsArray;
		Block* Prev;
		Block* Next;
	};

	static Block* m_pHead;
	static Block* m_pTail;

	static u32 m_numBlocks;
	static u32 m_numBytesAlloc;
	static u32 m_maxBytesAlloc;
	static u32 m_numAlloc;
	static u32 m_numDealloc;

	static void insertBlock(Block* pBlock);
	static void removeBlock(Block* pBlock);

public:
	static u32 getNumBytes();
	static u32 getPeakBytes();
	static u32 getNumBlocks();

	static void generateReport(const char* filename);

public:
	static void* allocate(size_t size, char* file, u32 line, bool isArray);
	static void deallocate(char* addr, bool isArray);
};
//----------------------------------------------------------------------------//
#include "MemoryManager.inl"
//----------------------------------------------------------------------------//
} // end namespace foragers
//----------------------------------------------------------------------------//
#define NEW			new(__FILE__,__LINE__)
#define DELETE		delete
//----------------------------------------------------------------------------//
void* operator new		(size_t size);
void* operator new[]	(size_t size);
void* operator new		(size_t size, char* file, thr::u32 line);
void* operator new[]	(size_t size, char* file, thr::u32 line);
void operator delete	(void* addr);
void operator delete[]	(void* addr);
void operator delete	(void* addr, char* file, thr::u32 line);
void operator delete[]	(void* addr, char* file, thr::u32 line);
//----------------------------------------------------------------------------//
#endif // USE_MEMORY_MANAGER
//----------------------------------------------------------------------------//
#endif // FORAGERS_MEMORYMANAGER_H
//----------------------------------------------------------------------------//
