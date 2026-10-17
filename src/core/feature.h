#pragma once

// Base class for every cheat/feature. Registration is automatic via
// REGISTER_FEATURE; the registry dispatches ticks and builds the menu.
class Feature
{
public:
	Feature(const char* category, const char* name, int toggleKey = 0);
	virtual ~Feature() = default;

	// Called once after game function pointers are resolved.
	virtual void OnStartup(uintptr_t gameAssemblyBase) {}
	// Called every frame while enabled (and every frame for actions, see IsAction).
	virtual void OnTick() {}
	// Extra widgets rendered under the feature's checkbox.
	virtual void OnMenu() {}
	// Edge callbacks for toggle transitions.
	virtual void OnEnable() {}
	virtual void OnDisable() {}
	// Action features render a button and run OnAction when pressed.
	virtual bool IsAction() const { return false; }
	virtual void OnAction() {}

	void PollToggleKey();

	const char* Category() const { return m_category; }
	const char* Name() const { return m_name; }
	int ToggleKey() const { return m_toggleKey; }

	bool enabled = false;

private:
	const char* m_category;
	const char* m_name;
	int m_toggleKey;
	bool m_keyWasDown = false;
};

#define REGISTER_FEATURE(ClassName) \
	static ClassName g_##ClassName; \
	static ::FeatureRegistrar g_##ClassName##_registrar(&g_##ClassName);

// Registers a feature whose type takes constructor arguments. The first macro
// argument is used only as the instance name.
#define REGISTER_FEATURE_AS(VarName, Type, ...) \
	static Type g_##VarName(__VA_ARGS__); \
	static ::FeatureRegistrar g_##VarName##_registrar(&g_##VarName);

struct FeatureRegistrar
{
	FeatureRegistrar(Feature* feature);
};

namespace FeatureRegistry
{
	void Startup(uintptr_t gameAssemblyBase);
	void Tick();
	void DrawMenu();
}
