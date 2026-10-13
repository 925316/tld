#include "pch.h"
#include "core/feature.h"

namespace
{
	std::vector<Feature*>& Features()
	{
		static std::vector<Feature*> instance;
		return instance;
	}
}

Feature::Feature(const char* category, const char* name, int toggleKey)
	: m_category(category)
	, m_name(name)
	, m_toggleKey(toggleKey)
{
}

FeatureRegistrar::FeatureRegistrar(Feature* feature)
{
	Features().push_back(feature);
}

void Feature::PollToggleKey()
{
	if (m_toggleKey == 0) return;

	bool down = (GetAsyncKeyState(m_toggleKey) & 0x8000) != 0;
	if (down && !m_keyWasDown)
	{
		enabled = !enabled;
	}
	m_keyWasDown = down;
}

namespace FeatureRegistry
{
	void Startup(uintptr_t gameAssemblyBase)
	{
		for (Feature* feature : Features())
		{
			feature->OnStartup(gameAssemblyBase);
		}
	}

	void Tick()
	{
		for (Feature* feature : Features())
		{
			feature->PollToggleKey();
			if (feature->enabled)
			{
				feature->OnTick();
			}
		}
	}

	void DrawMenu()
	{
		const char* currentCategory = nullptr;
		for (Feature* feature : Features())
		{
			if (feature->Category() != currentCategory)
			{
				if (currentCategory != nullptr)
				{
					ImGui::Separator();
				}
				ImGui::TextDisabled("%s", feature->Category());
				currentCategory = feature->Category();
			}

			ImGui::PushID(feature);
			ImGui::Checkbox(feature->Name(), &feature->enabled);
			if (feature->ToggleKey() != 0)
			{
				ImGui::SameLine();
				ImGui::TextDisabled("[F%d]", feature->ToggleKey() - VK_F1 + 1);
			}
			feature->OnMenu();
			ImGui::PopID();
		}
	}
}
