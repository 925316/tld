#include "pch.h"
#include "features/common.h"

namespace
{
	REGISTER_FEATURE_AS(DayDuration, SliderIntFeature, "Time", "Day Duration (minutes)",
		&GM_GetTimeOfDay, Offsets::TODDayDurationMinutes, 30, 1, 240)
	REGISTER_FEATURE_AS(NightDuration, SliderIntFeature, "Time", "Night Duration (minutes)",
		&GM_GetTimeOfDay, Offsets::TODNightDurationMinutes, 30, 1, 240)
}
