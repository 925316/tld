#include "pch.h"
#include "features/common.h"
#include "features/static_list.h"

namespace
{
	// HarvestableManager keeps a static List<Harvestable> m_Harvestables.
	class HarvestAlwaysReadyFeature : public Feature
	{
	public:
		HarvestAlwaysReadyFeature() : Feature("World", "Harvestables Always Ready") {}

		void OnTick() override
		{
			ForEachStaticList("HarvestableManager", "m_Harvestables", [](void* harvestable)
				{
					uintptr_t a = reinterpret_cast<uintptr_t>(harvestable);
					WriteBool(a, Offsets::HarvestableHarvested, false);
					WriteFloat(a, Offsets::HarvestableRefreshMin, 0.0f);
					WriteFloat(a, Offsets::HarvestableRefreshMax, 0.0f);
				});
		}
	};

	class HarvestExtraUnitsFeature : public Feature
	{
	public:
		HarvestExtraUnitsFeature() : Feature("World", "Harvestable Extra Units") {}

		void OnTick() override
		{
			ForEachStaticList("HarvestableManager", "m_Harvestables", [&](void* harvestable)
				{
					uintptr_t a = reinterpret_cast<uintptr_t>(harvestable);
					WriteInt(a, Offsets::HarvestableNumPrimary, m_units);
					WriteInt(a, Offsets::HarvestableNumSecondary, m_units);
				});
		}

		void OnMenu() override { ImGui::SliderInt("Units", &m_units, 1, 200); }

	private:
		int m_units = 50;
	};

	REGISTER_FEATURE(HarvestAlwaysReadyFeature)
	REGISTER_FEATURE(HarvestExtraUnitsFeature)
}
