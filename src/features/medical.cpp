#include "pch.h"
#include "features/common.h"

namespace
{
	void CureAllAfflictions()
	{
		if (void* o = Comp(&GM_GetFrostbite)) WriteBool(reinterpret_cast<uintptr_t>(o), Offsets::FrostbiteSuppress, true);
		if (void* o = Comp(&GM_GetHypothermia))
		{
			uintptr_t a = reinterpret_cast<uintptr_t>(o);
			WriteBool(a, Offsets::HypothermiaActive, false);
			WriteBool(a, Offsets::HypothermiaSuppress, true);
		}
		if (void* o = Comp(&GM_GetInfection))
		{
			uintptr_t a = reinterpret_cast<uintptr_t>(o);
			ClearManagedList(ReadPtr(a, Offsets::InfectionLocations));
			ClearManagedList(ReadPtr(a, Offsets::InfectionElapsedHours));
		}
		if (void* o = Comp(&GM_GetInfectionRisk))
		{
			uintptr_t a = reinterpret_cast<uintptr_t>(o);
			for (uintptr_t off : { Offsets::InfectionRiskLocations, Offsets::InfectionRiskElapsedHours })
				ClearManagedList(ReadPtr(a, off));
		}
		if (void* o = Comp(&GM_GetSprainedAnkle))
		{
			uintptr_t a = reinterpret_cast<uintptr_t>(o);
			ClearManagedList(ReadPtr(a, Offsets::SprainedAnkleLocations));
			ClearManagedList(ReadPtr(a, Offsets::SprainedAnkleElapsedHours));
		}
		if (void* o = Comp(&GM_GetSprainedWrist))
		{
			uintptr_t a = reinterpret_cast<uintptr_t>(o);
			WriteBool(a, Offsets::SprainedWristNoSprainForced, true);
			ClearManagedList(ReadPtr(a, Offsets::SprainedWristLocations));
		}
		if (void* o = Comp(&GM_GetBloodLoss))
		{
			uintptr_t a = reinterpret_cast<uintptr_t>(o);
			WriteBool(a, Offsets::BloodLossForceNoDamage, true);
			ClearManagedList(ReadPtr(a, Offsets::BloodLossLocations));
		}
		if (void* o = Comp(&GM_GetBurns)) WriteBool(reinterpret_cast<uintptr_t>(o), Offsets::BurnsActive, false);
		if (void* o = Comp(&GM_GetBurnsElectric)) WriteBool(reinterpret_cast<uintptr_t>(o), Offsets::BurnsElectricActive, false);
		if (void* o = Comp(&GM_GetFoodPoisoning)) WriteBool(reinterpret_cast<uintptr_t>(o), Offsets::FoodPoisoningActive, false);
		if (void* o = Comp(&GM_GetDysentery)) WriteBool(reinterpret_cast<uintptr_t>(o), Offsets::DysenteryActive, false);
		if (void* o = Comp(&GM_GetIntestinalParasites))
		{
			uintptr_t a = reinterpret_cast<uintptr_t>(o);
			WriteBool(a, Offsets::ParasitesHas, false);
			WriteBool(a, Offsets::ParasitesRisk, false);
		}
		if (void* o = Comp(&GM_GetCabinFever))
		{
			uintptr_t a = reinterpret_cast<uintptr_t>(o);
			WriteBool(a, Offsets::CabinFeverActive, false);
			WriteBool(a, Offsets::CabinFeverRiskActive, false);
		}
		if (void* o = Comp(&GM_GetBrokenRib)) ClearManagedList(ReadPtr(reinterpret_cast<uintptr_t>(o), Offsets::BrokenRibLocations));
		if (void* o = Comp(&GM_GetChemicalPoisoning)) WriteFloat(reinterpret_cast<uintptr_t>(o), Offsets::ChemPoisonToxicity, 0.0f);
	}

	REGISTER_FEATURE_AS(NoFrostbite, BoolFieldFeature, "Medical", "No Frostbite", &GM_GetFrostbite, Offsets::FrostbiteSuppress, true)
	REGISTER_FEATURE_AS(NoHypothermia, BoolFieldFeature, "Medical", "No Hypothermia", &GM_GetHypothermia, Offsets::HypothermiaActive, false)
	REGISTER_FEATURE_AS(NoHypothermia2, BoolFieldFeature, "Medical", "Hypothermia Cure", &GM_GetHypothermia, Offsets::HypothermiaSuppress, true)
	REGISTER_FEATURE_AS(NoBurns, BoolFieldFeature, "Medical", "No Burns", &GM_GetBurns, Offsets::BurnsActive, false)
	REGISTER_FEATURE_AS(NoElectricBurns, BoolFieldFeature, "Medical", "No Electric Burns", &GM_GetBurnsElectric, Offsets::BurnsElectricActive, false)
	REGISTER_FEATURE_AS(NoFoodPoisoning, BoolFieldFeature, "Medical", "No Food Poisoning", &GM_GetFoodPoisoning, Offsets::FoodPoisoningActive, false)
	REGISTER_FEATURE_AS(NoDysentery, BoolFieldFeature, "Medical", "No Dysentery", &GM_GetDysentery, Offsets::DysenteryActive, false)
	REGISTER_FEATURE_AS(NoParasites, BoolFieldFeature, "Medical", "No Intestinal Parasites", &GM_GetIntestinalParasites, Offsets::ParasitesHas, false)
	REGISTER_FEATURE_AS(NoParasiteRisk, BoolFieldFeature, "Medical", "No Parasite Risk", &GM_GetIntestinalParasites, Offsets::ParasitesRisk, false)
	REGISTER_FEATURE_AS(NoCabinFever, BoolFieldFeature, "Medical", "No Cabin Fever", &GM_GetCabinFever, Offsets::CabinFeverActive, false)
	REGISTER_FEATURE_AS(NoCabinFeverRisk, BoolFieldFeature, "Medical", "No Cabin Fever Risk", &GM_GetCabinFever, Offsets::CabinFeverRiskActive, false)
	REGISTER_FEATURE_AS(BloodLossNoDamage, BoolFieldFeature, "Medical", "No Blood Loss", &GM_GetBloodLoss, Offsets::BloodLossForceNoDamage, true)
	REGISTER_FEATURE_AS(WristNoSprain, BoolFieldFeature, "Medical", "No Sprained Wrist", &GM_GetSprainedWrist, Offsets::SprainedWristNoSprainForced, true)
	REGISTER_FEATURE_AS(NoSuffocation, BoolFieldFeature, "Medical", "No Suffocation", &GM_GetSuffocating, Offsets::SuffocatingBlock, true)
	REGISTER_FEATURE_AS(WellFedOn, BoolFieldFeature, "Medical", "Well Fed", &GM_GetWellFed, Offsets::WellFedActive, true)
	REGISTER_FEATURE_AS(SprainProtectionOn, BoolFieldFeature, "Medical", "Sprain Protection", &GM_GetSprainProtection, Offsets::SprainProtectionHas, true)

	REGISTER_FEATURE_AS(NoInfection, ClearListsFieldFeature, "Medical", "No Infection", &GM_GetInfection,
		{ Offsets::InfectionLocations, Offsets::InfectionElapsedHours })
	REGISTER_FEATURE_AS(NoInfectionRisk, ClearListsFieldFeature, "Medical", "No Infection Risk", &GM_GetInfectionRisk,
		{ Offsets::InfectionRiskLocations, Offsets::InfectionRiskElapsedHours })
	REGISTER_FEATURE_AS(NoSprainedAnkle, ClearListsFieldFeature, "Medical", "No Sprained Ankle", &GM_GetSprainedAnkle,
		{ Offsets::SprainedAnkleLocations, Offsets::SprainedAnkleElapsedHours })
	REGISTER_FEATURE_AS(NoAllSprains, ClearListsFieldFeature, "Medical", "No Sprains (Wrist)", &GM_GetSprainedWrist,
		{ Offsets::SprainedWristLocations })
	REGISTER_FEATURE_AS(NoBrokenRib, ClearListsFieldFeature, "Medical", "No Broken Ribs", &GM_GetBrokenRib,
		{ Offsets::BrokenRibLocations })

	REGISTER_FEATURE_AS(CureAllAction, ActionFeature, "Medical", "Cure All Afflictions", CureAllAfflictions)
}
