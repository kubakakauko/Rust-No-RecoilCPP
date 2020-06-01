#pragma once
#include <string>

class Recoil
{
private:


	public:
		static bool scriptActive;
		static float sens;
		static float fov;
		static int selectedWeapon;
		static int selectedScope;
		static int selectedAttachment;
	
	static void calculations();
	static std::string weaponName(int selectedWeapon);
	static std::string scopeName(int selectedScope);
	static std::string attachmentName(int selectedAttachment);
};
