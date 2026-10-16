#include "pch.h"
#include "features/common.h"
#include "core/tracking.h"

namespace
{
	template<typename F>
	void ForEachGun(F&& func)
	{
		Tracking::GearList().for_each([&](void* gi)
			{
				if (!gi) return;
				void* gun = ReadPtr(reinterpret_cast<uintptr_t>(gi), Offsets::GearGunItem);
				if (gun) func(gun);
			});
	}

	class NoRecoilFeature : public Feature
	{
	public:
		NoRecoilFeature() : Feature("Weapons", "No Recoil") {}

		void OnTick() override
		{
			ForEachGun([](void* gun)
				{
					uintptr_t a = reinterpret_cast<uintptr_t>(gun);
					WriteFloat(a, Offsets::GunPitchRecoilMin, 0.0f);
					WriteFloat(a, Offsets::GunPitchRecoilMax, 0.0f);
					WriteFloat(a, Offsets::GunYawRecoilMin, 0.0f);
					WriteFloat(a, Offsets::GunYawRecoilMax, 0.0f);
				});
		}
	};

	class NoSwayFeature : public Feature
	{
	public:
		NoSwayFeature() : Feature("Weapons", "No Sway") {}

		void OnTick() override
		{
			ForEachGun([](void* gun)
				{
					uintptr_t a = reinterpret_cast<uintptr_t>(gun);
					WriteFloat(a, Offsets::GunSwayZeroFatigue, 0.0f);
					WriteFloat(a, Offsets::GunSwayMaxFatigue, 0.0f);
				});
		}
	};

	class NoJamFeature : public Feature
	{
	public:
		NoJamFeature() : Feature("Weapons", "No Misfire") {}

		void OnTick() override
		{
			ForEachGun([](void* gun)
				{
					WriteStaticBool(gun, Offsets::GunForceNoJamStatic, true);
				});
		}
	};

	class InfiniteClipFeature : public Feature
	{
	public:
		InfiniteClipFeature() : Feature("Weapons", "Infinite Clip") {}

		void OnTick() override
		{
			ForEachGun([](void* gun)
				{
					uintptr_t a = reinterpret_cast<uintptr_t>(gun);
					WriteInt(a, Offsets::GunRoundsInClip, ReadInt(a, Offsets::GunClipSize));
				});
		}
	};

	class RapidFireFeature : public Feature
	{
	public:
		RapidFireFeature() : Feature("Weapons", "Rapid Fire") {}

		void OnTick() override
		{
			ForEachGun([](void* gun)
				{
					uintptr_t a = reinterpret_cast<uintptr_t>(gun);
					WriteFloat(a, Offsets::GunFiringRate, 0.0f);
					WriteFloat(a, Offsets::GunReloadCooldown, 0.0f);
				});
		}
	};

	class GunDamageFeature : public Feature
	{
	public:
		GunDamageFeature() : Feature("Weapons", "Gun Damage") {}

		void OnTick() override
		{
			ForEachGun([&](void* gun)
				{
					WriteFloat(reinterpret_cast<uintptr_t>(gun), Offsets::GunDamageHP, m_damage);
				});
		}

		void OnMenu() override
		{
			ImGui::SliderFloat("Damage", &m_damage, 1.0f, 1000.0f, "%.0f");
		}

	private:
		float m_damage = 100.0f;
	};

	class GunAccuracyFeature : public Feature
	{
	public:
		GunAccuracyFeature() : Feature("Weapons", "Gun Accuracy Range") {}

		void OnTick() override
		{
			ForEachGun([&](void* gun)
				{
					WriteFloat(reinterpret_cast<uintptr_t>(gun), Offsets::GunAccuracyRange, m_range);
				});
		}

		void OnMenu() override
		{
			ImGui::SliderFloat("Range", &m_range, 1.0f, 1000.0f, "%.0f m");
		}

	private:
		float m_range = 200.0f;
	};

	REGISTER_FEATURE(NoRecoilFeature)
	REGISTER_FEATURE(NoSwayFeature)
	REGISTER_FEATURE(NoJamFeature)
	REGISTER_FEATURE(InfiniteClipFeature)
	REGISTER_FEATURE(RapidFireFeature)
	REGISTER_FEATURE(GunDamageFeature)
	REGISTER_FEATURE(GunAccuracyFeature)
}
