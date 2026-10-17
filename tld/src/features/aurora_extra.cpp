#include "pch.h"
#include "features/common.h"

namespace
{
	class AuroraCalmWildlifeFeature : public Feature
	{
	public:
		AuroraCalmWildlifeFeature() : Feature("Weather", "Aurora Calm Wildlife") {}

		void OnTick() override
		{
			void* aurora = Comp(&GM_GetAuroraManager);
			if (!aurora) return;
			uintptr_t a = reinterpret_cast<uintptr_t>(aurora);
			WriteFloat(a, Offsets::AuroraPredatorInflictDamageScale, 0.0f);
			WriteFloat(a, Offsets::AuroraPredatorFleeChanceScale, 1.0f);
			WriteFloat(a, Offsets::AuroraWildlifeDetectionScale, 0.0f);
		}
	};

	REGISTER_FEATURE(AuroraCalmWildlifeFeature)

	REGISTER_FEATURE_AS(AuroraWildlifeDetection, SliderFloatFeature, "Weather", "Aurora Wildlife Detection Scale",
		&GM_GetAuroraManager, Offsets::AuroraWildlifeDetectionScale, 1.0f, 0.0f, 5.0f, "%.2f")
	REGISTER_FEATURE_AS(AuroraPredatorDamage, SliderFloatFeature, "Weather", "Aurora Predator Damage Scale",
		&GM_GetAuroraManager, Offsets::AuroraPredatorInflictDamageScale, 1.0f, 0.0f, 5.0f, "%.2f")
	REGISTER_FEATURE_AS(AuroraDamageToPredators, SliderFloatFeature, "Weather", "Aurora Damage To Predators Scale",
		&GM_GetAuroraManager, Offsets::AuroraDamageToPredatorsScale, 1.0f, 0.0f, 20.0f, "%.2f")
	REGISTER_FEATURE_AS(AuroraPredatorAttackDistance, SliderFloatFeature, "Weather", "Aurora Predator Attack Distance",
		&GM_GetAuroraManager, Offsets::AuroraPredatorAttackDistanceScale, 1.0f, 0.0f, 5.0f, "%.2f")
}
