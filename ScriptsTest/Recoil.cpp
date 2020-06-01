#include <iostream>
#include <windows.h>
#include "Weapons.h"
#include "Vector2.h"
#include <winuser.h>
#include "Utilites.h"
#include "Menu.h"
#include "Recoil.h"
using namespace std;


bool Recoil::scriptActive = false;
float Recoil::sens = 1.0f;
float Recoil::fov = 90.0f;
int Recoil::selectedWeapon = 7;
int Recoil::selectedScope = 0;
int Recoil::selectedAttachment = 0;

std::string Recoil::weaponName(int selectedWeapon)
{
	switch (selectedWeapon)
	{
		case 0:
			return "None";
		case 1:
			return "Assault-Rifle"; //Good
		case 2:
			return "LR-3000"; //Good
		case 3:
			return "Thompson";
		case 4:
			return "Custom-SMG";
		case 5:
			return "M249";
		case 6:
			return "MP5";
		//Semi Auto Rifles
		case 7:
			return "Semi-Auto-Rifle";
		case 8:
			return "M39";
		//Pistols
		case 9:
			return "M92";
		case 10:
			return "Semi-Auto-Pistol";
		case 11:
			return "Python";
		case  12:
			return "Revolver";
		case 13:
			return "NailGun";
		default:
			return "Undefined";
	}
};
std::string Recoil::scopeName(int selectedScope)
{
	switch (selectedScope)
	{
	case 0:
		return "None";
		break;

	case 1:
		return "Holosight";
		break;

	case 2:
		return "Home-Made";
		break;

	case 3:
		return "8x";
		break;

	case 4:
		return "16x";
		break;

	default:
		return "None";
		break;
	}

};
std::string Recoil::attachmentName(int selectedAttachment) {
	switch (selectedAttachment)
	{
	case 0:
		return "None";
		break;

	case 1:
		return "Muzzle-Boost";
		break;

	case 2:
		return "Muzzle-Brake";
		break;

	case 3:
		return "Silencer";
		break;

	default:
		return "None";
		break;
	}
};

	void mainText()
{
	cout << "----------" << endl;
	cout << "Activated:" << Recoil::scriptActive << endl;
	cout << "----------" << endl;
	cout << "Weapon: "<< Recoil::weaponName(Recoil::selectedWeapon) << endl;
	cout << "Scope: "<< Recoil::scopeName(Recoil::selectedScope) << endl;
	cout << "Attachment: " << Recoil::attachmentName(Recoil::selectedAttachment) << endl;
	

};
	void keyHandler()
	{
		//Activate the scripts
		if (GetAsyncKeyState(VK_F2))
		{
			Sleep(100);
			Recoil::scriptActive = !Recoil::scriptActive;

			if (Recoil::scriptActive)
			{
				Beep(300, 100);
			}
			else
			{
				Beep(100, 100);
			}
			Utilities::clear();

			mainText();

		}

		// AK-47
		if (GetAsyncKeyState(VK_NUMPAD0))
		{
			if (Recoil::selectedWeapon != 1)
			{
				Recoil::selectedWeapon = 1;

				Beep(1000, 300);
				Sleep(100);
			}
			else
			{
				Recoil::selectedWeapon = 0;

				Beep(100, 500);
				Sleep(100);
			}
			Utilities::clear();

			mainText();

		}
		//Changing Attachments 
		if (GetAsyncKeyState(VK_LEFT) && Recoil::selectedAttachment > 0)
		{
			Beep(200, 100);
			Recoil::selectedAttachment--;
			Utilities::clear();

			mainText();
			Sleep(300);

		}
		else if (GetAsyncKeyState(VK_RIGHT) && Recoil::selectedAttachment < 3)
		{
			Beep(200, 100);
			Recoil::selectedAttachment++;
			Utilities::clear();

			mainText();
			Sleep(300);
		}

		//Changing Scopes
		if (GetAsyncKeyState(VK_UP) && Recoil::selectedScope > 0)
		{
			Beep(200, 100);
			Recoil::selectedScope--;
			Utilities::clear();
			mainText();

			Sleep(300);

		}
		else if (GetAsyncKeyState(VK_DOWN) && Recoil::selectedScope < 4)
		{
			Beep(200, 100);
			Recoil::selectedScope++;
			Utilities::clear();

			mainText();
			Sleep(300);
		}

	}
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
	void smoothRecoil(float x, float y, float animationTime)
	{
		//Creating a new timer counting elapsed time
		Timer timer;
		//Creating two different vectors one inheriting from the method, the other one returning to 0
		Math::Vector2 targetMove = { x, y };
		Math::Vector2 totalMoved = { 0.0f, 0.0f };



		while (timer.Elapsed() < animationTime)
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
	void Recoil::calculations()
	{
		//for (;;)
		//	{
		
		
			keyHandler();

			//While Left and Right mouse buttons  && weapon is selected && scripts are active 
			while ((GetAsyncKeyState(1) & 0x8000) && (GetAsyncKeyState(2) & 0x8000 && selectedWeapon != -1 && scriptActive == true))
			{
				//Do as many times as the amount of ammo
				for ( int i = 0; i < weaponAmmo(selectedWeapon); i++)
				{
					//If either of mouse buttons is not pressed stop the code.
					if (!(GetAsyncKeyState(1) & 0x8000) || !(GetAsyncKeyState(2) & 0x8000))
					{
						break;
					}

					Math::Vector2 delta;
					//if there is not more ammunition stop the code to prevent weird recoils
					if (i == weaponAmmo(selectedWeapon) - 1)
					{
						SleepEx(1, false);
						break;
						
					}
					else
					{
						//Sets the value to change of delta between current and previous shot.
						delta.x = weaponDeltaX(selectedWeapon)[i + 1] - weaponDeltaX(selectedWeapon)[i];
						delta.y = weaponDeltaY(selectedWeapon)[i + 1] - weaponDeltaY(selectedWeapon)[i];
					}
					//Used to calculate the FOV and SENS multiplier 
					 float multiplier = -0.030f * (sens * 3.0f) * (fov / 100.0f);
					
					if(selectedWeapon >= 3 && selectedWeapon <=4)
					{
						 multiplier = -0.0335f * (sens * 3.0f) * (fov / 100.0f);
					}
					if (selectedWeapon == 5)
					{
						multiplier = -0.053f * (sens * 3.0f) * (fov / 100.0f);
					}
					if(selectedWeapon==7)
					{
						multiplier = -0.0600f * (sens * 3.0f) * (fov / 100.0f);
					}


					//Actual Pixel values | No-Recoil works with these however no smoothing
					float x = ((delta.x / multiplier) * scope(selectedScope)) * attatchment(selectedAttachment)[0];
					float y = ((delta.y / multiplier) * scope(selectedScope)) * attatchment(selectedAttachment)[0];

					//The time it takes for the gun to "Jump" (Unsure about this one)
					const float animationTime = (sqrt((delta.x * delta.x) + (delta.y * delta.y)) / 0.02f);



					//Runs the function responsible for recoil movement
					smoothRecoil(x, y, animationTime);
					//if there is a negative weapon time, go to sleep
					if (weaponTime(selectedWeapon) * attatchment(selectedAttachment)[1] - animationTime > 0.0f) { SleepEx(static_cast<int>((weaponTime(selectedWeapon) * attatchment(selectedAttachment)[1]) - animationTime), false); }
				}
			}
			
		//}
	}

	void gameSettings()
	{
		Utilities::clear();
		cout << "Sensitivity: ";
		cin >> Recoil::sens;
			cout << "\nFOV: ";
		cin >> Recoil::fov;
	}
	int main()
	{

		mainText();
		
		//starts threads
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Menu::MenuImGui(), 0, 0, 0);
		//CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Recoil::calculations(), 0, 0, 0);
		

		return 0;
	}


