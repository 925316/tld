#include "pch.h"
#include "features/common.h"

namespace
{
	class MuteVoiceFeature : public Feature
	{
	public:
		MuteVoiceFeature() : Feature("Audio", "Mute Non-Critical Voice") {}

		void OnTick() override
		{
			void* voice = Comp(&GM_GetPlayerVoice);
			if (voice) WriteFloat(reinterpret_cast<uintptr_t>(voice), 0x4C, 1.0e9f); // m_BlockNonCriticalLineTime
		}
	};

	class VoiceIntervalFeature : public Feature
	{
	public:
		VoiceIntervalFeature() : Feature("Audio", "Voice Line Interval") {}

		void OnTick() override
		{
			void* voice = Comp(&GM_GetPlayerVoice);
			if (voice) WriteFloat(reinterpret_cast<uintptr_t>(voice), 0x30, m_interval);
		}

		void OnMenu() override { ImGui::SliderFloat("Seconds", &m_interval, 0.0f, 300.0f, "%.0f"); }

	private:
		float m_interval = 120.0f;
	};

	REGISTER_FEATURE(MuteVoiceFeature)
	REGISTER_FEATURE(VoiceIntervalFeature)
}
