#include "pch.h"
#include "features/common.h"
#include "core/tracking.h"

namespace
{
	void GiveItem(const char* name, int count)
	{
		void* pm = Comp(&GetPlayerManager);
		if (!pm || !PlayerManager_AddItemCONSOLE) return;
		System_String* str = MakeString(name);
		if (!str) return;
		PlayerManager_AddItemCONSOLE(pm, str, count, 1.0f, nullptr);
	}

	void RepairAllItems()
	{
		if (!GearItem_SetNormalizedHP) return;
		Tracking::GearList().for_each([](void* gi)
			{
				if (gi) GearItem_SetNormalizedHP(gi, 1.0f, true, nullptr);
			});
	}

	// Manufacturer: sets weight override through the Inventory component.
	class UnlimitedWeightFeature : public Feature
	{
	public:
		UnlimitedWeightFeature() : Feature("Inventory", "Unlimited Weight") {}

		void OnTick() override
		{
			void* inv = Comp(&GM_GetInventory);
			if (!inv) return;
			uintptr_t a = reinterpret_cast<uintptr_t>(inv);
			WriteBool(a, Offsets::InvForceOverrideWeight, true);
			WriteInt64(a, Offsets::InvOverridedWeight, 0);
		}
	};

	// Keeps every tracked gear item at full condition.
	class RepairAllContinuousFeature : public Feature
	{
	public:
		RepairAllContinuousFeature() : Feature("Inventory", "All Items 100%") {}

		void OnTick() override
		{
			RepairAllItems();
		}
	};

	class NoDecayFeature : public Feature
	{
	public:
		NoDecayFeature() : Feature("Inventory", "Items Never Decay") {}

		void OnTick() override
		{
			Tracking::GearList().for_each([](void* gi)
				{
					if (!gi) return;
					uintptr_t a = reinterpret_cast<uintptr_t>(gi);
					WriteBool(a, Offsets::GearHaltDecay, true);
					WriteFloat(a, Offsets::GearDecayScalar, 0.0f);
				});
		}
	};

	class SpawnItemFeature : public Feature
	{
	public:
		SpawnItemFeature() : Feature("Inventory", "Spawn Item") {}

		bool IsAction() const override { return true; }

		void OnAction() override
		{
			GiveItem(m_name, m_count);
		}

		void OnMenu() override
		{
			ImGui::SetNextItemWidth(220.0f);
			ImGui::InputTextWithHint("Name", "e.g. GEAR_Knife", m_name, sizeof(m_name));
			ImGui::SliderInt("Count", &m_count, 1, 100);
		}

	private:
		char m_name[128] = "GEAR_Knife";
		int m_count = 1;
	};

	REGISTER_FEATURE(UnlimitedWeightFeature)
	REGISTER_FEATURE(RepairAllContinuousFeature)
	REGISTER_FEATURE(NoDecayFeature)
	REGISTER_FEATURE(SpawnItemFeature)

	REGISTER_FEATURE_AS(RepairAllAction, ActionFeature, "Inventory", "Repair All Items", RepairAllItems)
	REGISTER_FEATURE_AS(AddAllGearAction, ActionFeature, "Inventory", "Add All Gear", [] { if (Console_AddAllGear) Console_AddAllGear(nullptr); })
	REGISTER_FEATURE_AS(BuffsAddAllAction, ActionFeature, "Inventory", "Add All Buffs", [] { if (Console_BuffsAddAll) Console_BuffsAddAll(nullptr); })
	REGISTER_FEATURE_AS(ForceWeightAction, ActionFeature, "Inventory", "Force Gear Weight (console)", [] { if (Console_ForceGearWeight) Console_ForceGearWeight(nullptr); })
	REGISTER_FEATURE_AS(ResetWeightAction, ActionFeature, "Inventory", "Reset Forced Weight", [] { if (Console_ResetForcedGearWeight) Console_ResetForcedGearWeight(nullptr); })
	REGISTER_FEATURE_AS(DropLitItemAction, ActionFeature, "Inventory", "Drop Lit Item In Hands", [] { if (Console_DropLitItemInHands) Console_DropLitItemInHands(nullptr); })
	REGISTER_FEATURE_AS(UseBestGearAction, ActionFeature, "Inventory", "Use Best Gear Item", [] { if (Console_UseBestGearItem) Console_UseBestGearItem(nullptr); })

	REGISTER_FEATURE_AS(GiveKnife, ActionFeature, "Inventory", "Give Knife", [] { GiveItem("GEAR_Knife", 1); })
	REGISTER_FEATURE_AS(GiveHatchet, ActionFeature, "Inventory", "Give Hatchet", [] { GiveItem("GEAR_Hatchet", 1); })
	REGISTER_FEATURE_AS(GiveHacksaw, ActionFeature, "Inventory", "Give Hacksaw", [] { GiveItem("GEAR_Hacksaw", 1); })
	REGISTER_FEATURE_AS(GiveHammer, ActionFeature, "Inventory", "Give Hammer", [] { GiveItem("GEAR_Hammer", 1); })
	REGISTER_FEATURE_AS(GivePrybar, ActionFeature, "Inventory", "Give Prybar", [] { GiveItem("GEAR_Prybar", 1); })
	REGISTER_FEATURE_AS(GiveRifle, ActionFeature, "Inventory", "Give Rifle", [] { GiveItem("GEAR_Rifle", 1); })
	REGISTER_FEATURE_AS(GiveRevolver, ActionFeature, "Inventory", "Give Revolver", [] { GiveItem("GEAR_Revolver", 1); })
	REGISTER_FEATURE_AS(GiveBow, ActionFeature, "Inventory", "Give Bow", [] { GiveItem("GEAR_Bow", 1); })
	REGISTER_FEATURE_AS(GiveBearSpear, ActionFeature, "Inventory", "Give Bear Spear", [] { GiveItem("GEAR_BearSpear", 1); })
	REGISTER_FEATURE_AS(GiveFlareGun, ActionFeature, "Inventory", "Give Flare Gun", [] { GiveItem("GEAR_FlareGun", 1); })
	REGISTER_FEATURE_AS(GiveAmmo, ActionFeature, "Inventory", "Give Rifle Ammo", [] { GiveItem("GEAR_RifleAmmoSingle", 20); })
	REGISTER_FEATURE_AS(GiveRevolverAmmo, ActionFeature, "Inventory", "Give Revolver Ammo", [] { GiveItem("GEAR_RevolverAmmoSingle", 20); })
	REGISTER_FEATURE_AS(GiveArrow, ActionFeature, "Inventory", "Give Arrows", [] { GiveItem("GEAR_Arrow", 10); })
	REGISTER_FEATURE_AS(GiveFlareAmmo, ActionFeature, "Inventory", "Give Flare Shells", [] { GiveItem("GEAR_FlareGunAmmoSingle", 10); })
	REGISTER_FEATURE_AS(GiveMatches, ActionFeature, "Inventory", "Give Firestriker", [] { GiveItem("GEAR_Firestriker", 1); })
	REGISTER_FEATURE_AS(GiveFlintSteel, ActionFeature, "Inventory", "Give Flint & Steel", [] { GiveItem("GEAR_FlintAndSteel", 1); })
	REGISTER_FEATURE_AS(GiveTinder, ActionFeature, "Inventory", "Give Tinder", [] { GiveItem("GEAR_Tinder", 20); })
	REGISTER_FEATURE_AS(GiveCattailTinder, ActionFeature, "Inventory", "Give Cattail Tinder", [] { GiveItem("GEAR_CattailTinder", 20); })
	REGISTER_FEATURE_AS(GiveWater, ActionFeature, "Inventory", "Give Water", [] { GiveItem("GEAR_WaterSupplyPotable", 3); })
	REGISTER_FEATURE_AS(GiveBandage, ActionFeature, "Inventory", "Give Bandages", [] { GiveItem("GEAR_HeavyBandage", 10); })
	REGISTER_FEATURE_AS(GivePainkillers, ActionFeature, "Inventory", "Give Painkillers", [] { GiveItem("GEAR_BottlePainKillers", 10); })
	REGISTER_FEATURE_AS(GiveAntibiotics, ActionFeature, "Inventory", "Give Antibiotics", [] { GiveItem("GEAR_BottleAntibiotics", 10); })
	REGISTER_FEATURE_AS(GiveStim, ActionFeature, "Inventory", "Give Emergency Stim", [] { GiveItem("GEAR_EmergencyStim", 5); })
	REGISTER_FEATURE_AS(GiveBedRoll, ActionFeature, "Inventory", "Give Bed Roll", [] { GiveItem("GEAR_BedRoll", 1); })
	REGISTER_FEATURE_AS(GiveRope, ActionFeature, "Inventory", "Give Rope", [] { GiveItem("GEAR_Rope", 5); })
	REGISTER_FEATURE_AS(GiveLampFuel, ActionFeature, "Inventory", "Give Lamp Fuel", [] { GiveItem("GEAR_LampFuel", 5); })
	REGISTER_FEATURE_AS(GiveJerrycan, ActionFeature, "Inventory", "Give Jerry Can", [] { GiveItem("GEAR_JerrycanRusty", 1); })
	REGISTER_FEATURE_AS(GiveGunpowder, ActionFeature, "Inventory", "Give Gunpowder", [] { GiveItem("GEAR_GunpowderCan", 1); })
}
