#include "pch.h"
#include "features/common.h"

// Wrappers around the game's built-in developer console commands
// (ConsoleManager.CONSOLE_*). These are toggles/actions that take no
// arguments, so they can be invoked directly by RVA.
namespace
{
	// ---- player / movement ----
	REGISTER_FEATURE_AS(CmdGod, ConsoleActionFeature, "Console", "God", 0xBBEB00)
	REGISTER_FEATURE_AS(CmdGhost, ConsoleActionFeature, "Console", "Ghost", 0xBBE9F0)
	REGISTER_FEATURE_AS(CmdNeverDie, ConsoleActionFeature, "Console", "Never Die", 0xBC3060)
	REGISTER_FEATURE_AS(CmdInvulnerable, ConsoleActionFeature, "Console", "Invulnerable", 0xBC0420)
	REGISTER_FEATURE_AS(CmdFly, ConsoleActionFeature, "Console", "Fly", 0xBBEE10)
	REGISTER_FEATURE_AS(CmdUnlimitedSprint, ConsoleActionFeature, "Console", "Unlimited Sprint", 0xBD0DB0)
	REGISTER_FEATURE_AS(CmdLockPlayer, ConsoleActionFeature, "Console", "Lock Player", 0xBC12A0)
	REGISTER_FEATURE_AS(CmdLockCamera, ConsoleActionFeature, "Console", "Lock Camera", 0xBBEEE0)
	REGISTER_FEATURE_AS(CmdForceCrouch, ConsoleActionFeature, "Console", "Force Crouch", 0xBBB1D0)
	REGISTER_FEATURE_AS(CmdForceWalk, ConsoleActionFeature, "Console", "Force Walk", 0xBBC330)
	REGISTER_FEATURE_AS(CmdForceLimp, ConsoleActionFeature, "Console", "Force Limp", 0xBBB340)
	REGISTER_FEATURE_AS(CmdForceLimpSlow, ConsoleActionFeature, "Console", "Force Limp Slow", 0xBBB430)
	REGISTER_FEATURE_AS(CmdForceNoSprain, ConsoleActionFeature, "Console", "Force No Random Sprain", 0xBBBF70)
	REGISTER_FEATURE_AS(CmdForceNoSprainWrist, ConsoleActionFeature, "Console", "Force No Sprain Wrist", 0xBBC250)
	REGISTER_FEATURE_AS(CmdForceMobility, ConsoleActionFeature, "Console", "Force Mobility Reduction", 0xBBCAC0)
	REGISTER_FEATURE_AS(CmdWellFed, ConsoleActionFeature, "Console", "Well Fed", 0xBD1EB0)
	REGISTER_FEATURE_AS(CmdLampInfinite, ConsoleActionFeature, "Console", "Lamp Infinite", 0xBC0740)
	REGISTER_FEATURE_AS(CmdToughClothes, ConsoleActionFeature, "Console", "Tough Clothes", 0xBC6BC0)
	REGISTER_FEATURE_AS(CmdCheatDeath, ConsoleActionFeature, "Console", "Cheat Death", 0xBB3930)
	REGISTER_FEATURE_AS(CmdCheatDeathCure, ConsoleActionFeature, "Console", "Cheat Death Cure", 0xBB3A20)

	// ---- affliction cures ----
	REGISTER_FEATURE_AS(CmdAfflictionsCure, ConsoleActionFeature, "Console", "Cure All Afflictions", 0xBAF3D0)
	REGISTER_FEATURE_AS(CmdBloodLossCure, ConsoleActionFeature, "Console", "Cure Blood Loss", 0xBB08A0)
	REGISTER_FEATURE_AS(CmdBrokenRibCure, ConsoleActionFeature, "Console", "Cure Broken Rib", 0xBB1060)
	REGISTER_FEATURE_AS(CmdBurnsCure, ConsoleActionFeature, "Console", "Cure Burns", 0xBB1CD0)
	REGISTER_FEATURE_AS(CmdBurnsElectricCure, ConsoleActionFeature, "Console", "Cure Electric Burns", 0xBB1E50)
	REGISTER_FEATURE_AS(CmdCabinFeverCure, ConsoleActionFeature, "Console", "Cure Cabin Fever", 0xBB2040)
	REGISTER_FEATURE_AS(CmdChemHazardCure, ConsoleActionFeature, "Console", "Cure Chemical Poisoning", 0xBB3AE0)
	REGISTER_FEATURE_AS(CmdDysenteryCure, ConsoleActionFeature, "Console", "Cure Dysentery", 0xBB9120)
	REGISTER_FEATURE_AS(CmdFoodPoisonCure, ConsoleActionFeature, "Console", "Cure Food Poisoning", 0xBBCE30)
	REGISTER_FEATURE_AS(CmdFrostbiteCure, ConsoleActionFeature, "Console", "Cure Frostbite", 0xBBD2F0)
	REGISTER_FEATURE_AS(CmdHypothermiaCure, ConsoleActionFeature, "Console", "Cure Hypothermia", 0xBBF740)
	REGISTER_FEATURE_AS(CmdInfectionCure, ConsoleActionFeature, "Console", "Cure Infection", 0xBBFE80)
	REGISTER_FEATURE_AS(CmdInfectionRiskCure, ConsoleActionFeature, "Console", "Cure Infection Risk", 0xBC0120)
	REGISTER_FEATURE_AS(CmdParasitesCure, ConsoleActionFeature, "Console", "Cure Intestinal Parasites", 0xBC4570)
	REGISTER_FEATURE_AS(CmdLacerationsCure, ConsoleActionFeature, "Console", "Cure Severe Lacerations", 0xBCA1B0)
	REGISTER_FEATURE_AS(CmdSourStomachCure, ConsoleActionFeature, "Console", "Cure Sour Stomach", 0xBCBED0)
	REGISTER_FEATURE_AS(CmdSprainAnkleCure, ConsoleActionFeature, "Console", "Cure Sprained Ankle", 0xBCD240)
	REGISTER_FEATURE_AS(CmdSprainWristCure, ConsoleActionFeature, "Console", "Cure Sprained Wrist", 0xBCD590)
	REGISTER_FEATURE_AS(CmdUnsettledSleepCure, ConsoleActionFeature, "Console", "Cure Unsettled Sleep", 0xBD0F00)
	REGISTER_FEATURE_AS(CmdWeakConstitutionCure, ConsoleActionFeature, "Console", "Cure Weak Constitution", 0xBD1D90)
	REGISTER_FEATURE_AS(CmdWeakJointsCure, ConsoleActionFeature, "Console", "Cure Weak Joints", 0xBD1E50)
	REGISTER_FEATURE_AS(CmdPoorCirculationCure, ConsoleActionFeature, "Console", "Cure Poor Circulation", 0xBC5730)
	REGISTER_FEATURE_AS(CmdDiminishedStateCure, ConsoleActionFeature, "Console", "Cure Diminished State", 0xBB82A0)
	REGISTER_FEATURE_AS(CmdSuppressFrostbite, ConsoleActionFeature, "Console", "Suppress Frostbite", 0xBCE660)
	REGISTER_FEATURE_AS(CmdSuppressHypothermia, ConsoleActionFeature, "Console", "Suppress Hypothermia", 0xBCE500)
	REGISTER_FEATURE_AS(CmdInhibitToxicHeadache, ConsoleActionFeature, "Console", "Inhibit Toxic Fog Headache", 0xBC0240)

	// ---- weather / time ----
	REGISTER_FEATURE_AS(CmdSuppressBlizzards, ConsoleActionFeature, "Console", "Suppress Blizzards", 0xBCA210)
	REGISTER_FEATURE_AS(CmdForceAurora, ConsoleActionFeature, "Console", "Force Aurora", 0xBBA7E0)
	REGISTER_FEATURE_AS(CmdForceAuroraImmediate, ConsoleActionFeature, "Console", "Force Aurora Immediate", 0xBBA910)
	REGISTER_FEATURE_AS(CmdForceElectrostaticFog, ConsoleActionFeature, "Console", "Force Electrostatic Fog", 0xBBA6E0)
	REGISTER_FEATURE_AS(CmdNextWeather, ConsoleActionFeature, "Console", "Next Weather", 0xBC2E30)
	REGISTER_FEATURE_AS(CmdNextWeatherSet, ConsoleActionFeature, "Console", "Next Weather Set", 0xBC2FF0)
	REGISTER_FEATURE_AS(CmdTurboWeather, ConsoleActionFeature, "Console", "Turbo Weather", 0xBD08B0)
	REGISTER_FEATURE_AS(CmdRandomWeather, ConsoleActionFeature, "Console", "Random Weather", 0xBC5D70)
	REGISTER_FEATURE_AS(CmdReloadWeatherOverride, ConsoleActionFeature, "Console", "Reload Weather Override", 0xBADE30)
	REGISTER_FEATURE_AS(CmdTimeAccelerate, ConsoleActionFeature, "Console", "Accelerate Time", 0xBD0420)
	REGISTER_FEATURE_AS(CmdPassTime, ConsoleActionFeature, "Console", "Pass Time", 0xBC42C0)

	// ---- world ----
	REGISTER_FEATURE_AS(CmdSave, ConsoleActionFeature, "Console", "Save Game", 0xBC76C0)
	REGISTER_FEATURE_AS(CmdAutoSave, ConsoleActionFeature, "Console", "Auto Save", 0xBBFC50)
	REGISTER_FEATURE_AS(CmdClearJunk, ConsoleActionFeature, "Console", "Clear Junk", 0xBB40B0)
	REGISTER_FEATURE_AS(CmdHideWatermark, ConsoleActionFeature, "Console", "Hide Test Watermark", 0xBBF2A0)
	REGISTER_FEATURE_AS(CmdMapGps, ConsoleActionFeature, "Console", "Map GPS", 0xBD4460)

	// ---- animals / AI ----
	REGISTER_FEATURE_AS(CmdKillAllAnimals, ConsoleActionFeature, "Console", "Kill All Animals", 0xBD2C80)
	REGISTER_FEATURE_AS(CmdDisableAi, ConsoleActionFeature, "Console", "Disable AI", 0xBB4840)
	REGISTER_FEATURE_AS(CmdNpcInvulnerable, ConsoleActionFeature, "Console", "NPC Invulnerable", 0xBC3DB0)
	REGISTER_FEATURE_AS(CmdNpcDisableConditions, ConsoleActionFeature, "Console", "NPC Disable Conditions", 0xBC3600)
	REGISTER_FEATURE_AS(CmdForceHowl, ConsoleActionFeature, "Console", "Force Wolf Howl", 0xBBC520)
	REGISTER_FEATURE_AS(CmdStrugglePartnerFlee, ConsoleActionFeature, "Console", "Make Struggle Partner Flee", 0xBC2500)
	REGISTER_FEATURE_AS(CmdCarrionStagger, ConsoleActionFeature, "Console", "Carrion Stagger", 0xBB2710)

	// ---- items ----
	REGISTER_FEATURE_AS(CmdBuffsLoseAll, ConsoleActionFeature, "Console", "Remove All Buffs", 0xBB1B80)
	REGISTER_FEATURE_AS(CmdGearLostAndFound, ConsoleActionFeature, "Console", "Add Lost And Found Gear", 0xBAE3F0)
	REGISTER_FEATURE_AS(CmdDropScatterInHands, ConsoleActionFeature, "Console", "Drop Scatter Item In Hands", 0xBD0060)
	REGISTER_FEATURE_AS(CmdStowItem, ConsoleActionFeature, "Console", "Stow Item In Hands", 0xBD03C0)
	REGISTER_FEATURE_AS(CmdUnequipImmediate, ConsoleActionFeature, "Console", "Unequip Immediately", 0xBD0CB0)
	REGISTER_FEATURE_AS(CmdFireStartingSuccess, ConsoleActionFeature, "Console", "Force Fire Start Success", 0xBBC750)
	REGISTER_FEATURE_AS(CmdForceNoJam, ConsoleActionFeature, "Console", "Force No Jam", 0xBBC150)
	REGISTER_FEATURE_AS(CmdForceJam, ConsoleActionFeature, "Console", "Force Jam", 0xBBC050)

	// ---- camera / render ----
	REGISTER_FEATURE_AS(CmdDisableAmbientSway, ConsoleActionFeature, "Console", "Disable Ambient Sway", 0xBCFE70)
	REGISTER_FEATURE_AS(CmdDisableAimSway, ConsoleActionFeature, "Console", "Disable Aim Sway", 0xBCFB40)
	REGISTER_FEATURE_AS(CmdDisableAimShake, ConsoleActionFeature, "Console", "Disable Aim Shake", 0xBCFD50)
	REGISTER_FEATURE_AS(CmdDisableAimStamina, ConsoleActionFeature, "Console", "Disable Aim Stamina", 0xBCFC30)
	REGISTER_FEATURE_AS(CmdDisableAimBreath, ConsoleActionFeature, "Console", "Disable Aim Breath", 0xBCFA20)
	REGISTER_FEATURE_AS(CmdDisableAimDof, ConsoleActionFeature, "Console", "Disable Aim Depth Of Field", 0xBD02A0)
	REGISTER_FEATURE_AS(CmdShowFps, ConsoleActionFeature, "Console", "Show FPS", 0xBCAD20)
	REGISTER_FEATURE_AS(CmdShowCoords, ConsoleActionFeature, "Console", "Show Coordinates", 0xBCA820)
	REGISTER_FEATURE_AS(CmdShowCalories, ConsoleActionFeature, "Console", "Show Calories", 0xBCA740)
	REGISTER_FEATURE_AS(CmdShowTemperature, ConsoleActionFeature, "Console", "Show Temperature", 0xBCB250)
	REGISTER_FEATURE_AS(CmdShowDaysSurvived, ConsoleActionFeature, "Console", "Show Days Survived", 0xBCABB0)
	REGISTER_FEATURE_AS(CmdFarclip, ConsoleActionFeature, "Console", "Far Clip", 0xBB95B0)
	REGISTER_FEATURE_AS(CmdVsync, ConsoleActionFeature, "Console", "Toggle VSync", 0xBD1240)
}
