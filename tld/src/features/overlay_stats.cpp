#include "pch.h"
#include "features/common.h"

namespace
{
	float ReadComponentFloat(GameComponentGetter* getter, uintptr_t offset)
	{
		void* obj = Comp(getter);
		return obj ? ReadFloat(reinterpret_cast<uintptr_t>(obj), offset) : 0.0f;
	}

	class PlayerStatsHudFeature : public Feature
	{
	public:
		PlayerStatsHudFeature() : Feature("Overlay", "Player Stats HUD") {}

		void OnTick() override
		{
			if (!m_visible) return;

			ImGui::SetNextWindowPos(ImVec2(400, 20), ImGuiCond_FirstUseEver);
			ImGui::SetNextWindowSize(ImVec2(300, 0), ImGuiCond_FirstUseEver);
			ImGui::Begin("Player Stats", &m_visible, ImGuiWindowFlags_AlwaysAutoResize);

			float hp = ReadComponentFloat(&GetCondition, Offsets::ConditionHP);
			float maxHp = ReadComponentFloat(&GetCondition, Offsets::ConditionMaxHP);
			float fatigue = ReadComponentFloat(&GetFatigue, Offsets::CurrentFatigue);
			float freezing = ReadComponentFloat(&GetFreezing, Offsets::CurrentFreezing);
			float calories = ReadComponentFloat(&GetHunger, Offsets::CurrentCalories);
			float maxCalories = ReadComponentFloat(&GetHunger, Offsets::MaxCalories);
			float thirst = ReadComponentFloat(&GetThirst, Offsets::CurrentThirst);
			float temperature = ReadComponentFloat(&GM_GetWeather, Offsets::WeatherCurrentTemperature);
			float wind = ReadComponentFloat(&GM_GetWind, Offsets::WindCurrentMPH);
			float windChill = ReadComponentFloat(&GM_GetWind, Offsets::WindChill);

			ImGui::Text("HP:        %.1f / %.1f", hp, maxHp);
			ImGui::Text("Fatigue:   %.1f", fatigue);
			ImGui::Text("Freezing:  %.1f", freezing);
			ImGui::Text("Calories:  %.0f / %.0f", calories, maxCalories);
			ImGui::Text("Thirst:    %.1f", thirst);
			ImGui::Text("Temp:      %.1f C", temperature);
			ImGui::Text("Wind:      %.1f mph (chill %.1f)", wind, windChill);

			ImGui::End();
		}

	private:
		bool m_visible = true;
	};

	REGISTER_FEATURE(PlayerStatsHudFeature)
}
