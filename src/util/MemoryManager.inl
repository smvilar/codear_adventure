//----------------------------------------------------------------------------//
inline u32 MemoryManager::getNumBytes()
{
	return m_numBytesAlloc;
}
//----------------------------------------------------------------------------//
inline u32 MemoryManager::getPeakBytes()
{
	return m_maxBytesAlloc;
}
//----------------------------------------------------------------------------//
inline u32 MemoryManager::getNumBlocks()
{
	return m_numBlocks;
}
//----------------------------------------------------------------------------//
