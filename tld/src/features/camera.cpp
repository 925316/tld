#include "pch.h"
#include "features/common.h"

namespace
{
	void* FPSPlayer()
	{
		return Comp(&GM_GetVpFPSPlayer);
	}

	void* FPSCamera()
	{
		void* player = FPSPlayer();
		return player ? ReadPtr(reinterpret_cast<uintptr_t>(player), Offsets::FPSPlayerCamera) : nullptr;
	}

	class FieldOfViewFeature : public Feature
	{
	public:
		FieldOfViewFeature() : Feature("Camera", "Field Of View") {}

		void OnTick() override
		{
			void* cam = FPSCamera();
			if (!cam) return;
			uintptr_t a = reinterpret_cast<uintptr_t>(cam);
			WriteFloat(a, Offsets::CameraRenderingFOV, m_fov);
			WriteFloat(a, Offsets::CameraUnzoomedFOV, m_fov);
		}

		void OnMenu() override { ImGui::SliderFloat("FOV", &m_fov, 30.0f, 130.0f, "%.0f"); }

	private:
		float m_fov = 75.0f;
	};

	class MouseSensitivityFeature : public Feature
	{
	public:
		MouseSensitivityFeature() : Feature("Camera", "Mouse Sensitivity") {}

		void OnTick() override
		{
			void* cam = FPSCamera();
			if (cam) WriteFloat(reinterpret_cast<uintptr_t>(cam), Offsets::CameraMouseSensitivity, m_sensitivity);
		}

		void OnMenu() override { ImGui::SliderFloat("Sensitivity", &m_sensitivity, 0.0f, 5.0f, "%.2f"); }

	private:
		float m_sensitivity = 1.0f;
	};

	class NearClipFeature : public Feature
	{
	public:
		NearClipFeature() : Feature("Camera", "Near Clip Plane") {}

		void OnTick() override
		{
			void* cam = FPSCamera();
			if (cam) WriteFloat(reinterpret_cast<uintptr_t>(cam), Offsets::CameraNearClip, m_clip);
		}

		void OnMenu() override { ImGui::SliderFloat("Near", &m_clip, 0.01f, 5.0f, "%.2f"); }

	private:
		float m_clip = 0.1f;
	};

	class NoAmbientSwayFeature : public Feature
	{
	public:
		NoAmbientSwayFeature() : Feature("Camera", "No Ambient Sway") {}

		void OnTick() override
		{
			void* cam = FPSCamera();
			if (cam) WriteStaticBool(cam, Offsets::CameraDisableAmbientSwayStatic, true);
		}
	};

	class ForceZoomFeature : public Feature
	{
	public:
		ForceZoomFeature() : Feature("Camera", "Force Zoom") {}

		void OnTick() override
		{
			void* player = FPSPlayer();
			if (player) WriteBool(reinterpret_cast<uintptr_t>(player), Offsets::FPSPlayerInZoom, true);
		}
	};

	class AutoWalkFeature : public Feature
	{
	public:
		AutoWalkFeature() : Feature("Camera", "Auto Walk") {}

		void OnTick() override
		{
			void* player = FPSPlayer();
			if (player) WriteBool(reinterpret_cast<uintptr_t>(player), Offsets::FPSPlayerAutoWalking, true);
		}
	};

	REGISTER_FEATURE(FieldOfViewFeature)
	REGISTER_FEATURE(MouseSensitivityFeature)
	REGISTER_FEATURE(NearClipFeature)
	REGISTER_FEATURE(NoAmbientSwayFeature)
	REGISTER_FEATURE(ForceZoomFeature)
	REGISTER_FEATURE(AutoWalkFeature)
}
