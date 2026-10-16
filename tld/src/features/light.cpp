#include "pch.h"
#include "features/common.h"

namespace
{
	class AmbientLightFeature : public Feature
	{
	public:
		AmbientLightFeature() : Feature("Visual", "Fullbright") {}

		void OnTick() override
		{
			if (RenderSettings_SetAmbientIntensity) RenderSettings_SetAmbientIntensity(m_intensity, nullptr);
		}

		void OnMenu() override
		{
			ImGui::SliderFloat("Ambient", &m_intensity, 0.0f, 8.0f, "%.2f");
		}

	private:
		float m_intensity = 3.0f;
	};

	class NoFogFeature : public Feature
	{
	public:
		NoFogFeature() : Feature("Visual", "No Fog") {}

		void OnTick() override
		{
			if (RenderSettings_SetFog) RenderSettings_SetFog(false, nullptr);
		}
	};

	class FogDensityFeature : public Feature
	{
	public:
		FogDensityFeature() : Feature("Visual", "Fog Density") {}

		void OnTick() override
		{
			if (RenderSettings_SetFogDensity) RenderSettings_SetFogDensity(m_density, nullptr);
		}

		void OnMenu() override
		{
			ImGui::SliderFloat("Density", &m_density, 0.0f, 0.2f, "%.4f");
		}

	private:
		float m_density = 0.0f;
	};

	class FogStartFeature : public Feature
	{
	public:
		FogStartFeature() : Feature("Visual", "Fog Start Distance") {}

		void OnTick() override
		{
			if (RenderSettings_SetFogStartDistance) RenderSettings_SetFogStartDistance(m_distance, nullptr);
		}

		void OnMenu() override
		{
			ImGui::SliderFloat("Start", &m_distance, 0.0f, 500.0f, "%.0f");
		}

	private:
		float m_distance = 200.0f;
	};

	class FogEndFeature : public Feature
	{
	public:
		FogEndFeature() : Feature("Visual", "Fog End Distance") {}

		void OnTick() override
		{
			if (RenderSettings_SetFogEndDistance) RenderSettings_SetFogEndDistance(m_distance, nullptr);
		}

		void OnMenu() override
		{
			ImGui::SliderFloat("End", &m_distance, 0.0f, 5000.0f, "%.0f");
		}

	private:
		float m_distance = 2000.0f;
	};

	REGISTER_FEATURE(AmbientLightFeature)
	REGISTER_FEATURE(NoFogFeature)
	REGISTER_FEATURE(FogDensityFeature)
	REGISTER_FEATURE(FogStartFeature)
	REGISTER_FEATURE(FogEndFeature)
}
