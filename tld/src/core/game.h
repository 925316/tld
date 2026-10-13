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
	// vp_FPSCamera
	constexpr uintptr_t CameraInFPS = 0x1F0;
	// PlayerManager
	constexpr uintptr_t GodMode = 0x1C3;
	constexpr uintptr_t SuspendCondition = 0x1F2;
	// Condition
	constexpr uintptr_t ConditionHP = 0x20;
	constexpr uintptr_t ConditionMaxHP = 0x24;
	constexpr uintptr_t NeverDie = 0xD8;
	// Fatigue
	constexpr uintptr_t CurrentFatigue = 0x24;
	constexpr uintptr_t MaxFatigue = 0x28;
	// Freezing
	constexpr uintptr_t CurrentFreezing = 0x28;
	// Hunger
	constexpr uintptr_t CurrentCalories = 0x20;
	constexpr uintptr_t MaxCalories = 0x78;
	// Thirst
	constexpr uintptr_t CurrentThirst = 0x24;
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

bool ResolveGameFunctions();

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
