#include "pch.h"
#include "features/common.h"

namespace
{
	float ComponentFloat(GameComponentGetter* getter, uintptr_t offset)
	{
		void* obj = Comp(getter);
		return obj ? ReadFloat(reinterpret_cast<uintptr_t>(obj), offset) : 0.0f;
	}

	class GameStatsOverlayFeature : public Feature
	{
	public:
		GameStatsOverlayFeature() : Feature("Overlay", "Game Stats") {}

		void OnTick() override
		{
			if (!m_visible) return;

			ImGui::SetNextWindowPos(ImVec2(400, 220), ImGuiCond_FirstUseEver);
			ImGui::Begin("Game Stats", &m_visible, ImGuiWindowFlags_AlwaysAutoResize);

			ImGui::Text("Calories burned: %.0f", ComponentFloat(&GM_GetPlayerGameStats, 0x20));
			ImGui::Text("Calories eaten:  %.0f", ComponentFloat(&GM_GetPlayerGameStats, 0x24));
			ImGui::Text("Body temp hi/lo: %.1f / %.1f", ComponentFloat(&GM_GetPlayerGameStats, 0x28), ComponentFloat(&GM_GetPlayerGameStats, 0x2C));
			ImGui::Text("Dist day/night:  %.0f / %.0f m", ComponentFloat(&GM_GetPlayerGameStats, 0x30), ComponentFloat(&GM_GetPlayerGameStats, 0x34));
			ImGui::Text("Condition +/-:   %.1f / %.1f", ComponentFloat(&GM_GetPlayerGameStats, 0x38), ComponentFloat(&GM_GetPlayerGameStats, 0x3C));
			ImGui::Text("Calories today:  %.0f", ComponentFloat(&GM_GetPlayerGameStats, 0x40));

			ImGui::End();
		}

	private:
		bool m_visible = true;
	};

	REGISTER_FEATURE(GameStatsOverlayFeature)
}
