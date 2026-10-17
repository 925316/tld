#include "pch.h"
#include "features/common.h"

namespace
{
	REGISTER_FEATURE_AS(BlizzardDegreesDrop, SliderFloatFeature, "Weather", "Blizzard Degrees Drop",
		&GM_GetWeather, Offsets::WeatherBlizzardDegreesDrop, 15.0f, 0.0f, 60.0f, "%.1f C")
	REGISTER_FEATURE_AS(BlizzardChangePerSecond, SliderFloatFeature, "Weather", "Blizzard Change/Second",
		&GM_GetWeather, Offsets::WeatherBlizzardChangePerSecond, 1.0f, 0.0f, 20.0f, "%.2f")
	REGISTER_FEATURE_AS(DegreesPerSecondLow, SliderFloatFeature, "Weather", "Temp Change/Sec (Low)",
		&GM_GetWeather, Offsets::WeatherDegreesPerSecondLow, 0.1f, 0.0f, 10.0f, "%.3f")
	REGISTER_FEATURE_AS(DegreesPerSecondMedium, SliderFloatFeature, "Weather", "Temp Change/Sec (Medium)",
		&GM_GetWeather, Offsets::WeatherDegreesPerSecondMedium, 0.2f, 0.0f, 10.0f, "%.3f")
	REGISTER_FEATURE_AS(DegreesPerSecondHigh, SliderFloatFeature, "Weather", "Temp Change/Sec (High)",
		&GM_GetWeather, Offsets::WeatherDegreesPerSecondHigh, 0.4f, 0.0f, 10.0f, "%.3f")
	REGISTER_FEATURE_AS(MinWindBlowingSnow, SliderFloatFeature, "Weather", "Min Wind For Blowing Snow",
		&GM_GetWeather, Offsets::WeatherMinWindForBlowingSnow, 5.0f, 0.0f, 40.0f, "%.1f")
	REGISTER_FEATURE_AS(BlizzardClothingDamage, SliderFloatFeature, "Weather", "Blizzard Clothing Damage/Hour",
		&GM_GetWeather, Offsets::WeatherClothingDamageInBlizzard, 0.0f, 0.0f, 20.0f, "%.2f")
	REGISTER_FEATURE_AS(MaxWindMPH, SliderFloatFeature, "Weather", "Max Wind MPH",
		&GM_GetWind, Offsets::WindMaxMPH, 10.0f, 0.0f, 100.0f, "%.0f")
}
