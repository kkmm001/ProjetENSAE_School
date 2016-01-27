#include "BS_CloseForm.h"


BS_CloseForm::BS_CloseForm(VanillaOption* _option) :option(_option){}

double BS_CloseForm::pricing(double S)
{
	double T = option->getMaturity();
	double K = option->getStrike();
	double dividend = option->getDiv();
	double sigma = option->getVol()->GetParam(0);
	double r = option->getIR()->GetParam(0);

	double d1, d2;

	d1 = (std::log(S / K) + (r + 0.5*sigma*sigma)*T) / (sigma*std::sqrt(T));
	d2 = d1 - sigma*std::sqrt(T);

	if (option->isCall())
	{
		return S*repartition_std_gaussian(d1) - K*std::exp(-r*T)*repartition_std_gaussian(d2);
	}
	else
	{
		return -S*repartition_std_gaussian(-d1) + K*std::exp(-r*T)*repartition_std_gaussian(-d2);
	}

}

double BS_CloseForm::density_std_gaussian(double x)
{
	return 1 / std::sqrt(2 * pi)*std::exp(-0.5*(x*x));
}

double BS_CloseForm::repartition_std_gaussian(double param)
{
	long index,  N = 10001;
	std::vector<double> result;
	double x = 0, x_max = 5.0, x_min = -5.0, density = 0.0, sum_probability = 0.0;
	double dx = (x_max - x_min) / double(N-1);

	for (long i = 0; i < N;i++)
	{
		x = (i - (N-1)/2)*dx;
		density = density_std_gaussian(x);
		sum_probability = sum_probability + dx*density;
		result.push_back(sum_probability);
	}

	if (param >= 5)
	{
		return result.at(N-1);
	}
	else if (param <= -5){
		return result.at(0);
	}
	else
	{
		index = (long)((param + 5) / dx);
		return result.at(index);
	}
}



