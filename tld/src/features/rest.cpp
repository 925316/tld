#include "pch.h"
#include "features/common.h"

namespace
{
	REGISTER_FEATURE_AS(RestFatigueRate, SliderFloatFeature, "Rest", "Sleep Rest Rate",
		&GM_GetRest, Offsets::RestReduceFatiguePerHour, 20.0f, 0.0f, 100.0f, "%.1f/hr")
	REGISTER_FEATURE_AS(RestMaxHours, SliderIntFeature, "Rest", "Max Sleep Hours Per Day",
		&GM_GetRest, Offsets::RestMaxHoursSleepPerDay, 12, 1, 24)
	REGISTER_FEATURE_AS(NoPredatorInterruption, FloatFieldFeature, "Rest", "No Predator Interruption",
		&GM_GetRest, Offsets::RestPredatorInterruptionChance, 0.0f)
	REGISTER_FEATURE_AS(NoShelterInterruption, FloatFieldFeature, "Rest", "No Interruption In Snow Shelter",
		&GM_GetRest, Offsets::RestPredatorInterruptionChanceShelter, 0.0f)
	REGISTER_FEATURE_AS(WakeUpAtFullRest, BoolFieldFeature, "Rest", "Wake Up At Full Rest",
		&GM_GetRest, Offsets::RestWakeUpAtFullRest, true)
}
