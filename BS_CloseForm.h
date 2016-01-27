#pragma once

#include "Option.h"
#include <vector>
class BS_CloseForm
{
private:
	VanillaOption* option;
	const double pi = 3.1415926;

public:
	BS_CloseForm(){};
	BS_CloseForm(VanillaOption* _option);
	~BS_CloseForm(){};
	double pricing(double _spot);
	double density_std_gaussian(double x);
	double repartition_std_gaussian(double x);
};

