#include "pch.h"
#include "core/feature.h"
#include "core/game.h"

namespace
{
	void* PlayerManager()
	{
		return g_gameReady ? GetPlayerManager(nullptr) : nullptr;
	}

	class GodModeFeature : public Feature
	{
	public:
		GodModeFeature() : Feature("Player", "God Mode") {}

		void OnTick() override
		{
			void* pm = PlayerManager();
			if (!pm) return;
			uintptr_t addr = reinterpret_cast<uintptr_t>(pm);
			WriteBool(addr, Offsets::GodMode, true);
			WriteBool(addr, Offsets::SuspendCondition, true);

			void* cond = GetCondition(nullptr);
			if (cond)
			{
				uintptr_t condAddr = reinterpret_cast<uintptr_t>(cond);
				WriteBool(condAddr, Offsets::NeverDie, true);
				WriteFloat(condAddr, Offsets::ConditionHP, ReadFloat(condAddr, Offsets::ConditionMaxHP));
			}
		}
	};

	class NoFatigueFeature : public Feature
	{
	public:
		NoFatigueFeature() : Feature("Player", "No Fatigue") {}

		void OnTick() override
		{
			void* fatigue = GetFatigue(nullptr);
			if (fatigue)
			{
				WriteFloat(reinterpret_cast<uintptr_t>(fatigue), Offsets::CurrentFatigue, 0.0f);
			}
		}
	};

	class NoFreezingFeature : public Feature
	{
	public:
		NoFreezingFeature() : Feature("Player", "No Freezing") {}

		void OnTick() override
		{
			void* freezing = GetFreezing(nullptr);
			if (freezing)
			{
				WriteFloat(reinterpret_cast<uintptr_t>(freezing), Offsets::CurrentFreezing, 0.0f);
			}
		}
	};

	class NoHungerFeature : public Feature
	{
	public:
		NoHungerFeature() : Feature("Player", "No Hunger") {}

		void OnTick() override
		{
			void* hunger = GetHunger(nullptr);
			if (hunger)
			{
				uintptr_t addr = reinterpret_cast<uintptr_t>(hunger);
				WriteFloat(addr, Offsets::CurrentCalories, ReadFloat(addr, Offsets::MaxCalories));
			}
		}
	};

	class NoThirstFeature : public Feature
	{
	public:
		NoThirstFeature() : Feature("Player", "No Thirst") {}

		void OnTick() override
		{
			void* thirst = GetThirst(nullptr);
			if (thirst)
			{
				WriteFloat(reinterpret_cast<uintptr_t>(thirst), Offsets::CurrentThirst, 0.0f);
			}
		}
	};

	REGISTER_FEATURE(GodModeFeature)
	REGISTER_FEATURE(NoFatigueFeature)
	REGISTER_FEATURE(NoFreezingFeature)
	REGISTER_FEATURE(NoHungerFeature)
	REGISTER_FEATURE(NoThirstFeature)
}
