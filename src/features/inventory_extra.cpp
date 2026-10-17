#include "pch.h"
#include "features/common.h"
#include "core/tracking.h"

namespace
{
	class SetAllItemsConditionFeature : public Feature
	{
	public:
		SetAllItemsConditionFeature() : Feature("Inventory", "Set All Items Condition") {}

		void OnTick() override
		{
			if (!GearItem_SetNormalizedHP) return;
			Tracking::GearList().for_each([&](void* gi)
				{
					if (gi) GearItem_SetNormalizedHP(gi, m_condition, true, nullptr);
				});
		}

		void OnMenu() override
		{
			ImGui::SliderFloat("Condition", &m_condition, 0.0f, 1.0f, "%.2f");
		}

	private:
		float m_condition = 1.0f;
	};

	class DegradeAllItemsFeature : public Feature
	{
	public:
		DegradeAllItemsFeature() : Feature("Inventory", "All Items Ruined") {}

		void OnTick() override
		{
			if (!GearItem_SetNormalizedHP) return;
			Tracking::GearList().for_each([](void* gi)
				{
					if (gi) GearItem_SetNormalizedHP(gi, 0.0f, true, nullptr);
				});
		}
	};

	REGISTER_FEATURE(SetAllItemsConditionFeature)
	REGISTER_FEATURE(DegradeAllItemsFeature)
}
