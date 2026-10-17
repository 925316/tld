#include "pch.h"
#include "features/common.h"
#include "features/gear_iter.h"

namespace
{
	class LureBoostFeature : public Feature
	{
	public:
		LureBoostFeature() : Feature("Fishing", "Lure Catch Boost") {}

		void OnTick() override
		{
			ForEachGearSubcomponent(Offsets::GearLureItem, [&](void* lure)
				{
					uintptr_t a = reinterpret_cast<uintptr_t>(lure);
					WriteFloat(a, 0x20, m_catch);   // m_CatchModifier
					WriteFloat(a, 0x24, m_rare);    // m_RareFishModifier
				});
		}

		void OnMenu() override
		{
			ImGui::SliderFloat("Catch", &m_catch, 0.0f, 10.0f, "%.1f");
			ImGui::SliderFloat("Rare", &m_rare, 0.0f, 10.0f, "%.1f");
		}

	private:
		float m_catch = 5.0f;
		float m_rare = 5.0f;
	};

	class BaitBoostFeature : public Feature
	{
	public:
		BaitBoostFeature() : Feature("Fishing", "Bait Weight Boost") {}

		void OnTick() override
		{
			ForEachGearSubcomponent(Offsets::GearBaitItem, [&](void* bait)
				{
					WriteFloat(reinterpret_cast<uintptr_t>(bait), 0x20, m_weight); // m_MinFishWeightModifier
				});
		}

		void OnMenu() override { ImGui::SliderFloat("Weight", &m_weight, 0.0f, 10.0f, "%.1f"); }

	private:
		float m_weight = 5.0f;
	};

	REGISTER_FEATURE(LureBoostFeature)
	REGISTER_FEATURE(BaitBoostFeature)
}
