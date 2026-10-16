#include "pch.h"
#include "features/common.h"

namespace
{
	class NoWetnessFeature : public Feature
	{
	public:
		NoWetnessFeature() : Feature("Needs", "No Wetness") {}

		void OnTick() override
		{
			void* pm = Comp(&GetPlayerManager);
			if (!pm) return;
			uintptr_t a = reinterpret_cast<uintptr_t>(pm);
			WriteFloat(a, Offsets::PlayerWetnessLightSnow, 0.0f);
			WriteFloat(a, Offsets::PlayerWetnessHeavySnow, 0.0f);
			WriteFloat(a, Offsets::PlayerWetnessBlizzard, 0.0f);
		}
	};

	REGISTER_FEATURE(NoWetnessFeature)

	REGISTER_FEATURE_AS(WetnessLightSnow, SliderFloatFeature, "Needs", "Wetness Rate Light Snow",
		&GetPlayerManager, Offsets::PlayerWetnessLightSnow, 0.0f, 0.0f, 20.0f, "%.1f/hr")
	REGISTER_FEATURE_AS(WetnessHeavySnow, SliderFloatFeature, "Needs", "Wetness Rate Heavy Snow",
		&GetPlayerManager, Offsets::PlayerWetnessHeavySnow, 0.0f, 0.0f, 20.0f, "%.1f/hr")
	REGISTER_FEATURE_AS(WetnessBlizzard, SliderFloatFeature, "Needs", "Wetness Rate Blizzard",
		&GetPlayerManager, Offsets::PlayerWetnessBlizzard, 0.0f, 0.0f, 20.0f, "%.1f/hr")
}
