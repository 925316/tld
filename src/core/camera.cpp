#include "pch.h"
#include "core/camera.h"

CameraState g_camera;

void CameraState::Update()
{
	if (!g_gameReady)
	{
		valid = false;
		return;
	}

	void* fpsCamera = GetVpFPSCamera(nullptr);
	if (!fpsCamera) { valid = false; return; }

	void* cameraObj = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(fpsCamera) + Offsets::CameraInFPS);
	if (!cameraObj) { valid = false; return; }

	void* transform = GetTransform(cameraObj);
	if (!transform) { valid = false; return; }

	position = GetPosition(transform);
	rotation = GetRotation(transform);
	valid = true;
}
