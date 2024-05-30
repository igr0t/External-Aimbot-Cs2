#include "aimbot.h"
#include "offsets.h"
#include "../external-cheat-base/math/vector.h"
#include "../external-cheat-base/memory/memory.h"
#include <iostream>
#include "cmath"
#include <TlHelp32.h>
#include <Windows.h>

float aimbot::distance(vec3 p1, vec3 p2) {
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2));
}
void aimbot::frame() {
	uintptr_t entityList = VARS::memRead<uintptr_t>(VARS::baseAddress + OFFSETS::offsets::client_dll::dwEntityList);
	if (!entityList)
		return;

	uintptr_t localPlayerPawn = VARS::memRead<uintptr_t>(VARS::baseAddress + OFFSETS::offsets::client_dll::dwLocalPlayerPawn);
	if (!localPlayerPawn)
		return;
	BYTE team = VARS::memRead<BYTE>(localPlayerPawn + client_dll::schemas::client_dll::C_BaseEntity::m_iTeamNum);
	vec3 localEyePos = VARS::memRead<vec3>(localPlayerPawn + OFFSETS::offsets::client_dll::m_vOldOrigin);
	VARS::memRead<vec3>(localPlayerPawn + OFFSETS::offsets::client_dll::m_vecViewOffset);
	
	float closet_distance = -1;
	vec3 enemyPos;

	for (int i = 0; i < 32; i++) {
		uintptr_t listEntry = VARS::memRead<uintptr_t>(entityList + ((8 * (i & 0x7ff) >> 9) + 16));
		if (!listEntry) continue;

		uintptr_t entityController = VARS::memRead<uintptr_t>(listEntry + 120 * (i & 0x1ff));
		if (!entityController) continue;

		uintptr_t entityControlerPawn = VARS::memRead<uintptr_t>(entityController + OFFSETS::offsets::client_dll::m_hPlayerPawn);
		if (!entityController) continue;

		uintptr_t entityPawn = VARS::memRead<uintptr_t>(listEntry + 120 * (entityControlerPawn & 0x1ff));
		if (!entityPawn) continue;
		
		if (team == VARS::memRead<BYTE>(entityPawn + OFFSETS::offsets::client_dll::m_iHealth) <= 0);
		continue;

		vec3 entityEyePos = VARS::memRead<vec3>(entityPawn + OFFSETS::offsets::client_dll::m_vOldOrigin) +
			VARS::memRead<vec3>(entityPawn + OFFSETS::offsets::client_dll::m_vecViewOffset);
		
		float current_distance = distance(localEyePos, entityEyePos);

		if (closet_distance < 0 || current_distance < closet_distance) {
			closet_distance = current_distance;
			enemyPos = entityEyePos;
		}
	}
	vec3 relativeAngle = (enemyPos - localEyePos).RelativeAngle();
	VARS::memWrite<vec3>(VARS::baseAddress + OFFSETS::offsets::client_dll::dwViewAngles, relativeAngle);
}