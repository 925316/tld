#include "pch.h"
#include "features/common.h"
#include "core/il2cpp_api.h"

namespace
{
	// IceFishingHole keeps a static List<IceFishingHole> s_IceFishingHoles.
	void* IceHoleClass()
	{
		static void* klass = nullptr;
		if (!klass) klass = Il2Cpp::FindClass("", "IceFishingHole");
		return klass;
	}

	template<typename F>
	void ForEachIceHole(F&& func)
	{
		void* klass = IceHoleClass();
		if (!klass) return;

		void* list = Il2Cpp::GetStaticFieldValue(klass, "s_IceFishingHoles");
		if (!list) return;

		void* items = ManagedListItems(list);
		int count = ManagedListCount(list);
		if (count > 4096) count = 4096;
		for (int i = 0; i < count; ++i)
		{
			if (void* hole = ManagedArrayAt(items, i)) func(hole);
		}
	}

	class IceNeverFreezesFeature : public Feature
	{
	public:
		IceNeverFreezesFeature() : Feature("Fishing", "Ice Never Freezes") {}

		void OnTick() override
		{
			ForEachIceHole([](void* hole)
				{
					uintptr_t a = reinterpret_cast<uintptr_t>(hole);
					WriteFloat(a, Offsets::IceFreezePercentPerHour, 0.0f);
					WriteBool(a, Offsets::IcePauseFreezing, true);
				});
		}
	};

	class InstantCatchFeature : public Feature
	{
	public:
		InstantCatchFeature() : Feature("Fishing", "Instant Catch Fish") {}

		void OnTick() override
		{
			ForEachIceHole([](void* hole)
				{
					uintptr_t a = reinterpret_cast<uintptr_t>(hole);
					WriteFloat(a, Offsets::IceMinMinutesCatch, 0.0f);
					WriteFloat(a, Offsets::IceMaxMinutesCatch, 0.0f);
				});
		}
	};

	class NoLineSnapFeature : public Feature
	{
	public:
		NoLineSnapFeature() : Feature("Fishing", "No Line Snap") {}

		void OnTick() override
		{
			ForEachIceHole([](void* hole)
				{
					WriteFloat(reinterpret_cast<uintptr_t>(hole), Offsets::IceLineSnapDecay, 0.0f);
				});
		}
	};

	class NoOverfishingFeature : public Feature
	{
	public:
		NoOverfishingFeature() : Feature("Fishing", "No Overfishing") {}

		void OnTick() override
		{
			ForEachIceHole([](void* hole)
				{
					WriteInt(reinterpret_cast<uintptr_t>(hole), Offsets::IceOverfishingLimit, 9999);
				});
		}
	};

	REGISTER_FEATURE(IceNeverFreezesFeature)
	REGISTER_FEATURE(InstantCatchFeature)
	REGISTER_FEATURE(NoLineSnapFeature)
	REGISTER_FEATURE(NoOverfishingFeature)
}
