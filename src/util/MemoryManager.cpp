#include "util/MemoryManager.h"
//----------------------------------------------------------------------------//
#ifdef USE_MEMORY_MANAGER
//----------------------------------------------------------------------------//
#include <cstdlib>
#include <fstream>
#include "core/Assert.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
MemoryManager::Block* MemoryManager::m_pHead = NULL;
MemoryManager::Block* MemoryManager::m_pTail = NULL;
u32 MemoryManager::m_numBlocks = 0;
u32 MemoryManager::m_numBytesAlloc = 0;
u32 MemoryManager::m_maxBytesAlloc = 0;
u32 MemoryManager::m_numAlloc = 0;
u32 MemoryManager::m_numDealloc = 0;
//----------------------------------------------------------------------------//
void* MemoryManager::allocate(size_t size, char* file, u32 line, bool isArray)
{
	++m_numAlloc;

	size_t actualSize = size + sizeof(Block);
	char* addr = (char*)malloc(actualSize);
	Block* pBlock = (Block*)addr;

	pBlock->Size = size;
	pBlock->File = file;
	pBlock->Line = line;
	pBlock->IsArray = isArray;
	InsertBlock(pBlock);

	++m_numBlocks;
	m_numBytesAlloc += size;

	if (m_numBytesAlloc > m_maxBytesAlloc)
		m_maxBytesAlloc = m_numBytesAlloc;

	addr += sizeof(Block);

	return (void*)addr;
}
//----------------------------------------------------------------------------//
void MemoryManager::deallocate(char* addr, bool isArray)
{
	++m_numDealloc;

	addr -= sizeof(Block);
	Block* pBlock = (Block*)addr;
	RemoveBlock(pBlock);

	Assert(isArray == pBlock->IsArray,
		"Array mismatch in a delete call");

	Assert(m_numBlocks > 0 && m_numBytesAlloc >= pBlock->Size,
		"Unpaired number of new/deletes");

	--m_numBlocks;
	m_numBytesAlloc -= pBlock->Size;

	free(addr);
}
//----------------------------------------------------------------------------//
void MemoryManager::insertBlock(Block* pBlock)
{
	if (m_pHead)
	{
		pBlock->Prev = m_pTail;
		pBlock->Next = NULL;
		m_pTail->Next = pBlock;
		m_pTail = pBlock;
	}
	else
	{
		pBlock->Next = pBlock->Prev = NULL;
		m_pHead = pBlock;
		m_pTail = pBlock;
	}
}
//----------------------------------------------------------------------------//
void MemoryManager::removeBlock(Block* pBlock)
{
	if (pBlock->Prev)
		pBlock->Prev->Next = pBlock->Next;
	else
		m_pHead = pBlock->Next;

	if (pBlock->Next)
		pBlock->Next->Prev = pBlock->Prev;
	else
		m_pTail = pBlock->Prev;
}
//----------------------------------------------------------------------------//
void MemoryManager::generateReport(const char* filename)
{
	std::ofstream ofs(filename);
	ofs << "PeakBytes: " << m_maxBytesAlloc << std::endl
		<< "Allocate Calls: " << m_numAlloc << std::endl
		<< "Deallocate Calls: " << m_numDealloc << std::endl
		<< "Bytes leaked: " << m_numBytesAlloc << std::endl;

	Block* pBlock = m_pHead;
	while (pBlock)
	{
		ofs << "Block leaked:" << std::endl
			<< " " << pBlock->Size << " bytes" << std::endl;
		if (pBlock->File)
		{
			ofs << " " << pBlock->File << "(" << pBlock->Line << ")" << std::endl;
		}

		pBlock = pBlock->Next;
	}
}
//----------------------------------------------------------------------------//
void* operator new(size_t size)
{
	return MemoryManager::Allocate(size, 0, 0, false);
}
//----------------------------------------------------------------------------//
void* operator new[](size_t size)
{
	return MemoryManager::Allocate(size, 0, 0, true);
}
//----------------------------------------------------------------------------//
void* operator new(size_t size, char* file, thr::u32 line)
{
	return MemoryManager::Allocate(size, file, line, false);
}
//----------------------------------------------------------------------------//
void* operator new[](size_t size, char* file, thr::u32 line)
{
	return MemoryManager::Allocate(size, file, line, true);
}
//----------------------------------------------------------------------------//
void operator delete(void* addr)
{
	MemoryManager::Deallocate((char*)addr, false);
}
//----------------------------------------------------------------------------//
void operator delete[](void* addr)
{
	MemoryManager::Deallocate((char*)addr, true);
}
//----------------------------------------------------------------------------//
void operator delete(void* addr, char* /*file*/, thr::u32 /*line*/)
{
	MemoryManager::Deallocate((char*)addr, false);
}
//----------------------------------------------------------------------------//
void operator delete[](void* addr, char* /*file*/, thr::u32 /*line*/)
{
	MemoryManager::Deallocate((char*)addr, true);
}
//----------------------------------------------------------------------------//
#endif // USE_MEMORY_MANAGER
//----------------------------------------------------------------------------//
