#pragma once
#ifndef FINITDIFFMETHODE_H
#define FINITDIFFMETHODE_H


#include "BS_PDE.h"
#include <fstream>

typedef std::vector<double> spotVector;

class FinitDiffMethode
{
public:
	FinitDiffMethode(void){};
	virtual ~FinitDiffMethode(void){};

	double virtual discount_factor(unsigned long Tcurrent, unsigned long duration) = 0;
	void virtual discretization() = 0; 
	void virtual init_vector() = 0 ;
	void virtual init_condition() = 0;
	void virtual boudary_condition() = 0;
	unsigned long virtual calculation_nexttime(unsigned long Tlast) = 0;
	bool virtual calculation_all() = 0;
	void virtual output_csv(std::string _name_file) = 0;
	double virtual pricing(double _spot) = 0;
};


class ExplicitGrid
{
private:
	BS_PDE* pde;

	//spot discretisation
	double Smax;			//require to be init
	unsigned long N_spot;		//number of step
	double dS;

	//time discretisation
	double Tmax;			//maturity
	unsigned long N_time;		//number of step
	double dt;

	//time recurrence index
	//unsigned long Tlast, Tcurrent;		//index


	//Explicit methode coeffs for time recurrence F(t,s)=a(s)F(t+1,s-1)+ b(s)F(t+1,s) +c(s)F(t+1,s+1)
	double a, b, c;


	//result vector for Tcurrent/Tlast
	//spotVector Rcurrent, Rlast;

	std::vector<spotVector> result;
public:
	ExplicitGrid(void){};
	ExplicitGrid(BS_PDE* _pde, double _Smax, unsigned long _N_spot, unsigned long _N_time);
	virtual ~ExplicitGrid(void){};

	double virtual discount_factor(unsigned long index_T, unsigned long duration);
	void virtual discretization(); 
	void virtual init_vector();
	void virtual init_condition();
	void virtual boudary_condition();
	unsigned long virtual calculation_nexttime(unsigned long Tlast);
	bool virtual calculation_all();
	void virtual output_csv(std::string _name_file);
	double virtual pricing(double _spot);
};




#endif