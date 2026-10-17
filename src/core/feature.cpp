#include "pch.h"
#include "core/feature.h"

namespace
{
	std::vector<Feature*>& Features()
	{
		static std::vector<Feature*> instance;
		return instance;
	}

	char s_filter[128] = "";

	bool ContainsIgnoreCase(const char* haystack, const char* needle)
	{
		if (!haystack || !needle) return false;
		std::string h(haystack), n(needle);
		std::transform(h.begin(), h.end(), h.begin(), ::tolower);
		std::transform(n.begin(), n.end(), n.begin(), ::tolower);
		return h.find(n) != std::string::npos;
	}

	bool Visible(const Feature* feature)
	{
		if (s_filter[0] == '\0') return true;
		return ContainsIgnoreCase(feature->Name(), s_filter) ||
			ContainsIgnoreCase(feature->Category(), s_filter);
	}

	bool SameCategory(const char* a, const char* b)
	{
		if (!a || !b) return false;
		return std::strcmp(a, b) == 0;
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
			bool wasEnabled = feature->enabled;
			feature->PollToggleKey();

			if (!wasEnabled && feature->enabled) feature->OnEnable();
			if (wasEnabled && !feature->enabled) feature->OnDisable();

			if (feature->enabled)
			{
				feature->OnTick();
			}
		}
	}

	void DrawMenu()
	{
		ImGui::SetNextItemWidth(260.0f);
		ImGui::InputTextWithHint("##filter", "Search features...", s_filter, sizeof(s_filter));
		ImGui::Separator();

		// Collect the distinct categories in registration order, then draw each
		// group so that features sharing a category name always sit together.
		std::vector<const char*> categories;
		for (Feature* feature : Features())
		{
			if (!Visible(feature)) continue;
			bool known = false;
			for (const char* c : categories)
			{
				if (SameCategory(c, feature->Category())) { known = true; break; }
			}
			if (!known) categories.push_back(feature->Category());
		}

		for (const char* category : categories)
		{
			bool open = ImGui::TreeNodeEx(category, ImGuiTreeNodeFlags_DefaultOpen);
			if (!open) continue;

			for (Feature* feature : Features())
			{
				if (!Visible(feature)) continue;
				if (!SameCategory(feature->Category(), category)) continue;

				ImGui::PushID(feature);

				if (feature->IsAction())
				{
					if (ImGui::Button(feature->Name()))
					{
						feature->OnAction();
					}
				}
				else
				{
					ImGui::Checkbox(feature->Name(), &feature->enabled);
					if (feature->ToggleKey() != 0)
					{
						ImGui::SameLine();
						ImGui::TextDisabled("[F%d]", feature->ToggleKey() - VK_F1 + 1);
					}
				}

				feature->OnMenu();
				ImGui::PopID();
			}

			ImGui::TreePop();
		}
	}
}
