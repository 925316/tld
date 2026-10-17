#include "pch.h"
#include "features/common.h"
#include "core/game.h"

namespace
{
	void Give(const char* name, int count)
	{
		void* pm = Comp(&GetPlayerManager);
		if (!pm || !PlayerManager_AddItemCONSOLE) return;
		System_String* str = MakeString(name);
		if (!str) return;
		PlayerManager_AddItemCONSOLE(pm, str, count, 1.0f, nullptr);
	}

	REGISTER_FEATURE_AS(GiveImprovisedKnife, ActionFeature, "Inventory", "Give Improvised Knife", [] { Give("GEAR_KnifeImprovised", 1); })
	REGISTER_FEATURE_AS(GiveImprovisedHatchet, ActionFeature, "Inventory", "Give Improvised Hatchet", [] { Give("GEAR_HatchetImprovised", 1); })
	REGISTER_FEATURE_AS(GiveScrapKnife, ActionFeature, "Inventory", "Give Scrap Metal Knife", [] { Give("GEAR_KnifeScrapMetal", 1); })
	REGISTER_FEATURE_AS(GivePeroxide, ActionFeature, "Inventory", "Give Hydrogen Peroxide", [] { Give("GEAR_BottleHydrogenPeroxide", 5); })
	REGISTER_FEATURE_AS(GiveCattailStalk, ActionFeature, "Inventory", "Give Cattail Stalk", [] { Give("GEAR_CattailStalk", 20); })
	REGISTER_FEATURE_AS(GiveRoseHipTea, ActionFeature, "Inventory", "Give Rose Hip Tea", [] { Give("GEAR_RoseHipTea", 5); })
	REGISTER_FEATURE_AS(GiveReishiTea, ActionFeature, "Inventory", "Give Reishi Tea", [] { Give("GEAR_ReishiTea", 5); })
	REGISTER_FEATURE_AS(GiveBirchbarkTea, ActionFeature, "Inventory", "Give Birchbark Tea", [] { Give("GEAR_BirchbarkTea", 5); })
	REGISTER_FEATURE_AS(GiveOldMansBeard, ActionFeature, "Inventory", "Give Old Man's Beard", [] { Give("GEAR_OldMansBeard", 10); })
	REGISTER_FEATURE_AS(GiveOldMansBeardDressing, ActionFeature, "Inventory", "Give Old Man's Beard Dressing", [] { Give("GEAR_OldMansBeardDressing", 5); })
	REGISTER_FEATURE_AS(GiveCandyBar, ActionFeature, "Inventory", "Give Candy Bar", [] { Give("GEAR_CandyBar", 10); })
	REGISTER_FEATURE_AS(GiveBirchbark, ActionFeature, "Inventory", "Give Prepared Birchbark", [] { Give("GEAR_BirchbarkPrepared", 10); })
	REGISTER_FEATURE_AS(GiveToque, ActionFeature, "Inventory", "Give Toque", [] { Give("GEAR_Toque", 1); })
	REGISTER_FEATURE_AS(GiveWolfSkinCape, ActionFeature, "Inventory", "Give Wolf Skin Cape", [] { Give("GEAR_WolfSkinCape", 1); })
	REGISTER_FEATURE_AS(GiveDeerSkinBoots, ActionFeature, "Inventory", "Give Deerskin Boots", [] { Give("GEAR_DeerSkinBoots", 1); })
	REGISTER_FEATURE_AS(GiveRabbitMittens, ActionFeature, "Inventory", "Give Rabbit Skin Mittens", [] { Give("GEAR_RabbitSkinMittens", 1); })
	REGISTER_FEATURE_AS(GiveBearSkinBedRoll, ActionFeature, "Inventory", "Give Bear Skin Bedroll", [] { Give("GEAR_BearSkinBedRoll", 1); })
	REGISTER_FEATURE_AS(GiveCookingPot, ActionFeature, "Inventory", "Give Cooking Pot", [] { Give("GEAR_CookingPotDummy", 1); })
	REGISTER_FEATURE_AS(GiveSprayPaint, ActionFeature, "Inventory", "Give Spray Paint", [] { Give("GEAR_SprayPaintCan", 1); })
	REGISTER_FEATURE_AS(GiveCamera, ActionFeature, "Inventory", "Give Camera", [] { Give("GEAR_Camera", 1); })
}
