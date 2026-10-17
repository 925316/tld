#include "pch.h"
#include "features/common.h"

namespace
{
	REGISTER_FEATURE_AS(NoSprainMoving, FloatFieldFeature, "Movement", "No Sprain While Moving",
		&GM_GetSprains, Offsets::SprainChanceMovingWrist, 0.0f)
	REGISTER_FEATURE_AS(NoSprainSlope, FloatFieldFeature, "Movement", "No Sprain On Slopes",
		&GM_GetSprains, Offsets::SprainBaseChanceSlope, 0.0f)
	REGISTER_FEATURE_AS(NoSprainEncumbered, FloatFieldFeature, "Movement", "No Sprain When Encumbered",
		&GM_GetSprains, Offsets::SprainChanceEncumbered, 0.0f)
	REGISTER_FEATURE_AS(NoSprainExhausted, FloatFieldFeature, "Movement", "No Sprain When Exhausted",
		&GM_GetSprains, Offsets::SprainChanceExhausted, 0.0f)
	REGISTER_FEATURE_AS(NoSprainSprinting, FloatFieldFeature, "Movement", "No Sprain When Sprinting",
		&GM_GetSprains, Offsets::SprainChanceSprinting, 0.0f)
}
