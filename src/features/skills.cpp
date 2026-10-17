#include "pch.h"
#include "features/common.h"

namespace
{
	// Pushes a skill's points high enough to max its tier.
	class SkillMaxFeature : public Feature
	{
	public:
		SkillMaxFeature(const char* name, GameComponentGetter* getter)
			: Feature("Skills", name)
			, m_getter(getter)
		{
		}

		void OnTick() override
		{
			void* skill = Comp(m_getter);
			if (skill && Skill_SetPoints) Skill_SetPoints(skill, m_points, 0, nullptr);
		}

		void OnMenu() override
		{
			ImGui::SliderInt("Points", &m_points, 100, 500000);
		}

	private:
		GameComponentGetter* m_getter;
		int m_points = 100000;
	};

	void MaxAllSkills()
	{
		GameComponentGetter* getters[] = {
			&GM_GetSkillFireStarting, &GM_GetSkillCarcassHarvesting, &GM_GetSkillCooking,
			&GM_GetSkillIceFishing, &GM_GetSkillRifle, &GM_GetSkillArchery,
			&GM_GetSkillClothingRepair, &GM_GetSkillRevolver, &GM_GetSkillGunsmithing,
		};
		for (GameComponentGetter* getter : getters)
		{
			if (void* skill = Comp(getter))
			{
				if (Skill_SetPoints) Skill_SetPoints(skill, 100000, 0, nullptr);
			}
		}
	}

	REGISTER_FEATURE_AS(SkillFirestarting, SkillMaxFeature, "Firestarting", &GM_GetSkillFireStarting)
	REGISTER_FEATURE_AS(SkillCarcassHarvesting, SkillMaxFeature, "Carcass Harvesting", &GM_GetSkillCarcassHarvesting)
	REGISTER_FEATURE_AS(SkillCooking, SkillMaxFeature, "Cooking", &GM_GetSkillCooking)
	REGISTER_FEATURE_AS(SkillIceFishing, SkillMaxFeature, "Ice Fishing", &GM_GetSkillIceFishing)
	REGISTER_FEATURE_AS(SkillRifle, SkillMaxFeature, "Rifle", &GM_GetSkillRifle)
	REGISTER_FEATURE_AS(SkillArchery, SkillMaxFeature, "Archery", &GM_GetSkillArchery)
	REGISTER_FEATURE_AS(SkillClothingRepair, SkillMaxFeature, "Clothing Repair", &GM_GetSkillClothingRepair)
	REGISTER_FEATURE_AS(SkillRevolver, SkillMaxFeature, "Revolver", &GM_GetSkillRevolver)
	REGISTER_FEATURE_AS(SkillGunsmithing, SkillMaxFeature, "Gunsmithing", &GM_GetSkillGunsmithing)
	REGISTER_FEATURE_AS(MaxAllSkillsAction, ActionFeature, "Skills", "Max All Skills", MaxAllSkills)
}
