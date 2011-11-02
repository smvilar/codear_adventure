//----------------------------------------------------------------------------//
inline void World::removeObject(const std::string &name)
{
	removeObject(getObject(name));
}
//----------------------------------------------------------------------------//
inline Scene& World::getScene()
{
	return scene_;
}
//----------------------------------------------------------------------------//
inline ResourceManager& World::getResourceManager()
{
	return resourceManager_;
}
//----------------------------------------------------------------------------//
