#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#include <Psapi.h>
#include <thread>

#include <sstream>
#include <iostream>
#include <iomanip>

#include <vector>
#include <string>
#include <cmath>
#include <set>
#include <mutex>
#include <algorithm>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "psapi.lib")

#include <d3d11.h>
#include <imgui.h>
#include <backends/imgui_impl_win32.h>
#include <backends/imgui_impl_dx11.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxgi.lib")

#include <MinHook.h>

#include "scan_pattern.hpp"

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif
