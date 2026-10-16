#include "pch.h"
#include "features/common.h"

namespace
{
	// Zeroes every damage scalar applied to the player during a struggle.
	class NoStruggleDamageFeature : public Feature
	{
	public:
		NoStruggleDamageFeature() : Feature("Combat", "No Struggle Damage") {}

		void OnTick() override
		{
			void* s = Comp(&GM_GetPlayerStruggle);
			if (!s) return;
			uintptr_t a = reinterpret_cast<uintptr_t>(s);
			WriteFloat(a, Offsets::StruggleBearConditionLoss, 0.0f);
			WriteFloat(a, Offsets::StruggleMooseConditionLoss, 0.0f);
			WriteFloat(a, Offsets::StruggleWolfDamagePerSecond, 0.0f);
			WriteFloat(a, Offsets::StruggleCougarDamagePerSecond, 0.0f);
			WriteFloat(a, Offsets::StruggleWolfClothingDamageMin, 0.0f);
			WriteFloat(a, Offsets::StruggleWolfClothingDamageMax, 0.0f);
			WriteFloat(a, Offsets::StruggleBearClothingDamageMin, 0.0f);
			WriteFloat(a, Offsets::StruggleBearClothingDamageMax, 0.0f);
			WriteFloat(a, Offsets::StruggleCougarClothingDamageMin, 0.0f);
			WriteFloat(a, Offsets::StruggleCougarClothingDamageMax, 0.0f);
		}
	};

	class NoKnockoutFeature : public Feature
	{
	public:
		NoKnockoutFeature() : Feature("Combat", "No Struggle Knockout") {}

		void OnTick() override
		{
			void* s = Comp(&GM_GetPlayerStruggle);
			if (!s) return;
			uintptr_t a = reinterpret_cast<uintptr_t>(s);
			WriteFloat(a, Offsets::StruggleStunnedAfterBear, 0.0f);
			WriteFloat(a, Offsets::StruggleStunnedAfterWolf, 0.0f);
			WriteFloat(a, Offsets::StruggleStunnedAfterCougar, 0.0f);
		}
	};

	REGISTER_FEATURE(NoStruggleDamageFeature)
	REGISTER_FEATURE(NoKnockoutFeature)

	REGISTER_FEATURE_AS(PredatorFleesOnHit, FloatFieldFeature, "Combat", "Predator Flees On Hit",
		&GM_GetPlayerStruggle, Offsets::StruggleFleeChanceOnHit, 1.0f)
	REGISTER_FEATURE_AS(PredatorFleesOnShot, FloatFieldFeature, "Combat", "Predator Flees On Shot",
		&GM_GetPlayerStruggle, Offsets::StruggleFleeChanceOnShot, 1.0f)
	REGISTER_FEATURE_AS(DisableStruggleSystem, BoolFieldFeature, "Combat", "Disable Struggle System",
		&GM_GetPlayerStruggle, Offsets::StruggleSystemEnabled, false)
	REGISTER_FEATURE_AS(StruggleBearConditionLoss, SliderFloatFeature, "Combat", "Bear Attack Condition Loss %",
		&GM_GetPlayerStruggle, Offsets::StruggleBearConditionLoss, 0.0f, 0.0f, 100.0f, "%.0f%%")
	REGISTER_FEATURE_AS(StruggleWolfDamage, SliderFloatFeature, "Combat", "Wolf Damage/Second",
		&GM_GetPlayerStruggle, Offsets::StruggleWolfDamagePerSecond, 0.0f, 0.0f, 100.0f, "%.1f")
}
