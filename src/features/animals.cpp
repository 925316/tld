#include "pch.h"
#include "features/common.h"
#include "core/tracking.h"

namespace
{
	void KillAllAnimals()
	{
		Tracking::AiList().for_each([](void* ai)
			{
				if (ai) WriteFloat(reinterpret_cast<uintptr_t>(ai), Offsets::AiCurrentHP, 0.0f);
			});
	}

	class OneHitKillFeature : public Feature
	{
	public:
		OneHitKillFeature() : Feature("Animals", "One Hit Kill") {}

		void OnTick() override
		{
			Tracking::AiList().for_each([](void* ai)
				{
					if (!ai) return;
					uintptr_t a = reinterpret_cast<uintptr_t>(ai);
					if (ReadFloat(a, Offsets::AiCurrentHP) > 1.0f)
						WriteFloat(a, Offsets::AiCurrentHP, 1.0f);
				});
		}
	};

	class FreezeAnimalsFeature : public Feature
	{
	public:
		FreezeAnimalsFeature() : Feature("Animals", "Freeze Animals") {}

		void OnTick() override
		{
			Tracking::AiList().for_each([](void* ai)
				{
					if (!ai) return;
					uintptr_t a = reinterpret_cast<uintptr_t>(ai);
					WriteBool(a, 0xA0, true);                 // m_SpeedForPathfindingOverride
					WriteFloat(a, Offsets::AiOverrideSpeed, 0.0f);
				});
		}
	};

	class MaxAiHpFeature : public Feature
	{
	public:
		MaxAiHpFeature() : Feature("Animals", "Animals Full HP") {}

		void OnTick() override
		{
			Tracking::AiList().for_each([](void* ai)
				{
					if (!ai) return;
					uintptr_t a = reinterpret_cast<uintptr_t>(ai);
					WriteFloat(a, Offsets::AiCurrentHP, ReadFloat(a, Offsets::AiMaxHP));
				});
		}
	};

	REGISTER_FEATURE(OneHitKillFeature)
	REGISTER_FEATURE(FreezeAnimalsFeature)
	REGISTER_FEATURE(MaxAiHpFeature)
	REGISTER_FEATURE_AS(KillAllAnimalsAction, ActionFeature, "Animals", "Kill All Animals", KillAllAnimals)

	REGISTER_FEATURE_AS(SpawnWolf, ActionFeature, "Animals", "Spawn Wolf", [] { if (Console_SpawnWolf) Console_SpawnWolf(nullptr); })
	REGISTER_FEATURE_AS(SpawnWolfStarving, ActionFeature, "Animals", "Spawn Starving Wolf", [] { if (Console_SpawnWolfStarving) Console_SpawnWolfStarving(nullptr); })
	REGISTER_FEATURE_AS(SpawnGreyWolf, ActionFeature, "Animals", "Spawn Grey Wolf", [] { if (Console_SpawnGreyWolf) Console_SpawnGreyWolf(nullptr); })
	REGISTER_FEATURE_AS(SpawnAuroraWolf, ActionFeature, "Animals", "Spawn Aurora Wolf", [] { if (Console_SpawnAuroraWolf) Console_SpawnAuroraWolf(nullptr); })
	REGISTER_FEATURE_AS(SpawnBear, ActionFeature, "Animals", "Spawn Bear", [] { if (Console_SpawnBear) Console_SpawnBear(nullptr); })
	REGISTER_FEATURE_AS(SpawnAuroraBear, ActionFeature, "Animals", "Spawn Aurora Bear", [] { if (Console_SpawnAuroraBear) Console_SpawnAuroraBear(nullptr); })
	REGISTER_FEATURE_AS(SpawnMoose, ActionFeature, "Animals", "Spawn Moose", [] { if (Console_SpawnMoose) Console_SpawnMoose(nullptr); })
	REGISTER_FEATURE_AS(SpawnStag, ActionFeature, "Animals", "Spawn Stag", [] { if (Console_SpawnStag) Console_SpawnStag(nullptr); })
	REGISTER_FEATURE_AS(SpawnDoe, ActionFeature, "Animals", "Spawn Doe", [] { if (Console_SpawnDoe) Console_SpawnDoe(nullptr); })
	REGISTER_FEATURE_AS(SpawnRabbit, ActionFeature, "Animals", "Spawn Rabbit", [] { if (Console_SpawnRabbit) Console_SpawnRabbit(nullptr); })
	REGISTER_FEATURE_AS(SpawnPtarmigan, ActionFeature, "Animals", "Spawn Ptarmigan", [] { if (Console_SpawnPtarmigan) Console_SpawnPtarmigan(nullptr); })
	REGISTER_FEATURE_AS(SpawnCougar, ActionFeature, "Animals", "Spawn Cougar", [] { if (Console_SpawnCougar) Console_SpawnCougar(nullptr); })
}
