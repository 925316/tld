#include "pch.h"
#include "features/common.h"

namespace
{
	void SaveGameAction()
	{
		if (GameManager_SaveGame) GameManager_SaveGame(nullptr);
	}

	void ForceSaveGameAction()
	{
		if (GameManager_ForceSaveGame) GameManager_ForceSaveGame(nullptr);
	}

	REGISTER_FEATURE_AS(SaveGame, ActionFeature, "Time", "Save Game", SaveGameAction)
	REGISTER_FEATURE_AS(ForceSaveGame, ActionFeature, "Time", "Force Save Game", ForceSaveGameAction)

	REGISTER_FEATURE_AS(TimeSpeed, SliderFloatFeature, "Time", "Time Speed", &GM_GetTimeOfDay,
		Offsets::TODDayLengthScale, 1.0f, 0.0f, 20.0f, "%.2f")
	REGISTER_FEATURE_AS(FreezeTime, FloatFieldFeature, "Time", "Freeze Time", &GM_GetTimeOfDay,
		Offsets::TODDayLengthScale, 0.0f)
	REGISTER_FEATURE_AS(LockTimeOfDay, BoolFieldFeature, "Time", "Lock Time Of Day", &GM_GetTimeOfDay,
		Offsets::TODLockedTOD, true)
	REGISTER_FEATURE_AS(TimeSpeedupCounter, SliderIntFeature, "Time", "Time Speedup Counter", &GM_GetTimeOfDay,
		Offsets::TODSpeedupCounter, 0, 0, 200)
}
