#pragma once

class Feature
{
public:
	Feature(const char* category, const char* name, int toggleKey = 0);
	virtual ~Feature() = default;

	virtual void OnStartup(uintptr_t gameAssemblyBase) {}
	virtual void OnTick() {}
	virtual void OnMenu() {}

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
