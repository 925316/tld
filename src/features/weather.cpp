#include "pch.h"
#include "features/common.h"

namespace
{
	class SetWeatherStageFeature : public Feature
	{
	public:
		SetWeatherStageFeature(const char* name, int stage)
			: Feature("Weather", name)
			, m_stage(stage)
		{
		}

		bool IsAction() const override { return true; }

		void OnAction() override
		{
			void* wt = Comp(&GM_GetWeatherTransition);
			if (wt && WeatherTransition_SetStage) WeatherTransition_SetStage(wt, m_stage, nullptr);
		}

	private:
		int m_stage;
	};

	REGISTER_FEATURE_AS(WeatherClear, SetWeatherStageFeature, "Set Clear", 4)
	REGISTER_FEATURE_AS(WeatherCloudy, SetWeatherStageFeature, "Set Cloudy", 5)
	REGISTER_FEATURE_AS(WeatherPartlyCloudy, SetWeatherStageFeature, "Set Partly Cloudy", 3)
	REGISTER_FEATURE_AS(WeatherLightSnow, SetWeatherStageFeature, "Set Light Snow", 1)
	REGISTER_FEATURE_AS(WeatherHeavySnow, SetWeatherStageFeature, "Set Heavy Snow", 2)
	REGISTER_FEATURE_AS(WeatherBlizzard, SetWeatherStageFeature, "Set Blizzard", 7)
	REGISTER_FEATURE_AS(WeatherLightFog, SetWeatherStageFeature, "Set Light Fog", 6)
	REGISTER_FEATURE_AS(WeatherDenseFog, SetWeatherStageFeature, "Set Dense Fog", 0)
	REGISTER_FEATURE_AS(WeatherClearAurora, SetWeatherStageFeature, "Set Clear Aurora", 8)
	REGISTER_FEATURE_AS(WeatherToxicFog, SetWeatherStageFeature, "Set Toxic Fog", 9)
	REGISTER_FEATURE_AS(WeatherElectrostaticFog, SetWeatherStageFeature, "Set Electrostatic Fog", 10)

	REGISTER_FEATURE_AS(SetTemperature, SliderFloatFeature, "Weather", "Set Temperature", &GM_GetWeather,
		Offsets::WeatherCurrentTemperature, 5.0f, -60.0f, 30.0f, "%.1f C")
	REGISTER_FEATURE_AS(SetBaseTemperature, SliderFloatFeature, "Weather", "Set Base Temperature", &GM_GetWeather,
		Offsets::WeatherBaseTemperature, 5.0f, -60.0f, 30.0f, "%.1f C")
	REGISTER_FEATURE_AS(SetIndoorTemperature, SliderFloatFeature, "Weather", "Set Indoor Temperature", &GM_GetWeather,
		Offsets::WeatherIndoorTemperature, 15.0f, -60.0f, 30.0f, "%.1f C")
	REGISTER_FEATURE_AS(LockTemperature, SliderFloatFeature, "Weather", "Lock Temperature", &GM_GetWeather,
		Offsets::WeatherLockedAirTemperature, 5.0f, -60.0f, 30.0f, "%.1f C")
	REGISTER_FEATURE_AS(WeatherArtificialTemp, SliderFloatFeature, "Weather", "Artificial Temp Increase", &GM_GetWeather,
		Offsets::WeatherArtificialTempIncrease, 0.0f, 0.0f, 60.0f, "%.1f C")

	REGISTER_FEATURE_AS(NoWind, FloatFieldFeature, "Weather", "No Wind", &GM_GetWind, Offsets::WindCurrentMPH, 0.0f)
	REGISTER_FEATURE_AS(SetWindSpeed, SliderFloatFeature, "Weather", "Set Wind Speed", &GM_GetWind,
		Offsets::WindCurrentMPH, 0.0f, 0.0f, 80.0f, "%.1f")
	REGISTER_FEATURE_AS(NoWindChill, FloatFieldFeature, "Weather", "No Wind Chill", &GM_GetWind, Offsets::WindChill, 0.0f)
	REGISTER_FEATURE_AS(WindNeverCalm, BoolFieldFeature, "Weather", "Wind Never Calm", &GM_GetWind, Offsets::WindNeverCalm, true)
	REGISTER_FEATURE_AS(WindArtificialIncrease, SliderFloatFeature, "Weather", "Artificial Wind Increase", &GM_GetWind,
		Offsets::WindArtificialSpeedIncrease, 0.0f, 0.0f, 60.0f, "%.1f")

	REGISTER_FEATURE_AS(SuppressBlizzards, StaticBoolFieldFeature, "Weather", "Suppress Blizzards",
		&GM_GetWeatherTransition, Offsets::WeatherSuppressBlizzards, true)
	REGISTER_FEATURE_AS(WeatherTimeScalar, StaticSliderFloatFeature, "Weather", "Weather Transition Scalar",
		&GM_GetWeatherTransition, Offsets::WeatherTransitionTimeScalar, 1.0f, 0.0f, 20.0f, "%.2f")
	REGISTER_FEATURE_AS(AuroraForceDisable, StaticBoolFieldFeature, "Weather", "Disable Aurora",
		&GM_GetAuroraManager, Offsets::AuroraForceDisable, true)
}
