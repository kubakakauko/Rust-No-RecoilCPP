#pragma once

bool scriptActive = false;
float sens = 1.0f;
float fov = 90.0f;
int selectedWeapon = 0;
int selectedScope = 0;
int selectedAttachment = 0;


#pragma region Values
namespace assaultRifle{

	const int AssaultRifleAmmo= 30;
	float AssaultRifleX[] = {0.0f, 1.390706f, 1.176434f, 3.387171f, 5.087049f, 5.094189f, 4.426013f, 3.250455f, 1.73545f, 0.04893398f, -1.641158f, -3.166891f, -4.360331f, -5.053545f, -5.090651f, -4.489915f, -3.382552f, -1.899585f, -0.1720295f, 1.669086f, 3.492748f, 5.16793f, 6.563614f, 7.548776f, 7.992399f, 7.512226f, 6.063792f, 4.117367f, 2.143932f, 0.6144824f};
	float AssaultRifleY[] = {0.0f, -2.003941f, -3.844176f, -5.516686f, -7.017456f, -8.342467f, -9.487704f, -10.44915f, -11.22279f, -11.8046f, -12.19056f, -12.58713f, -13.32077f, -14.32128f, -15.51103f, -16.81242f, -18.14783f, -19.43966f, -20.61031f, -21.58213f, -22.27755f, -22.61893f, -22.81778f, -23.37389f, -24.21139f, -25.23734f, -26.35886f, -27.48302f, -28.51692f, -29.36766f};
    float AssaultRifleTimes = 1000.0f / (450.0f / 60.0f);
}

namespace LR300{
	const int LR300Ammo = 30;
	float lr300x[] = { 0.09836517f, 0.3469534f, 0.7512205f, 1.326888f, 1.958069f, 2.527623f, 2.918412f, 3.007762f, 2.641919f, 1.950645f, 1.144313f, 0.4332969f, 0.02797037f, 0.04550591f, 0.2685102f, 0.6408804f, 1.127565f, 1.693516f, 2.303682f, 2.923013f, 3.516459f, 4.04897f, 4.485496f, 4.790986f, 4.92656f, 4.387823f, 3.16274f, 1.714368f, 0.5057687f };
	float lr300y[] = { -1.004928f, -2.248523f, -3.575346f, -4.829963f, -5.858609f, -6.687347f, -7.399671f, -8.005643f, -8.515327f, -8.938788f, -9.286088f, -9.567291f, -9.793953f, -9.992137f, -10.17017f, -10.33037f, -10.47505f, -10.60654f, -10.72716f, -10.83923f, -10.94506f, -11.04699f, -11.14732f, -11.24838f, -11.35249f, -11.46197f, -11.57914f, -11.70632f, -11.84584f };
	float lr300Times = 1000.0f / (500.0f / 60.0f);
}

namespace Thompson
{
	const int thompsonAmmo = 20;
	float thompsonX[] = { 0.7399524f, 1.011324f, 0.8437103f, 0.3127854f, -0.3338249f, -0.8446444f, -0.9689822f, -0.6067921f, 0.01632042f, 0.6324611f, 0.9737339f, 0.8438975f, 0.3745165f, -0.2263549f, -0.7514643f, -0.9935587f, -0.862007f, -0.5397906f, -0.1962007f };
	float thompsonY[] = { -1.565956f, -3.109221f, -4.587918f, -5.960169f, -7.184096f, -8.217823f, -9.093672f, -9.877484f, -10.57721f, -11.20081f, -11.75624f, -12.25145f, -12.6944f, -13.09305f, -13.45534f, -13.78924f, -14.1027f, -14.40368f, -14.70013f };
	float thomposnTimes = 1000.0f / (462.0f / 60.0f);

}
namespace CustomSmg
{
	const int customSmgAmmo = 30;
	float customSmgX[]= { 0.6512542f, 0.9681615f, 0.9872047f, 0.6951124f, 0.2062594f, -0.3338249f, -0.7796098f, -0.9855663f, -0.8372459f, -0.4148501f, 0.1267298f, 0.6324611f, 0.9473124f, 0.9353167f, 0.6385964f, 0.1786009f, -0.3247314f, -0.7514643f, -0.9816588f, -0.9354943f, -0.714118f, -0.4193012f, -0.1487077f };
	float customSmgY[] = { -1.305408f, -2.599905f, -3.859258f, -5.05923f, -6.175588f, -7.184096f, -8.060521f, -8.812342f, -9.496586f, -10.11968f, -10.68622f, -11.20081f, -11.66807f, -12.09258f, -12.47896f, -12.83181f, -13.15574f, -13.45534f, -13.73522f, -13.99999f, -14.25425f, -14.5026f, -14.74965f };
	float customSmgTimes = 1000.0f / (600.0f / 60.0f);
}
namespace M249
{
	const int m249Ammo = 100;
	float m249X[] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, };
	float m249Y[] = { -2.75f, -5.5f, -8.25f, -11.0f, -13.75f, -16.5f, -19.25f, -22.0f, -24.75f, -27.5f, -30.25f, -33.0f, -35.75f, -38.5f, -41.25f, -44.0f, -46.75f, -49.5f, -52.25f, -55.0f, -57.75f, -60.5f, -63.25f, -66.0f, -68.75f, -71.5f, -74.25f, -77.0f, -79.75f, -82.5f, -85.25f, -88.0f, -90.75f, -93.5f, -96.25f, -99.0f, -101.75f, -104.5f, -107.25f, -110.0f, -112.75f, -115.5f, -118.25f, -121.0f, -123.75f, -126.5f, -129.25f, -132.0f, -134.75f, -137.5f, -140.25f, -143.0f, -145.75f, -148.5f, -151.25f, -154.0f, -156.75f, -159.5f, -162.25f, -165.0f, -167.75f, -170.5f, -173.25f, -176.0f, -178.75f, -181.5f, -184.25f, -187.0f, -189.75f, -192.5f, -195.25f, -198.0f, -200.75f, -203.5f, -206.25f, -209.0f, -211.75f, -214.5f, -217.25f, -220.0f, -222.75f, -225.5f, -228.25f, -231.0f, -233.75f, -236.5f, -239.25f, -242.0f, -244.75f, -247.5f, -250.25f, -253.0f, -255.75f, -258.5f, -261.25f, -264.0f, -266.75f, -269.5f, -272.25f, -275.0f, -277.75f };
	float m249Times = 1000.0f / (500.0f / 60.0f);
}
namespace MP5
{
	const int mp5Ammo = 30;
	float mp5X[] = { 0.0f, 0.0f, -2.992364E-14f, -0.5103882f, -1.687297f, -2.999344f, -3.915147f, -3.948318f, -3.224567f, -2.228431f, -1.438722f, -1.288914f, -1.598686f, -2.154637f, -2.826861f, -3.485454f, -4.000507f, -4.242117f, -4.184897f, -3.969568f, -3.629241f, -3.194572f, -2.696223f, -2.16485f, -1.631112f, -1.125667f, -0.6791761f, -0.3222946f, -0.08568263f };
	float mp5Y[] = { -0.8688382f, -2.042219f, -3.370441f, -4.703804f, -5.892606f, -6.787148f, -7.311441f, -7.742482f, -8.127406f, -8.468721f, -8.768936f, -9.03056f, -9.2561f, -9.448063f, -9.60896f, -9.741299f, -9.847586f, -9.930332f, -9.992043f, -10.03523f, -10.0624f, -10.07606f, -10.07872f, -10.07288f, -10.06106f, -10.04577f, -10.02951f, -10.01479f, -10.00412f};
	float mp5Times = 1000.0f / (600.0f / 60.0f);
}

namespace M39
{
	const int m39Ammo = 20;
	float m39X[] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
	float m39Y[] = { -3.5f, -7.0f, -10.5f, -14.0f, -17.5f, -21.0f, -24.5f, -28.0f, -31.5f, -35.0f, -38.5f, -42.0f, -45.5f, -49.0f, -52.5f, -56.0f };
	float m39Times = 1000.0f / (300.0f / 60.0f);

}

namespace SAR // capacity 16 rpm 343
{
	const int sarAmmo = 16;
	float sarX[] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	float sarY[] = { -3.25f, -6.5f, -9.75f, -13.0f, -16.25f, -19.5f, -22.75f, -26.0f, -29.25f, -32.5f, -35.75f, -39.0f, -42.25f, -45.5f, -48.75f, -52.0f };
	float sarTimes = 1000.0f / (343.0f / 60.0f);
}
namespace M92 //pistol capacity 15 400rpm
{
	const int m92Ammo = 15;
	float m92X[] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	float m92Y[] = { -3.75f, -7.5f, -11.25f, -15.0f, -18.75f, -22.5f, -26.25f, -30.0f, -33.75f, -37.5f, -41.25f, -45.0f, -48.75f, -52.5f, -56.25f, -60.0f };
	float m92Times = 1000.0f / (400.0f / 60.0f);
}
namespace SAP //capacity 10 rpm 400
{
	const int sapAmmo = 10;
	float sapX[] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	float sapY[] = { -4.0f, -8.0f, -12.0f, -16.0f, -20.0f, -24.0f, -28.0f, -32.0f, -36.0f, -40.0f, -44.0f };
	float sapTimes = 1000.0f / (400.0f / 60.0f);
}
namespace python // capacity 6 and rpm of 400
{
	const int pythonAmmo = 6;
	float pythonX[] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	float pythonY[] = { -8.0f, -16.0f, -24.0f, -32.0f, -40.0f, -48.0f, -56.0f };
	float pythonTimes = 1000.0f / (400.0f / 60.0f);
}
namespace revolver//capacity 8 rpm 343
{
	const int revolverAmmo = 8;
	float revolverX[] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	float revolverY[] = { -2.5f, -5.0f, -7.5f, -10.0f, -12.5f, -15.0f, -17.5f, -20.0f, -22.5f };
	float revolverTimes = 1000.0f / (343.0f / 60.0f);
}
namespace nailGun//capacity 16 rpm 400
{
	const int nailAmmo = 16;
	float nailX[] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	float nailY[] = { -2.5f, -5.0f, -7.5f, -10.0f, -12.5f, -15.0f, -17.5f, -20.0f, -22.5f, -25.0f, -27.5f, -30.0f, -32.5f, -35.0f, -37.5f, -40.0f, -42.5f };
	float nailTimes = 1000.0f / (400.0f / 60.0f);
}
#pragma endregion 

float* weaponDeltaX(int selected)
{
	switch (selected)
	{
	case 1:
		return assaultRifle::AssaultRifleX;
		break;

	default:
		return 0;
	}
}
float* weaponDeltaY(int selected)
{
	switch (selected)
	{
	case 1:
		return assaultRifle::AssaultRifleY;
		
	default:
		return 0;
	}
}
float weaponTime(int selected)
{
	switch (selected)
	{
		case 1:
			return assaultRifle::AssaultRifleTimes;
			
		default:
			return 1;
	}
}
int weaponAmmo(int selected)
{
	switch (selected)
	{
		case 1:
			return assaultRifle::AssaultRifleAmmo;
			
		default:
			return 0;
	}
}

float* attatchment(int selectedAttachment)
{
	//Returning recoil:fireRate Multipliers 
	float muzzleBoost[] = { 1.0f , 0.9f };
	float muzzleBrake[] = { 0.5f, 1.0f };
	float silencer[] = { 0.8f, 1.0f };
	float nothing[] = { 1.0, 1.0f };

	switch (selectedAttachment)
	{
	case 0:
		return nothing;
		break;

	case 1:
		return muzzleBoost;
		break;

	case 2:
		return muzzleBrake;
		break;

	case 3:
		return silencer;
		break;

	default:
		return nothing;
		break;
	}

}
float scope(int selectedScope)
{
	const float scope8x = 3.83721f;
	const float scope16x = 7.65116f;
	const float holosight = 1.18605f;
	const float homeMade = 0.8f;

	switch (selectedScope)
	{
	case 0:
		return 1;
		break;

	case 1:
		return holosight;
		break;

	case 2:
		return homeMade;
		break;

	case 3:
		return scope8x;
		break;

	case 4:
		return scope16x;
		break;

	default:
		return 1;
		break;
	}
}



