#include "pch.h"
#include "core/feature.h"
#include "core/game.h"
#include "core/hooks.h"

namespace
{
	Feature* g_self = nullptr;

	FireManager_CalculateFireStartSuccess oFireStart = nullptr;
	PanelRepair_GetChanceSuccess oRepair = nullptr;
	Examine_RollForActionSuccess oExamine = nullptr;
	IceFishingHole_OnActiveFishingComplete oFishing = nullptr;

	float __fastcall hkFireStart(void* _this, void* starter, void* fuel, void* accel, void* method)
	{
		if (g_self->enabled) return 100.0f;
		return oFireStart(_this, starter, fuel, accel, method);
	}

	float __fastcall hkRepair(void* _this, void* method)
	{
		if (g_self->enabled) return 100.0f;
		return oRepair(_this, method);
	}

	bool __fastcall hkExamine(void* _this, float baseSkillChance, void* method)
	{
		if (g_self->enabled) return true;
		return oExamine(_this, baseSkillChance, method);
	}

	void __fastcall hkFishing(void* _this, bool success, bool playerCancel, float progress, void* method)
	{
		if (g_self->enabled && !playerCancel)
		{
			success = true;
		}
		oFishing(_this, success, playerCancel, progress, method);
	}

	class AlwaysSucceedFeature : public Feature
	{
	public:
		AlwaysSucceedFeature() : Feature("Player", "Always Succeed")
		{
			g_self = this;
		}

		void OnStartup(uintptr_t) override
		{
			InstallHook(Rva::FireManager_CalculateFireStartSuccess, hkFireStart, reinterpret_cast<void**>(&oFireStart), "FireManager.CalculateFireStartSuccess");
			InstallHook(Rva::PanelRepair_GetChanceSuccess, hkRepair, reinterpret_cast<void**>(&oRepair), "Panel_Repair.GetChanceSuccess");
			InstallHook(Rva::Examine_RollForActionSuccess, hkExamine, reinterpret_cast<void**>(&oExamine), "Panel_Inventory_Examine.RollForActionSuccess");
			InstallHook(Rva::IceFishingHole_OnActiveFishingComplete, hkFishing, reinterpret_cast<void**>(&oFishing), "IceFishingHole.OnActiveFishingComplete");
		}

		void OnMenu() override
		{
			ImGui::SameLine();
			ImGui::TextDisabled("fire/repair/examine/fishing rolls");
		}
	};

	REGISTER_FEATURE(AlwaysSucceedFeature)
}
