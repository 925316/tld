#include "pch.h"
#include "features/common.h"
#include "features/gear_iter.h"

namespace
{
	class ShortwaveRangeFeature : public Feature
	{
	public:
		ShortwaveRangeFeature() : Feature("World", "Shortwave Max Range") {}

		void OnTick() override
		{
			ForEachGearSubcomponent(Offsets::GearHandheldShortwave, [](void* shortwave)
				{
					uintptr_t a = reinterpret_cast<uintptr_t>(shortwave);
					WriteFloat(a, Offsets::ShortwaveIntensity, 1.0f);
					WriteFloat(a, Offsets::ShortwaveFullSignalRange, 99999.0f);
					WriteFloat(a, Offsets::ShortwaveMaxRange, 99999.0f);
				});
		}
	};

	REGISTER_FEATURE(ShortwaveRangeFeature)
}
