#include "BS_PDE.h"

BS_PDE::BS_PDE(VanillaOption* _vanillaCall) :vanillaCall(_vanillaCall){}

double BS_PDE::coeff_DerivTime(double time, double spot)		//Coeff for time derivative Item			coeff_DerivTime=1
{
	return 1.0;
}

double BS_PDE::coeff_DerivSpotFirst(double time, double spot)	//Coeff for first spot derivative Item		coeff_DerivSpotFirst = (r-q)S
{
	double r = vanillaCall->getIR()->GetParam(time);
	double q = vanillaCall->getDiv();
	return (r-q)*spot;
}

double BS_PDE::coeff_DerivSpotSecond(double time, double spot)	//Coeff for second time derivative Item		coeff_DerivSpotSecond = 1/2*sigma*sigma*spot*spot
{
	double sigma = vanillaCall->getVol()->GetParam(time);
	return 0.5*sigma*sigma*spot*spot;
}

double BS_PDE::coeff_DerivSpotZero(double time, double spot)	//Coeff for non-derivative Item				coeff_DerivSpotZero = -r	
{
	double r = vanillaCall->getIR()->GetParam(time);
	return (-1)*r;
}

VanillaOption* BS_PDE::getVanillaOption(void)
{
	return vanillaCall;
}