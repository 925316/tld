#include "pch.h"
#include "core/camera.h"
#include "core/game.h"
#include "core/feature.h"
#include "core/hooks.h"
#include "core/tracking.h"
#include "overlay/menu.h"

static ID3D11Device* g_pd3dDevice = nullptr;
static ID3D11DeviceContext* g_pd3dContext = nullptr;
static ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;
static HWND g_hwnd = nullptr;
static void* g_originalPresent = nullptr;
static WNDPROC g_originalWndProc = nullptr;
static bool g_imGuiInitialized = false;

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
	}

	g_camera.Update();
	FeatureRegistry::Tick();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	Menu::Draw();

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

		ResolveGameFunctions();
		Tracking::Install();
		FeatureRegistry::Startup(g_gameAssemblyBase);

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
