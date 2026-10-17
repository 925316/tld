#include "pch.h"
#include "features/common.h"

namespace
{
	void RestoreNeeds()
	{
		if (void* f = Comp(&GetFatigue)) WriteFloat(reinterpret_cast<uintptr_t>(f), Offsets::CurrentFatigue, 0.0f);
		if (void* fr = Comp(&GetFreezing)) WriteFloat(reinterpret_cast<uintptr_t>(fr), Offsets::CurrentFreezing, 0.0f);
		if (void* h = Comp(&GetHunger))
		{
			uintptr_t a = reinterpret_cast<uintptr_t>(h);
			WriteFloat(a, Offsets::CurrentCalories, ReadFloat(a, Offsets::MaxCalories));
		}
		if (void* t = Comp(&GetThirst)) WriteFloat(reinterpret_cast<uintptr_t>(t), Offsets::CurrentThirst, 0.0f);
	}

	// Suppresses the scent indicator through the game's own setter.
	class NoScentFeature : public Feature
	{
	public:
		NoScentFeature() : Feature("Needs", "No Scent") {}

		void OnTick() override
		{
			void* inv = Comp(&GM_GetInventory);
			if (inv && Inventory_SetSuppressScent) Inventory_SetSuppressScent(inv, true, nullptr);
		}
	};

	REGISTER_FEATURE(NoScentFeature)
	REGISTER_FEATURE_AS(RestoreNeedsAction, ActionFeature, "Needs", "Restore Needs", RestoreNeeds)

	REGISTER_FEATURE_AS(FatigueRateScale, SliderFloatFeature, "Needs", "Fatigue Rate Scale", &GetPlayerManager,
		Offsets::PlayerFatigueRateScale, 0.0f, 0.0f, 5.0f, "%.2f")
	REGISTER_FEATURE_AS(FreezingRateScale, SliderFloatFeature, "Needs", "Freezing Rate Scale", &GetPlayerManager,
		Offsets::PlayerFreezingRateScale, 0.0f, 0.0f, 5.0f, "%.2f")

	REGISTER_FEATURE_AS(SetFatigue, SliderFloatFeature, "Needs", "Set Fatigue", &GetFatigue,
		Offsets::CurrentFatigue, 0.0f, 0.0f, 100.0f, "%.0f")
	REGISTER_FEATURE_AS(SetMaxFatigue, SliderFloatFeature, "Needs", "Set Max Fatigue", &GetFatigue,
		Offsets::MaxFatigue, 100.0f, 10.0f, 500.0f, "%.0f")
	REGISTER_FEATURE_AS(SetFreezing, SliderFloatFeature, "Needs", "Set Freezing", &GetFreezing,
		Offsets::CurrentFreezing, 0.0f, 0.0f, 100.0f, "%.0f")
	REGISTER_FEATURE_AS(SetMaxFreezing, SliderFloatFeature, "Needs", "Set Max Freezing", &GetFreezing,
		Offsets::MaxFreezing, 100.0f, 10.0f, 500.0f, "%.0f")
	REGISTER_FEATURE_AS(SetCalories, SliderFloatFeature, "Needs", "Set Calories", &GetHunger,
		Offsets::CurrentCalories, 2500.0f, 0.0f, 10000.0f, "%.0f")
	REGISTER_FEATURE_AS(SetMaxCalories, SliderFloatFeature, "Needs", "Set Max Calories", &GetHunger,
		Offsets::MaxCalories, 2500.0f, 100.0f, 20000.0f, "%.0f")
	REGISTER_FEATURE_AS(SetThirst, SliderFloatFeature, "Needs", "Set Thirst", &GetThirst,
		Offsets::CurrentThirst, 0.0f, 0.0f, 100.0f, "%.0f")
	REGISTER_FEATURE_AS(SetMaxThirst, SliderFloatFeature, "Needs", "Set Max Thirst", &GetThirst,
		Offsets::MaxThirst, 100.0f, 10.0f, 500.0f, "%.0f")
}
