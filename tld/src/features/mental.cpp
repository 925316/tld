#include "pch.h"
#include "features/common.h"

namespace
{
	REGISTER_FEATURE_AS(NoAnxiety, BoolFieldFeature, "Medical", "No Anxiety",
		&GM_GetAnxiety, Offsets::MentalHasAffliction, false)
	REGISTER_FEATURE_AS(NoFear, BoolFieldFeature, "Medical", "No Fear",
		&GM_GetFear, Offsets::MentalHasAffliction, false)
	REGISTER_FEATURE_AS(NoToxicFog, BoolFieldFeature, "Medical", "No Toxic Fog",
		&GM_GetToxicFog, Offsets::ToxicFogHasAffliction, false)
	REGISTER_FEATURE_AS(NoToxicFogHeadache, BoolFieldFeature, "Medical", "No Toxic Fog Headache",
		&GM_GetToxicFog, Offsets::ToxicFogAllowHeadache, false)
	REGISTER_FEATURE_AS(AnxietyDamageRate, SliderFloatFeature, "Medical", "Anxiety Damage/Minute",
		&GM_GetAnxiety, Offsets::MentalHealthLossPerMinute, 0.0f, 0.0f, 20.0f, "%.2f")
	REGISTER_FEATURE_AS(FearDamageRate, SliderFloatFeature, "Medical", "Fear Damage/Minute",
		&GM_GetFear, Offsets::MentalHealthLossPerMinute, 0.0f, 0.0f, 20.0f, "%.2f")
	REGISTER_FEATURE_AS(ToxicFogDamageRate, SliderFloatFeature, "Medical", "Toxic Fog Damage/Minute",
		&GM_GetToxicFog, Offsets::ToxicFogHealthLossPerMinute, 0.0f, 0.0f, 20.0f, "%.2f")
	REGISTER_FEATURE_AS(WillpowerTime, SliderFloatFeature, "Medical", "Willpower Time (s)",
		&GM_GetWillpower, Offsets::WillpowerTimeRemainingSeconds, 1.0e9f, 0.0f, 1.0e9f, "%.0f")
	REGISTER_FEATURE_AS(WillpowerBonus, SliderFloatFeature, "Medical", "Willpower HP Bonus/Second",
		&GM_GetWillpower, Offsets::WillpowerConditionBonusPerSecond, 10.0f, 0.0f, 100.0f, "%.1f")
	REGISTER_FEATURE_AS(WillpowerNoDamage, FloatFieldFeature, "Medical", "Willpower No Damage Scale",
		&GM_GetWillpower, Offsets::WillpowerConditionDamageScale, 0.0f)
}
