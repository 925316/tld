#include "pch.h"
#include "features/common.h"
#include "features/gear_iter.h"

namespace
{
	class ForageNoHpLossFeature : public Feature
	{
	public:
		ForageNoHpLossFeature() : Feature("Crafting", "Forage No HP Loss") {}

		void OnTick() override
		{
			ForEachGearSubcomponent(Offsets::GearForageItem, [](void* forage)
				{
					WriteFloat(reinterpret_cast<uintptr_t>(forage), 0x34, 0.0f); // m_HPDecreasePerHourForaging
				});
		}
	};

	class ForageRateFeature : public Feature
	{
	public:
		ForageRateFeature() : Feature("Crafting", "Forage Rate") {}

		void OnTick() override
		{
			ForEachGearSubcomponent(Offsets::GearForageItem, [&](void* forage)
				{
					uintptr_t a = reinterpret_cast<uintptr_t>(forage);
					WriteFloat(a, 0x20, m_rate); // Tinder outdoor
					WriteFloat(a, 0x24, m_rate); // Tinder indoor
					WriteFloat(a, 0x28, m_rate); // Softwood
					WriteFloat(a, 0x2C, m_rate); // Hardwood
					WriteFloat(a, 0x30, m_rate); // Reclaimed wood
				});
		}

		void OnMenu() override { ImGui::SliderFloat("Units/hour", &m_rate, 0.0f, 20.0f, "%.1f"); }

	private:
		float m_rate = 5.0f;
	};

	class InstantBreakDownFeature : public Feature
	{
	public:
		InstantBreakDownFeature() : Feature("Crafting", "Instant Break Down") {}

		void OnTick() override
		{
			ForEachGearSubcomponent(Offsets::GearBreakDownItem, [](void* bd)
				{
					WriteFloat(reinterpret_cast<uintptr_t>(bd), 0x20, 0.0f); // m_BreakDownTimeModifier
				});
		}
	};

	class InstantMillFeature : public Feature
	{
	public:
		InstantMillFeature() : Feature("Crafting", "Instant Mill Repair") {}

		void OnTick() override
		{
			ForEachGearSubcomponent(Offsets::GearMillable, [](void* mill)
				{
					uintptr_t a = reinterpret_cast<uintptr_t>(mill);
					WriteInt(a, 0x44, 0); // m_RepairDurationMinutes
					WriteInt(a, 0x48, 0); // m_RecoveryDurationMinutes
				});
		}
	};

	class SmashNoLossFeature : public Feature
	{
	public:
		SmashNoLossFeature() : Feature("Crafting", "Smash No Condition Loss") {}

		void OnTick() override
		{
			ForEachGearSubcomponent(Offsets::GearSmashableItem, [](void* smash)
				{
					uintptr_t a = reinterpret_cast<uintptr_t>(smash);
					WriteInt(a, 0x20, 0); // m_MinPercentLoss
					WriteInt(a, 0x24, 0); // m_MaxPercentLoss
					WriteInt(a, 0x28, 0); // m_TimeToSmash
				});
		}
	};

	REGISTER_FEATURE(ForageNoHpLossFeature)
	REGISTER_FEATURE(ForageRateFeature)
	REGISTER_FEATURE(InstantBreakDownFeature)
	REGISTER_FEATURE(InstantMillFeature)
	REGISTER_FEATURE(SmashNoLossFeature)
}
