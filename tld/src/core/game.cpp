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

	GetVpFPSCamera = reinterpret_cast<GameManager_GetVpFPSCamera>(base + Rva::GetVpFPSCamera);
	GetCameraComponent = reinterpret_cast<vp_FPSCamera_GetCameraComponent>(base + Rva::GetCameraComponent);
	GetTransform = reinterpret_cast<Component_get_transform>(base + Rva::Component_get_transform);
	GetPosition = reinterpret_cast<Transform_get_position>(base + Rva::Transform_get_position);
	GetRotation = reinterpret_cast<Transform_get_rotation>(base + Rva::Transform_get_rotation);
	GetGameObject = reinterpret_cast<Component_get_gameObject>(base + Rva::Component_get_gameObject);
	IsActive = reinterpret_cast<GameObject_get_activeInHierarchy>(base + Rva::GameObject_get_activeInHierarchy);
	GetGameObjectTransform = reinterpret_cast<GameObject_get_transform>(base + Rva::GameObject_get_transform);
	GetMainCamera = reinterpret_cast<Camera_get_main>(base + Rva::Camera_get_main);
	WorldToScreen = reinterpret_cast<Camera_WorldToScreenPoint>(base + Rva::Camera_WorldToScreenPoint);
	GearItem_GetName = reinterpret_cast<GearItem_get_DisplayName>(base + Rva::GearItem_get_DisplayName);
	GetPlayerManager = reinterpret_cast<GameManager_GetPlayerManager>(base + Rva::GetPlayerManagerComponent);
	GetCondition = reinterpret_cast<GameManager_GetCondition>(base + Rva::GetConditionComponent);
	GetFatigue = reinterpret_cast<GameManager_GetFatigue>(base + Rva::GetFatigueComponent);
	GetFreezing = reinterpret_cast<GameManager_GetFreezing>(base + Rva::GetFreezingComponent);
	GetHunger = reinterpret_cast<GameManager_GetHunger>(base + Rva::GetHungerComponent);
	GetThirst = reinterpret_cast<GameManager_GetThirst>(base + Rva::GetThirstComponent);
	SetCameraAngle = reinterpret_cast<vp_FPSCamera_SetAngle>(base + Rva::SetAngle);
	GetAiEyePos = reinterpret_cast<BaseAi_GetEyePos>(base + Rva::BaseAi_GetEyePos);

	g_gameReady = GetVpFPSCamera && GetCameraComponent && GetTransform && GetPosition &&
		GetRotation && GetGameObject && IsActive && GetGameObjectTransform &&
		GetMainCamera && WorldToScreen && GearItem_GetName &&
		GetPlayerManager && GetCondition && GetFatigue && GetFreezing &&
		GetHunger && GetThirst && SetCameraAngle && GetAiEyePos;

	if (!g_gameReady)
	{
		std::cout << "[ERROR] some function pointers are null - check RVA table against a fresh dump\n";
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
