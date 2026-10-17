#include "pch.h"
#include "features/common.h"

namespace
{
	// Silences footsteps by zeroing the footstep range scales.
	class SilentFootstepsFeature : public Feature
	{
	public:
		SilentFootstepsFeature() : Feature("Stealth", "No Footstep Sound") {}

		void OnTick() override
		{
			void* pm = Comp(&GM_GetPlayerMovement);
			if (!pm) return;
			uintptr_t a = reinterpret_cast<uintptr_t>(pm);
			WriteFloat(a, Offsets::FootStepRangeScaleCrouched, 0.0f);
			WriteFloat(a, Offsets::FootStepRangeScaleWalking, 0.0f);
		}
	};

	class UndetectableFeature : public Feature
	{
	public:
		UndetectableFeature() : Feature("Stealth", "Invisible To Wildlife") {}

		void OnTick() override
		{
			void* pm = Comp(&GM_GetPlayerMovement);
			if (!pm) return;
			uintptr_t a = reinterpret_cast<uintptr_t>(pm);
			WriteFloat(a, Offsets::DetectionRangeScaleCrouched, 0.0f);
			WriteFloat(a, Offsets::FootStepRangeScaleWalking, 0.0f);
		}
	};

	class DetectionRangeFeature : public Feature
	{
	public:
		DetectionRangeFeature() : Feature("Stealth", "Detection Range Scale") {}

		void OnTick() override
		{
			void* pm = Comp(&GM_GetPlayerMovement);
			if (pm) WriteFloat(reinterpret_cast<uintptr_t>(pm), Offsets::DetectionRangeScaleCrouched, m_scale);
		}

		void OnMenu() override
		{
			ImGui::SliderFloat("Scale", &m_scale, 0.0f, 2.0f, "%.2f");
		}

	private:
		float m_scale = 0.0f;
	};

	REGISTER_FEATURE(SilentFootstepsFeature)
	REGISTER_FEATURE(UndetectableFeature)
	REGISTER_FEATURE(DetectionRangeFeature)

	REGISTER_FEATURE_AS(FootstepRangeCrouched, SliderFloatFeature, "Stealth", "Footstep Range (Crouched)",
		&GM_GetPlayerMovement, Offsets::FootStepRangeScaleCrouched, 0.0f, 0.0f, 2.0f, "%.2f")
	REGISTER_FEATURE_AS(FootstepRangeWalking, SliderFloatFeature, "Stealth", "Footstep Range (Walking)",
		&GM_GetPlayerMovement, Offsets::FootStepRangeScaleWalking, 0.0f, 0.0f, 2.0f, "%.2f")
}
