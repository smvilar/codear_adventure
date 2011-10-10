//----------------------------------------------------------------------------//
template <class ResType>
boost::shared_ptr<ResType> ResourceManager::get(const char* name)
{
	// first check in the map
	ResourceMap::iterator it = _resMap.find(name);
	if (it != _resMap.end())
	{
		// found, return it
		return boost::static_pointer_cast<ResType, IResource>(it->second);
	}
	// then create a new one and store it in the map
	ResType* res = new ResType;
	res->loadFromFile(name);
	return add(name, res);
}
//----------------------------------------------------------------------------//
template <class ResType>
boost::shared_ptr<ResType> ResourceManager::add(const char* name, ResType* res)
{
	boost::shared_ptr<ResType> ptr(res);
	_resMap[name] = ptr;
	return ptr;
}
//----------------------------------------------------------------------------//
