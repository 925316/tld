#include "pch.h"
#include "features/common.h"

namespace
{
	// Keeps condition HP pinned to the current max.
	class InfiniteHPFeature : public Feature
	{
	public:
		InfiniteHPFeature() : Feature("Player", "Infinite HP") {}

		void OnTick() override
		{
			void* cond = Comp(&GetCondition);
			if (!cond) return;
			uintptr_t c = reinterpret_cast<uintptr_t>(cond);
			WriteFloat(c, Offsets::ConditionHP, ReadFloat(c, Offsets::ConditionMaxHP));
		}
	};

	class MaxHPSliderFeature : public Feature
	{
	public:
		MaxHPSliderFeature() : Feature("Player", "Set Max HP") {}

		void OnTick() override
		{
			void* cond = Comp(&GetCondition);
			if (!cond) return;
			uintptr_t c = reinterpret_cast<uintptr_t>(cond);
			WriteFloat(c, Offsets::ConditionMaxHP, m_maxHp);
			if (ReadFloat(c, Offsets::ConditionHP) > m_maxHp)
				WriteFloat(c, Offsets::ConditionHP, m_maxHp);
		}

		void OnMenu() override
		{
			ImGui::SliderFloat("Max HP", &m_maxHp, 10.0f, 500.0f, "%.0f");
		}

	private:
		float m_maxHp = 100.0f;
	};

	class ConditionPercentFeature : public Feature
	{
	public:
		ConditionPercentFeature() : Feature("Player", "Condition % Bonus") {}

		void OnTick() override
		{
			void* pm = Comp(&GetPlayerManager);
			if (pm) WriteFloat(reinterpret_cast<uintptr_t>(pm), Offsets::PlayerConditionPercentBonus, m_percent);
		}

		void OnMenu() override
		{
			ImGui::SliderFloat("Bonus %", &m_percent, 0.0f, 100.0f, "%.0f%%");
		}

	private:
		float m_percent = 25.0f;
	};

	class ConditionPerHourFeature : public Feature
	{
	public:
		ConditionPerHourFeature() : Feature("Player", "Condition Regen") {}

		void OnTick() override
		{
			void* pm = Comp(&GetPlayerManager);
			if (pm) WriteFloat(reinterpret_cast<uintptr_t>(pm), Offsets::PlayerConditionPerHourBonus, m_perHour);
		}

		void OnMenu() override
		{
			ImGui::SliderFloat("HP/hour", &m_perHour, 0.0f, 50.0f, "%.1f");
		}

	private:
		float m_perHour = 10.0f;
	};

	class WarmthBonusFeature : public Feature
	{
	public:
		WarmthBonusFeature() : Feature("Player", "Warmth Bonus") {}

		void OnTick() override
		{
			void* pm = Comp(&GetPlayerManager);
			if (!pm) return;
			uintptr_t p = reinterpret_cast<uintptr_t>(pm);
			WriteFloat(p, Offsets::PlayerWarmthBonusFromClothing, m_warmth);
			WriteFloat(p, Offsets::PlayerWindproofBonusFromClothing, m_windproof);
		}

		void OnMenu() override
		{
			ImGui::SliderFloat("Warmth", &m_warmth, 0.0f, 100.0f, "%.0f");
			ImGui::SliderFloat("Windproof", &m_windproof, 0.0f, 100.0f, "%.0f");
		}

	private:
		float m_warmth = 40.0f;
		float m_windproof = 40.0f;
	};

	class RestoreAllFeature : public Feature
	{
	public:
		RestoreAllFeature() : Feature("Player", "Restore All Condition") {}

		bool IsAction() const override { return true; }

		void OnAction() override
		{
			if (void* cond = Comp(&GetCondition))
			{
				uintptr_t c = reinterpret_cast<uintptr_t>(cond);
				WriteFloat(c, Offsets::ConditionHP, ReadFloat(c, Offsets::ConditionMaxHP));
			}
			if (void* f = Comp(&GetFatigue)) WriteFloat(reinterpret_cast<uintptr_t>(f), Offsets::CurrentFatigue, 0.0f);
			if (void* fr = Comp(&GetFreezing)) WriteFloat(reinterpret_cast<uintptr_t>(fr), Offsets::CurrentFreezing, 0.0f);
			if (void* h = Comp(&GetHunger))
			{
				uintptr_t a = reinterpret_cast<uintptr_t>(h);
				WriteFloat(a, Offsets::CurrentCalories, ReadFloat(a, Offsets::MaxCalories));
			}
			if (void* t = Comp(&GetThirst)) WriteFloat(reinterpret_cast<uintptr_t>(t), Offsets::CurrentThirst, 0.0f);
		}
	};

	REGISTER_FEATURE(InfiniteHPFeature)
	REGISTER_FEATURE(MaxHPSliderFeature)
	REGISTER_FEATURE(ConditionPercentFeature)
	REGISTER_FEATURE(ConditionPerHourFeature)
	REGISTER_FEATURE(WarmthBonusFeature)
	REGISTER_FEATURE(RestoreAllFeature)

	REGISTER_FEATURE_AS(PlayerInvulnerable, BoolFieldFeature, "Player", "Invulnerable", &GetCondition, Offsets::Invulnerable, true)
	REGISTER_FEATURE_AS(PlayerNeverDie, BoolFieldFeature, "Player", "Never Die", &GetCondition, Offsets::NeverDie, true)
	REGISTER_FEATURE_AS(PlayerHideDamage, BoolFieldFeature, "Player", "Hide Damage Events", &GetCondition, Offsets::HideDamageEvents, true)
	REGISTER_FEATURE_AS(PlayerForceUncrouched, BoolFieldFeature, "Player", "Force Uncrouched", &GetCondition, Offsets::ConditionForceUncrouched, true)
	REGISTER_FEATURE_AS(PlayerGhost, BoolFieldFeature, "Player", "Ghost Mode", &GetPlayerManager, Offsets::GhostMode, true)
	REGISTER_FEATURE_AS(PlayerForceAIFlee, BoolFieldFeature, "Player", "Force AI Flee", &GetPlayerManager, Offsets::ForceAIFlee, true)
	REGISTER_FEATURE_AS(PlayerDisableSpeech, BoolFieldFeature, "Player", "Disable All Speech", &GetPlayerManager, Offsets::PlayerDisableAllSpeech, true)
	REGISTER_FEATURE_AS(PlayerFreezeMovement, BoolFieldFeature, "Player", "Freeze Movement", &GetPlayerManager, Offsets::PlayerFreezeMovement, true)
	REGISTER_FEATURE_AS(PlayerAllowPanel, BoolFieldFeature, "Player", "Allow Panel Interaction", &GetPlayerManager, Offsets::PlayerAllowPanelInteraction, true)
}
