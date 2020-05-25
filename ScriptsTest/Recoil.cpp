#include "imGui/imgui.h"
#include "imGui/imgui_impl_dx9.h"
#include "imGui/imgui_impl_win32.h"
#include <d3d9.h>

#include <iostream>
#include <string>
#include "Weapons.h"
#include "Vector2.h"
#include <array>
#include "Utilites.h"



using namespace std;
using namespace AssaultRifle;

#pragma region Variables
float sens = 1.0f;
float fov = 90.0f;
int selectedWeapon = -1; //Checks what weapon is selected | -1 none | 0 AK |
bool scriptActive = false;

int selectedScope;
int selectedBarrel;
#pragma endregion
void mouse_move(int x, int y) //Mouse Movement (For now takes integers but want to be reprogrammed to take in Vector2)
{
	INPUT input;
	input.type = INPUT_MOUSE;
	input.mi.mouseData = 0;
	input.mi.time = 0;
	input.mi.dx = x;
	input.mi.dy = y;
	input.mi.dwFlags = MOUSEEVENTF_MOVE;
	SendInput(1, &input, sizeof(input));
}
void KeyHandler()  // Determines if the script was activated.
{
	
		//Activate the scripts
		if (GetAsyncKeyState(VK_F2))
		{
			Sleep(100);
			scriptActive = !scriptActive;

			if (scriptActive)
			{
				Beep(300, 100);
			}
			else
			{
				Beep(100, 100);
			}
		}

		// AK-47
		if (GetAsyncKeyState(VK_NUMPAD0) < 0)
		{
			if (selectedWeapon != -1)
			{
				selectedWeapon = -1;
				Beep(100, 500);
				Sleep(100);
			}
			else
			{
				selectedWeapon = 0;
				Beep(1000, 300);
				Sleep(100);
			}
		}
	
}


float* weaponDeltaX(int selected)
{
	switch (selected)
	{
		case 0:
			return AssaultRifleX;
			break;

		default:
			return 0;
			break;
	}
}
float* weaponDeltaY(int selected)
{
	switch (selected)
	{
	case 0:
		return AssaultRifleY;
		break;

	default:
		return 0;
		break;
	}
}
float weaponTime(int selected)
{
	switch (selected)
	{
	case 0:
		return AssaultRifleTimes;
		break;
		
	}
}
int weaponAmmo(int selected)
{
	switch (selected)
	{
	case 0:
		return AssaultRifleAmmo;
		break;
		
	default:
		return 0;
	}
}

float* attatchment(int selectedAttachment)
{
	float barrel[] = { 0, 0 };
	
	switch (selectedBarrel)
	{
	case 0:
		return (barrel);
	case 1:
		return;
	}
	
}

float scope(int selectedScope)
{
	
}
void smoothRecoil(float x, float y, float animationTime)
{
	//Creating a new timer counting elapsed time
	Timer timer;
	//Creating two different vectors one inheriting from the method, the other one returning to 0
	Math::Vector2 targetMove = { x, y };
	Math::Vector2 totalMoved = { 0.0f, 0.0f };


	
	while(timer.Elapsed() < animationTime)
	{
		float t = timer.Elapsed() / animationTime;

		Math::Vector2 moveTo = (targetMove.Lerp(t) - totalMoved).Floor();

		mouse_move(static_cast<int>(moveTo.x), static_cast<int>(moveTo.y));

		totalMoved += moveTo;

		SleepEx(1, false);

		
	}
	
	Math::Vector2 extraMove = (targetMove - totalMoved).Floor();
	mouse_move(static_cast<int>(extraMove.x), static_cast<int>(extraMove.y));
}

void calculations()
{
	//Forever
	for(;;)
	{
		KeyHandler();
		//While Left and Right mouse buttons  && weapon is selected && scripts are active 
		while ((GetAsyncKeyState(1) & 0x8000) && (GetAsyncKeyState(2) & 0x8000 && selectedWeapon != -1 && scriptActive == true))
		{
			//Do as many times as the amount of ammo
			for (int i = 0; i < weaponAmmo(selectedWeapon); i++)
			{
				//If either of mouse buttons is not pressed stop the code.
				if (!(GetAsyncKeyState(1) & 0x8000) || !(GetAsyncKeyState(2) & 0x8000))
				{
					break;
				}
				
				Math::Vector2 delta;
				//if there is not more ammunition stop the code to prevent weird recoils
				if(i == weaponAmmo(selectedWeapon) - 1)
				{
					break;
				}
				else
				{
					//Sets the value to change of delta between current and previous shot.
					delta.x = weaponDeltaX(selectedWeapon)[i + 1] - weaponDeltaX(selectedWeapon)[i];
					delta.y = weaponDeltaY(selectedWeapon)[i + 1] - weaponDeltaY(selectedWeapon)[i];
				}
				
				
				//Used to calculate the FOV and SENS multiplier 
				float multiplier = -0.03f * (sens * 3.0f) * (fov / 100.0f);


				//Actual Pixel values | No-Recoil works with these however no smoothing
				float x = delta.x / multiplier;
				float y = delta.y / multiplier;

				//The time it takes for the gun to "Jump" (Unsure about this one)
				float animationTime = (sqrt((delta.x * delta.x) + (delta.y * delta.y)) / 0.02f);



				//Runs the function responsible for recoil movement
				smoothRecoil(x, y, animationTime);
				//if there is a negative weapon time, go to sleep
				if (weaponTime(selectedWeapon) - animationTime > 0.0f) { SleepEx(static_cast<int>(weaponTime(selectedWeapon) - animationTime), false); }
			}
		}
	}
}


void drawing()
{

}
void gameSettings()
{

	Utilities::clear();
	std::string sSensitivity;
	std::string sFov;


	std::cout << "Sensitivity: ";
	getline(std::cin, sSensitivity);
	std::cout << std::endl << "FOV: ";
	getline(std::cin, sFov);

	fov = ::atof(sSensitivity.c_str());
	sens = ::atof(sFov.c_str());
	Utilities::clear();
}
void main()
{
	gameSettings();
	cout << "Welcome to COMBO-X\n";
	cout << "------------------\n";
	cout << "AK-47    = NUMPAD_0\n";
	cout << "LR-300   = 2\n";
	cout << "SAR      = 3\n";
	cout << "THOMPSON = 4\n\n\n";

	//starts threads
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)calculations, 0, 0, 0);

	//Puts the thead to sleep to decrease CPU load
	for (;;)
	{
		Sleep(50);
	}

}
