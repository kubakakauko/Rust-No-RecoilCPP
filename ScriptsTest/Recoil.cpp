#include <Windows.h>
#include <iostream>
#include <string>
#include "Weapons.h"
#include <array>
#include "Vector2.h"


using namespace std;
using namespace AssaultRifle;
using namespace defaultNothingNamespace;
using namespace classes;


#pragma region Variables
double sens = 1.0f;
double fov = 90.0f;
int selectedWeapon = -1; //Checks what weapon is selected | -1 none | 0 AK |
bool scriptActive = false;
#pragma endregion

void mouse_move(Math::Vector2 vector2) //Mouse Movement (For now takes integers but want to be reprogrammed to take in Vector2)
{
	INPUT input;
	input.type = INPUT_MOUSE;
	input.mi.mouseData = 0;
	input.mi.time = 0;
	input.mi.dx = (int) vector2.x;
	input.mi.dy = (int) vector2.y;
	input.mi.dwFlags = MOUSEEVENTF_MOVE;
	SendInput(1, &input, sizeof(input));
}
int KeyHandler() // Determines if the script was activated.
{
	for(;;)
	{
		Sleep(10);
		if (GetAsyncKeyState(VK_F2))
		{
			Sleep(100);
			scriptActive = !scriptActive;
			
			if(scriptActive) 
			{
				Beep(300, 200);
			}else
			{
				Beep(100, 200);
			}	
		}
		if (GetAsyncKeyState(VK_NUMPAD0) < 0) // AK-47
		{
			if(selectedWeapon != -1)
			{
				selectedWeapon = -1;
				Beep(100, 500);
				Sleep(200);
			}else
			{
				selectedWeapon = 0;
				Beep(1000, 300);
				Sleep(200);
			}
		}
		Sleep(200);
	}	
}

#pragma region Recoil Delta Return

float* weaponDeltaX(int selected)
{
	int s = selected;

	switch (s)
	{
		case 0:
			return AssaultRifleX;
			break;

		default:
			defaultNothing;
			break;
	}
}

float* weaponDeltaY(int selected)
{
	int s = selected;

	switch (s)
	{
	case 0:
		return AssaultRifleY;
		break;

	default:
		defaultNothing;
		break;
	}
}

float weaponTime(int selected)
{
	int s = selected;

	switch (s)
	{
	case 0:
		return AssaultRifleTimes;
		break;
		
	}
}
int weaponAmmo(int selected)
{
	int s = selected;
	switch (s)
	{
	case 0:
		return AssaultRifleAmmo;
		break;
		
	default:
		return 0;
	}
}
#pragma endregion Recoil Delta Return

void Recoil()
{
	while (true)
	{
		while ((GetAsyncKeyState(1) & 0x8000) && (GetAsyncKeyState(2) & 0x8000 && selectedWeapon != -1 && scriptActive == true))
		{
			
			for(int i=0; i < weaponAmmo(selectedWeapon); i++)
			{
				Timer timer;
				if (!(GetAsyncKeyState(1) & 0x8000) || !(GetAsyncKeyState(2) & 0x8000))
				{
					continue;
				}
				
				Math::Vector2 delta; delta.x = weaponDeltaX(selectedWeapon)[i + 1] - weaponDeltaX(selectedWeapon)[i]; delta.y = weaponDeltaY(selectedWeapon)[i + 1] - weaponDeltaY(selectedWeapon)[i];
				float multiplier = -0.03f * (sens * 3.0f) * (fov / 100.0f);
				Math::Vector2 px; px.x = delta.x / multiplier; px.y = delta.y / multiplier;
				Math::Vector2 totalMoved;

				float animationTime = sqrt((delta.x * delta.x) + (delta.x * delta.x))/0.02f;
				
				float elapsed = timer.Elapsed();

				cout << "AnimationTime:" << animationTime << " Elapsed: " << elapsed << endl;
				
				//Used to be start of while elapsed < animationTime
					float t = elapsed / animationTime;

					Math::Vector2 toMove = (px.Lerp(t) - totalMoved).Floor();

					mouse_move(toMove);
					//totalMoved += toMove;
					//mouse_move((px - totalMoved).Floor());
					SleepEx(weaponTime(selectedWeapon), false);
				//End of while
				

			}
			
			Sleep(1);
		}	
	}
}
void gameSettings()
{
	string sSensitivity;
	string sFov;
	

	cout << "Sensitivity: ";
	getline(cin, sSensitivity);
	cout  << endl << "FOV: ";
	getline(cin, sFov);

	sens = ::atof(sSensitivity.c_str());
	fov = ::atof(sFov.c_str());
	Clear();
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


	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Recoil, 0, 0, 0);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)KeyHandler, 0, 0, 0);

	for (;;)
	{
		Sleep(200);
	}

}