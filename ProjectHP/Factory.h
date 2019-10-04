#pragma once
#include <memory>
#include <string>
#include <map>
#include <functional>

class GameObject;

// template factory design pattern
template<class T, class key, class U>
class Factory
{
public:
	static std::shared_ptr<T> create(key, U i, U j);
	static bool registerit(key Id, std::shared_ptr<T>(*f)(U,U));
	static std::map<key, std::function<std::shared_ptr<T>(U,U) >> &getMap();

private:
	static std::map<key, std::function<std::shared_ptr<T>()>> m_map;
};

//=============================================================================

// creating an object
template<class T, class key, class U>
inline std::shared_ptr<T> Factory<T, key, U>::create(key Id, U i, U j)
{
	auto it = getMap().find(Id);
		if (it == getMap().end())
			return nullptr;
		return it->second(i, j);
}

//=============================================================================

// registering a new object to the map
template<class T, class key, class U>
inline bool Factory<T, key, U>::registerit(key Id, std::shared_ptr<T>(*f)(U, U))
{
	getMap().emplace(Id, f);
		return true;
}

//=============================================================================

// returning the map
template<class T, class key, class U>
inline std::map<key, std::function<std::shared_ptr<T>(U, U)>>& Factory<T, key, U>::getMap()
{
	static std::map<key, std::function<std::shared_ptr<T>(U, U)>> m_map;
	
		return m_map;
}

