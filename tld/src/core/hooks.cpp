#include "pch.h"
#include "core/game.h"
#include "core/hooks.h"

bool InstallHook(uintptr_t rva, void* detour, void** original, const char* label)
{
	if (!g_gameAssemblyBase)
	{
		std::cout << "[ERROR] hook '" << label << "': game base unknown\n";
		return false;
	}

	MH_STATUS status = MH_CreateHook(reinterpret_cast<void*>(g_gameAssemblyBase + rva), detour, original);
	if (status != MH_OK)
	{
		std::cout << "[ERROR] hook '" << label << "' failed: " << MH_StatusToString(status) << '\n';
		return false;
	}
	return true;
}
