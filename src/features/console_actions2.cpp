#include "pch.h"
#include "features/common.h"

// Second batch of built-in developer-console commands: individual feats,
// affliction visual-effect suppression and assorted utility toggles.
namespace
{
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
