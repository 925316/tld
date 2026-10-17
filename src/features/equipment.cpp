#include "pch.h"
#include "features/common.h"
#include "core/tracking.h"

namespace
{
	template<typename F>
	void ForEachGearItem(F&& func)
	{
		Tracking::GearList().for_each([&](void* gi)
			{
				if (gi) func(gi);
			});
	}

	// Applies a subcomponent action to every gear item that exposes the
	// given subcomponent field.
	template<typename F>
	void ForEachSubcomponent(uintptr_t fieldOffset, F&& func)
	{
		ForEachGearItem([&](void* gi)
			{
				void* component = ReadPtr(reinterpret_cast<uintptr_t>(gi), fieldOffset);
				if (component) func(component);
			});
	}

	class ClothingDryFeature : public Feature
	{
	public:
		ClothingDryFeature() : Feature("Equipment", "Clothing Never Wet") {}

		void OnTick() override
		{
			ForEachSubcomponent(Offsets::GearClothingItem, [](void* c)
				{
					WriteFloat(reinterpret_cast<uintptr_t>(c), Offsets::ClothingPercentWet, 0.0f);
				});
		}
	};

	class ClothingThawFeature : public Feature
	{
	public:
		ClothingThawFeature() : Feature("Equipment", "Clothing Never Frozen") {}

		void OnTick() override
		{
			ForEachSubcomponent(Offsets::GearClothingItem, [](void* c)
				{
					WriteFloat(reinterpret_cast<uintptr_t>(c), Offsets::ClothingPercentFrozen, 0.0f);
				});
		}
	};

	class ClothingWarmthFeature : public Feature
	{
	public:
		ClothingWarmthFeature() : Feature("Equipment", "Clothing Warmth Boost") {}

		void OnTick() override
		{
			ForEachSubcomponent(Offsets::GearClothingItem, [&](void* c)
				{
					uintptr_t a = reinterpret_cast<uintptr_t>(c);
					WriteFloat(a, Offsets::ClothingWarmth, m_warmth);
					WriteFloat(a, Offsets::ClothingWindproof, m_windproof);
				});
		}

		void OnMenu() override
		{
			ImGui::SliderFloat("Warmth", &m_warmth, 0.0f, 50.0f, "%.0f");
			ImGui::SliderFloat("Windproof", &m_windproof, 0.0f, 50.0f, "%.0f");
		}

	private:
		float m_warmth = 20.0f;
		float m_windproof = 20.0f;
	};

	class ClothingWaterproofFeature : public Feature
	{
	public:
		ClothingWaterproofFeature() : Feature("Equipment", "Clothing Waterproof") {}

		void OnTick() override
		{
			ForEachSubcomponent(Offsets::GearClothingItem, [](void* c)
				{
					WriteFloat(reinterpret_cast<uintptr_t>(c), Offsets::ClothingWaterproofness, 1.0f);
				});
		}
	};

	class TorchInfiniteFeature : public Feature
	{
	public:
		TorchInfiniteFeature() : Feature("Equipment", "Torch Infinite Burn") {}

		void OnTick() override
		{
			ForEachSubcomponent(Offsets::GearTorchItem, [](void* c)
				{
					WriteFloat(reinterpret_cast<uintptr_t>(c), Offsets::TorchElapsedBurn, 0.0f);
				});
		}
	};

	class TorchNoWindFeature : public Feature
	{
	public:
		TorchNoWindFeature() : Feature("Equipment", "Torch No Wind Blowout") {}

		void OnTick() override
		{
			ForEachSubcomponent(Offsets::GearTorchItem, [](void* c)
				{
					WriteFloat(reinterpret_cast<uintptr_t>(c), Offsets::TorchWindExtinguish, 9999.0f);
				});
		}
	};

	class LampInfiniteFuelFeature : public Feature
	{
	public:
		LampInfiniteFuelFeature() : Feature("Equipment", "Lamp Infinite Fuel") {}

		void OnTick() override
		{
			ForEachSubcomponent(Offsets::GearKeroseneLampItem, [](void* c)
				{
					uintptr_t a = reinterpret_cast<uintptr_t>(c);
					WriteFloat(a, Offsets::LampCurrentFuel, ReadFloat(a, Offsets::LampMaxFuel));
				});
		}
	};

	class FlashlightBatteryFeature : public Feature
	{
	public:
		FlashlightBatteryFeature() : Feature("Equipment", "Flashlight Infinite Battery") {}

		void OnTick() override
		{
			ForEachSubcomponent(Offsets::GearFlashlightItem, [](void* c)
				{
					WriteFloat(reinterpret_cast<uintptr_t>(c), Offsets::FlashlightBattery, 1.0f);
				});
		}
	};

	class FlareInfiniteFeature : public Feature
	{
	public:
		FlareInfiniteFeature() : Feature("Equipment", "Flare Infinite Burn") {}

		void OnTick() override
		{
			ForEachSubcomponent(Offsets::GearFlareItem, [](void* c)
				{
					WriteFloat(reinterpret_cast<uintptr_t>(c), Offsets::FlareElapsedBurn, 0.0f);
				});
		}
	};

	class FoodFreshFeature : public Feature
	{
	public:
		FoodFreshFeature() : Feature("Equipment", "Food Never Spoils") {}

		void OnTick() override
		{
			ForEachSubcomponent(Offsets::GearFoodItem, [](void* c)
				{
					uintptr_t a = reinterpret_cast<uintptr_t>(c);
					WriteFloat(a, Offsets::FoodCaloriesRemaining, ReadFloat(a, Offsets::FoodCaloriesTotal));
					WriteFloat(a, Offsets::FoodHeatPercent, 1.0f);
				});
		}
	};

	class FoodNoPoisonFeature : public Feature
	{
	public:
		FoodNoPoisonFeature() : Feature("Equipment", "Food No Poisoning") {}

		void OnTick() override
		{
			ForEachSubcomponent(Offsets::GearFoodItem, [](void* c)
				{
					WriteFloat(reinterpret_cast<uintptr_t>(c), Offsets::FoodChancePoisoning, 0.0f);
				});
		}
	};

	class WaterInfiniteFeature : public Feature
	{
	public:
		WaterInfiniteFeature() : Feature("Equipment", "Water Supply Full") {}

		void OnTick() override
		{
			ForEachSubcomponent(Offsets::GearWaterSupply, [](void* c)
				{
					WriteFloat(reinterpret_cast<uintptr_t>(c), Offsets::WaterVolume, 10.0f);
				});
		}
	};

	class ToolNoDegradeFeature : public Feature
	{
	public:
		ToolNoDegradeFeature() : Feature("Equipment", "Tools No Degrade") {}

		void OnTick() override
		{
			ForEachSubcomponent(Offsets::GearDegradeOnUse, [](void* c)
				{
					WriteFloat(reinterpret_cast<uintptr_t>(c), Offsets::DegradeHP, 0.0f);
				});
		}
	};

	REGISTER_FEATURE(ClothingDryFeature)
	REGISTER_FEATURE(ClothingThawFeature)
	REGISTER_FEATURE(ClothingWarmthFeature)
	REGISTER_FEATURE(ClothingWaterproofFeature)
	REGISTER_FEATURE(TorchInfiniteFeature)
	REGISTER_FEATURE(TorchNoWindFeature)
	REGISTER_FEATURE(LampInfiniteFuelFeature)
	REGISTER_FEATURE(FlashlightBatteryFeature)
	REGISTER_FEATURE(FlareInfiniteFeature)
	REGISTER_FEATURE(FoodFreshFeature)
	REGISTER_FEATURE(FoodNoPoisonFeature)
	REGISTER_FEATURE(WaterInfiniteFeature)
	REGISTER_FEATURE(ToolNoDegradeFeature)

	// Repair/sharpening subcomponents (per gear item).
	class RepairNeverFailFeature : public Feature
	{
	public:
		RepairNeverFailFeature() : Feature("Equipment", "Repair Never Fails") {}

		void OnTick() override
		{
			ForEachSubcomponent(Offsets::GearRepairable, [](void* c)
				{
					WriteBool(reinterpret_cast<uintptr_t>(c), Offsets::RepairNeverFail, true);
				});
		}
	};

	class SharpenBoostFeature : public Feature
	{
	public:
		SharpenBoostFeature() : Feature("Equipment", "Sharpen Condition Boost") {}

		void OnTick() override
		{
			ForEachSubcomponent(Offsets::GearSharpenable, [&](void* c)
				{
					WriteFloat(reinterpret_cast<uintptr_t>(c), Offsets::SharpenConditionIncreaseMin, m_amount);
				});
		}

		void OnMenu() override
		{
			ImGui::SliderFloat("Increase", &m_amount, 0.0f, 50.0f, "%.0f");
		}

	private:
		float m_amount = 10.0f;
	};

	REGISTER_FEATURE(RepairNeverFailFeature)
	REGISTER_FEATURE(SharpenBoostFeature)
}
