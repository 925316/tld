#include "pch.h"
#include "features/common.h"
#include "core/tracking.h"

namespace
{
	template<typename F>
	void ForEachSubcomponent(uintptr_t fieldOffset, F&& func)
	{
		Tracking::GearList().for_each([&](void* gi)
			{
				if (!gi) return;
				void* component = ReadPtr(reinterpret_cast<uintptr_t>(gi), fieldOffset);
				if (component) func(component);
			});
	}

	class InstantRepairFeature : public Feature
	{
	public:
		InstantRepairFeature() : Feature("Equipment", "Instant Repair") {}

		void OnTick() override
		{
			ForEachSubcomponent(Offsets::GearRepairable, [](void* c)
				{
					WriteInt(reinterpret_cast<uintptr_t>(c), Offsets::RepairableDurationMinutes, 0);
				});
		}
	};

	class InstantSharpenFeature : public Feature
	{
	public:
		InstantSharpenFeature() : Feature("Equipment", "Instant Sharpening") {}

		void OnTick() override
		{
			ForEachSubcomponent(Offsets::GearSharpenable, [](void* c)
				{
					uintptr_t a = reinterpret_cast<uintptr_t>(c);
					WriteInt(a, Offsets::SharpenDurationMinutesMin, 0);
					WriteInt(a, Offsets::SharpenDurationMinutesMax, 0);
				});
		}
	};

	class RepairAmountFeature : public Feature
	{
	public:
		RepairAmountFeature() : Feature("Equipment", "Repair Condition Amount") {}

		void OnTick() override
		{
			ForEachSubcomponent(Offsets::GearRepairable, [&](void* c)
				{
					WriteFloat(reinterpret_cast<uintptr_t>(c), Offsets::RepairConditionIncrease, m_amount);
				});
		}

		void OnMenu() override
		{
			ImGui::SliderFloat("Amount", &m_amount, 0.0f, 100.0f, "%.0f");
		}

	private:
		float m_amount = 50.0f;
	};

	REGISTER_FEATURE(InstantRepairFeature)
	REGISTER_FEATURE(InstantSharpenFeature)
	REGISTER_FEATURE(RepairAmountFeature)
}
