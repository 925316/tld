#pragma once

#include "core/game.h"

struct CameraState
{
	Vector3 position{};
	Quaternion rotation{};
	bool valid = false;

	void Update();
	Vector3 Forward() const { return QuaternionForward(rotation); }
};

extern CameraState g_camera;
