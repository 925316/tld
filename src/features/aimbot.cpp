#include "pch.h"
#include "core/feature.h"
#include "core/camera.h"
#include "core/game.h"
#include "core/tracking.h"

namespace
{
	class AimbotFeature : public Feature
	{
	public:
		AimbotFeature() : Feature("Combat", "Aimbot", VK_F6) {}

		void OnTick() override
		{
			if (!g_camera.valid || !GetAiEyePos || !SetCameraAngle) return;

			void* fpsCam = GetVpFPSCamera(nullptr);
			if (!fpsCam) return;

			const Vector3 camPos = g_camera.position;
			const Vector3 camFwd = g_camera.Forward();
			const float minDot = std::cosf(m_fov * 3.14159265f / 180.0f);

			void* best = nullptr;
			float bestDot = minDot;
			Tracking::AiList().for_each([&](void* ai)
				{
					if (AiHP(ai) <= 0.0f) return;

					Vector3 eye = GetAiEyePos(ai, nullptr);
					Vector3 dir = { eye.x - camPos.x, eye.y - camPos.y, eye.z - camPos.z };
					float len = std::sqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
					if (len < 1.0f || len > m_range) return;

					float dot = (dir.x * camFwd.x + dir.y * camFwd.y + dir.z * camFwd.z) / len;
					if (dot > bestDot)
					{
						bestDot = dot;
						best = ai;
					}
				});

			if (!best) return;

			Vector3 eye = GetAiEyePos(best, nullptr);
			Vector3 dir = { eye.x - camPos.x, eye.y - camPos.y, eye.z - camPos.z };
			float len = std::sqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
			if (len < 0.01f) return;

			// vp_FPSCamera pitch: positive = down
			float targetYaw = std::atan2f(dir.x, dir.z) * 57.2957795f;
			float targetPitch = -std::asinf(dir.y / len) * 57.2957795f;

			float curYaw = std::atan2f(camFwd.x, camFwd.z) * 57.2957795f;
			float curPitch = -std::asinf(camFwd.y) * 57.2957795f;

			float dyaw = targetYaw - curYaw;
			while (dyaw > 180.0f) dyaw -= 360.0f;
			while (dyaw < -180.0f) dyaw += 360.0f;

			SetCameraAngle(fpsCam, curYaw + dyaw * m_smoothing, curPitch + (targetPitch - curPitch) * m_smoothing, nullptr);
		}

		void OnMenu() override
		{
			ImGui::SliderFloat("FOV", &m_fov, 1.0f, 45.0f, "%.0f deg");
			ImGui::SliderFloat("Range", &m_range, 20.0f, 500.0f, "%.0f m");
			ImGui::SliderFloat("Smoothing", &m_smoothing, 0.05f, 1.0f, "%.2f");
		}

	private:
		float m_fov = 10.0f;
		float m_range = 200.0f;
		float m_smoothing = 0.35f;
	};

	REGISTER_FEATURE(AimbotFeature)
}
