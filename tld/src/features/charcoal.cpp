#include "pch.h"
#include "features/common.h"
#include "features/gear_iter.h"

namespace
{
	class InstantSurveyFeature : public Feature
	{
	public:
		InstantSurveyFeature() : Feature("World", "Instant Charcoal Survey") {}

		void OnTick() override
		{
			ForEachGearSubcomponent(Offsets::GearCharcoalItem, [](void* charcoal)
				{
					uintptr_t a = reinterpret_cast<uintptr_t>(charcoal);
					WriteFloat(a, Offsets::CharcoalSurveyGameMinutes, 0.0f);
					WriteFloat(a, Offsets::CharcoalSurveyRealSeconds, 0.0f);
				});
		}
	};

	REGISTER_FEATURE(InstantSurveyFeature)
}
