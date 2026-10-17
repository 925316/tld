#include "pch.h"
#include "features/common.h"
#include "features/static_list.h"

namespace
{
	// MapDetailManager keeps a static List<MapDetail> s_MapDetails.
	class RevealMapFeature : public Feature
	{
	public:
		RevealMapFeature() : Feature("World", "Reveal Full Map") {}

		void OnTick() override
		{
			ForEachStaticList("MapDetailManager", "s_MapDetails", [](void* detail)
				{
					uintptr_t a = reinterpret_cast<uintptr_t>(detail);
					WriteBool(a, Offsets::MapDetailUnlocked, true);
					WriteBool(a, Offsets::MapDetailDiscovered, true);
					WriteBool(a, Offsets::MapDetailSurveyed, true);
				});
		}
	};

	REGISTER_FEATURE(RevealMapFeature)
}
