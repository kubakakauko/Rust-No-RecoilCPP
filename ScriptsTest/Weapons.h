#pragma once

namespace AssaultRifle{

	int AssaultRifleAmmo= 30;
	float AssaultRifleX[] = {0.0f, 1.390706f, 1.176434f, 3.387171f, 5.087049f, 5.094189f, 4.426013f, 3.250455f, 1.73545f, 0.04893398f, -1.641158f, -3.166891f, -4.360331f, -5.053545f, -5.090651f, -4.489915f, -3.382552f, -1.899585f, -0.1720295f, 1.669086f, 3.492748f, 5.16793f, 6.563614f, 7.548776f, 7.992399f, 7.512226f, 6.063792f, 4.117367f, 2.143932f, 0.6144824f};
	float AssaultRifleY[] = {0.0f, -2.003941f, -3.844176f, -5.516686f, -7.017456f, -8.342467f, -9.487704f, -10.44915f, -11.22279f, -11.8046f, -12.19056f, -12.58713f, -13.32077f, -14.32128f, -15.51103f, -16.81242f, -18.14783f, -19.43966f, -20.61031f, -21.58213f, -22.27755f, -22.61893f, -22.81778f, -23.37389f, -24.21139f, -25.23734f, -26.35886f, -27.48302f, -28.51692f, -29.36766f};
    float AssaultRifleTimes = 1000.0f / (450.0f / 60.0f);
}

//This namespace can be used when there is nothing selected
namespace defaultNothingNamespace
{
	float defaultNothing[] = { 0, 0 };
	float defaultNothingTimes = 0.0f;
}


