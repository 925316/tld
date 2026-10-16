#include "pch.h"
#include "features/common.h"
#include "core/tracking.h"

namespace
{
	template<typename F>
	void ForEachClothing(F&& func)
	{
		Tracking::GearList().for_each([&](void* gi)
			{
				if (!gi) return;
				void* clothing = ReadPtr(reinterpret_cast<uintptr_t>(gi), Offsets::GearClothingItem);
				if (clothing) func(clothing);
			});
	}

	class ClothingNoDamageFeature : public Feature
	{
	public:
		ClothingNoDamageFeature() : Feature("Equipment", "Clothing No Damage") {}

		void OnTick() override
		{
			ForEachClothing([](void* c)
				{
					uintptr_t a = reinterpret_cast<uintptr_t>(c);
					WriteFloat(a, Offsets::ClothingDecayWornOutside, 0.0f);
					WriteFloat(a, Offsets::ClothingDecayWornInside, 0.0f);
				});
		}
	};

	REGISTER_FEATURE(ClothingNoDamageFeature)
}
