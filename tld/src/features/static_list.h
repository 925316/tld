#pragma once

#include "core/game.h"
#include "core/il2cpp_api.h"

// Iterates every element of a static List<T> field (found by class name).
// Used for systems that expose their instances through a static list
// (HarvestableManager.m_Harvestables, MapDetailManager.s_MapDetails, ...).
inline void* CachedClass(const char* className)
{
	static std::map<std::string, void*> cache;
	auto it = cache.find(className);
	if (it != cache.end()) return it->second;

	void* klass = Il2Cpp::FindClass("", className);
	cache[className] = klass;
	return klass;
}

template<typename F>
inline bool ForEachStaticList(const char* className, const char* fieldName, F&& func)
{
	void* klass = CachedClass(className);
	if (!klass) return false;

	void* list = Il2Cpp::GetStaticFieldValue(klass, fieldName);
	if (!list) return false;

	void* items = ManagedListItems(list);
	int count = ManagedListCount(list);
	if (count > 65536) count = 65536;
	for (int i = 0; i < count; ++i)
	{
		if (void* item = ManagedArrayAt(items, i)) func(item);
	}
	return true;
}
