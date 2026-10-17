#pragma once

bool InstallHook(uintptr_t rva, void* detour, void** original, const char* label);
