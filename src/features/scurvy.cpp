#include "pch.h"
#include "features/common.h"

namespace
{
	class NoScurvyImpactFeature : public Feature
	{
	public:
		NoScurvyImpactFeature() : Feature("Medical", "No Scurvy Impact") {}

		void OnTick() override
		{
			void* scurvy = Comp(&GM_GetScurvy);
			if (!scurvy) return;
			uintptr_t a = reinterpret_cast<uintptr_t>(scurvy);
			WriteFloat(a, Offsets::ScurvyRiskThreshold, 1.0e9f);
			WriteFloat(a, Offsets::ScurvyCureThreshold, 0.0f);
			WriteFloat(a, Offsets::ScurvyStaminaDrainMultiplier, 1.0f);
			WriteFloat(a, Offsets::ScurvyFatigueMultiplier, 1.0f);
		}
	};

	REGISTER_FEATURE(NoScurvyImpactFeature)

	REGISTER_FEATURE_AS(ScurvyRiskThreshold, SliderFloatFeature, "Medical", "Scurvy Risk Threshold",
		&GM_GetScurvy, Offsets::ScurvyRiskThreshold, 1.0e9f, 0.0f, 1.0e9f, "%.0f")
}
