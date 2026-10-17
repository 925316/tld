#pragma once

#include "core/feature.h"
#include "core/game.h"

// Small building blocks shared by the feature files. Every helper reads its
// target object lazily (at tick time), so passing the address of a global
// getter is safe even though the getters are null during static init.

inline void* Comp(GameComponentGetter* getter)
{
	if (!g_gameReady || !getter || !*getter) return nullptr;
	return (*getter)(nullptr);
}

// Writes a constant bool into an object field every frame while enabled.
class BoolFieldFeature : public Feature
{
public:
	BoolFieldFeature(const char* category, const char* name, GameComponentGetter* getter,
		uintptr_t offset, bool value, int toggleKey = 0)
		: Feature(category, name, toggleKey)
		, m_getter(getter)
		, m_offset(offset)
		, m_value(value)
	{
	}

	void OnTick() override
	{
		void* obj = Comp(m_getter);
		if (obj) WriteBool(reinterpret_cast<uintptr_t>(obj), m_offset, m_value);
	}

private:
	GameComponentGetter* m_getter;
	uintptr_t m_offset;
	bool m_value;
};

// Writes a constant float into an object field every frame while enabled.
class FloatFieldFeature : public Feature
{
public:
	FloatFieldFeature(const char* category, const char* name, GameComponentGetter* getter,
		uintptr_t offset, float value)
		: Feature(category, name)
		, m_getter(getter)
		, m_offset(offset)
		, m_value(value)
	{
	}

	void OnTick() override
	{
		void* obj = Comp(m_getter);
		if (obj) WriteFloat(reinterpret_cast<uintptr_t>(obj), m_offset, m_value);
	}

private:
	GameComponentGetter* m_getter;
	uintptr_t m_offset;
	float m_value;
};

// Writes a constant int into an object field every frame while enabled.
class IntFieldFeature : public Feature
{
public:
	IntFieldFeature(const char* category, const char* name, GameComponentGetter* getter,
		uintptr_t offset, int value)
		: Feature(category, name)
		, m_getter(getter)
		, m_offset(offset)
		, m_value(value)
	{
	}

	void OnTick() override
	{
		void* obj = Comp(m_getter);
		if (obj) WriteInt(reinterpret_cast<uintptr_t>(obj), m_offset, m_value);
	}

private:
	GameComponentGetter* m_getter;
	uintptr_t m_offset;
	int m_value;
};

// Button that runs a callback once per press.
class ActionFeature : public Feature
{
public:
	ActionFeature(const char* category, const char* name, std::function<void()> action)
		: Feature(category, name)
		, m_action(std::move(action))
	{
	}

	bool IsAction() const override { return true; }

	void OnAction() override
	{
		if (m_action) m_action();
	}

private:
	std::function<void()> m_action;
};

// Runs one of the game's built-in developer-console commands by RVA.
// The commands are static void CONSOLE_xxx() methods on ConsoleManager.
class ConsoleActionFeature : public Feature
{
public:
	ConsoleActionFeature(const char* category, const char* name, uintptr_t rva)
		: Feature(category, name)
		, m_rva(rva)
	{
	}

	bool IsAction() const override { return true; }

	void OnAction() override
	{
		if (!g_gameAssemblyBase || m_rva == 0) return;
		using ConsoleFn = void (*)(void*);
		reinterpret_cast<ConsoleFn>(g_gameAssemblyBase + m_rva)(nullptr);
	}

private:
	uintptr_t m_rva;
};

// Read-only feature (only renders OnMenu widgets / info).
class InfoFeature : public Feature
{
public:
	InfoFeature(const char* category, const char* name, std::function<void()> menu)
		: Feature(category, name)
		, m_menu(std::move(menu))
	{
	}

	void OnMenu() override
	{
		if (m_menu) m_menu();
	}

private:
	std::function<void()> m_menu;
};

// Empties one or more managed List<T> fields every frame while enabled.
class ClearListsFieldFeature : public Feature
{
public:
	ClearListsFieldFeature(const char* category, const char* name, GameComponentGetter* getter,
		std::initializer_list<uintptr_t> offsets)
		: Feature(category, name)
		, m_getter(getter)
		, m_offsets(offsets)
	{
	}

	void OnTick() override
	{
		void* obj = Comp(m_getter);
		if (!obj) return;
		for (uintptr_t offset : m_offsets)
		{
			ClearManagedList(ReadPtr(reinterpret_cast<uintptr_t>(obj), offset));
		}
	}

private:
	GameComponentGetter* m_getter;
	std::vector<uintptr_t> m_offsets;
};

// Writes a slider-controlled float into an object field every frame.
class SliderFloatFeature : public Feature
{
public:
	SliderFloatFeature(const char* category, const char* name, GameComponentGetter* getter,
		uintptr_t offset, float value, float minValue, float maxValue, const char* format = "%.2f")
		: Feature(category, name)
		, m_getter(getter)
		, m_offset(offset)
		, m_value(value)
		, m_min(minValue)
		, m_max(maxValue)
		, m_format(format)
	{
	}

	void OnTick() override
	{
		void* obj = Comp(m_getter);
		if (obj) WriteFloat(reinterpret_cast<uintptr_t>(obj), m_offset, m_value);
	}

	void OnMenu() override
	{
		ImGui::SliderFloat("Value", &m_value, m_min, m_max, m_format);
	}

private:
	GameComponentGetter* m_getter;
	uintptr_t m_offset;
	float m_value;
	float m_min;
	float m_max;
	const char* m_format;
};

// Writes a slider-controlled int into an object field every frame.
class SliderIntFeature : public Feature
{
public:
	SliderIntFeature(const char* category, const char* name, GameComponentGetter* getter,
		uintptr_t offset, int value, int minValue, int maxValue)
		: Feature(category, name)
		, m_getter(getter)
		, m_offset(offset)
		, m_value(value)
		, m_min(minValue)
		, m_max(maxValue)
	{
	}

	void OnTick() override
	{
		void* obj = Comp(m_getter);
		if (obj) WriteInt(reinterpret_cast<uintptr_t>(obj), m_offset, m_value);
	}

	void OnMenu() override
	{
		ImGui::SliderInt("Value", &m_value, m_min, m_max);
	}

private:
	GameComponentGetter* m_getter;
	uintptr_t m_offset;
	int m_value;
	int m_min;
	int m_max;
};

// Writes a constant bool into a static field (via klass->static_fields).
class StaticBoolFieldFeature : public Feature
{
public:
	StaticBoolFieldFeature(const char* category, const char* name, GameComponentGetter* getter,
		uintptr_t offset, bool value)
		: Feature(category, name)
		, m_getter(getter)
		, m_offset(offset)
		, m_value(value)
	{
	}

	void OnTick() override
	{
		void* obj = Comp(m_getter);
		if (obj) WriteStaticBool(obj, m_offset, m_value);
	}

private:
	GameComponentGetter* m_getter;
	uintptr_t m_offset;
	bool m_value;
};

// Writes a slider-controlled float into a static field.
class StaticSliderFloatFeature : public Feature
{
public:
	StaticSliderFloatFeature(const char* category, const char* name, GameComponentGetter* getter,
		uintptr_t offset, float value, float minValue, float maxValue, const char* format = "%.2f")
		: Feature(category, name)
		, m_getter(getter)
		, m_offset(offset)
		, m_value(value)
		, m_min(minValue)
		, m_max(maxValue)
		, m_format(format)
	{
	}

	void OnTick() override
	{
		void* obj = Comp(m_getter);
		if (obj) WriteStaticFloat(obj, m_offset, m_value);
	}

	void OnMenu() override
	{
		ImGui::SliderFloat("Value", &m_value, m_min, m_max, m_format);
	}

private:
	GameComponentGetter* m_getter;
	uintptr_t m_offset;
	float m_value;
	float m_min;
	float m_max;
	const char* m_format;
};
