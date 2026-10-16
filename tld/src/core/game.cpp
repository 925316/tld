#include "pch.h"
#include "core/game.h"

uintptr_t g_gameAssemblyBase = 0;
bool g_gameReady = false;

GameManager_GetVpFPSCamera GetVpFPSCamera = nullptr;
vp_FPSCamera_GetCameraComponent GetCameraComponent = nullptr;
Component_get_transform GetTransform = nullptr;
Transform_get_position GetPosition = nullptr;
Transform_get_rotation GetRotation = nullptr;
Component_get_gameObject GetGameObject = nullptr;
GameObject_get_activeInHierarchy IsActive = nullptr;
GameObject_get_transform GetGameObjectTransform = nullptr;
Camera_get_main GetMainCamera = nullptr;
Camera_WorldToScreenPoint WorldToScreen = nullptr;
GearItem_get_DisplayName GearItem_GetName = nullptr;
GameManager_GetPlayerManager GetPlayerManager = nullptr;
GameManager_GetCondition GetCondition = nullptr;
GameManager_GetFatigue GetFatigue = nullptr;
GameManager_GetFreezing GetFreezing = nullptr;
GameManager_GetHunger GetHunger = nullptr;
GameManager_GetThirst GetThirst = nullptr;
vp_FPSCamera_SetAngle SetCameraAngle = nullptr;
BaseAi_GetEyePos GetAiEyePos = nullptr;

// GameManager component getters
GameComponentGetter GM_GetVpFPSPlayer = nullptr;
GameComponentGetter GM_GetUniStorm = nullptr;
GameComponentGetter GM_GetAuroraManager = nullptr;
GameComponentGetter GM_GetBurns = nullptr;
GameComponentGetter GM_GetBurnsElectric = nullptr;
GameComponentGetter GM_GetBloodLoss = nullptr;
GameComponentGetter GM_GetBodyHarvestManager = nullptr;
GameComponentGetter GM_GetBreath = nullptr;
GameComponentGetter GM_GetBrokenRib = nullptr;
GameComponentGetter GM_GetCabinFever = nullptr;
GameComponentGetter GM_GetDysentery = nullptr;
GameComponentGetter GM_GetEmergencyStim = nullptr;
GameComponentGetter GM_GetEncumber = nullptr;
GameComponentGetter GM_GetEnergyBoost = nullptr;
GameComponentGetter GM_GetExperienceModeManager = nullptr;
GameComponentGetter GM_GetFireManager = nullptr;
GameComponentGetter GM_GetFoodPoisoning = nullptr;
GameComponentGetter GM_GetFrostbite = nullptr;
GameComponentGetter GM_GetSuffocating = nullptr;
GameComponentGetter GM_GetHeatSourceManager = nullptr;
GameComponentGetter GM_GetHeadache = nullptr;
GameComponentGetter GM_GetHypothermia = nullptr;
GameComponentGetter GM_GetInfection = nullptr;
GameComponentGetter GM_GetInfectionRisk = nullptr;
GameComponentGetter GM_GetIntestinalParasites = nullptr;
GameComponentGetter GM_GetFallDamage = nullptr;
GameComponentGetter GM_GetInventory = nullptr;
GameComponentGetter GM_GetLog = nullptr;
GameComponentGetter GM_GetPlayerClimbRope = nullptr;
GameComponentGetter GM_GetPlayerGameStats = nullptr;
GameComponentGetter GM_GetPlayerKnowledge = nullptr;
GameComponentGetter GM_GetPlayerMovement = nullptr;
GameComponentGetter GM_GetPlayerSkills = nullptr;
GameComponentGetter GM_GetPlayerStruggle = nullptr;
GameComponentGetter GM_GetPlayerStunned = nullptr;
GameComponentGetter GM_GetPlayerSwing = nullptr;
GameComponentGetter GM_GetPlayerVoice = nullptr;
GameComponentGetter GM_GetRest = nullptr;
GameComponentGetter GM_GetSkillArchery = nullptr;
GameComponentGetter GM_GetSkillCarcassHarvesting = nullptr;
GameComponentGetter GM_GetSkillClothingRepair = nullptr;
GameComponentGetter GM_GetSkillCooking = nullptr;
GameComponentGetter GM_GetSkillFireStarting = nullptr;
GameComponentGetter GM_GetSkillIceFishing = nullptr;
GameComponentGetter GM_GetSkillRifle = nullptr;
GameComponentGetter GM_GetSkillRevolver = nullptr;
GameComponentGetter GM_GetSkillGunsmithing = nullptr;
GameComponentGetter GM_GetSkillsManager = nullptr;
GameComponentGetter GM_GetSprainedAnkle = nullptr;
GameComponentGetter GM_GetSprainedWrist = nullptr;
GameComponentGetter GM_GetSprainPain = nullptr;
GameComponentGetter GM_GetSprains = nullptr;
GameComponentGetter GM_GetAnxiety = nullptr;
GameComponentGetter GM_GetFear = nullptr;
GameComponentGetter GM_GetToxicFog = nullptr;
GameComponentGetter GM_GetStatsManager = nullptr;
GameComponentGetter GM_GetTimeOfDay = nullptr;
GameComponentGetter GM_GetWeather = nullptr;
GameComponentGetter GM_GetWeatherTransition = nullptr;
GameComponentGetter GM_GetWellFed = nullptr;
GameComponentGetter GM_GetWillpower = nullptr;
GameComponentGetter GM_GetWind = nullptr;
GameComponentGetter GM_GetSprainProtection = nullptr;
GameComponentGetter GM_GetInsomnia = nullptr;
GameComponentGetter GM_GetChemicalPoisoning = nullptr;

// game methods
PlayerManager_AddItemCONSOLE_fn PlayerManager_AddItemCONSOLE = nullptr;
PlayerManager_TeleportPlayer_fn PlayerManager_TeleportPlayer = nullptr;
GearItem_SetNormalizedHP_fn GearItem_SetNormalizedHP = nullptr;
GearItem_GetNormalizedCondition_fn GearItem_GetNormalizedCondition = nullptr;
GearItem_SetHaltDecay_fn GearItem_SetHaltDecay = nullptr;
GearItem_SetDecayScale_fn GearItem_SetDecayScale = nullptr;
Inventory_SetSuppressScentIndicator_fn Inventory_SetSuppressScent = nullptr;
Skill_SetPoints_fn Skill_SetPoints = nullptr;
ConsoleCommand_fn Console_AddAllGear = nullptr;
ConsoleCommand_fn Console_BuffsAddAll = nullptr;
ConsoleCommand_fn Console_ForceGearWeight = nullptr;
ConsoleCommand_fn Console_ResetForcedGearWeight = nullptr;
ConsoleCommand_fn Console_SpawnBear = nullptr;
ConsoleCommand_fn Console_SpawnDoe = nullptr;
ConsoleCommand_fn Console_SpawnMoose = nullptr;
ConsoleCommand_fn Console_SpawnRabbit = nullptr;
ConsoleCommand_fn Console_SpawnStag = nullptr;
ConsoleCommand_fn Console_SpawnPtarmigan = nullptr;
ConsoleCommand_fn Console_SpawnWolf = nullptr;
ConsoleCommand_fn Console_SpawnWolfStarving = nullptr;
ConsoleCommand_fn Console_SpawnGreyWolf = nullptr;
ConsoleCommand_fn Console_SpawnCougar = nullptr;
ConsoleCommand_fn Console_SpawnAuroraWolf = nullptr;
ConsoleCommand_fn Console_SpawnAuroraBear = nullptr;
ConsoleCommand_fn Console_UseBestGearItem = nullptr;
ConsoleCommand_fn Console_DropLitItemInHands = nullptr;
ConsoleCommand_fn GameManager_SaveGame = nullptr;
ConsoleCommand_fn GameManager_ForceSaveGame = nullptr;

WeatherTransition_SetStage_fn WeatherTransition_SetStage = nullptr;
WeatherTransition_ForceStage_fn WeatherTransition_ForceStage = nullptr;
ObjectGetter_fn BlueprintManager_GetInstance = nullptr;
UnlockBlueprint_fn BlueprintManager_UnlockSilent = nullptr;

Il2CppStringNew il2cpp_string_new = nullptr;

System_String* MakeString(const char* utf8)
{
	if (!il2cpp_string_new || !utf8) return nullptr;
	return il2cpp_string_new(utf8);
}

template<typename T>
static T Resolve(uintptr_t base, uintptr_t rva)
{
	return reinterpret_cast<T>(base + rva);
}

bool ResolveGameFunctions()
{
	HMODULE gameAssembly = GetModuleHandleA("GameAssembly.dll");
	if (!gameAssembly)
	{
		std::cout << "[ERROR] GameAssembly.dll not loaded\n";
		return false;
	}

	g_gameAssemblyBase = reinterpret_cast<uintptr_t>(gameAssembly);
	uintptr_t base = g_gameAssemblyBase;
	std::cout << "[INFO] GameAssembly.dll base: 0x" << std::hex << base << std::dec << '\n';

	GetVpFPSCamera = Resolve<GameManager_GetVpFPSCamera>(base, Rva::GetVpFPSCamera);
	GetCameraComponent = Resolve<vp_FPSCamera_GetCameraComponent>(base, Rva::GetCameraComponent);
	GetTransform = Resolve<Component_get_transform>(base, Rva::Component_get_transform);
	GetPosition = Resolve<Transform_get_position>(base, Rva::Transform_get_position);
	GetRotation = Resolve<Transform_get_rotation>(base, Rva::Transform_get_rotation);
	GetGameObject = Resolve<Component_get_gameObject>(base, Rva::Component_get_gameObject);
	IsActive = Resolve<GameObject_get_activeInHierarchy>(base, Rva::GameObject_get_activeInHierarchy);
	GetGameObjectTransform = Resolve<GameObject_get_transform>(base, Rva::GameObject_get_transform);
	GetMainCamera = Resolve<Camera_get_main>(base, Rva::Camera_get_main);
	WorldToScreen = Resolve<Camera_WorldToScreenPoint>(base, Rva::Camera_WorldToScreenPoint);
	GearItem_GetName = Resolve<GearItem_get_DisplayName>(base, Rva::GearItem_get_DisplayName);
	GetPlayerManager = Resolve<GameManager_GetPlayerManager>(base, Rva::GetPlayerManagerComponent);
	GetCondition = Resolve<GameManager_GetCondition>(base, Rva::GetConditionComponent);
	GetFatigue = Resolve<GameManager_GetFatigue>(base, Rva::GetFatigueComponent);
	GetFreezing = Resolve<GameManager_GetFreezing>(base, Rva::GetFreezingComponent);
	GetHunger = Resolve<GameManager_GetHunger>(base, Rva::GetHungerComponent);
	GetThirst = Resolve<GameManager_GetThirst>(base, Rva::GetThirstComponent);
	SetCameraAngle = Resolve<vp_FPSCamera_SetAngle>(base, Rva::SetAngle);
	GetAiEyePos = Resolve<BaseAi_GetEyePos>(base, Rva::BaseAi_GetEyePos);

	// component getters
	GM_GetUniStorm = Resolve<GameComponentGetter>(base, Rva::GM_GetUniStorm);
	GM_GetBurns = Resolve<GameComponentGetter>(base, Rva::GM_GetBurns);
	GM_GetBurnsElectric = Resolve<GameComponentGetter>(base, Rva::GM_GetBurnsElectric);
	GM_GetBloodLoss = Resolve<GameComponentGetter>(base, Rva::GM_GetBloodLoss);
	GM_GetBodyHarvestManager = Resolve<GameComponentGetter>(base, Rva::GM_GetBodyHarvestManager);
	GM_GetBreath = Resolve<GameComponentGetter>(base, Rva::GM_GetBreath);
	GM_GetBrokenRib = Resolve<GameComponentGetter>(base, Rva::GM_GetBrokenRib);
	GM_GetCabinFever = Resolve<GameComponentGetter>(base, Rva::GM_GetCabinFever);
	GM_GetDysentery = Resolve<GameComponentGetter>(base, Rva::GM_GetDysentery);
	GM_GetEmergencyStim = Resolve<GameComponentGetter>(base, Rva::GM_GetEmergencyStim);
	GM_GetEncumber = Resolve<GameComponentGetter>(base, Rva::GM_GetEncumber);
	GM_GetEnergyBoost = Resolve<GameComponentGetter>(base, Rva::GM_GetEnergyBoost);
	GM_GetExperienceModeManager = Resolve<GameComponentGetter>(base, Rva::GM_GetExperienceModeManager);
	GM_GetFireManager = Resolve<GameComponentGetter>(base, Rva::GM_GetFireManager);
	GM_GetFoodPoisoning = Resolve<GameComponentGetter>(base, Rva::GM_GetFoodPoisoning);
	GM_GetFrostbite = Resolve<GameComponentGetter>(base, Rva::GM_GetFrostbite);
	GM_GetSuffocating = Resolve<GameComponentGetter>(base, Rva::GM_GetSuffocating);
	GM_GetHeatSourceManager = Resolve<GameComponentGetter>(base, Rva::GM_GetHeatSourceManager);
	GM_GetHeadache = Resolve<GameComponentGetter>(base, Rva::GM_GetHeadache);
	GM_GetHypothermia = Resolve<GameComponentGetter>(base, Rva::GM_GetHypothermia);
	GM_GetInfection = Resolve<GameComponentGetter>(base, Rva::GM_GetInfection);
	GM_GetInfectionRisk = Resolve<GameComponentGetter>(base, Rva::GM_GetInfectionRisk);
	GM_GetIntestinalParasites = Resolve<GameComponentGetter>(base, Rva::GM_GetIntestinalParasites);
	GM_GetFallDamage = Resolve<GameComponentGetter>(base, Rva::GM_GetFallDamage);
	GM_GetInventory = Resolve<GameComponentGetter>(base, Rva::GM_GetInventory);
	GM_GetLog = Resolve<GameComponentGetter>(base, Rva::GM_GetLog);
	GM_GetPlayerClimbRope = Resolve<GameComponentGetter>(base, Rva::GM_GetPlayerClimbRope);
	GM_GetPlayerGameStats = Resolve<GameComponentGetter>(base, Rva::GM_GetPlayerGameStats);
	GM_GetPlayerKnowledge = Resolve<GameComponentGetter>(base, Rva::GM_GetPlayerKnowledge);
	GM_GetPlayerMovement = Resolve<GameComponentGetter>(base, Rva::GM_GetPlayerMovement);
	GM_GetPlayerSkills = Resolve<GameComponentGetter>(base, Rva::GM_GetPlayerSkills);
	GM_GetPlayerStruggle = Resolve<GameComponentGetter>(base, Rva::GM_GetPlayerStruggle);
	GM_GetPlayerStunned = Resolve<GameComponentGetter>(base, Rva::GM_GetPlayerStunned);
	GM_GetPlayerSwing = Resolve<GameComponentGetter>(base, Rva::GM_GetPlayerSwing);
	GM_GetPlayerVoice = Resolve<GameComponentGetter>(base, Rva::GM_GetPlayerVoice);
	GM_GetRest = Resolve<GameComponentGetter>(base, Rva::GM_GetRest);
	GM_GetSkillArchery = Resolve<GameComponentGetter>(base, Rva::GM_GetSkillArchery);
	GM_GetSkillCarcassHarvesting = Resolve<GameComponentGetter>(base, Rva::GM_GetSkillCarcassHarvesting);
	GM_GetSkillClothingRepair = Resolve<GameComponentGetter>(base, Rva::GM_GetSkillClothingRepair);
	GM_GetSkillCooking = Resolve<GameComponentGetter>(base, Rva::GM_GetSkillCooking);
	GM_GetSkillFireStarting = Resolve<GameComponentGetter>(base, Rva::GM_GetSkillFireStarting);
	GM_GetSkillIceFishing = Resolve<GameComponentGetter>(base, Rva::GM_GetSkillIceFishing);
	GM_GetSkillRifle = Resolve<GameComponentGetter>(base, Rva::GM_GetSkillRifle);
	GM_GetSkillRevolver = Resolve<GameComponentGetter>(base, Rva::GM_GetSkillRevolver);
	GM_GetSkillGunsmithing = Resolve<GameComponentGetter>(base, Rva::GM_GetSkillGunsmithing);
	GM_GetSkillsManager = Resolve<GameComponentGetter>(base, Rva::GM_GetSkillsManager);
	GM_GetSprainedAnkle = Resolve<GameComponentGetter>(base, Rva::GM_GetSprainedAnkle);
	GM_GetSprainedWrist = Resolve<GameComponentGetter>(base, Rva::GM_GetSprainedWrist);
	GM_GetSprainPain = Resolve<GameComponentGetter>(base, Rva::GM_GetSprainPain);
	GM_GetSprains = Resolve<GameComponentGetter>(base, Rva::GM_GetSprains);
	GM_GetAnxiety = Resolve<GameComponentGetter>(base, Rva::GM_GetAnxiety);
	GM_GetFear = Resolve<GameComponentGetter>(base, Rva::GM_GetFear);
	GM_GetToxicFog = Resolve<GameComponentGetter>(base, Rva::GM_GetToxicFog);
	GM_GetStatsManager = Resolve<GameComponentGetter>(base, Rva::GM_GetStatsManager);
	GM_GetTimeOfDay = Resolve<GameComponentGetter>(base, Rva::GM_GetTimeOfDay);
	GM_GetWeather = Resolve<GameComponentGetter>(base, Rva::GM_GetWeather);
	GM_GetWeatherTransition = Resolve<GameComponentGetter>(base, Rva::GM_GetWeatherTransition);
	GM_GetWellFed = Resolve<GameComponentGetter>(base, Rva::GM_GetWellFed);
	GM_GetWillpower = Resolve<GameComponentGetter>(base, Rva::GM_GetWillpower);
	GM_GetWind = Resolve<GameComponentGetter>(base, Rva::GM_GetWind);
	GM_GetSprainProtection = Resolve<GameComponentGetter>(base, Rva::GM_GetSprainProtection);
	GM_GetInsomnia = Resolve<GameComponentGetter>(base, Rva::GM_GetInsomnia);
	GM_GetChemicalPoisoning = Resolve<GameComponentGetter>(base, Rva::GM_GetChemicalPoisoning);

	// game methods
	PlayerManager_AddItemCONSOLE = Resolve<PlayerManager_AddItemCONSOLE_fn>(base, Rva::PlayerManager_AddItemCONSOLE);
	PlayerManager_TeleportPlayer = Resolve<PlayerManager_TeleportPlayer_fn>(base, Rva::PlayerManager_TeleportPlayer);
	GearItem_SetNormalizedHP = Resolve<GearItem_SetNormalizedHP_fn>(base, Rva::GearItem_SetNormalizedHP);
	GearItem_GetNormalizedCondition = Resolve<GearItem_GetNormalizedCondition_fn>(base, Rva::GearItem_GetNormalizedCondition);
	GearItem_SetHaltDecay = Resolve<GearItem_SetHaltDecay_fn>(base, Rva::GearItem_SetHaltDecay);
	GearItem_SetDecayScale = Resolve<GearItem_SetDecayScale_fn>(base, Rva::GearItem_SetDecayScale);
	Inventory_SetSuppressScent = Resolve<Inventory_SetSuppressScentIndicator_fn>(base, Rva::Inventory_SetSuppressScentIndicator);
	Skill_SetPoints = Resolve<Skill_SetPoints_fn>(base, Rva::Skill_SetPoints);
	Console_AddAllGear = Resolve<ConsoleCommand_fn>(base, Rva::ConsoleManager_AddAllGear);
	Console_BuffsAddAll = Resolve<ConsoleCommand_fn>(base, Rva::ConsoleManager_BuffsAddAll);
	Console_ForceGearWeight = Resolve<ConsoleCommand_fn>(base, Rva::ConsoleManager_ForceGearWeight);
	Console_ResetForcedGearWeight = Resolve<ConsoleCommand_fn>(base, Rva::ConsoleManager_ResetForcedGearWeight);
	Console_SpawnBear = Resolve<ConsoleCommand_fn>(base, Rva::ConsoleManager_SpawnBear);
	Console_SpawnDoe = Resolve<ConsoleCommand_fn>(base, Rva::ConsoleManager_SpawnDoe);
	Console_SpawnMoose = Resolve<ConsoleCommand_fn>(base, Rva::ConsoleManager_SpawnMoose);
	Console_SpawnRabbit = Resolve<ConsoleCommand_fn>(base, Rva::ConsoleManager_SpawnRabbit);
	Console_SpawnStag = Resolve<ConsoleCommand_fn>(base, Rva::ConsoleManager_SpawnStag);
	Console_SpawnPtarmigan = Resolve<ConsoleCommand_fn>(base, Rva::ConsoleManager_SpawnPtarmigan);
	Console_SpawnWolf = Resolve<ConsoleCommand_fn>(base, Rva::ConsoleManager_SpawnWolf);
	Console_SpawnWolfStarving = Resolve<ConsoleCommand_fn>(base, Rva::ConsoleManager_SpawnWolfStarving);
	Console_SpawnGreyWolf = Resolve<ConsoleCommand_fn>(base, Rva::ConsoleManager_SpawnGreyWolf);
	Console_SpawnCougar = Resolve<ConsoleCommand_fn>(base, Rva::ConsoleManager_SpawnCougar);
	Console_SpawnAuroraWolf = Resolve<ConsoleCommand_fn>(base, Rva::ConsoleManager_SpawnAuroraWolf);
	Console_SpawnAuroraBear = Resolve<ConsoleCommand_fn>(base, Rva::ConsoleManager_SpawnAuroraBear);
	Console_UseBestGearItem = Resolve<ConsoleCommand_fn>(base, Rva::ConsoleManager_UseBestGearItem);
	Console_DropLitItemInHands = Resolve<ConsoleCommand_fn>(base, Rva::ConsoleManager_DropLitItemInHands);
	GameManager_SaveGame = Resolve<ConsoleCommand_fn>(base, Rva::GameManager_SaveGame);
	GameManager_ForceSaveGame = Resolve<ConsoleCommand_fn>(base, Rva::GameManager_ForceSaveGame);
	GM_GetVpFPSPlayer = Resolve<GameComponentGetter>(base, Rva::GM_GetVpFPSPlayer);
	GM_GetAuroraManager = Resolve<GameComponentGetter>(base, Rva::GM_GetAuroraManager);
	WeatherTransition_SetStage = Resolve<WeatherTransition_SetStage_fn>(base, Rva::WeatherTransition_ActivateStage);
	WeatherTransition_ForceStage = Resolve<WeatherTransition_ForceStage_fn>(base, Rva::WeatherTransition_ForceUnmanagedStage);
	BlueprintManager_GetInstance = Resolve<ObjectGetter_fn>(base, Rva::BlueprintManager_GetInstance);
	BlueprintManager_UnlockSilent = Resolve<UnlockBlueprint_fn>(base, Rva::BlueprintManager_UnlockSilent);

	il2cpp_string_new = reinterpret_cast<Il2CppStringNew>(
		GetProcAddress(gameAssembly, "il2cpp_string_new"));

	g_gameReady = GetVpFPSCamera && GetCameraComponent && GetTransform && GetPosition &&
		GetRotation && GetGameObject && IsActive && GetGameObjectTransform &&
		GetMainCamera && WorldToScreen && GearItem_GetName &&
		GetPlayerManager && GetCondition && GetFatigue && GetFreezing &&
		GetHunger && GetThirst && SetCameraAngle && GetAiEyePos;

	if (!g_gameReady)
	{
		std::cout << "[ERROR] some function pointers are null - check RVA table against a fresh dump\n";
	}
	if (!il2cpp_string_new)
	{
		std::cout << "[ERROR] il2cpp_string_new export not found - item spawning disabled\n";
	}
	return g_gameReady;
}

const char* AiSubTypeName(int subType)
{
	switch (subType)
	{
	case 1: return "Wolf";
	case 2: return "Bear";
	case 3: return "Stag";
	case 4: return "Rabbit";
	case 5: return "Moose";
	case 6: return "Cougar";
	default: return "Ai";
	}
}

bool AiModeIsHostile(int mode)
{
	return mode == 1 || mode == 13 || mode == 14 || mode == 25; // Attack/Stalking/Struggle/PassingAttack
}

Vector3 GetWorldPosition(void* component)
{
	if (!component) return { -9999.0f, -9999.0f, -9999.0f };
	void* transform = GetTransform(component);
	return transform ? GetPosition(transform) : Vector3{ -9999.0f, -9999.0f, -9999.0f };
}

Vector3 GetGearItemWorldPosition(void* gearItem)
{
	if (!gearItem) return { -9999.0f, -9999.0f, -9999.0f };
	void* gameObject = GetGameObject(gearItem);
	if (!gameObject || !IsActive(gameObject)) return { -9999.0f, -9999.0f, -9999.0f };
	void* transform = GetGameObjectTransform(gameObject);
	return transform ? GetPosition(transform) : Vector3{ -9999.0f, -9999.0f, -9999.0f };
}
