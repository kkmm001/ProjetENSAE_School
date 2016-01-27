#pragma once
#ifndef CURVE_H
#define CURVE_H

#include <vector>
#include <array>
#include <cmath>
typedef std::array<double, 2> aNoeud;
typedef std::vector<aNoeud> vCurve;

//Parent class Curve
class Curve
{
public:
	Curve(void){};
	virtual ~Curve(void){};
	virtual double GetParam(const double time) const = 0; // const is not allowed to change members
};

//Extended Children Class--IRCure for interest rate
class IRCurve: public Curve
{
private:
	
	vCurve irVector;	//Type vCurve stands for std::vector<aNoeud> 

public:
	IRCurve(void){};
	IRCurve(vCurve _irVector);
	virtual ~IRCurve(void){};
	double GetParam(const double time) const; // One marked "const" is not allowed to change members
};

//Extended Children Class--VolCure for volatility
class VolCurve: public Curve
{
private:
	
	vCurve volVector;	//Type vCurve stands for std::vector<aNoeud> 

public:
	VolCurve(void){};
	VolCurve(vCurve _irVector);
	virtual ~VolCurve(void){};
	double GetParam(const double time) const; // One marked "const" is not allowed to change members
};



#endif