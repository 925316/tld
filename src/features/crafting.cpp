#include "pch.h"
#include "features/common.h"
#include "core/tracking.h"

namespace
{
	template<typename F>
	void ForEachSubcomponent(uintptr_t fieldOffset, F&& func)
	{
		Tracking::GearList().for_each([&](void* gi)
			{
				if (!gi) return;
				void* component = ReadPtr(reinterpret_cast<uintptr_t>(gi), fieldOffset);
				if (component) func(component);
			});
	}

	class InstantCookFeature : public Feature
	{
	public:
		InstantCookFeature() : Feature("Crafting", "Instant Cook") {}

		void OnTick() override
		{
			ForEachSubcomponent(Offsets::GearCookable, [](void* c)
				{
					uintptr_t a = reinterpret_cast<uintptr_t>(c);
					WriteFloat(a, Offsets::CookTimeMinutes, 0.0f);
					WriteFloat(a, 0x34, 0.0f); // m_ReadyTimeMinutes
				});
		}
	};

	class CookTimeFeature : public Feature
	{
	public:
		CookTimeFeature() : Feature("Crafting", "Cook Time") {}

		void OnTick() override
		{
			ForEachSubcomponent(Offsets::GearCookable, [&](void* c)
				{
					WriteFloat(reinterpret_cast<uintptr_t>(c), Offsets::CookTimeMinutes, m_minutes);
				});
		}

		void OnMenu() override
		{
			ImGui::SliderFloat("Minutes", &m_minutes, 0.0f, 120.0f, "%.0f");
		}

	private:
		float m_minutes = 5.0f;
	};

	class InstantIgniteFeature : public Feature
	{
	public:
		InstantIgniteFeature() : Feature("Crafting", "Instant Ignite") {}

		void OnTick() override
		{
			ForEachSubcomponent(Offsets::GearFireStarterItem, [](void* c)
				{
					uintptr_t a = reinterpret_cast<uintptr_t>(c);
					WriteFloat(a, Offsets::FireStarterIgniteTinder, 0.0f);
					WriteFloat(a, Offsets::FireStarterIgniteTorch, 0.0f);
				});
		}
	};

	class CookingSpeedFeature : public Feature
	{
	public:
		CookingSpeedFeature() : Feature("Crafting", "Cooking Time Multiplier") {}

		void OnTick() override
		{
			ForEachSubcomponent(Offsets::GearCookingPotItem, [&](void* c)
				{
					WriteFloat(reinterpret_cast<uintptr_t>(c), Offsets::PotCookingTimeMultiplier, m_multiplier);
				});
		}

		void OnMenu() override
		{
			ImGui::SliderFloat("Multiplier", &m_multiplier, 0.0f, 5.0f, "%.2f");
		}

	private:
		float m_multiplier = 0.0f;
	};

	REGISTER_FEATURE(InstantCookFeature)
	REGISTER_FEATURE(CookTimeFeature)
	REGISTER_FEATURE(InstantIgniteFeature)
	REGISTER_FEATURE(CookingSpeedFeature)
}
