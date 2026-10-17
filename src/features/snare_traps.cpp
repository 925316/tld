#include "pch.h"
#include "features/common.h"
#include "features/gear_iter.h"

namespace
{
	class SnareChanceFeature : public Feature
	{
	public:
		SnareChanceFeature() : Feature("Crafting", "Snare Always Catches") {}

		void OnTick() override
		{
			ForEachGearSubcomponent(Offsets::GearSnareItem, [](void* snare)
				{
					uintptr_t a = reinterpret_cast<uintptr_t>(snare);
					WriteFloat(a, 0x58, 1.0f); // m_ChanceSpawnCarcassOnRoll
					WriteFloat(a, 0x5C, 0.0f); // m_ChanceBreakOnRoll
					WriteFloat(a, 0x54, 0.0f); // m_HoursBeforeRoll
				});
		}
	};

	class SnareNeverBreaksFeature : public Feature
	{
	public:
		SnareNeverBreaksFeature() : Feature("Crafting", "Snare Never Breaks") {}

		void OnTick() override
		{
			ForEachGearSubcomponent(Offsets::GearSnareItem, [](void* snare)
				{
					WriteFloat(reinterpret_cast<uintptr_t>(snare), 0x5C, 0.0f);
				});
		}
	};

	REGISTER_FEATURE(SnareChanceFeature)
	REGISTER_FEATURE(SnareNeverBreaksFeature)
}
