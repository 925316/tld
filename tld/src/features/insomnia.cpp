#include "pch.h"
#include "features/common.h"

namespace
{
	class ResistInsomniaFeature : public Feature
	{
	public:
		ResistInsomniaFeature() : Feature("Medical", "Resist Insomnia") {}

		void OnTick() override
		{
			void* insomnia = Comp(&GM_GetInsomnia);
			if (!insomnia) return;
			uintptr_t a = reinterpret_cast<uintptr_t>(insomnia);
			WriteFloat(a, Offsets::InsomniaResistHours, 1.0e9f);
			WriteFloat(a, Offsets::InsomniaResistMultiplier, 1.0f);
		}
	};

	REGISTER_FEATURE(ResistInsomniaFeature)
}
