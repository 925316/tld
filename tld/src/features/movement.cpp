#include "pch.h"
#include "features/common.h"

namespace
{
	void* FPSPlayer()
	{
		return Comp(&GM_GetVpFPSPlayer);
	}

	void* FPSController()
	{
		void* player = FPSPlayer();
		return player ? ReadPtr(reinterpret_cast<uintptr_t>(player), Offsets::FPSPlayerController) : nullptr;
	}

	// Keeps sprint stamina topped up.
	class UnlimitedSprintFeature : public Feature
	{
	public:
		UnlimitedSprintFeature() : Feature("Movement", "Unlimited Sprint") {}

		void OnTick() override
		{
			void* pm = Comp(&GM_GetPlayerMovement);
			if (!pm) return;
			uintptr_t p = reinterpret_cast<uintptr_t>(pm);
			WriteFloat(p, Offsets::SprintStamina, ReadFloat(p, Offsets::MaxSprintStamina));
		}
	};

	class MoveSpeedFeature : public Feature
	{
	public:
		MoveSpeedFeature() : Feature("Movement", "Movement Speed") {}

		void OnTick() override
		{
			void* c = FPSController();
			if (!c) return;
			uintptr_t a = reinterpret_cast<uintptr_t>(c);
			WriteFloat(a, Offsets::MotorVelocityMin, m_min);
			WriteFloat(a, Offsets::MotorVelocityMax, m_max);
		}

		void OnMenu() override
		{
			ImGui::SliderFloat("Min", &m_min, 0.0f, 30.0f, "%.1f");
			ImGui::SliderFloat("Max", &m_max, 0.5f, 40.0f, "%.1f");
		}

	private:
		float m_min = 2.0f;
		float m_max = 12.0f;
	};

	class JumpForceFeature : public Feature
	{
	public:
		JumpForceFeature() : Feature("Movement", "Jump Force") {}

		void OnTick() override
		{
			void* c = FPSController();
			if (c) WriteFloat(reinterpret_cast<uintptr_t>(c), Offsets::MotorJumpForce, m_force);
		}

		void OnMenu() override
		{
			ImGui::SliderFloat("Force", &m_force, 0.0f, 30.0f, "%.1f");
		}

	private:
		float m_force = 8.0f;
	};

	class GravityFeature : public Feature
	{
	public:
		GravityFeature() : Feature("Movement", "Gravity Scale") {}

		void OnTick() override
		{
			void* c = FPSController();
			if (c) WriteFloat(reinterpret_cast<uintptr_t>(c), Offsets::PhysicsGravityModifier, m_scale);
		}

		void OnMenu() override
		{
			ImGui::SliderFloat("Gravity", &m_scale, 0.0f, 3.0f, "%.2f");
		}

	private:
		float m_scale = 1.0f;
	};

	class ForcedMovementFeature : public Feature
	{
	public:
		ForcedMovementFeature() : Feature("Movement", "Force Walk") {}

		void OnTick() override
		{
			void* pm = Comp(&GM_GetPlayerMovement);
			if (pm) WriteInt(reinterpret_cast<uintptr_t>(pm), Offsets::PlayerForcedMovement, 2);
		}
	};

	class ForceCrouchFeature : public Feature
	{
	public:
		ForceCrouchFeature() : Feature("Movement", "Force Crouch") {}

		void OnTick() override
		{
			void* pm = Comp(&GM_GetPlayerMovement);
			if (pm) WriteInt(reinterpret_cast<uintptr_t>(pm), Offsets::PlayerForcedMovement, 1);
		}
	};

	class ClimbSpeedFeature : public Feature
	{
	public:
		ClimbSpeedFeature() : Feature("Movement", "Climb Speed") {}

		void OnTick() override
		{
			void* c = Comp(&GM_GetPlayerClimbRope);
			if (!c) return;
			uintptr_t a = reinterpret_cast<uintptr_t>(c);
			WriteFloat(a, Offsets::ClimbSpeedUpFullyRested, m_speed);
			WriteFloat(a, Offsets::ClimbSpeedDownFullyRested, m_speed);
		}

		void OnMenu() override
		{
			ImGui::SliderFloat("Speed", &m_speed, 0.0f, 20.0f, "%.1f");
		}

	private:
		float m_speed = 3.0f;
	};

	REGISTER_FEATURE(UnlimitedSprintFeature)
	REGISTER_FEATURE(MoveSpeedFeature)
	REGISTER_FEATURE(JumpForceFeature)
	REGISTER_FEATURE(GravityFeature)
	REGISTER_FEATURE(ForcedMovementFeature)
	REGISTER_FEATURE(ForceCrouchFeature)
	REGISTER_FEATURE(ClimbSpeedFeature)

	REGISTER_FEATURE_AS(NoSprintDrain, SliderFloatFeature, "Movement", "Sprint Drain",
		&GM_GetPlayerMovement, Offsets::SprintStaminaUsagePerSecond, 0.0f, 0.0f, 20.0f, "%.1f")
	REGISTER_FEATURE_AS(NoFallDamage, FloatFieldFeature, "Movement", "No Fall Damage",
		&GM_GetFallDamage, Offsets::FallDamagePerMeter, 0.0f)
	REGISTER_FEATURE_AS(FallStartHeight, SliderFloatFeature, "Movement", "Fall Damage Height",
		&GM_GetFallDamage, Offsets::FallHeightStartDamage, 999.0f, 0.0f, 999.0f, "%.0f")
	REGISTER_FEATURE_AS(NoFallClothingDamage, FloatFieldFeature, "Movement", "No Fall Clothing Damage",
		&GM_GetFallDamage, Offsets::FallClothingDamagePerMeter, 0.0f)
	REGISTER_FEATURE_AS(RopeNoSlip, FloatFieldFeature, "Movement", "No Rope Slip",
		&GM_GetPlayerClimbRope, Offsets::ClimbSlipChanceInitial, 0.0f)
	REGISTER_FEATURE_AS(RopeNoFall, FloatFieldFeature, "Movement", "No Rope Fall",
		&GM_GetPlayerClimbRope, Offsets::ClimbFallChanceInitial, 0.0f)
	REGISTER_FEATURE_AS(ClimbNoStaminaDrain, FloatFieldFeature, "Movement", "Climb No Stamina Drain",
		&GM_GetPlayerClimbRope, Offsets::ClimbStaminaDrainUp, 0.0f)
	REGISTER_FEATURE_AS(NoSprainFromFalls, BoolFieldFeature, "Movement", "No Sprain From Falls",
		&GM_GetPlayerMovement, Offsets::PlayerForceNoRandomSprain, true)
	REGISTER_FEATURE_AS(NoWeightCalorieBurn, FloatFieldFeature, "Movement", "No Weight Calorie Burn",
		&GM_GetEncumber, Offsets::HourlyCalorieBurnPerKG, 0.0f)
}
