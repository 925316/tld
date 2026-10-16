#include "pch.h"
#include "features/common.h"

namespace
{
	// FireManager keeps a static List<Fire> m_Fires at static offset 0.
	class FiresNeverDieFeature : public Feature
	{
	public:
		FiresNeverDieFeature() : Feature("Fire", "Fires Never Die") {}

		void OnTick() override
		{
			void* fm = Comp(&GM_GetFireManager);
			if (!fm) return;
			void* staticFields = StaticFields(fm);
			if (!staticFields) return;

			void* list = ReadPtr(reinterpret_cast<uintptr_t>(staticFields), 0x0);
			if (!list) return;

			void* items = ManagedListItems(list);
			int count = ManagedListCount(list);
			if (count > 4096) count = 4096;
			for (int i = 0; i < count; ++i)
			{
				if (void* fire = ManagedArrayAt(items, i))
				{
					WriteBool(reinterpret_cast<uintptr_t>(fire), Offsets::FireIsPerpetual, true);
				}
			}
		}
	};

	REGISTER_FEATURE(FiresNeverDieFeature)

	REGISTER_FEATURE_AS(FireAlwaysSucceeds, BoolFieldFeature, "Fire", "Fire Always Succeeds",
		&GM_GetFireManager, Offsets::FireForceStartSuccess, true)
	REGISTER_FEATURE_AS(InstantFireStart, FloatFieldFeature, "Fire", "Instant Fire Start",
		&GM_GetFireManager, Offsets::FireStartTimeSeconds, 0.0f)
	REGISTER_FEATURE_AS(InstantFireStartWet, FloatFieldFeature, "Fire", "Instant Fire Start (Wet)",
		&GM_GetFireManager, Offsets::FireStartTimeSecondsWet, 0.0f)
	REGISTER_FEATURE_AS(FireNoWindBlowout, FloatFieldFeature, "Fire", "No Wind Blows Out Fire",
		&GM_GetFireManager, Offsets::FireWindBlowsOut, 9999.0f)
	REGISTER_FEATURE_AS(FireStartAnyWind, FloatFieldFeature, "Fire", "Fire Startable In Any Wind",
		&GM_GetFireManager, Offsets::FireWindStartingImpossible, 9999.0f)
	REGISTER_FEATURE_AS(FireMaxDuration, SliderFloatFeature, "Fire", "Max Fire Duration (hours)",
		&GM_GetFireManager, Offsets::FireMaxDurationHours, 12.0f, 0.0f, 240.0f, "%.0f")
	REGISTER_FEATURE_AS(FireMaxHeat, SliderFloatFeature, "Fire", "Fire Max Heat Increase",
		&GM_GetFireManager, Offsets::FireMaxHeatIncrease, 20.0f, 0.0f, 100.0f, "%.0f")
}
