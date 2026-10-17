#include "pch.h"
#include "features/common.h"
#include "features/gear_iter.h"

namespace
{
	class HeatPadFeature : public Feature
	{
	public:
		HeatPadFeature() : Feature("Equipment", "Heat Pad Boost") {}

		void OnTick() override
		{
			ForEachGearSubcomponent(Offsets::GearHeatPadItem, [&](void* pad)
				{
					uintptr_t a = reinterpret_cast<uintptr_t>(pad);
					WriteFloat(a, 0x2C, m_heat);   // m_MaxHeatBonus
					WriteFloat(a, 0x20, 0.0f);     // m_HoursUntilFullyActive
					WriteFloat(a, 0x24, 999.0f);   // m_HoursFullyActive
					WriteFloat(a, 0x28, 999.0f);   // m_HoursUntilExpired
				});
		}

		void OnMenu() override { ImGui::SliderFloat("Heat", &m_heat, 0.0f, 60.0f, "%.1f"); }

	private:
		float m_heat = 30.0f;
	};

	class FlaskNoHeatLossFeature : public Feature
	{
	public:
		FlaskNoHeatLossFeature() : Feature("Equipment", "Flask No Heat Loss") {}

		void OnTick() override
		{
			ForEachGearSubcomponent(Offsets::GearInsulatedFlask, [](void* flask)
				{
					uintptr_t a = reinterpret_cast<uintptr_t>(flask);
					WriteFloat(a, 0x28, 0.0f); // Indoors
					WriteFloat(a, 0x2C, 0.0f); // Outdoors
				});
		}
	};

	REGISTER_FEATURE(HeatPadFeature)
	REGISTER_FEATURE(FlaskNoHeatLossFeature)
}
