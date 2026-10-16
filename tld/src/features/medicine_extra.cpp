#include "pch.h"
#include "features/common.h"

namespace
{
	REGISTER_FEATURE_AS(NoHeadache, ClearListsFieldFeature, "Medical", "No Headache",
		&GM_GetHeadache, { Offsets::HeadacheInstances })
	REGISTER_FEATURE_AS(NoSprainPain, ClearListsFieldFeature, "Medical", "No Pain",
		&GM_GetSprainPain, { Offsets::SprainPainInstances })
	REGISTER_FEATURE_AS(NoToxicity, FloatFieldFeature, "Medical", "No Chemical Poisoning",
		&GM_GetChemicalPoisoning, Offsets::ChemPoisonToxicity, 0.0f)
	REGISTER_FEATURE_AS(NoStarvationDamage, FloatFieldFeature, "Medical", "No Starving Damage Rate",
		&GetCondition, 0x38, 0.0f)
	REGISTER_FEATURE_AS(NoDehydrationDamage, FloatFieldFeature, "Medical", "No Dehydration Damage Rate",
		&GetCondition, 0x3C, 0.0f)
	REGISTER_FEATURE_AS(NoExhaustionDamage, FloatFieldFeature, "Medical", "No Exhaustion Damage Rate",
		&GetCondition, 0x40, 0.0f)
	REGISTER_FEATURE_AS(NoFreezingDamage, FloatFieldFeature, "Medical", "No Freezing Damage Rate",
		&GetCondition, 0x44, 0.0f)
	REGISTER_FEATURE_AS(NoHealthRegen, FloatFieldFeature, "Medical", "Max Health Regen/Day",
		&GetCondition, 0x34, 100.0f)
}
