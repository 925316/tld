#pragma once

#include "core/game.h"
#include "core/tracking.h"

// Runs func on each tracked gear item that exposes the given subcomponent
// field (see Offsets::GearXxx).
template<typename F>
inline void ForEachGearSubcomponent(uintptr_t fieldOffset, F&& func)
{
	Tracking::GearList().for_each([&](void* gi)
		{
			if (!gi) return;
			void* component = ReadPtr(reinterpret_cast<uintptr_t>(gi), fieldOffset);
			if (component) func(component);
		});
}
