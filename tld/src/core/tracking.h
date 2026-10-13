#pragma once

#include "core/object_list.h"

namespace Tracking
{
	const ObjectList<void*>& AiList();
	const ObjectList<void*>& GearList();

	void Install();
}
