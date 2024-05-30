#pragma once
#include "client.h"
#include "offsets.h"
#include "memory.h"
#include "../external-cheat-base/math/vector.h"

namespace aimbot {
	inline uintptr_t modulebase;
	inline uintptr_t procId;

	float distance(vec3 p1, vec3 p2);
	void frame();
}