#pragma once
#include "Option.h"



class BS_PDE
{
private:
	VanillaOption* vanillaCall;	//class pointor makes it easy to call virtual function
public:
	BS_PDE(void){};
	BS_PDE(VanillaOption* _vanillaCall);
	~BS_PDE(void){};

	double coeff_DerivTime(double time, double spot);		//Coeff for time derivative Item			coeff_DerivTime=1
	double coeff_DerivSpotFirst(double time, double spot);	//Coeff for first spot derivative Item		coeff_DerivSpotFirst = (r-q)S
	double coeff_DerivSpotSecond(double time, double spot);	//Coeff for second time derivative Item		coeff_DerivSpotSecond = 1/2*sigma*sigma*spot*spot
	double coeff_DerivSpotZero(double time, double spot);	//Coeff for non-derivative Item				coeff_DerivSpotZero = -r	

	VanillaOption* getVanillaOption(void);
};

