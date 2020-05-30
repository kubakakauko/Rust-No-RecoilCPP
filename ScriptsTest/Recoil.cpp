#include "Recoil.h"

#include <iostream>
#include <windows.h>
#include "Weapons.h"
#include "Vector2.h"
#include <winuser.h>
#include "Utilites.h"
#include "Menu.h"
using namespace std;



	void Recoil::keyHandler()
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
			names::mainText();

		}

		// AK-47
		if (GetAsyncKeyState(VK_NUMPAD0))
		{
			if (selectedWeapon != 1)
			{
				selectedWeapon = 1;

				Beep(1000, 300);
				Sleep(100);
			}
			else
			{
				selectedWeapon = 0;

				Beep(100, 500);
				Sleep(100);
			}
			names::mainText();

		}
		//Changing Attachments 
		if (GetAsyncKeyState(VK_LEFT) && selectedAttachment > 0)
		{
			Beep(200, 100);
			selectedAttachment--;

			names::mainText();
			Sleep(300);

		}
		else if (GetAsyncKeyState(VK_RIGHT) && selectedAttachment < 3)
		{
			Beep(200, 100);
			selectedAttachment++;

			names::mainText();
			Sleep(300);
		}

		//Changing Scopes
		if (GetAsyncKeyState(VK_UP) && selectedScope > 0)
		{
			Beep(200, 100);
			selectedScope--;

			names::mainText();

			Sleep(300);

		}
		else if (GetAsyncKeyState(VK_DOWN) && selectedScope < 4)
		{
			Beep(200, 100);
			selectedScope++;

			names::mainText();
			Sleep(300);
		}

	}


	void Recoil::mouse_move(int x, int y) //Mouse Movement (For now takes integers but want to be reprogrammed to take in Vector2)
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


	void Recoil::smoothRecoil(float x, float y, float animationTime)
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
		//Forever
	//for(;;)
	//{
		Recoil::keyHandler();

		//While Left and Right mouse buttons  && weapon is selected && scripts are active 
		if((GetAsyncKeyState(1) & 0x8000) && (GetAsyncKeyState(2) & 0x8000 && selectedWeapon != -1 && scriptActive == true))
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
				if (i == weaponAmmo(selectedWeapon) - 1)
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
				float x = ((delta.x / multiplier) * scope(selectedScope)) * attatchment(selectedAttachment)[0];
				float y = ((delta.y / multiplier) * scope(selectedScope)) * attatchment(selectedAttachment)[0];

				//The time it takes for the gun to "Jump" (Unsure about this one)
				float animationTime = (sqrt((delta.x * delta.x) + (delta.y * delta.y)) / 0.02f);



				//Runs the function responsible for recoil movement
				smoothRecoil(x, y, animationTime);
				//if there is a negative weapon time, go to sleep
				if (weaponTime(selectedWeapon) * attatchment(selectedAttachment)[1] - animationTime > 0.0f) { SleepEx(static_cast<int>((weaponTime(selectedWeapon) * attatchment(selectedAttachment)[1]) - animationTime), false); }
			}
		}
	//	}
	}
	void Recoil::gameSettings()
	{
		Utilities::clear();
		cout << "Sensitivity: ";
		cin >> sens;
		cout << "\nFOV: ";
		cin >> fov;
	}


	int main()
	{
		names::mainText();
		//gameSettings();


		//starts threads
		
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Menu::MenuImGui(), 0, 0, 0);


		return 0;
	}


