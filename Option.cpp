#include "Option.h"

// Attention: Function body is not in need for pur visual function.


VanillaOption::VanillaOption(IRCurve* _ircurve, VolCurve* _volcurve, double _dMaturity, double _dStrike, double _dividend, int _iNBStrike, bool _bCall)
	:ircurve(_ircurve),volcurve(_volcurve), dMaturity(_dMaturity), dStrike(_dStrike), dividend(_dividend), iNBStrike(_iNBStrike), bCall(_bCall){}


double VanillaOption::payoff(double spot) const
{
	if(bCall)	//payoff =max(S-K,0)
	{
		return std::max(spot-VanillaOption::dStrike, 0.0);
	}
	else		//payoff =max(K-S,0)
	{
		return std::max(VanillaOption::dStrike-spot, 0.0);
	}
}

Curve* VanillaOption::getIR()
{
	return ircurve;
}
	

Curve* VanillaOption::getVol()
{
	return volcurve;
}

double VanillaOption::getMaturity()
{
	return dMaturity;
}

double VanillaOption::getStrike()
{
	return dStrike;
}

double VanillaOption::getDiv()
{
	return dividend;
}

bool VanillaOption::isCall()
{
	return bCall;
}
