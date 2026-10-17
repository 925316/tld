#include "pch.h"
#include "features/common.h"

namespace
{
	REGISTER_FEATURE_AS(SetConditionHP, SliderFloatFeature, "Player", "Set Condition",
		&GetCondition, Offsets::ConditionHP, 100.0f, 0.0f, 500.0f, "%.0f")
	REGISTER_FEATURE_AS(SetCriticalHP, SliderFloatFeature, "Player", "Set Critical HP",
		&GetCondition, Offsets::ConditionCriticalHP, 10.0f, 0.0f, 100.0f, "%.0f")
	REGISTER_FEATURE_AS(OverrideBlurLevel, SliderIntFeature, "Player", "Override Blur Level",
		&GetCondition, Offsets::ConditionOverrideBlurLevel, 0, 0, 3)
	REGISTER_FEATURE_AS(HealthRegenPerDay, SliderFloatFeature, "Player", "Health Regen Per Day",
		&GetCondition, 0x34, 100.0f, 0.0f, 1000.0f, "%.0f")
}
