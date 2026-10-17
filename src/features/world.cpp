#include "pch.h"
#include "features/common.h"
#include "core/camera.h"
#include "core/tracking.h"

namespace
{
	template<typename F>
	void ForEachCorpse(F&& func)
	{
		Tracking::GearList().for_each([&](void* gi)
			{
				if (!gi) return;
				void* corpse = ReadPtr(reinterpret_cast<uintptr_t>(gi), Offsets::GearBodyHarvest);
				if (corpse) func(corpse);
			});
	}

	void TeleportTo(const Vector3& position)
	{
		void* pm = Comp(&GetPlayerManager);
		if (!pm || !PlayerManager_TeleportPlayer) return;
		PlayerManager_TeleportPlayer(pm, position, g_camera.rotation, nullptr);
	}

	class TeleportToAnimalFeature : public Feature
	{
	public:
		TeleportToAnimalFeature() : Feature("World", "Teleport To Nearest Animal") {}

		bool IsAction() const override { return true; }

		void OnAction() override
		{
			const Vector3 camPos = g_camera.position;
			void* best = nullptr;
			float bestDistance = 1.0e30f;
			Vector3 bestPosition{};

			Tracking::AiList().for_each([&](void* ai)
				{
					if (!ai) return;
					Vector3 position = GetWorldPosition(ai);
					float distance = Vector3_Distance(camPos, position);
					if (distance < bestDistance)
					{
						bestDistance = distance;
						best = ai;
						bestPosition = position;
					}
				});

			if (!best) return;
			bestPosition.y += 1.5f;
			TeleportTo(bestPosition);
		}
	};

	class TeleportForwardFeature : public Feature
	{
	public:
		TeleportForwardFeature() : Feature("World", "Teleport Forward") {}

		bool IsAction() const override { return true; }

		void OnAction() override
		{
			Vector3 forward = g_camera.Forward();
			Vector3 position = {
				g_camera.position.x + forward.x * m_distance,
				g_camera.position.y + forward.y * m_distance + 1.0f,
				g_camera.position.z + forward.z * m_distance,
			};
			TeleportTo(position);
		}

		void OnMenu() override
		{
			ImGui::SliderFloat("Distance", &m_distance, 1.0f, 500.0f, "%.0f m");
		}

	private:
		float m_distance = 20.0f;
	};

	class TeleportUpFeature : public Feature
	{
	public:
		TeleportUpFeature() : Feature("World", "Teleport Up") {}

		bool IsAction() const override { return true; }

		void OnAction() override
		{
			Vector3 position = g_camera.position;
			position.y += 25.0f;
			TeleportTo(position);
		}
	};

	class CorpsesNeverFreezeFeature : public Feature
	{
	public:
		CorpsesNeverFreezeFeature() : Feature("World", "Corpses Never Freeze") {}

		void OnTick() override
		{
			ForEachCorpse([](void* corpse)
				{
					uintptr_t a = reinterpret_cast<uintptr_t>(corpse);
					WriteBool(a, Offsets::CorpseFrozen, false);
					WriteBool(a, Offsets::CorpseAllowFreezing, false);
					WriteFloat(a, Offsets::CorpsePercentFrozen, 0.0f);
				});
		}
	};

	class CorpsesNeverDecayFeature : public Feature
	{
	public:
		CorpsesNeverDecayFeature() : Feature("World", "Corpses Never Decay") {}

		void OnTick() override
		{
			ForEachCorpse([](void* corpse)
				{
					uintptr_t a = reinterpret_cast<uintptr_t>(corpse);
					WriteBool(a, Offsets::CorpseAllowDecay, false);
					WriteFloat(a, Offsets::CorpseCondition, 1.0f);
				});
		}
	};

	class CorpsesFreshFeature : public Feature
	{
	public:
		CorpsesFreshFeature() : Feature("World", "Corpses 100% Fresh") {}

		void OnTick() override
		{
			ForEachCorpse([](void* corpse)
				{
					WriteFloat(reinterpret_cast<uintptr_t>(corpse), Offsets::CorpseCondition, 1.0f);
				});
		}
	};

	REGISTER_FEATURE(TeleportToAnimalFeature)
	REGISTER_FEATURE(TeleportForwardFeature)
	REGISTER_FEATURE(TeleportUpFeature)
	REGISTER_FEATURE(CorpsesNeverFreezeFeature)
	REGISTER_FEATURE(CorpsesNeverDecayFeature)
	REGISTER_FEATURE(CorpsesFreshFeature)
}
