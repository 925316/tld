#include "pch.h"
#include "features/common.h"
#include "features/gear_iter.h"

namespace
{
	class BowNoSwayFeature : public Feature
	{
	public:
		BowNoSwayFeature() : Feature("Weapons", "Bow No Sway") {}

		void OnTick() override
		{
			ForEachGearSubcomponent(Offsets::GearBowItem, [](void* bow)
				{
					uintptr_t a = reinterpret_cast<uintptr_t>(bow);
					WriteFloat(a, 0x48, 0.0f); // m_SwayValueZeroFatigue
					WriteFloat(a, 0x4C, 0.0f); // m_SwayValueMaxFatigue
					WriteFloat(a, 0x50, 0.0f); // m_SwayIncreasePerSecond
				});
		}
	};

	class BowDamageFeature : public Feature
	{
	public:
		BowDamageFeature() : Feature("Weapons", "Bow Damage Multiplier") {}

		void OnTick() override
		{
			ForEachGearSubcomponent(Offsets::GearBowItem, [&](void* bow)
				{
					WriteFloat(reinterpret_cast<uintptr_t>(bow), 0x64, m_multiplier);
				});
		}

		void OnMenu() override { ImGui::SliderFloat("Multiplier", &m_multiplier, 1.0f, 50.0f, "%.1f"); }

	private:
		float m_multiplier = 10.0f;
	};

	class ArrowDamageFeature : public Feature
	{
	public:
		ArrowDamageFeature() : Feature("Weapons", "Arrow Damage") {}

		void OnTick() override
		{
			ForEachGearSubcomponent(Offsets::GearArrowItem, [&](void* arrow)
				{
					WriteFloat(reinterpret_cast<uintptr_t>(arrow), 0x70, m_damage);
				});
		}

		void OnMenu() override { ImGui::SliderFloat("Damage", &m_damage, 1.0f, 1000.0f, "%.0f"); }

	private:
		float m_damage = 100.0f;
	};

	class ArrowVelocityFeature : public Feature
	{
	public:
		ArrowVelocityFeature() : Feature("Weapons", "Arrow Release Velocity") {}

		void OnTick() override
		{
			ForEachGearSubcomponent(Offsets::GearArrowItem, [&](void* arrow)
				{
					WriteFloat(reinterpret_cast<uintptr_t>(arrow), 0x68, m_velocity);
				});
		}

		void OnMenu() override { ImGui::SliderFloat("Velocity", &m_velocity, 10.0f, 500.0f, "%.0f"); }

	private:
		float m_velocity = 100.0f;
	};

	class NoBowDegradeFeature : public Feature
	{
	public:
		NoBowDegradeFeature() : Feature("Weapons", "No Bow Degrade") {}

		void OnTick() override
		{
			ForEachGearSubcomponent(Offsets::GearArrowItem, [](void* arrow)
				{
					WriteFloat(reinterpret_cast<uintptr_t>(arrow), 0x84, 0.0f); // m_BowDegradeModifier
				});
		}
	};

	REGISTER_FEATURE(BowNoSwayFeature)
	REGISTER_FEATURE(BowDamageFeature)
	REGISTER_FEATURE(ArrowDamageFeature)
	REGISTER_FEATURE(ArrowVelocityFeature)
	REGISTER_FEATURE(NoBowDegradeFeature)
}
