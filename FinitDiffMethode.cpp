#include "FinitDiffMethode.h"

ExplicitGrid::ExplicitGrid(BS_PDE* _pde, double _Smax, unsigned long _N_spot, unsigned long _N_time):pde(_pde), Smax(_Smax), N_spot(_N_spot), N_time(_N_time){}


void ExplicitGrid::discretization()
{
	Tmax=pde->getVanillaOption()->getMaturity();
	dt = Tmax/(double)(N_time-1); //Time index starts from 0
	dS = Smax/(double)(N_spot-1); //Spot index starts from 0
}

void ExplicitGrid::init_vector()
{
	spotVector Rcurrent;
	Rcurrent.resize(N_spot, 0.0);		//We get it done once for all
	//Rcurrent.resize(N_spot, 0.0);	//Alternative is to use vector.push_back()

	result.resize(N_time, Rcurrent);
}

void ExplicitGrid::init_condition()
{	
	double spotCurrent;
	spotVector Rlast;

	for(unsigned long i=0; i<N_spot;i++)	
	{
		spotCurrent = (double)i*dS;
		Rlast.push_back(pde->getVanillaOption()->payoff(spotCurrent));	//affect the payoff to the maturity column.
	}
	result.at(N_time-1) = Rlast;
}


void ExplicitGrid::boudary_condition(void)		//recall this function for every recurrence
{

	for (unsigned long i = 0; i < N_time-1; i++)
	{
		//S=0 for below boundary so that neoud value is always null.
		result.at(i).at(0) = 0.0;						
		//S=Smax the call will be always exerced, which can be actualized from last result.
		//result.at(i).at(N_spot - 1) = Smax - pde->getVanillaOption()->getStrike()*discount_factor(i, N_time - i);
	}
}


double ExplicitGrid::discount_factor(unsigned long Tcurrent, unsigned long duration)
{
	// r is considered as annual interest rate, and discount term is less than 1y for ordinary liquid call.
	// therefore we prefer the linear rate for calculating the discount_factor
	double r = pde->getVanillaOption()->getIR()->GetParam(Tcurrent*dt);
	double DiscountFactor = 1 / ((1 + r*duration*dt));
	return DiscountFactor;
}


unsigned long ExplicitGrid::calculation_nexttime(unsigned long Tlast)
{
	double r = pde->getVanillaOption()->getIR()->GetParam(Tlast*dt);
	
	spotVector Rcurrent=result.at(Tlast-1), Rlast = result.at(Tlast);
	
	for (unsigned long j = 1; j < N_spot - 1; j++)	//Loop from begin_index+1 to end_index-1
	{
		a = (dt / (1 + r*dt))*(pde->coeff_DerivSpotSecond(Tlast*dt, j) - 0.5*pde->coeff_DerivSpotFirst(Tlast*dt, j));
		b = (1 / (1 + r*dt))*(1 - 2 * pde->coeff_DerivSpotSecond(Tlast*dt, j)*dt);
		c = (dt / (1 + r*dt))*(pde->coeff_DerivSpotSecond(Tlast*dt, j) + 0.5*pde->coeff_DerivSpotFirst(Tlast*dt, j));
		Rcurrent[j] = Rlast[j - 1] * a + Rlast[j] * b + Rlast[j + 1] * c;
	}
	Rcurrent[N_spot-1] = 2 * Rcurrent[N_spot - 2] - Rcurrent[N_spot - 3];
	result.at(Tlast - 1) = Rcurrent;
	return (Tlast - 1);
}

bool ExplicitGrid::calculation_all()
{
	unsigned long Tlast = N_time - 1;
	for (unsigned long i = N_time - 1; i > 0; i--)
	{
		if (Tlast == i)
		{
			Tlast = calculation_nexttime(i);
		}
		else
			return false;
	}
 	return true;
}
void ExplicitGrid::output_csv(std::string _name_file){

	std::ofstream csv_out(_name_file+".csv");
	double dSpot, dTime;
	for (unsigned int i = 0; i < N_spot; i++)
	{
		dSpot = i*dS;
		csv_out << dSpot << ";";
		for (unsigned int j = 0; j < N_time; j++)
		{
			dTime = j*dt;
			csv_out << dTime << ";" << result.at(j).at(i) << ";";
		}
		csv_out << std::endl;
	}
	csv_out.close();
}

double ExplicitGrid::pricing(double _spot)
{
	double newdis, distanceMin = std::abs(0 - _spot);
	unsigned long index=0;
	for (unsigned long j = 1; j < N_spot; j++)
	{
		newdis = std::abs(j*dS - _spot);
		if (newdis < distanceMin)
		{
			distanceMin = newdis;
			index = j;
		}
	}

	return result.at(0).at(index);
}

double closest(std::vector<double> const& vec, double value) {
	auto const it = std::lower_bound(vec.begin(), vec.end(), value);
	if (it == vec.end()) { return -1; }

	return *it;
}