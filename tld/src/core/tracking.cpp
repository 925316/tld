#include "pch.h"
#include "core/game.h"
#include "core/hooks.h"
#include "core/tracking.h"

namespace
{
	ObjectList<void*> g_aiList;
	ObjectList<void*> g_gearList;

	BaseAiManager_Add oAiAdd = nullptr;
	BaseAiManager_Remove oAiRemove = nullptr;
	GearManager_Add oGearAdd = nullptr;
	GearManager_Remove oGearRemove = nullptr;

	// BaseAiManager.Add/Remove and GearManager.Add/Remove are STATIC in this
	// build: first arg is the tracked object itself (no this pointer).
	void hkAiAdd(void* bai, void* method)
	{
		oAiAdd(bai, method);
		g_aiList.add(bai);
	}

	void hkAiRemove(void* bai, void* method)
	{
		g_aiList.remove(bai);
		oAiRemove(bai, method);
	}

	void hkGearAdd(void* gi, void* method)
	{
		oGearAdd(gi, method);
		g_gearList.add(gi);
	}

	void hkGearRemove(void* gi, void* method)
	{
		g_gearList.remove(gi);
		oGearRemove(gi, method);
	}
}

namespace Tracking
{
	const ObjectList<void*>& AiList() { return g_aiList; }
	const ObjectList<void*>& GearList() { return g_gearList; }

	void Install()
	{
		InstallHook(Rva::BaseAiManager_Add, hkAiAdd, reinterpret_cast<void**>(&oAiAdd), "BaseAiManager.Add");
		InstallHook(Rva::BaseAiManager_Remove, hkAiRemove, reinterpret_cast<void**>(&oAiRemove), "BaseAiManager.Remove");
		InstallHook(Rva::GearManager_Add, hkGearAdd, reinterpret_cast<void**>(&oGearAdd), "GearManager.Add");
		InstallHook(Rva::GearManager_Remove, hkGearRemove, reinterpret_cast<void**>(&oGearRemove), "GearManager.Remove");
	}
}
