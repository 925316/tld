#include "pch.h"
#include "features/common.h"

// Second batch of built-in developer-console commands: individual feats,
// affliction visual-effect suppression and assorted utility toggles.
namespace
{
	// ---- feats ----
	REGISTER_FEATURE_AS(CmdFeatBooksmarts, ConsoleActionFeature, "Console", "Grant Feat: Book Smarts", 0xBB9670)
	REGISTER_FEATURE_AS(CmdFeatColdFusion, ConsoleActionFeature, "Console", "Grant Feat: Cold Fusion", 0xBB96D0)
	REGISTER_FEATURE_AS(CmdFeatEfficientMachine, ConsoleActionFeature, "Console", "Grant Feat: Efficient Machine", 0xBB9740)
	REGISTER_FEATURE_AS(CmdFeatFireMaster, ConsoleActionFeature, "Console", "Grant Feat: Fire Master", 0xBB97B0)
	REGISTER_FEATURE_AS(CmdFeatFreeRunner, ConsoleActionFeature, "Console", "Grant Feat: Free Runner", 0xBB9820)
	REGISTER_FEATURE_AS(CmdFeatSnowWalker, ConsoleActionFeature, "Console", "Grant Feat: Snow Walker", 0xBB9890)
	REGISTER_FEATURE_AS(CmdFeatExpertTrapper, ConsoleActionFeature, "Console", "Grant Feat: Expert Trapper", 0xBB9900)
	REGISTER_FEATURE_AS(CmdFeatStraightToHeart, ConsoleActionFeature, "Console", "Grant Feat: Straight To Heart", 0xBB9970)
	REGISTER_FEATURE_AS(CmdFeatBlizzardWalker, ConsoleActionFeature, "Console", "Grant Feat: Blizzard Walker", 0xBB99E0)
	REGISTER_FEATURE_AS(CmdFeatNightWalker, ConsoleActionFeature, "Console", "Grant Feat: Night Walker", 0xBB9A50)
	REGISTER_FEATURE_AS(CmdFeatMasterHunter, ConsoleActionFeature, "Console", "Grant Feat: Master Hunter", 0xBB9AC0)
	REGISTER_FEATURE_AS(CmdFeatSettledMind, ConsoleActionFeature, "Console", "Grant Feat: Settled Mind", 0xBB9B30)
	REGISTER_FEATURE_AS(CmdFeatCelestialNavigator, ConsoleActionFeature, "Console", "Grant Feat: Celestial Navigator", 0xBB9BA0)

	// ---- affliction effect suppression ----
	REGISTER_FEATURE_AS(CmdAfflictionsNofx, ConsoleActionFeature, "Console", "Suppress All Affliction FX", 0xBAF830)
	REGISTER_FEATURE_AS(CmdBloodLossNofx, ConsoleActionFeature, "Console", "Suppress Blood Loss FX", 0xBB09E0)
	REGISTER_FEATURE_AS(CmdBrokenRibNofx, ConsoleActionFeature, "Console", "Suppress Broken Rib FX", 0xBB11D0)
	REGISTER_FEATURE_AS(CmdBurnsNofx, ConsoleActionFeature, "Console", "Suppress Burns FX", 0xBB1D30)
	REGISTER_FEATURE_AS(CmdBurnsElectricNofx, ConsoleActionFeature, "Console", "Suppress Electric Burns FX", 0xBB1EB0)
	REGISTER_FEATURE_AS(CmdCabinFeverNofx, ConsoleActionFeature, "Console", "Suppress Cabin Fever FX", 0xBB20F0)
	REGISTER_FEATURE_AS(CmdDysenteryNofx, ConsoleActionFeature, "Console", "Suppress Dysentery FX", 0xBB9180)
	REGISTER_FEATURE_AS(CmdFoodPoisonNofx, ConsoleActionFeature, "Console", "Suppress Food Poisoning FX", 0xBBCE90)
	REGISTER_FEATURE_AS(CmdFrostbiteNofx, ConsoleActionFeature, "Console", "Suppress Frostbite FX", 0xBBD350)
	REGISTER_FEATURE_AS(CmdHypothermiaNofx, ConsoleActionFeature, "Console", "Suppress Hypothermia FX", 0xBBF7A0)
	REGISTER_FEATURE_AS(CmdInfectionNofx, ConsoleActionFeature, "Console", "Suppress Infection FX", 0xBBFEE0)
	REGISTER_FEATURE_AS(CmdInfectionRiskNofx, ConsoleActionFeature, "Console", "Suppress Infection Risk FX", 0xBC0180)
	REGISTER_FEATURE_AS(CmdParasitesNofx, ConsoleActionFeature, "Console", "Suppress Parasites FX", 0xBC4690)
	REGISTER_FEATURE_AS(CmdSprainAnkleNofx, ConsoleActionFeature, "Console", "Suppress Sprained Ankle FX", 0xBCD2A0)
	REGISTER_FEATURE_AS(CmdSprainWristNofx, ConsoleActionFeature, "Console", "Suppress Sprained Wrist FX", 0xBCD5F0)
	REGISTER_FEATURE_AS(CmdSuppressBreathFx, ConsoleActionFeature, "Console", "Suppress Breath FX", 0xBCE420)

	// ---- utility ----
	REGISTER_FEATURE_AS(CmdForceGc, ConsoleActionFeature, "Console", "Force Garbage Collection", 0xBBC830)
	REGISTER_FEATURE_AS(CmdClearForceSleep, ConsoleActionFeature, "Console", "Clear Forced Sleep Length", 0xBB4030)
	REGISTER_FEATURE_AS(CmdCloseUi, ConsoleActionFeature, "Console", "Close UI", 0xBB4120)
	REGISTER_FEATURE_AS(CmdSnowShelter, ConsoleActionFeature, "Console", "Build Snow Shelter", 0xBCBFE0)
	REGISTER_FEATURE_AS(CmdSnowPatch, ConsoleActionFeature, "Console", "Snow Patch Debug", 0xBCBF30)
	REGISTER_FEATURE_AS(CmdLightingPreview, ConsoleActionFeature, "Console", "Lighting Preview", 0xBC0BE0)
}
