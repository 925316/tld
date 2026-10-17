#include "pch.h"
#include "features/common.h"

namespace
{
	// FireManager exposes static List<Campfire> m_Campfires (0x18) and
	// static List<WoodStove> m_WoodStoves (0x10) through class statics.
	class CampfiresNeverBurnOutFeature : public Feature
	{
	public:
		CampfiresNeverBurnOutFeature() : Feature("Fire", "Campfires Never Burn Out") {}

		void OnTick() override
		{
			void* manager = Comp(&GM_GetFireManager);
			if (!manager) return;
			void* statics = StaticFields(manager);
			if (!statics) return;

			const uintptr_t lists[] = { 0x18, 0x10 }; // Campfires, WoodStoves
			for (uintptr_t offset : lists)
			{
				void* list = ReadPtr(reinterpret_cast<uintptr_t>(statics), offset);
				if (!list) continue;

				void* items = ManagedListItems(list);
				int count = ManagedListCount(list);
				if (count > 4096) count = 4096;
				for (int i = 0; i < count; ++i)
				{
					void* place = ManagedArrayAt(items, i);
					if (!place) continue;

					WriteBool(reinterpret_cast<uintptr_t>(place), Offsets::CampfireBurnedOut, false);

					void* fire = ReadPtr(reinterpret_cast<uintptr_t>(place), Offsets::FireplaceFire);
					if (fire) WriteBool(reinterpret_cast<uintptr_t>(fire), Offsets::FireIsPerpetual, true);
				}
			}
		}
	};

	// Adds fuel time to every live fire so it never runs out.
	class FiresKeepBurningFeature : public Feature
	{
	public:
		FiresKeepBurningFeature() : Feature("Fire", "Keep Fires Burning") {}

		void OnTick() override
		{
			void* manager = Comp(&GM_GetFireManager);
			if (!manager) return;
			void* statics = StaticFields(manager);
			if (!statics) return;

			void* list = ReadPtr(reinterpret_cast<uintptr_t>(statics), 0x0); // m_Fires
			if (!list) return;

			void* items = ManagedListItems(list);
			int count = ManagedListCount(list);
			if (count > 4096) count = 4096;
			for (int i = 0; i < count; ++i)
			{
				void* fire = ManagedArrayAt(items, i);
				if (!fire) continue;
				uintptr_t a = reinterpret_cast<uintptr_t>(fire);
				WriteBool(a, Offsets::FireIsPerpetual, true);
				WriteFloat(a, Offsets::FireElapsedOnTOD, 0.0f);
			}
		}
	};

	REGISTER_FEATURE(CampfiresNeverBurnOutFeature)
	REGISTER_FEATURE(FiresKeepBurningFeature)
}
