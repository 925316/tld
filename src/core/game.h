#pragma once

struct Vector3 { float x, y, z; };
struct Quaternion { float x, y, z, w; };

struct System_String
{
	void* klass;
	void* monitor;
	int m_iLength;
	wchar_t m_wString[1024];

	std::string ToString() const
	{
		if (!this) return {};
		std::string result(static_cast<size_t>(m_iLength + 1) * 4, '\0');
		int len = WideCharToMultiByte(CP_UTF8, 0, m_wString, m_iLength,
			result.data(), static_cast<int>(result.size()),
			nullptr, nullptr);
		result.resize(len);
		return result;
	}
};

// ---- function pointer types ----

using GameManager_GetVpFPSCamera = void* (*)(void*);
using vp_FPSCamera_GetCameraComponent = void* (*)(void*);
using Component_get_transform = void* (*)(void*);
using Transform_get_position = Vector3(*)(void*);
using Transform_get_rotation = Quaternion(*)(void*);
using Component_get_gameObject = void* (*)(void*);
using GameObject_get_activeInHierarchy = bool (*)(void*);
using GameObject_get_transform = void* (*)(void*);
using Camera_get_main = void* (*)();
using Camera_WorldToScreenPoint = Vector3(*)(void*, Vector3, int);
using GearItem_get_DisplayName = System_String * (*)(void*);
using GameManager_GetPlayerManager = void* (*)(void*);
using GameManager_GetCondition = void* (*)(void*);
using GameManager_GetFatigue = void* (*)(void*);
using GameManager_GetFreezing = void* (*)(void*);
using GameManager_GetHunger = void* (*)(void*);
using GameManager_GetThirst = void* (*)(void*);
using vp_FPSCamera_SetAngle = void (*)(void*, float, float, void*);
using BaseAi_GetEyePos = Vector3(*)(void*, void*);

using BaseAiManager_Add = void (*)(void*, void*);
using BaseAiManager_Remove = void (*)(void*, void*);
using GearManager_Add = void (*)(void*, void*);
using GearManager_Remove = void (*)(void*, void*);

using FireManager_CalculateFireStartSuccess = float (*)(void*, void*, void*, void*, void*);
using PanelRepair_GetChanceSuccess = float (*)(void*, void*);
using Examine_RollForActionSuccess = bool (*)(void*, float, void*);
using IceFishingHole_OnActiveFishingComplete = void (*)(void*, bool, bool, float, void*);

// ---- field offsets (sdk/dump.cs, 2026-04 build) ----

namespace Offsets
{
	// BaseAi
	constexpr uintptr_t AiCurrentHP = 0x328;
	constexpr uintptr_t AiMaxHP = 0x32C;
	constexpr uintptr_t AiDisplayName = 0x2F8;
	constexpr uintptr_t AiMode = 0x470;
	constexpr uintptr_t AiSubType = 0x31C;
	constexpr uintptr_t AiOverrideSpeed = 0xA4;
	// vp_FPSCamera
	constexpr uintptr_t CameraInFPS = 0x1F0;
	// PlayerManager
	constexpr uintptr_t GodMode = 0x1C3;
	constexpr uintptr_t SuspendCondition = 0x1F2;
	constexpr uintptr_t GhostMode = 0x1C2;
	constexpr uintptr_t ForceAIFlee = 0x1F1;
	constexpr uintptr_t PlayerFreezeMovement = 0x210;
	constexpr uintptr_t PlayerDisableAllSpeech = 0x1F4;
	constexpr uintptr_t PlayerAllowPanelInteraction = 0x1F0;
	constexpr uintptr_t PlayerFatigueRateScale = 0x28;
	constexpr uintptr_t PlayerFreezingRateScale = 0x20;
	constexpr uintptr_t PlayerConditionPercentBonus = 0x2C;
	constexpr uintptr_t PlayerConditionPerHourBonus = 0x38;
	constexpr uintptr_t PlayerWarmthBonusFromClothing = 0xC0;
	constexpr uintptr_t PlayerWindproofBonusFromClothing = 0xC4;
	// Condition
	constexpr uintptr_t ConditionHP = 0x20;
	constexpr uintptr_t ConditionMaxHP = 0x24;
	constexpr uintptr_t NeverDie = 0xD8;
	constexpr uintptr_t Invulnerable = 0xD9;
	constexpr uintptr_t HideDamageEvents = 0xDA;
	constexpr uintptr_t ConditionForceUncrouched = 0xDB;
	// Fatigue
	constexpr uintptr_t CurrentFatigue = 0x24;
	constexpr uintptr_t MaxFatigue = 0x28;
	// Freezing
	constexpr uintptr_t CurrentFreezing = 0x28;
	constexpr uintptr_t MaxFreezing = 0x2C;
	// Hunger
	constexpr uintptr_t CurrentCalories = 0x20;
	constexpr uintptr_t MaxCalories = 0x78;
	// Thirst
	constexpr uintptr_t CurrentThirst = 0x24;
	constexpr uintptr_t MaxThirst = 0x28;
	// Frostbite
	constexpr uintptr_t FrostbiteSuppress = 0x91;
	// Hypothermia
	constexpr uintptr_t HypothermiaActive = 0x60;
	constexpr uintptr_t HypothermiaSuppress = 0x79;
	// Infection
	constexpr uintptr_t InfectionLocations = 0x70;
	constexpr uintptr_t InfectionElapsedHours = 0x78;
	// InfectionRisk
	constexpr uintptr_t InfectionRiskLocations = 0x88;
	constexpr uintptr_t InfectionRiskElapsedHours = 0x98;
	// SprainedAnkle
	constexpr uintptr_t SprainedAnkleLocations = 0xB0;
	constexpr uintptr_t SprainedAnkleElapsedHours = 0xB8;
	// SprainedWrist
	constexpr uintptr_t SprainedWristLocations = 0x78;
	constexpr uintptr_t SprainedWristNoSprainForced = 0x98;
	// BloodLoss
	constexpr uintptr_t BloodLossLocations = 0x98;
	constexpr uintptr_t BloodLossForceNoDamage = 0xB1;
	// Burns
	constexpr uintptr_t BurnsActive = 0x90;
	constexpr uintptr_t BurnsElectricActive = 0x98;
	// FoodPoisoning
	constexpr uintptr_t FoodPoisoningActive = 0x70;
	// Dysentery
	constexpr uintptr_t DysenteryActive = 0x78;
	// IntestinalParasites
	constexpr uintptr_t ParasitesHas = 0x50;
	constexpr uintptr_t ParasitesRisk = 0x51;
	// CabinFever
	constexpr uintptr_t CabinFeverActive = 0x58;
	constexpr uintptr_t CabinFeverRiskActive = 0x59;
	// BrokenRib
	constexpr uintptr_t BrokenRibLocations = 0x70;
	// ChemicalPoisoning
	constexpr uintptr_t ChemPoisonToxicity = 0xB4;
	// Suffocating
	constexpr uintptr_t SuffocatingBlock = 0x9D;
	// PlayerMovement
	constexpr uintptr_t MaxSprintStamina = 0x7C;
	constexpr uintptr_t SprintStamina = 0x80;
	constexpr uintptr_t SprintStaminaUsagePerSecond = 0x60;
	constexpr uintptr_t SprintStaminaRecoverPerHour = 0x5C;
	// vp_FPSController
	constexpr uintptr_t FPSController = 0x48;
	constexpr uintptr_t MotorVelocityMin = 0x50;
	constexpr uintptr_t MotorVelocityMax = 0x54;
	constexpr uintptr_t MotorAcceleration = 0x58;
	constexpr uintptr_t MotorJumpForce = 0x60;
	constexpr uintptr_t MotorAirSpeed = 0x64;
	constexpr uintptr_t PhysicsGravityModifier = 0x98;
	// FallDamage
	constexpr uintptr_t FallHeightStartDamage = 0x20;
	constexpr uintptr_t FallDamagePerMeter = 0x24;
	// PlayerClimbRope
	constexpr uintptr_t ClimbSpeedUpFullyRested = 0x20;
	constexpr uintptr_t ClimbStaminaDrainUp = 0x38;
	constexpr uintptr_t ClimbSlipChanceInitial = 0x68;
	constexpr uintptr_t ClimbFallChanceInitial = 0x78;
	// Encumber
	constexpr uintptr_t MaxCarryCapacity = 0x20;
	constexpr uintptr_t HourlyCalorieBurnPerKG = 0x48;
	// WellFed
	constexpr uintptr_t WellFedActive = 0x50;
	// SprainProtection
	constexpr uintptr_t SprainProtectionHas = 0x20;
	// Weather
	constexpr uintptr_t WeatherCurrentTemperature = 0x1F0;
	constexpr uintptr_t WeatherBaseTemperature = 0x1EC;
	constexpr uintptr_t WeatherIndoorTemperature = 0x20;
	constexpr uintptr_t WeatherWindChill = 0x1F8;
	constexpr uintptr_t WeatherArtificialTempIncrease = 0x208;
	constexpr uintptr_t WeatherLockedAirTemperature = 0x230;
	// WeatherTransition
	constexpr uintptr_t WeatherUnmanagedStage = 0x34;
	// Wind
	constexpr uintptr_t WindCurrentMPH = 0xF8;
	constexpr uintptr_t WindChill = 0x130;
	constexpr uintptr_t WindLockedSpeed = 0x170;
	constexpr uintptr_t WindNeverCalm = 0x174;
	constexpr uintptr_t WindArtificialSpeedIncrease = 0x180;
	// TimeOfDay
	constexpr uintptr_t TODDayLengthScale = 0x98;
	constexpr uintptr_t TODLockedTOD = 0xE4;
	constexpr uintptr_t TODSpeedupCounter = 0x30;
	// FireManager
	constexpr uintptr_t FireForceStartSuccess = 0x90;
	constexpr uintptr_t FireStartTimeSeconds = 0x30;
	constexpr uintptr_t FireStartTimeSecondsWet = 0x34;
	constexpr uintptr_t FireMaxDurationHours = 0x48;
	constexpr uintptr_t FireWindBlowsOut = 0x24;
	constexpr uintptr_t FireWindStartingImpossible = 0x20;
	constexpr uintptr_t FireMaxHeatIncrease = 0x44;
	// Fire
	constexpr uintptr_t FireIsPerpetual = 0x29;
	constexpr uintptr_t FireStartLit = 0x28;
	constexpr uintptr_t FireElapsedOnTOD = 0xCC;
	constexpr uintptr_t FireMaxOnTOD = 0xD4;
	// Inventory
	constexpr uintptr_t InvForceOverrideWeight = 0xD1;
	constexpr uintptr_t InvOverridedWeight = 0xD8;
	constexpr uintptr_t InvSuppressScent = 0xE8;
	constexpr uintptr_t InvItems = 0x30;
	constexpr uintptr_t InvTotalWeight = 0xA8;
	// GearItem
	constexpr uintptr_t GearCurrentHP = 0x340;
	constexpr uintptr_t GearHaltDecay = 0x37A;
	constexpr uintptr_t GearDecayScalar = 0x38C;
	constexpr uintptr_t GearInPlayerInventory = 0x28;
	// GearItem subcomponents
	constexpr uintptr_t GearBodyHarvest = 0x78;
	constexpr uintptr_t GearClothingItem = 0xB0;
	constexpr uintptr_t GearCookable = 0xC8;
	constexpr uintptr_t GearDegradeOnUse = 0xD8;
	constexpr uintptr_t GearFireStarterItem = 0x100;
	constexpr uintptr_t GearFlareItem = 0x120;
	constexpr uintptr_t GearFlashlightItem = 0x128;
	constexpr uintptr_t GearFoodItem = 0x130;
	constexpr uintptr_t GearGunItem = 0x168;
	constexpr uintptr_t GearKeroseneLampItem = 0x190;
	constexpr uintptr_t GearRepairable = 0x1E0;
	constexpr uintptr_t GearSharpenable = 0x210;
	constexpr uintptr_t GearTorchItem = 0x250;
	constexpr uintptr_t GearWaterSupply = 0x260;
	constexpr uintptr_t GearBowItem = 0x80;
	constexpr uintptr_t GearArrowItem = 0x50;
	constexpr uintptr_t GearSnareItem = 0x220;
	constexpr uintptr_t GearForageItem = 0x140;
	constexpr uintptr_t GearBreakDownItem = 0x88;
	constexpr uintptr_t GearMillable = 0x1B0;
	constexpr uintptr_t GearSmashableItem = 0x218;
	constexpr uintptr_t GearFirstAidItem = 0x108;
	constexpr uintptr_t GearPurifyWater = 0x1D8;
	constexpr uintptr_t GearHeatPadItem = 0x2B0;
	constexpr uintptr_t GearInsulatedFlask = 0x2A8;
	constexpr uintptr_t GearSprayPaintCan = 0x228;
	constexpr uintptr_t GearHandheldShortwave = 0x160;
	constexpr uintptr_t GearLureItem = 0x290;
	constexpr uintptr_t GearBaitItem = 0x298;
	constexpr uintptr_t GearTravois = 0x258;
	constexpr uintptr_t GearCharcoalItem = 0xA0;
	constexpr uintptr_t GearCanOpeningItem = 0x90;
	constexpr uintptr_t GearEmergencyStim = 0xE0;
	constexpr uintptr_t GearEnergyBoost = 0xE8;
	constexpr uintptr_t GearFuelSourceItem = 0x158;
	constexpr uintptr_t GearFirstPersonItem = 0x110;
	constexpr uintptr_t GearInspect = 0x188;
	constexpr uintptr_t GearMatchesItem = 0x1A8;
	constexpr uintptr_t GearResearchItem = 0x1E8;
	constexpr uintptr_t GearStackableItem = 0x230;
	constexpr uintptr_t GearStruggleBonus = 0x240;
	constexpr uintptr_t GearToolsItem = 0x248;
	constexpr uintptr_t GearCookingPotItem = 0xD0;
	// FireStarterItem
	constexpr uintptr_t FireStarterIgniteTinder = 0x20;
	constexpr uintptr_t FireStarterIgniteTorch = 0x24;
	// PlayerMovement stealth
	constexpr uintptr_t DetectionRangeScaleCrouched = 0x4C;
	constexpr uintptr_t FootStepRangeScaleCrouched = 0x50;
	constexpr uintptr_t FootStepRangeScaleWalking = 0x54;
	// Sprains
	constexpr uintptr_t SprainChanceMovingWrist = 0x2C;
	constexpr uintptr_t SprainBaseChanceSlope = 0x34;
	constexpr uintptr_t SprainChanceEncumbered = 0x40;
	constexpr uintptr_t SprainChanceExhausted = 0x44;
	constexpr uintptr_t SprainChanceSprinting = 0x48;
	// PlayerStruggle
	constexpr uintptr_t StruggleBearConditionLoss = 0x38;
	constexpr uintptr_t StruggleMooseConditionLoss = 0x3C;
	constexpr uintptr_t StruggleWolfDamagePerSecond = 0x90;
	constexpr uintptr_t StruggleWolfClothingDamageMin = 0x94;
	constexpr uintptr_t StruggleWolfClothingDamageMax = 0x98;
	constexpr uintptr_t StruggleBearClothingDamageMin = 0x9C;
	constexpr uintptr_t StruggleBearClothingDamageMax = 0xA0;
	constexpr uintptr_t StruggleCougarDamagePerSecond = 0xA4;
	constexpr uintptr_t StruggleCougarClothingDamageMin = 0xA8;
	constexpr uintptr_t StruggleCougarClothingDamageMax = 0xAC;
	constexpr uintptr_t StruggleFleeChanceOnHit = 0xB0;
	constexpr uintptr_t StruggleFleeChanceOnShot = 0xB4;
	constexpr uintptr_t StruggleStunnedAfterBear = 0x50;
	constexpr uintptr_t StruggleStunnedAfterWolf = 0x54;
	constexpr uintptr_t StruggleSystemEnabled = 0x132;
	constexpr uintptr_t StruggleStunnedAfterCougar = 0x48;
	// ClothingItem damage
	constexpr uintptr_t ClothingDecayWornOutside = 0x30;
	constexpr uintptr_t ClothingDecayWornInside = 0x34;
	// Headache
	constexpr uintptr_t HeadacheInstances = 0x30;
	// SprainPain
	constexpr uintptr_t SprainPainInstances = 0x50;
	// TimeOfDay durations
	constexpr uintptr_t TODDayDurationMinutes = 0x3C;
	constexpr uintptr_t TODNightDurationMinutes = 0x40;
	// PlayerManager wetness rates
	constexpr uintptr_t PlayerWetnessLightSnow = 0xA8;
	constexpr uintptr_t PlayerWetnessHeavySnow = 0xAC;
	constexpr uintptr_t PlayerWetnessBlizzard = 0xB0;
	// IceFishingHole
	constexpr uintptr_t IceFreezePercentPerHour = 0x28;
	constexpr uintptr_t IceMinMinutesCatch = 0x2C;
	constexpr uintptr_t IceMaxMinutesCatch = 0x30;
	constexpr uintptr_t IceLineSnapDecay = 0x44;
	constexpr uintptr_t IceOverfishingLimit = 0x4C;
	constexpr uintptr_t IcePauseFreezing = 0x128;
	// Repairable / Sharpenable
	constexpr uintptr_t RepairableDurationMinutes = 0x40;
	constexpr uintptr_t SharpenDurationMinutesMin = 0x38;
	constexpr uintptr_t SharpenDurationMinutesMax = 0x3C;
	// Rest
	constexpr uintptr_t RestReduceFatiguePerHour = 0x20;
	constexpr uintptr_t RestMaxHoursSleepPerDay = 0x24;
	constexpr uintptr_t RestPredatorInterruptionChance = 0x40;
	constexpr uintptr_t RestPredatorInterruptionChanceShelter = 0x44;
	constexpr uintptr_t RestWakeUpAtFullRest = 0x60;
	// Anxiety / Fear
	constexpr uintptr_t MentalHasAffliction = 0x78;
	constexpr uintptr_t MentalHealthLossPerMinute = 0x64;
	// ToxicFog
	constexpr uintptr_t ToxicFogHasAffliction = 0x6C;
	constexpr uintptr_t ToxicFogHealthLossPerMinute = 0x48;
	constexpr uintptr_t ToxicFogAllowHeadache = 0x6D;
	// Willpower
	constexpr uintptr_t WillpowerTimeRemainingSeconds = 0x20;
	constexpr uintptr_t WillpowerConditionBonusPerSecond = 0x24;
	constexpr uintptr_t WillpowerConditionBonusCap = 0x28;
	constexpr uintptr_t WillpowerConditionDamageScale = 0x2C;
	// Condition extras
	constexpr uintptr_t ConditionCriticalHP = 0x28;
	constexpr uintptr_t ConditionOverrideBlurLevel = 0xDC;
	// Weather extras
	constexpr uintptr_t WeatherBlizzardDegreesDrop = 0x34;
	constexpr uintptr_t WeatherBlizzardChangePerSecond = 0x38;
	constexpr uintptr_t WeatherDegreesPerSecondLow = 0x58;
	constexpr uintptr_t WeatherDegreesPerSecondMedium = 0x5C;
	constexpr uintptr_t WeatherDegreesPerSecondHigh = 0x60;
	constexpr uintptr_t WeatherMinWindForBlowingSnow = 0x68;
	constexpr uintptr_t WeatherClothingDamageInBlizzard = 0x138;
	// Wind extras
	constexpr uintptr_t WindMaxMPH = 0x28;
	// Campfire / FireplaceInteraction
	constexpr uintptr_t CampfireBurnedOut = 0xB8;
	constexpr uintptr_t FireplaceFire = 0x60;
	// MapDetail
	constexpr uintptr_t MapDetailUnlocked = 0x88;
	constexpr uintptr_t MapDetailDiscovered = 0x98;
	constexpr uintptr_t MapDetailSurveyed = 0x99;
	// Harvestable
	constexpr uintptr_t HarvestableHarvested = 0x90;
	constexpr uintptr_t HarvestableNumPrimary = 0x88;
	constexpr uintptr_t HarvestableNumSecondary = 0x8C;
	constexpr uintptr_t HarvestableRefreshMin = 0x74;
	constexpr uintptr_t HarvestableRefreshMax = 0x78;
	// Insomnia
	constexpr uintptr_t InsomniaResistHours = 0x40;
	constexpr uintptr_t InsomniaResistMultiplier = 0x44;
	// Scurvy
	constexpr uintptr_t ScurvyRiskThreshold = 0x30;
	constexpr uintptr_t ScurvyCureThreshold = 0x34;
	constexpr uintptr_t ScurvyStaminaDrainMultiplier = 0x48;
	constexpr uintptr_t ScurvyFatigueMultiplier = 0x4C;
	// Aurora wildlife scales
	constexpr uintptr_t AuroraWildlifeDetectionScale = 0x34;
	constexpr uintptr_t AuroraWildlifeFleeScale = 0x38;
	constexpr uintptr_t AuroraDamageToPredatorsScale = 0x3C;
	constexpr uintptr_t AuroraPredatorInflictDamageScale = 0x40;
	constexpr uintptr_t AuroraPredatorFleeChanceScale = 0x44;
	constexpr uintptr_t AuroraPredatorAttackDistanceScale = 0x48;
	// CharcoalItem
	constexpr uintptr_t CharcoalSurveyGameMinutes = 0x20;
	constexpr uintptr_t CharcoalSurveyRealSeconds = 0x24;
	// HandheldShortwaveItem
	constexpr uintptr_t ShortwaveIntensity = 0x38;
	constexpr uintptr_t ShortwaveFullSignalRange = 0x40;
	constexpr uintptr_t ShortwaveMaxRange = 0x44;
	// Repairable
	constexpr uintptr_t RepairNeverFail = 0x59;
	constexpr uintptr_t RepairConditionIncrease = 0x38;
	// Sharpenable
	constexpr uintptr_t SharpenConditionIncreaseMin = 0x30;
	// ClothingItem
	constexpr uintptr_t ClothingPercentWet = 0xA0;
	constexpr uintptr_t ClothingPercentFrozen = 0xA4;
	constexpr uintptr_t ClothingWarmth = 0x38;
	constexpr uintptr_t ClothingWindproof = 0x40;
	constexpr uintptr_t ClothingWaterproofness = 0x4C;
	// TorchItem
	constexpr uintptr_t TorchElapsedBurn = 0xC4;
	constexpr uintptr_t TorchBurnLifetime = 0x20;
	constexpr uintptr_t TorchWindExtinguish = 0x8C;
	// KeroseneLampItem
	constexpr uintptr_t LampCurrentFuel = 0x70;
	constexpr uintptr_t LampMaxFuel = 0x20;
	// FlashlightItem
	constexpr uintptr_t FlashlightBattery = 0xB4;
	// FlareItem
	constexpr uintptr_t FlareElapsedBurn = 0xAC;
	constexpr uintptr_t FlareBurnLifetime = 0x24;
	// FoodItem
	constexpr uintptr_t FoodCaloriesRemaining = 0x28;
	constexpr uintptr_t FoodCaloriesTotal = 0x2C;
	constexpr uintptr_t FoodChancePoisoning = 0x3C;
	constexpr uintptr_t FoodHeatPercent = 0x98;
	// WaterSupply
	constexpr uintptr_t WaterVolume = 0x28;
	// Cookable
	constexpr uintptr_t CookTimeMinutes = 0x30;
	// CookingPotItem
	constexpr uintptr_t PotCookingTimeMultiplier = 0x40;
	// DegradeOnUse
	constexpr uintptr_t DegradeHP = 0x20;
	// GunItem
	constexpr uintptr_t GunRoundsInClip = 0x3C;
	constexpr uintptr_t GunClipSize = 0x40;
	constexpr uintptr_t GunDamageHP = 0x48;
	constexpr uintptr_t GunAccuracyRange = 0x5C;
	constexpr uintptr_t GunPitchRecoilMin = 0x120;
	constexpr uintptr_t GunYawRecoilMin = 0x128;
	constexpr uintptr_t GunSwayZeroFatigue = 0x100;
	constexpr uintptr_t GunSwayMaxFatigue = 0x104;
	constexpr uintptr_t GunFiringRate = 0x4C;
	constexpr uintptr_t GunReloadCooldown = 0x50;
	constexpr uintptr_t GunPitchRecoilMax = 0x124;
	constexpr uintptr_t GunYawRecoilMax = 0x12C;
	constexpr uintptr_t GunForceNoJamStatic = 0x8;
	// BodyHarvest (carcass)
	constexpr uintptr_t CorpseFrozen = 0x120;
	constexpr uintptr_t CorpseAllowFreezing = 0x14E;
	constexpr uintptr_t CorpsePercentFrozen = 0x150;
	constexpr uintptr_t CorpseAllowDecay = 0x14D;
	constexpr uintptr_t CorpseDecayPerHour = 0xA8;
	constexpr uintptr_t CorpseCondition = 0x148;
	// Skill
	constexpr uintptr_t SkillCurrentPoints = 0x60;
	// SkillsManager skill instance fields
	constexpr uintptr_t SkillsMgrFirestarting = 0x70;
	constexpr uintptr_t SkillsMgrCarcassHarvesting = 0x78;
	constexpr uintptr_t SkillsMgrCooking = 0x80;
	constexpr uintptr_t SkillsMgrIceFishing = 0x88;
	constexpr uintptr_t SkillsMgrRifle = 0x90;
	constexpr uintptr_t SkillsMgrArchery = 0x98;
	constexpr uintptr_t SkillsMgrClothingRepair = 0xA0;
	constexpr uintptr_t SkillsMgrRevolver = 0xA8;
	constexpr uintptr_t SkillsMgrGunsmithing = 0xB0;
	// vp_FPSPlayer
	constexpr uintptr_t FPSPlayerCamera = 0x28;
	constexpr uintptr_t FPSPlayerController = 0x30;
	constexpr uintptr_t FPSPlayerCrouchToggle = 0x50;
	constexpr uintptr_t FPSPlayerInZoom = 0x55;
	constexpr uintptr_t FPSPlayerAutoWalking = 0x75;
	// vp_FPSCamera
	constexpr uintptr_t CameraMouseSensitivity = 0xB8;
	constexpr uintptr_t CameraZoomedSensitivity = 0xC0;
	constexpr uintptr_t CameraRenderingFOV = 0xE8;
	constexpr uintptr_t CameraUnzoomedFOV = 0xEC;
	constexpr uintptr_t CameraNearClip = 0x278;
	constexpr uintptr_t CameraAmbientSwayAngle = 0x98;
	constexpr uintptr_t CameraAmbientSwaySpeed = 0x9C;
	constexpr uintptr_t CameraDisableAmbientSwayStatic = 0x2;
	// extra FallDamage
	constexpr uintptr_t FallRopeDamagePerMeter = 0x28;
	constexpr uintptr_t FallClothingDamagePerMeter = 0x34;
	// extra PlayerMovement
	constexpr uintptr_t PlayerForcedMovement = 0xA4;
	constexpr uintptr_t PlayerForceNoRandomSprain = 0xA8;
	// extra PlayerClimbRope
	constexpr uintptr_t ClimbSpeedDownFullyRested = 0x28;
	constexpr uintptr_t ClimbStaminaDrainDown = 0x3C;
	constexpr uintptr_t ClimbSlipIncreasePerRoll = 0x6C;
	constexpr uintptr_t ClimbFallIncreasePerRoll = 0x7C;
	// static fields (written through klass->static_fields)
	constexpr uintptr_t AuroraForceDisable = 0x0;
	constexpr uintptr_t WeatherSuppressBlizzards = 0x4;
	constexpr uintptr_t WeatherTransitionTimeScalar = 0x0;
}

// ---- resolved pointers ----

extern uintptr_t g_gameAssemblyBase;
extern bool g_gameReady;

// RVAs relative to GameAssembly.dll base (sdk/dump.cs, 2026-04 build).
namespace Rva
{
	// GameManager
	constexpr uintptr_t GetVpFPSCamera = 0xC409E0;
	constexpr uintptr_t GetMainCamera = 0xC40800;
	constexpr uintptr_t GetPlayerManagerComponent = 0xC42E00;
	constexpr uintptr_t GetConditionComponent = 0xC41510;
	constexpr uintptr_t GetFatigueComponent = 0xC41A60;
	constexpr uintptr_t GetFreezingComponent = 0xC41BE0;
	constexpr uintptr_t GetHungerComponent = 0xC41DC0;
	constexpr uintptr_t GetThirstComponent = 0xC43E50;
	// vp_FPSCamera
	constexpr uintptr_t GetCameraComponent = 0x54A2C0;
	constexpr uintptr_t SetAngle = 0x551D40;
	// UnityEngine
	constexpr uintptr_t Component_get_transform = 0x3ADEDB0;
	constexpr uintptr_t Transform_get_position = 0x3AFFE30;
	constexpr uintptr_t Transform_get_rotation = 0x3B00FB0;
	constexpr uintptr_t Component_get_gameObject = 0x3ADEE70;
	constexpr uintptr_t GameObject_get_activeInHierarchy = 0x3AE4F10;
	constexpr uintptr_t GameObject_get_transform = 0x3AE4A60;
	constexpr uintptr_t Camera_get_main = 0x3A45BB0;
	constexpr uintptr_t Camera_WorldToScreenPoint = 0x3A44650;
	constexpr uintptr_t RenderSettings_SetFog = 0x3A72890;
	constexpr uintptr_t RenderSettings_SetAmbientIntensity = 0x3A72790;
	constexpr uintptr_t RenderSettings_SetFogDensity = 0x3A72BE0;
	constexpr uintptr_t RenderSettings_SetFogStartDistance = 0x3A72930;
	constexpr uintptr_t RenderSettings_SetFogEndDistance = 0x3A729E0;
	// game
	constexpr uintptr_t GearItem_get_DisplayName = 0x8369A0;
	constexpr uintptr_t BaseAi_GetEyePos = 0x59C3F0;
	// manager hooks (tracking.cpp)
	constexpr uintptr_t BaseAiManager_Add = 0xC04050;
	constexpr uintptr_t BaseAiManager_Remove = 0xC04470;
	constexpr uintptr_t GearManager_Add = 0xC54500;
	constexpr uintptr_t GearManager_Remove = 0xC556D0;
	// roll hooks (features/always_succeed.cpp)
	constexpr uintptr_t FireManager_CalculateFireStartSuccess = 0xC24FC0;
	constexpr uintptr_t PanelRepair_GetChanceSuccess = 0xB4A960;
	constexpr uintptr_t Examine_RollForActionSuccess = 0xA99DB0;
	constexpr uintptr_t IceFishingHole_OnActiveFishingComplete = 0x909B60;

	// ---- GameManager component getters ----
	constexpr uintptr_t GM_GetVpFPSPlayer = 0xC40A40;
	constexpr uintptr_t GM_GetUniStorm = 0xC41080;
	constexpr uintptr_t GM_GetAuroraManager = 0xC410F0;
	constexpr uintptr_t GM_GetAchievementManager = 0xC41150;
	constexpr uintptr_t GM_GetBurns = 0xC411B0;
	constexpr uintptr_t GM_GetBurnsElectric = 0xC41210;
	constexpr uintptr_t GM_GetBloodLoss = 0xC41270;
	constexpr uintptr_t GM_GetBodyHarvestManager = 0xC412D0;
	constexpr uintptr_t GM_GetBreath = 0xC41330;
	constexpr uintptr_t GM_GetBrokenRib = 0xC413F0;
	constexpr uintptr_t GM_GetCabinFever = 0xC41450;
	constexpr uintptr_t GM_GetCheatDeathAffliction = 0xC414B0;
	constexpr uintptr_t GM_GetDysentery = 0xC41820;
	constexpr uintptr_t GM_GetEmergencyStim = 0xC418E0;
	constexpr uintptr_t GM_GetEncumber = 0xC41940;
	constexpr uintptr_t GM_GetEnergyBoost = 0xC419A0;
	constexpr uintptr_t GM_GetExperienceModeManager = 0xC41A00;
	constexpr uintptr_t GM_GetFireManager = 0xC41AC0;
	constexpr uintptr_t GM_GetFoodPoisoning = 0xC41B20;
	constexpr uintptr_t GM_GetFootStepSounds = 0xC41B80;
	constexpr uintptr_t GM_GetFrostbite = 0xC41C40;
	constexpr uintptr_t GM_GetSuffocating = 0xC41CA0;
	constexpr uintptr_t GM_GetHeatSourceManager = 0xC41D00;
	constexpr uintptr_t GM_GetHeadache = 0xC41D60;
	constexpr uintptr_t GM_GetHypothermia = 0xC41E20;
	constexpr uintptr_t GM_GetInfection = 0xC41E80;
	constexpr uintptr_t GM_GetInfectionRisk = 0xC41EE0;
	constexpr uintptr_t GM_GetIntestinalParasites = 0xC41F40;
	constexpr uintptr_t GM_GetFallDamage = 0xC41FA0;
	constexpr uintptr_t GM_GetFlyOver = 0xC425A0;
	constexpr uintptr_t GM_GetInventory = 0xC427E0;
	constexpr uintptr_t GM_GetLog = 0xC42840;
	constexpr uintptr_t GM_GetPlayerClimbRope = 0xC42BC0;
	constexpr uintptr_t GM_GetPlayerGameStats = 0xC42C20;
	constexpr uintptr_t GM_GetPlayerKnowledge = 0xC42D40;
	constexpr uintptr_t GM_GetPlayerAnimation = 0xC42DA0;
	constexpr uintptr_t GM_GetPlayerMovement = 0xC42E60;
	constexpr uintptr_t GM_GetPlayerSkills = 0xC42EC0;
	constexpr uintptr_t GM_GetPlayerStruggle = 0xC42F20;
	constexpr uintptr_t GM_GetPlayerStunned = 0xC42F80;
	constexpr uintptr_t GM_GetPlayerSwing = 0xC42FE0;
	constexpr uintptr_t GM_GetPlayerVoice = 0xC43040;
	constexpr uintptr_t GM_GetRest = 0xC43220;
	constexpr uintptr_t GM_GetSkillArchery = 0xC433A0;
	constexpr uintptr_t GM_GetSkillCarcassHarvesting = 0xC43410;
	constexpr uintptr_t GM_GetSkillClothingRepair = 0xC43480;
	constexpr uintptr_t GM_GetSkillCooking = 0xC434F0;
	constexpr uintptr_t GM_GetSkillFireStarting = 0xC43560;
	constexpr uintptr_t GM_GetSkillIceFishing = 0xC435D0;
	constexpr uintptr_t GM_GetSkillRifle = 0xC43640;
	constexpr uintptr_t GM_GetSkillRevolver = 0xC436B0;
	constexpr uintptr_t GM_GetSkillGunsmithing = 0xC43720;
	constexpr uintptr_t GM_GetSkillsManager = 0xC437F0;
	constexpr uintptr_t GM_GetSprainedAnkle = 0xC439D0;
	constexpr uintptr_t GM_GetSprainedWrist = 0xC43A30;
	constexpr uintptr_t GM_GetSprainPain = 0xC43A90;
	constexpr uintptr_t GM_GetSprains = 0xC43AF0;
	constexpr uintptr_t GM_GetAnxiety = 0xC43BB0;
	constexpr uintptr_t GM_GetFear = 0xC43C10;
	constexpr uintptr_t GM_GetToxicFog = 0xC43C70;
	constexpr uintptr_t GM_GetStatsManager = 0xC43D30;
	constexpr uintptr_t GM_GetTimeOfDay = 0xC43F10;
	constexpr uintptr_t GM_GetWeather = 0xC440F0;
	constexpr uintptr_t GM_GetWeatherTransition = 0xC44150;
	constexpr uintptr_t GM_GetWellFed = 0xC441B0;
	constexpr uintptr_t GM_GetWillpower = 0xC44210;
	constexpr uintptr_t GM_GetWind = 0xC44270;
	constexpr uintptr_t GM_GetSprainProtection = 0xC44570;
	constexpr uintptr_t GM_GetInsomnia = 0xC44930;
	constexpr uintptr_t GM_GetChemicalPoisoning = 0xC44A50;
	constexpr uintptr_t GM_GetScurvy = 0xC44AB0;

	// ---- game methods ----
	constexpr uintptr_t PlayerManager_AddItemCONSOLE = 0xCE0C50;
	constexpr uintptr_t PlayerManager_TeleportPlayer = 0xCBD540;
	constexpr uintptr_t GearItem_SetNormalizedHP = 0x8434F0;
	constexpr uintptr_t GearItem_GetNormalizedCondition = 0x847BE0;
	constexpr uintptr_t GearItem_SetHaltDecay = 0x848B70;
	constexpr uintptr_t GearItem_SetDecayScale = 0x84C550;
	constexpr uintptr_t Inventory_SetSuppressScentIndicator = 0xDB7E30;
	constexpr uintptr_t Skill_SetPoints = 0xE776A0;
	constexpr uintptr_t ConsoleManager_AddAllGear = 0xBADFF0;
	constexpr uintptr_t ConsoleManager_BuffsAddAll = 0xBB19B0;
	constexpr uintptr_t ConsoleManager_ForceGearWeight = 0xBBC420;
	constexpr uintptr_t ConsoleManager_ResetForcedGearWeight = 0xBBC650;
	constexpr uintptr_t ConsoleManager_SpawnBear = 0xBCC460;
	constexpr uintptr_t ConsoleManager_SpawnDoe = 0xBCC6D0;
	constexpr uintptr_t ConsoleManager_SpawnMoose = 0xBCC7A0;
	constexpr uintptr_t ConsoleManager_SpawnRabbit = 0xBCC870;
	constexpr uintptr_t ConsoleManager_SpawnStag = 0xBCC940;
	constexpr uintptr_t ConsoleManager_SpawnPtarmigan = 0xBCCA10;
	constexpr uintptr_t ConsoleManager_SpawnWolf = 0xBCCCB0;
	constexpr uintptr_t ConsoleManager_SpawnWolfStarving = 0xBCCD80;
	constexpr uintptr_t ConsoleManager_SpawnGreyWolf = 0xBCCE50;
	constexpr uintptr_t ConsoleManager_SpawnCougar = 0xBCCFF0;
	constexpr uintptr_t ConsoleManager_SpawnAuroraWolf = 0xBCC2C0;
	constexpr uintptr_t ConsoleManager_SpawnAuroraBear = 0xBCC390;
	constexpr uintptr_t ConsoleManager_UseBestGearItem = 0xBD0F60;
	constexpr uintptr_t ConsoleManager_DropLitItemInHands = 0xBCFFA0;
	constexpr uintptr_t GameManager_SaveGame = 0xC3C430;
	constexpr uintptr_t GameManager_ForceSaveGame = 0xC3C4A0;
	constexpr uintptr_t WeatherTransition_ActivateStage = 0x747FC0;
	constexpr uintptr_t WeatherTransition_ForceUnmanagedStage = 0x748A60;
	constexpr uintptr_t BlueprintManager_GetInstance = 0x11F9640;
	constexpr uintptr_t BlueprintManager_UnlockSilent = 0x11FAFE0;
}

extern GameManager_GetVpFPSCamera GetVpFPSCamera;
extern vp_FPSCamera_GetCameraComponent GetCameraComponent;
extern Component_get_transform GetTransform;
extern Transform_get_position GetPosition;
extern Transform_get_rotation GetRotation;
extern Component_get_gameObject GetGameObject;
extern GameObject_get_activeInHierarchy IsActive;
extern GameObject_get_transform GetGameObjectTransform;
extern Camera_get_main GetMainCamera;
extern Camera_WorldToScreenPoint WorldToScreen;
extern GearItem_get_DisplayName GearItem_GetName;
extern GameManager_GetPlayerManager GetPlayerManager;
extern GameManager_GetCondition GetCondition;
extern GameManager_GetFatigue GetFatigue;
extern GameManager_GetFreezing GetFreezing;
extern GameManager_GetHunger GetHunger;
extern GameManager_GetThirst GetThirst;
extern vp_FPSCamera_SetAngle SetCameraAngle;
extern BaseAi_GetEyePos GetAiEyePos;

// ---- GameManager component getter pointers (signature: X* Get(void* method)) ----
using GameComponentGetter = void* (*)(void*);

extern GameComponentGetter GM_GetVpFPSPlayer;
extern GameComponentGetter GM_GetUniStorm;
extern GameComponentGetter GM_GetAuroraManager;
extern GameComponentGetter GM_GetBurns;
extern GameComponentGetter GM_GetBurnsElectric;
extern GameComponentGetter GM_GetBloodLoss;
extern GameComponentGetter GM_GetBodyHarvestManager;
extern GameComponentGetter GM_GetBreath;
extern GameComponentGetter GM_GetBrokenRib;
extern GameComponentGetter GM_GetCabinFever;
extern GameComponentGetter GM_GetDysentery;
extern GameComponentGetter GM_GetEmergencyStim;
extern GameComponentGetter GM_GetEncumber;
extern GameComponentGetter GM_GetEnergyBoost;
extern GameComponentGetter GM_GetExperienceModeManager;
extern GameComponentGetter GM_GetFireManager;
extern GameComponentGetter GM_GetFoodPoisoning;
extern GameComponentGetter GM_GetFrostbite;
extern GameComponentGetter GM_GetSuffocating;
extern GameComponentGetter GM_GetHeatSourceManager;
extern GameComponentGetter GM_GetHeadache;
extern GameComponentGetter GM_GetHypothermia;
extern GameComponentGetter GM_GetInfection;
extern GameComponentGetter GM_GetInfectionRisk;
extern GameComponentGetter GM_GetIntestinalParasites;
extern GameComponentGetter GM_GetFallDamage;
extern GameComponentGetter GM_GetInventory;
extern GameComponentGetter GM_GetLog;
extern GameComponentGetter GM_GetPlayerClimbRope;
extern GameComponentGetter GM_GetPlayerGameStats;
extern GameComponentGetter GM_GetPlayerKnowledge;
extern GameComponentGetter GM_GetPlayerMovement;
extern GameComponentGetter GM_GetPlayerSkills;
extern GameComponentGetter GM_GetPlayerStruggle;
extern GameComponentGetter GM_GetPlayerStunned;
extern GameComponentGetter GM_GetPlayerSwing;
extern GameComponentGetter GM_GetPlayerVoice;
extern GameComponentGetter GM_GetRest;
extern GameComponentGetter GM_GetSkillArchery;
extern GameComponentGetter GM_GetSkillCarcassHarvesting;
extern GameComponentGetter GM_GetSkillClothingRepair;
extern GameComponentGetter GM_GetSkillCooking;
extern GameComponentGetter GM_GetSkillFireStarting;
extern GameComponentGetter GM_GetSkillIceFishing;
extern GameComponentGetter GM_GetSkillRifle;
extern GameComponentGetter GM_GetSkillRevolver;
extern GameComponentGetter GM_GetSkillGunsmithing;
extern GameComponentGetter GM_GetSkillsManager;
extern GameComponentGetter GM_GetSprainedAnkle;
extern GameComponentGetter GM_GetSprainedWrist;
extern GameComponentGetter GM_GetSprainPain;
extern GameComponentGetter GM_GetSprains;
extern GameComponentGetter GM_GetAnxiety;
extern GameComponentGetter GM_GetFear;
extern GameComponentGetter GM_GetToxicFog;
extern GameComponentGetter GM_GetStatsManager;
extern GameComponentGetter GM_GetTimeOfDay;
extern GameComponentGetter GM_GetWeather;
extern GameComponentGetter GM_GetWeatherTransition;
extern GameComponentGetter GM_GetWellFed;
extern GameComponentGetter GM_GetWillpower;
extern GameComponentGetter GM_GetWind;
extern GameComponentGetter GM_GetSprainProtection;
extern GameComponentGetter GM_GetInsomnia;
extern GameComponentGetter GM_GetChemicalPoisoning;
extern GameComponentGetter GM_GetScurvy;

// ---- game method pointers ----
using PlayerManager_AddItemCONSOLE_fn = void* (*)(void*, System_String*, int, float, void*);
using PlayerManager_TeleportPlayer_fn = void (*)(void*, Vector3, Quaternion, void*);
using GearItem_SetNormalizedHP_fn = void (*)(void*, float, bool, void*);
using GearItem_GetNormalizedCondition_fn = float (*)(void*);
using GearItem_SetHaltDecay_fn = void (*)(void*, bool, void*);
using GearItem_SetDecayScale_fn = void (*)(void*, float, void*);
using Inventory_SetSuppressScentIndicator_fn = void (*)(void*, bool, void*);
using Skill_SetPoints_fn = void (*)(void*, int, int, void*);
using ConsoleCommand_fn = void (*)(void*);

extern PlayerManager_AddItemCONSOLE_fn PlayerManager_AddItemCONSOLE;
extern PlayerManager_TeleportPlayer_fn PlayerManager_TeleportPlayer;
extern GearItem_SetNormalizedHP_fn GearItem_SetNormalizedHP;
extern GearItem_GetNormalizedCondition_fn GearItem_GetNormalizedCondition;
extern GearItem_SetHaltDecay_fn GearItem_SetHaltDecay;
extern GearItem_SetDecayScale_fn GearItem_SetDecayScale;
extern Inventory_SetSuppressScentIndicator_fn Inventory_SetSuppressScent;
extern Skill_SetPoints_fn Skill_SetPoints;
extern ConsoleCommand_fn Console_AddAllGear;
extern ConsoleCommand_fn Console_BuffsAddAll;
extern ConsoleCommand_fn Console_ForceGearWeight;
extern ConsoleCommand_fn Console_ResetForcedGearWeight;
extern ConsoleCommand_fn Console_SpawnBear;
extern ConsoleCommand_fn Console_SpawnDoe;
extern ConsoleCommand_fn Console_SpawnMoose;
extern ConsoleCommand_fn Console_SpawnRabbit;
extern ConsoleCommand_fn Console_SpawnStag;
extern ConsoleCommand_fn Console_SpawnPtarmigan;
extern ConsoleCommand_fn Console_SpawnWolf;
extern ConsoleCommand_fn Console_SpawnWolfStarving;
extern ConsoleCommand_fn Console_SpawnGreyWolf;
extern ConsoleCommand_fn Console_SpawnCougar;
extern ConsoleCommand_fn Console_SpawnAuroraWolf;
extern ConsoleCommand_fn Console_SpawnAuroraBear;
extern ConsoleCommand_fn Console_UseBestGearItem;
extern ConsoleCommand_fn Console_DropLitItemInHands;
extern ConsoleCommand_fn GameManager_SaveGame;
extern ConsoleCommand_fn GameManager_ForceSaveGame;

bool ResolveGameFunctions();

using WeatherTransition_SetStage_fn = void (*)(void*, int, void*);
using WeatherTransition_ForceStage_fn = void (*)(void*, int, float, void*);
extern WeatherTransition_SetStage_fn WeatherTransition_SetStage;
extern WeatherTransition_ForceStage_fn WeatherTransition_ForceStage;

using ObjectGetter_fn = void* (*)(void*);
using UnlockBlueprint_fn = void (*)(void*, void*, void*);
extern ObjectGetter_fn BlueprintManager_GetInstance;
extern UnlockBlueprint_fn BlueprintManager_UnlockSilent;

using RenderBool_fn = void (*)(bool, void*);
using RenderFloat_fn = void (*)(float, void*);
extern RenderBool_fn RenderSettings_SetFog;
extern RenderFloat_fn RenderSettings_SetAmbientIntensity;
extern RenderFloat_fn RenderSettings_SetFogDensity;
extern RenderFloat_fn RenderSettings_SetFogStartDistance;
extern RenderFloat_fn RenderSettings_SetFogEndDistance;

// ---- il2cpp runtime API ----

using Il2CppStringNew = System_String* (*)(const char*);
extern Il2CppStringNew il2cpp_string_new;

System_String* MakeString(const char* utf8);

// ---- typed field/memory helpers ----

inline float ReadFloat(uintptr_t obj, uintptr_t offset)
{
	return *reinterpret_cast<float*>(obj + offset);
}

inline void WriteFloat(uintptr_t obj, uintptr_t offset, float value)
{
	*reinterpret_cast<float*>(obj + offset) = value;
}

inline void WriteBool(uintptr_t obj, uintptr_t offset, bool value)
{
	*reinterpret_cast<bool*>(obj + offset) = value;
}

inline int ReadInt(uintptr_t obj, uintptr_t offset)
{
	return *reinterpret_cast<int*>(obj + offset);
}

inline void WriteInt(uintptr_t obj, uintptr_t offset, int value)
{
	*reinterpret_cast<int*>(obj + offset) = value;
}

inline void WriteInt64(uintptr_t obj, uintptr_t offset, long long value)
{
	*reinterpret_cast<long long*>(obj + offset) = value;
}

inline bool ReadBool(uintptr_t obj, uintptr_t offset)
{
	return *reinterpret_cast<bool*>(obj + offset);
}

inline void* ReadPtr(uintptr_t obj, uintptr_t offset)
{
	return *reinterpret_cast<void**>(obj + offset);
}

// System.Collections.Generic.List<T> layout in il2cpp:
//   klass(0x00) monitor(0x08) _items(0x10) _size(0x18) _version(0x1C)
// Setting _size to 0 empties the list (elements remain but are unreachable).
inline void ClearManagedList(void* list)
{
	if (!list) return;
	WriteInt(reinterpret_cast<uintptr_t>(list), 0x18, 0);
}

inline int ManagedListCount(void* list)
{
	if (!list) return 0;
	return ReadInt(reinterpret_cast<uintptr_t>(list), 0x18);
}

inline void* ManagedListItems(void* list)
{
	if (!list) return 0;
	return ReadPtr(reinterpret_cast<uintptr_t>(list), 0x10);
}

// Il2CppArray layout: klass(0x00) monitor(0x08) bounds(0x10: length,lower)
// then elements at 0x20.
inline void* ManagedArrayAt(void* array, int index)
{
	if (!array || index < 0) return nullptr;
	return ReadPtr(reinterpret_cast<uintptr_t>(array), 0x20 + static_cast<uintptr_t>(index) * sizeof(void*));
}

// ---- BaseAi accessors ----

inline float AiHP(void* ai) { return ReadFloat(reinterpret_cast<uintptr_t>(ai), Offsets::AiCurrentHP); }
inline float AiMaxHP(void* ai) { return ReadFloat(reinterpret_cast<uintptr_t>(ai), Offsets::AiMaxHP); }
inline int AiMode(void* ai) { return ReadInt(reinterpret_cast<uintptr_t>(ai), Offsets::AiMode); }
inline int AiSubType(void* ai) { return ReadInt(reinterpret_cast<uintptr_t>(ai), Offsets::AiSubType); }
inline System_String* AiDisplayName(void* ai) { return *reinterpret_cast<System_String**>(reinterpret_cast<uintptr_t>(ai) + Offsets::AiDisplayName); }

inline float Vector3_Distance(const Vector3& a, const Vector3& b)
{
	float dx = a.x - b.x, dy = a.y - b.y, dz = a.z - b.z;
	return std::sqrtf(dx * dx + dy * dy + dz * dz);
}

inline Vector3 QuaternionForward(const Quaternion& q)
{
	return Vector3{
		2.0f * (q.x * q.z + q.w * q.y),
		2.0f * (q.y * q.z - q.w * q.x),
		1.0f - 2.0f * (q.x * q.x + q.y * q.y)
	};
}

const char* AiSubTypeName(int subType);
bool AiModeIsHostile(int mode);

Vector3 GetWorldPosition(void* component);
Vector3 GetGearItemWorldPosition(void* gearItem);

// Convenience wrappers that null-check the getter pointer itself.
inline void* Component(GameComponentGetter getter)
{
	return (g_gameReady && getter) ? getter(nullptr) : nullptr;
}

// ---- static field helpers ----
// Il2CppObject::klass sits at offset 0; Il2CppClass::static_fields at 0xB8.
inline void* StaticFields(void* obj)
{
	if (!obj) return nullptr;
	void* klass = ReadPtr(reinterpret_cast<uintptr_t>(obj), 0);
	if (!klass) return nullptr;
	return ReadPtr(reinterpret_cast<uintptr_t>(klass), 0xB8);
}

inline void WriteStaticBool(void* obj, uintptr_t offset, bool value)
{
	if (void* sf = StaticFields(obj)) WriteBool(reinterpret_cast<uintptr_t>(sf), offset, value);
}

inline void WriteStaticFloat(void* obj, uintptr_t offset, float value)
{
	if (void* sf = StaticFields(obj)) WriteFloat(reinterpret_cast<uintptr_t>(sf), offset, value);
}
