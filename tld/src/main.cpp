#include "pch.h"

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
using GearItem_get_m_DisplayName = System_String * (*)(void*);
using BaseAiManager_Add = void (*)(void*, void*);
using BaseAiManager_Remove = void (*)(void*, void*);
using GearManager_Add = void (*)(void*, void*);
using GearManager_Remove = void (*)(void*, void*);

using GameManager_GetPlayerManager = void* (*)(void*);
using GameManager_GetCondition = void* (*)(void*);
using GameManager_GetFatigue = void* (*)(void*);
using GameManager_GetFreezing = void* (*)(void*);
using GameManager_GetHunger = void* (*)(void*);
using GameManager_GetThirst = void* (*)(void*);
using vp_FPSCamera_SetAngle = void (*)(void*, float, float, void*);
using BaseAi_GetEyePos = Vector3(*)(void*, void*);

using FireManager_CalculateFireStartSuccess = float (*)(void*, void*, void*, void*, void*);
using PanelRepair_GetChanceSuccess = float (*)(void*, void*);
using Examine_RollForActionSuccess = bool (*)(void*, float, void*);
using IceFishingHole_OnActiveFishingComplete = void (*)(void*, bool, bool, float, void*);

namespace Offsets
{
	constexpr uintptr_t CurrentHP = 0x328;   // BaseAi::m_CurrentHP
	constexpr uintptr_t MaxHP = 0x32C;   // BaseAi::m_MaxHP
	constexpr uintptr_t DisplayName = 0x2F8;   // BaseAi::m_DisplayName
	constexpr uintptr_t CameraInFPS = 0x1F0;   // vp_FPSCamera::m_Camera
	constexpr uintptr_t AiMode = 0x470;   // BaseAi::m_CurrentMode
	constexpr uintptr_t AiSubType = 0x31C;   // BaseAi::m_AiSubType
	constexpr uintptr_t GodMode = 0x1C3;   // PlayerManager::m_God
	constexpr uintptr_t SuspendCondition = 0x1F2;   // PlayerManager::m_SuspendConditionUpdate
	constexpr uintptr_t ConditionHP = 0x20;   // Condition::m_CurrentHP
	constexpr uintptr_t ConditionMaxHP = 0x24;   // Condition::m_MaxHP
	constexpr uintptr_t NeverDie = 0xD8;   // Condition::m_NeverDie
	constexpr uintptr_t CurrentFatigue = 0x24;   // Fatigue::m_CurrentFatigue
	constexpr uintptr_t MaxFatigue = 0x28;   // Fatigue::m_MaxFatigue
	constexpr uintptr_t CurrentFreezing = 0x28;   // Freezing::m_CurrentFreezing
	constexpr uintptr_t CurrentCalories = 0x20;   // Hunger::m_CurrentReserveCalories
	constexpr uintptr_t MaxCalories = 0x78;   // Hunger::m_MaxReserveCalories
	constexpr uintptr_t CurrentThirst = 0x24;   // Thirst::m_CurrentThirst
}

void* g_gameAssemblyBase = nullptr;
bool g_hooksInitialized = false;

GameManager_GetVpFPSCamera   GetVpFPSCamera = nullptr;
vp_FPSCamera_GetCameraComponent GetCameraComponent = nullptr;
Component_get_transform      GetTransform = nullptr;
Transform_get_position       GetPosition = nullptr;
Transform_get_rotation       GetRotation = nullptr;
Component_get_gameObject     GetGameObject = nullptr;
GameObject_get_activeInHierarchy IsActive = nullptr;
GameObject_get_transform      GetGameObjectTransform = nullptr;
Camera_get_main              GetMainCamera = nullptr;
Camera_WorldToScreenPoint     WorldToScreen = nullptr;
GearItem_get_m_DisplayName    GearItem_GetDisplayName = nullptr;

GameManager_GetPlayerManager  GetPlayerManager = nullptr;
GameManager_GetCondition      GetCondition = nullptr;
GameManager_GetFatigue        GetFatigue = nullptr;
GameManager_GetFreezing       GetFreezing = nullptr;
GameManager_GetHunger         GetHunger = nullptr;
GameManager_GetThirst         GetThirst = nullptr;
vp_FPSCamera_SetAngle         SetCameraAngle = nullptr;
BaseAi_GetEyePos              GetAiEyePos = nullptr;

BaseAiManager_Add            oBaseAiManagerAdd = nullptr;
BaseAiManager_Remove         oBaseAiManagerRemove = nullptr;
GearManager_Add              oGearManagerAdd = nullptr;
GearManager_Remove           oGearManagerRemove = nullptr;

FireManager_CalculateFireStartSuccess  oCalculateFireStartSuccess = nullptr;
PanelRepair_GetChanceSuccess      oRepairGetChanceSuccess = nullptr;
Examine_RollForActionSuccess      oExamineRollForActionSuccess = nullptr;
IceFishingHole_OnActiveFishingComplete   oActiveFishingComplete = nullptr;

bool g_godMode = false;
bool g_noFatigue = false;
bool g_noFreezing = false;
bool g_noHunger = false;
bool g_noThirst = false;
bool g_alwaysSucceed = false;   // fire starting / repair / examine / fishing rolls
bool g_espAnimals = false;
bool g_aimbot = false;
float g_aimbotFov = 10.0f;      // degrees off crosshair to acquire
float g_aimbotRange = 200.0f;
float g_aimbotSmoothing = 0.35f; // 1 = snap, lower = smoother

template<typename T>
class ObjectList
{
	std::vector<T> items;
	mutable std::mutex mtx;
public:
	void add(T item)
	{
		std::lock_guard lock(mtx);
		items.push_back(item);
	}

	void remove(T item)
	{
		std::lock_guard lock(mtx);
		auto it = std::find(items.begin(), items.end(), item);
		if (it != items.end())
		{
			std::swap(*it, items.back());
			items.pop_back();
		}
	}

	template<typename F>
	void for_each(F&& func) const
	{
		std::lock_guard lock(mtx);
		for (auto item : items)
			func(item);
	}

	size_t size() const
	{
		std::lock_guard lock(mtx);
		return items.size();
	}
};

ObjectList<void*> g_baseAiList;
ObjectList<void*> g_gearItemList;

bool g_drawEsp = false;
bool g_showBaseAiESP = false;
bool g_showBaseAiHP = true;
bool g_showBaseAiName = true;
bool g_showGearItemESP = false;
float g_espDistance = 250.0f;

struct CameraInfo
{
	Vector3 position{};
	Quaternion rotation{};
	bool valid = false;

	void update();
} g_camera;

inline float GetCurrentHP(void* ai) { return *reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(ai) + Offsets::CurrentHP); }
inline float GetMaxHP(void* ai) { return *reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(ai) + Offsets::MaxHP); }
inline System_String* GetDisplayNameString(void* ai) { return *reinterpret_cast<System_String**>(reinterpret_cast<uintptr_t>(ai) + Offsets::DisplayName); }
inline void* GetCameraFromFPS(void* fpsCamera) { return *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(fpsCamera) + Offsets::CameraInFPS); }

inline float Vector3_Distance(const Vector3& a, const Vector3& b)
{
	float dx = a.x - b.x, dy = a.y - b.y, dz = a.z - b.z;
	return std::sqrtf(dx * dx + dy * dy + dz * dz);
}

inline std::string GetStringFromSystemString(System_String* str)
{
	return str ? str->ToString() : "Unknown";
}

void CameraInfo::update()
{
	if (!g_hooksInitialized || !GetVpFPSCamera)
	{
		valid = false;
		return;
	}

	try
	{
		void* fpsCamera = GetVpFPSCamera(nullptr);
		if (!fpsCamera) { valid = false; return; }

		void* cameraObj = GetCameraFromFPS(fpsCamera);
		if (!cameraObj) { valid = false; return; }

		void* transform = GetTransform(cameraObj);
		if (!transform) { valid = false; return; }

		position = GetPosition(transform);
		rotation = GetRotation(transform);
		valid = true;
	}
	catch (...)
	{
		valid = false;
	}
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

void InitializeUnityPointers()
{
	HMODULE gameAssembly = GetModuleHandleA("GameAssembly.dll");
	if (!gameAssembly)
	{
		std::cout << "[ERROR] GameAssembly.dll not found!\n";
		return;
	}

	g_gameAssemblyBase = gameAssembly;
	uintptr_t base = reinterpret_cast<uintptr_t>(gameAssembly);

	std::cout << "[INFO] GameAssembly.dll base: 0x" << std::hex << base << std::dec << '\n';

	GetVpFPSCamera = reinterpret_cast<GameManager_GetVpFPSCamera>(base + 0xC409E0);
	GetCameraComponent = reinterpret_cast<vp_FPSCamera_GetCameraComponent>(base + 0x54A2C0);
	GetTransform = reinterpret_cast<Component_get_transform>(base + 0x3ADEDB0);
	GetPosition = reinterpret_cast<Transform_get_position>(base + 0x3AFFE30);
	GetRotation = reinterpret_cast<Transform_get_rotation>(base + 0x3B00FB0);
	GetGameObject = reinterpret_cast<Component_get_gameObject>(base + 0x3ADEE70);
	IsActive = reinterpret_cast<GameObject_get_activeInHierarchy>(base + 0x3AE4F10);
	GetGameObjectTransform = reinterpret_cast<GameObject_get_transform>(base + 0x3AE4A60);
	GetMainCamera = reinterpret_cast<Camera_get_main>(base + 0x3A45BB0);
	WorldToScreen = reinterpret_cast<Camera_WorldToScreenPoint>(base + 0x3A44650);

	GearItem_GetDisplayName = reinterpret_cast<GearItem_get_m_DisplayName>(base + 0x8369A0);

	// o* hook trampolines are owned by MH_CreateHook in Start() only;
	// re-seeding them here would clobber the trampoline with the raw address.
	GetPlayerManager = reinterpret_cast<GameManager_GetPlayerManager>(base + 0xC42E00);
	GetCondition = reinterpret_cast<GameManager_GetCondition>(base + 0xC41510);
	GetFatigue = reinterpret_cast<GameManager_GetFatigue>(base + 0xC41A60);
	GetFreezing = reinterpret_cast<GameManager_GetFreezing>(base + 0xC41BE0);
	GetHunger = reinterpret_cast<GameManager_GetHunger>(base + 0xC41DC0);
	GetThirst = reinterpret_cast<GameManager_GetThirst>(base + 0xC43E50);
	SetCameraAngle = reinterpret_cast<vp_FPSCamera_SetAngle>(base + 0x551D40);
	GetAiEyePos = reinterpret_cast<BaseAi_GetEyePos>(base + 0x59C3F0);

	const bool allValid = GetVpFPSCamera && GetCameraComponent && GetTransform && GetPosition &&
		GetRotation && GetGameObject && IsActive && GetGameObjectTransform &&
		GetMainCamera && WorldToScreen && GearItem_GetDisplayName &&
		GetPlayerManager && GetCondition && GetFatigue && GetFreezing &&
		GetHunger && GetThirst && SetCameraAngle && GetAiEyePos;

	if (allValid)
	{
		std::cout << "[SUCCESS] All function pointers initialized!\n";
		g_hooksInitialized = true;
	}
	else
	{
		std::cout << "[ERROR] Some function pointers are null!\n";
	}
}

// BaseAiManager.Add/Remove and GearManager.Add/Remove are STATIC in this build:
// first arg is the tracked object itself (no this pointer).
void hkBaseAiManagerAdd(void* bai, void* method)
{
	oBaseAiManagerAdd(bai, method);
	g_baseAiList.add(bai);
}

void hkBaseAiManagerRemove(void* bai, void* method)
{
	g_baseAiList.remove(bai);
	oBaseAiManagerRemove(bai, method);
}

void hkGearManagerAdd(void* gi, void* method)
{
	oGearManagerAdd(gi, method);
	g_gearItemList.add(gi);
}

void hkGearManagerRemove(void* gi, void* method)
{
	g_gearItemList.remove(gi);
	oGearManagerRemove(gi, method);
}

float hkCalculateFireStartSuccess(void* _this, void* starter, void* fuel, void* accel, void* method)
{
	if (g_alwaysSucceed)
	{
		return 100.0f;
	}
	return oCalculateFireStartSuccess(_this, starter, fuel, accel, method);
}

float hkRepairGetChanceSuccess(void* _this, void* method)
{
	if (g_alwaysSucceed)
	{
		return 100.0f;
	}
	return oRepairGetChanceSuccess(_this, method);
}

bool hkExamineRollForActionSuccess(void* _this, float baseSkillChance, void* method)
{
	if (g_alwaysSucceed)
	{
		return true;
	}
	return oExamineRollForActionSuccess(_this, baseSkillChance, method);
}

void hkActiveFishingComplete(void* _this, bool success, bool playerCancel, float progress, void* method)
{
	// "always succeed" means every completed fishing session yields a catch;
	// player-initiated cancels still pass through unchanged.
	if (g_alwaysSucceed && !playerCancel)
	{
		success = true;
	}
	oActiveFishingComplete(_this, success, playerCancel, progress, method);
}

inline void WriteBool(uintptr_t obj, uintptr_t offset, bool value)
{
	*reinterpret_cast<bool*>(obj + offset) = value;
}

inline void WriteFloat(uintptr_t obj, uintptr_t offset, float value)
{
	*reinterpret_cast<float*>(obj + offset) = value;
}

inline float ReadFloat(uintptr_t obj, uintptr_t offset)
{
	return *reinterpret_cast<float*>(obj + offset);
}

void ApplyPlayerCheats()
{
	if (!g_hooksInitialized || !GetPlayerManager) return;

	void* pm = GetPlayerManager(nullptr);
	if (!pm) return;
	uintptr_t pmAddr = reinterpret_cast<uintptr_t>(pm);

	if (g_godMode)
	{
		WriteBool(pmAddr, Offsets::GodMode, true);
		WriteBool(pmAddr, Offsets::SuspendCondition, true);
		void* cond = GetCondition ? GetCondition(nullptr) : nullptr;
		if (cond)
		{
			WriteBool(reinterpret_cast<uintptr_t>(cond), Offsets::NeverDie, true);
			// top up HP once when god is enabled
			uintptr_t condAddr = reinterpret_cast<uintptr_t>(cond);
			WriteFloat(condAddr, Offsets::ConditionHP, ReadFloat(condAddr, Offsets::ConditionMaxHP));
		}
	}

	if (g_noFatigue)
	{
		void* fatigue = GetFatigue ? GetFatigue(nullptr) : nullptr;
		if (fatigue)
		{
			WriteFloat(reinterpret_cast<uintptr_t>(fatigue), Offsets::CurrentFatigue, 0.0f);
		}
	}

	if (g_noFreezing)
	{
		void* freezing = GetFreezing ? GetFreezing(nullptr) : nullptr;
		if (freezing)
		{
			WriteFloat(reinterpret_cast<uintptr_t>(freezing), Offsets::CurrentFreezing, 0.0f);
		}
	}

	if (g_noHunger)
	{
		void* hunger = GetHunger ? GetHunger(nullptr) : nullptr;
		if (hunger)
		{
			uintptr_t addr = reinterpret_cast<uintptr_t>(hunger);
			WriteFloat(addr, Offsets::CurrentCalories, ReadFloat(addr, Offsets::MaxCalories));
		}
	}

	if (g_noThirst)
	{
		void* thirst = GetThirst ? GetThirst(nullptr) : nullptr;
		if (thirst)
		{
			WriteFloat(reinterpret_cast<uintptr_t>(thirst), Offsets::CurrentThirst, 0.0f);
		}
	}
}

// returns dot-product cosine between camera forward and direction to an ai's eye
static float AimScoreAi(void* ai, const Vector3& camPos, const Vector3& camFwd)
{
	if (!ai) return -2.0f;
	uintptr_t addr = reinterpret_cast<uintptr_t>(ai);
	if (ReadFloat(addr, Offsets::CurrentHP) <= 0.0f) return -2.0f;

	Vector3 eye = GetAiEyePos(ai, nullptr);
	Vector3 dir = { eye.x - camPos.x, eye.y - camPos.y, eye.z - camPos.z };
	float len = std::sqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
	if (len < 1.0f || len > g_aimbotRange) return -2.0f;

	return (dir.x * camFwd.x + dir.y * camFwd.y + dir.z * camFwd.z) / len;
}

void UpdateAimbot()
{
	if (!g_hooksInitialized || !g_aimbot || !GetAiEyePos || !SetCameraAngle) return;

	void* fpsCam = GetVpFPSCamera(nullptr);
	if (!fpsCam) return;

	const Vector3& camPos = g_camera.position;
	const Quaternion& q = g_camera.rotation;
	Vector3 camFwd = {
		2.0f * (q.x * q.z + q.w * q.y),
		2.0f * (q.y * q.z - q.w * q.x),
		1.0f - 2.0f * (q.x * q.x + q.y * q.y)
	};

	float minDot = std::cosf(g_aimbotFov * 3.14159265f / 180.0f);
	void* best = nullptr;
	float bestDot = minDot;

	g_baseAiList.for_each([&](void* ai)
		{
			float dot = AimScoreAi(ai, camPos, camFwd);
			if (dot > bestDot)
			{
				bestDot = dot;
				best = ai;
			}
		});

	if (!best) return;

	Vector3 eye = GetAiEyePos(best, nullptr);
	Vector3 dir = { eye.x - camPos.x, eye.y - camPos.y, eye.z - camPos.z };
	float len = std::sqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
	if (len < 0.01f) return;

	// vp_FPSCamera pitch: positive = down
	float targetYaw = std::atan2f(dir.x, dir.z) * 57.2957795f;
	float targetPitch = -std::asinf(dir.y / len) * 57.2957795f;

	float curYaw = std::atan2f(camFwd.x, camFwd.z) * 57.2957795f;
	float curPitch = -std::asinf(camFwd.y) * 57.2957795f;

	float dyaw = targetYaw - curYaw;
	while (dyaw > 180.0f) dyaw -= 360.0f;
	while (dyaw < -180.0f) dyaw += 360.0f;

	float s = g_aimbotSmoothing;
	SetCameraAngle(fpsCam, curYaw + dyaw * s, curPitch + (targetPitch - curPitch) * s, nullptr);
}

void DrawEspText(ImDrawList* draw, const Vector3& worldPos, void* camera, const Vector3& camPos,
	const std::string& text, ImU32 color)
{
	Vector3 screenPos = WorldToScreen(camera, worldPos, 0);
	if (screenPos.z < 0.1f) return;

	float dist = Vector3_Distance(camPos, worldPos);
	if (dist > g_espDistance) return;

	ImGuiIO& io = ImGui::GetIO();
	float y = io.DisplaySize.y - screenPos.y;
	draw->AddText(ImVec2(screenPos.x, y), color, text.c_str());
}

static const char* AiSubTypeName(int subType)
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

static bool AiModeIsHostile(int mode)
{
	return mode == 1 || mode == 13 || mode == 14 || mode == 25; // Attack/Stalking/Struggle/PassingAttack
}

void DrawESP()
{
	if (!g_drawEsp) return;

	void* camera = GetMainCamera();
	if (!camera) return;

	ImDrawList* draw = ImGui::GetForegroundDrawList();
	const Vector3& camPos = g_camera.position;
	const Vector3& camFwd = []() -> Vector3
		{
			const Quaternion& q = g_camera.rotation;
			return Vector3{
				2.0f * (q.x * q.z + q.w * q.y),
				2.0f * (q.y * q.z - q.w * q.x),
				1.0f - 2.0f * (q.x * q.x + q.y * q.y)
			};
		}();

	if (g_showBaseAiESP || g_espAnimals)
	{
		g_baseAiList.for_each([&](void* ai)
			{
				Vector3 worldPos = GetWorldPosition(ai);
				uintptr_t addr = reinterpret_cast<uintptr_t>(ai);
				int mode = *reinterpret_cast<int*>(addr + Offsets::AiMode);
				int subType = *reinterpret_cast<int*>(addr + Offsets::AiSubType);
				bool dead = ReadFloat(addr, Offsets::CurrentHP) <= 0.0f;
				if (dead && !g_showBaseAiESP) return;

				std::string text = AiSubTypeName(subType);
				text += '\n';
				if (g_showBaseAiHP)
				{
					int hp = static_cast<int>(GetCurrentHP(ai));
					int maxHp = static_cast<int>(GetMaxHP(ai));
					text += std::to_string(hp) + '/' + std::to_string(maxHp) + '\n';
				}
				char distBuf[32];
				sprintf_s(distBuf, "%.1fm", Vector3_Distance(camPos, worldPos));
				text += distBuf;
				if (g_showBaseAiName)
				{
					text += '\n' + GetStringFromSystemString(GetDisplayNameString(ai));
				}

				ImU32 color;
				if (AiModeIsHostile(mode))
				{
					color = IM_COL32(255, 40, 40, 255);
					// threat on screen: draw even past ESP distance
					Vector3 screenPos = WorldToScreen(camera, worldPos, 0);
					if (screenPos.z >= 0.1f)
					{
						ImGuiIO& io = ImGui::GetIO();
						draw->AddText(ImVec2(screenPos.x, io.DisplaySize.y - screenPos.y), color, text.c_str());
					}
					return;
				}
				color = IM_COL32(255, 100, 100, 255);
				DrawEspText(draw, worldPos, camera, camPos, text, color);
			});
	}

	if (g_showGearItemESP)
	{
		g_gearItemList.for_each([&](void* item)
			{
				Vector3 worldPos = GetGearItemWorldPosition(item);
				if (worldPos.x == -9999.0f) return;

				std::string text = "*\n";
				char distBuf[32];
				sprintf_s(distBuf, "%.1fm", Vector3_Distance(camPos, worldPos));
				text += distBuf;

				System_String* nameStr = GearItem_GetDisplayName(item);
				if (nameStr)
				{
					std::string name = nameStr->ToString();
					if (name.find('[') == std::string::npos)
					{
						text += '\n' + name;
					}
				}
				DrawEspText(draw, worldPos, camera, camPos, text, IM_COL32(255, 255, 100, 255));
			});
	}
}

static ID3D11Device* g_pd3dDevice = nullptr;
static IDXGISwapChain* g_pSwapChain = nullptr;
static ID3D11DeviceContext* g_pd3dContext = nullptr;
static ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;
static HWND g_hwnd = nullptr;
void* g_originalPresent = nullptr;
WNDPROC g_originalWndProc = nullptr;
bool g_imGuiInitialized = false;

using Present = HRESULT(__stdcall*)(IDXGISwapChain*, UINT, UINT);

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT, WPARAM, LPARAM);
LRESULT __stdcall WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam))
		return true;
	return CallWindowProc(g_originalWndProc, hwnd, msg, wParam, lParam);
}

long __stdcall hk_present(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags)
{
	if (!g_imGuiInitialized)
	{
		swapChain->GetDevice(__uuidof(ID3D11Device), reinterpret_cast<void**>(&g_pd3dDevice));
		g_pd3dDevice->GetImmediateContext(&g_pd3dContext);

		DXGI_SWAP_CHAIN_DESC desc;
		swapChain->GetDesc(&desc);
		g_hwnd = desc.OutputWindow;

		ID3D11Texture2D* backBuffer = nullptr;
		swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer));
		g_pd3dDevice->CreateRenderTargetView(backBuffer, nullptr, &g_mainRenderTargetView);
		backBuffer->Release();

		g_originalWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(g_hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndProc)));

		ImGui::CreateContext();
		ImGui_ImplWin32_Init(g_hwnd);
		ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dContext);
		g_imGuiInitialized = true;

		InitializeUnityPointers();
	}

	g_camera.update();
	g_drawEsp = g_showBaseAiESP || g_showGearItemESP || g_espAnimals;

	static bool f6WasDown = false;
	bool f6Down = (GetAsyncKeyState(VK_F6) & 0x8000) != 0;
	if (f6Down && !f6WasDown)
	{
		g_aimbot = !g_aimbot;
	}
	f6WasDown = f6Down;

	ApplyPlayerCheats();
	UpdateAimbot();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Debug Control", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Checkbox("NPC ESP", &g_showBaseAiESP);
	ImGui::SameLine();
	ImGui::Checkbox("Show HP", &g_showBaseAiHP);
	ImGui::SameLine();
	ImGui::Checkbox("Show Name", &g_showBaseAiName);
	ImGui::Checkbox("Item ESP", &g_showGearItemESP);
	ImGui::SliderFloat("ESP Distance", &g_espDistance, 10.0f, 1000.0f);
	ImGui::Separator();
	ImGui::Text("Animals");
	ImGui::Checkbox("Animal ESP", &g_espAnimals);
	ImGui::Text("Aimbot");
	ImGui::Checkbox("Enable Aimbot", &g_aimbot);
	ImGui::SameLine();
	ImGui::Text("[F6]");
	ImGui::SliderFloat("Aimbot FOV", &g_aimbotFov, 1.0f, 45.0f, "%.0f deg");
	ImGui::SliderFloat("Aimbot Range", &g_aimbotRange, 20.0f, 500.0f, "%.0f m");
	ImGui::SliderFloat("Aimbot Smoothing", &g_aimbotSmoothing, 0.05f, 1.0f, "%.2f");
	ImGui::Separator();
	ImGui::Text("Player");
	ImGui::Checkbox("God Mode", &g_godMode);
	ImGui::SameLine();
	ImGui::Checkbox("No Fatigue", &g_noFatigue);
	ImGui::Checkbox("No Freezing", &g_noFreezing);
	ImGui::SameLine();
	ImGui::Checkbox("No Hunger", &g_noHunger);
	ImGui::Checkbox("No Thirst", &g_noThirst);
	ImGui::SameLine();
	ImGui::Checkbox("Always Succeed", &g_alwaysSucceed);
	ImGui::TextDisabled("fire/repair/examine/fishing rolls");
	ImGui::Text("NPC Count: %zu", g_baseAiList.size());
	ImGui::Text("Item Count: %zu", g_gearItemList.size());
	ImGui::End();

	if (g_camera.valid)
	{
		ImDrawList* bgDraw = ImGui::GetBackgroundDrawList();
		char status[256];
		snprintf(status, sizeof(status),
			"Camera Pos: (%.1f, %.1f, %.1f) | Rot: (%.2f, %.2f, %.2f, %.2f)",
			g_camera.position.x, g_camera.position.y, g_camera.position.z,
			g_camera.rotation.x, g_camera.rotation.y, g_camera.rotation.z, g_camera.rotation.w
		);
		bgDraw->AddText(ImVec2(10, 10), IM_COL32(0, 255, 0, 255), status);
	}
	else
	{
		ImGui::GetBackgroundDrawList()->AddText(ImVec2(10, 10), IM_COL32(255, 0, 0, 255),
			"Camera not found / Player not loaded");
	}

	DrawESP();

	ImGui::EndFrame();
	ImGui::Render();
	g_pd3dContext->OMSetRenderTargets(1, &g_mainRenderTargetView, nullptr);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	return reinterpret_cast<Present>(g_originalPresent)(swapChain, syncInterval, flags);
}

DWORD WINAPI Start(LPVOID)
{
	const D3D_FEATURE_LEVEL levels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0 };
	DXGI_SWAP_CHAIN_DESC sd{};
	sd.BufferCount = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = GetForegroundWindow();
	sd.SampleDesc.Count = 1;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	ID3D11Device* device = nullptr;
	IDXGISwapChain* swapChain = nullptr;
	D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0,
		levels, _countof(levels), D3D11_SDK_VERSION,
		&sd, &swapChain, &device, nullptr, nullptr);

	if (swapChain)
	{
		void*** vtable = *reinterpret_cast<void****>(swapChain);
		void* present = vtable[8];

		MH_Initialize();
		MH_CreateHook(present, hk_present, &g_originalPresent);

		uintptr_t base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
		MH_CreateHook(reinterpret_cast<void*>(base + 0xC04050), hkBaseAiManagerAdd, reinterpret_cast<void**>(&oBaseAiManagerAdd));
		MH_CreateHook(reinterpret_cast<void*>(base + 0xC04470), hkBaseAiManagerRemove, reinterpret_cast<void**>(&oBaseAiManagerRemove));
		MH_CreateHook(reinterpret_cast<void*>(base + 0xC54500), hkGearManagerAdd, reinterpret_cast<void**>(&oGearManagerAdd));
		MH_CreateHook(reinterpret_cast<void*>(base + 0xC556D0), hkGearManagerRemove, reinterpret_cast<void**>(&oGearManagerRemove));

		MH_CreateHook(reinterpret_cast<void*>(base + 0xC24FC0), hkCalculateFireStartSuccess, reinterpret_cast<void**>(&oCalculateFireStartSuccess));
		MH_CreateHook(reinterpret_cast<void*>(base + 0xB4A960), hkRepairGetChanceSuccess, reinterpret_cast<void**>(&oRepairGetChanceSuccess));
		MH_CreateHook(reinterpret_cast<void*>(base + 0xA99DB0), hkExamineRollForActionSuccess, reinterpret_cast<void**>(&oExamineRollForActionSuccess));
		MH_CreateHook(reinterpret_cast<void*>(base + 0x909B60), hkActiveFishingComplete, reinterpret_cast<void**>(&oActiveFishingComplete));

		MH_EnableHook(MH_ALL_HOOKS);

		device->Release();
		swapChain->Release();
	}
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);
		CreateThread(nullptr, 0, Start, hModule, 0, nullptr);
	}
	return TRUE;
}