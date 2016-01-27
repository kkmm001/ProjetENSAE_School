#pragma once
#ifndef OPTION_H
#define OPTION_H

#include "Curve.h"

class Option
{
public:
	Option(void){};
	virtual ~Option(void){};
	double virtual payoff(double spot) const = 0;
};

class VanillaOption:public Option
{
private:
	Curve *ircurve;		
	Curve *volcurve;	
	double dMaturity;	//T should be annulized.
	double dStrike;
	double dividend;
	int iNBStrike;
	bool bCall;

public:
	VanillaOption(void){};
	VanillaOption(IRCurve* _ircurve, VolCurve* _volcurve, double _dMaturity, double _dStrike, double dividend, int _iNBStrike=1, bool _bCall=true);
	virtual ~VanillaOption(void){};
	double virtual payoff(double spot) const;
	Curve* getIR();
	Curve* getVol();
	double getMaturity();
	double getStrike();
	double getDiv();
	bool isCall();
};




#endif
