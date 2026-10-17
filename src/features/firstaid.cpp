#include "pch.h"
#include "features/common.h"
#include "features/gear_iter.h"

namespace
{
	class FirstAidBoostFeature : public Feature
	{
	public:
		FirstAidBoostFeature() : Feature("Medical", "First Aid HP Boost") {}

		void OnTick() override
		{
			ForEachGearSubcomponent(Offsets::GearFirstAidItem, [&](void* aid)
				{
					WriteFloat(reinterpret_cast<uintptr_t>(aid), 0x38, m_hp); // m_HPIncrease
				});
		}

		void OnMenu() override { ImGui::SliderFloat("HP", &m_hp, 0.0f, 200.0f, "%.0f"); }

	private:
		float m_hp = 100.0f;
	};

	class InstantFirstAidFeature : public Feature
	{
	public:
		InstantFirstAidFeature() : Feature("Medical", "Instant First Aid") {}

		void OnTick() override
		{
			ForEachGearSubcomponent(Offsets::GearFirstAidItem, [](void* aid)
				{
					WriteFloat(reinterpret_cast<uintptr_t>(aid), 0x44, 0.0f); // m_TimeToUseSeconds
				});
		}
	};

	class FreeFirstAidFeature : public Feature
	{
	public:
		FreeFirstAidFeature() : Feature("Medical", "Free First Aid Use") {}

		void OnTick() override
		{
			ForEachGearSubcomponent(Offsets::GearFirstAidItem, [](void* aid)
				{
					WriteInt(reinterpret_cast<uintptr_t>(aid), 0x50, 0); // m_UnitsPerUse
				});
		}
	};

	class PurifyWaterFeature : public Feature
	{
	public:
		PurifyWaterFeature() : Feature("Medical", "Instant Purify Water") {}

		void OnTick() override
		{
			ForEachGearSubcomponent(Offsets::GearPurifyWater, [](void* purify)
				{
					uintptr_t a = reinterpret_cast<uintptr_t>(purify);
					WriteFloat(a, 0x28, 0.0f); // m_ProgressBarDurationSeconds
					WriteFloat(a, 0x20, 5.0f); // m_LitersPurify
				});
		}
	};

	REGISTER_FEATURE(FirstAidBoostFeature)
	REGISTER_FEATURE(InstantFirstAidFeature)
	REGISTER_FEATURE(FreeFirstAidFeature)
	REGISTER_FEATURE(PurifyWaterFeature)
}
