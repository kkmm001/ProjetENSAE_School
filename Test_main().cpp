// erasing from vector
#include <iostream>
#include "FinitDiffMethode.h"
#include "BS_CloseForm.h"


int main ()
{
	aNoeud Data;
	vCurve myvector1, myvector2;
	
	// Random curve generator for interest rate among [0, 0.1]
	for (int i = 1; i <= 10; i++)
	{
		Data[0] = (double)i / 10;
		Data[1] = rand() / (double(RAND_MAX) * 10);
		myvector1.push_back(Data);
	}

	// Random curve generator for volatility among [0, 0.1]
	for (int i = 1; i <= 10; i++)
	{
		Data[0] = (double)i / 10;
		Data[1] =  rand() / (double(RAND_MAX) * 10);
		myvector2.push_back(Data);
	}



	/**************************************************************************************************/
	// Test1: GetParam function
	/**************************************************************************************************/
	
	// Creat instance of IRCurve and VolCurve
	IRCurve* ir_curve = new IRCurve(myvector1);
	VolCurve* vol_curve = new VolCurve(myvector2);

	std::cout << "Test 1: Curve working-test: " << "time = 0.6" << "\n";
	std::cout << "\n";
	std::cout << "Interest rate  : " << ir_curve->GetParam(0.6) << "\n";
	std::cout << "\n";
	std::cout << "Volatility : " << vol_curve->GetParam(0.6) << "\n";
	std::cout << "\n";
	std::cout << "Test1 works well!" << "\n";
	std::cout << "/**************************************************************************************************/" << "\n";
	std::cout << "\n";
	std::cout << "\n";
	std::cout << "\n";
	/**************************************************************************************************/


	
	
	/**************************************************************************************************/
	// Test2: Payoff function
	/**************************************************************************************************/

	//Initialize vanillaCall
	double maturity = 1.0, strike = 0.5, dividend = 0;

	//Create call instance
	VanillaOption* vanillaCall = new VanillaOption(ir_curve, vol_curve, maturity, strike, dividend);

	//Create put instance
	VanillaOption* vanillaput = new VanillaOption(ir_curve, vol_curve, maturity, strike, dividend, 1, false);
	
	std::cout << "Test 2: Curve working-test: " << "\n";
	std::cout << "\n";
	std::cout << "maturity is" << maturity << "; strike = " << strike << "; dividend = " << dividend << std::endl;
	std::cout << "\n";
	std::cout << "Given spot = 0.60, payoff is equal to: " << vanillaCall->payoff(0.60) << std::endl;
	std::cout << "\n";
	std::cout << "Given spot = 0.40, payoff is equal to: " << vanillaput->payoff(0.40) << std::endl;
	std::cout << "\n";
	std::cout << "Test2 works well!" << "\n";
	std::cout << "/**************************************************************************************************/" << "\n";
	std::cout << "\n";
	std::cout << "\n";
	std::cout << "\n";

	/**************************************************************************************************/


	
	/**************************************************************************************************/
	// Test3: Partial differential equation coefficients
	/**************************************************************************************************/

	//Create instance of class BS_PDE by including vanilla_Call.
	BS_PDE* _pde = new BS_PDE(vanillaCall);

	double time = 0.6, spot = 0.5;
	std::cout << "Test 3: Partial differential equation coefficients: " << "time = 0.6, spot = 0.5" << "\n";
	std::cout << "\n";
	std::cout << "Coeff_DerivTime = " << _pde->coeff_DerivTime(time, spot) << std::endl;
	std::cout << "\n";
	std::cout << "Coeff_DerivSpotFirst = " << _pde->coeff_DerivSpotFirst(time, spot) << std::endl;
	std::cout << "\n";
	std::cout << "Coeff_DerivSpotSecond = " << _pde->coeff_DerivSpotSecond(time, spot) << std::endl;
	std::cout << "\n";
	std::cout << "Coeff_DerivSpotZero = " << _pde->coeff_DerivSpotZero(time, spot) << std::endl;
	std::cout << "\n";
	std::cout << "Test3 works well!" << "\n";
	std::cout << "/**************************************************************************************************/" << "\n";
	std::cout << "\n";
	std::cout << "\n";
	std::cout << "\n";

	/**************************************************************************************************/






	/**************************************************************************************************/
	// Test4: explicit grid and resolution of PDE
	/**************************************************************************************************/


	double _Smax = 1.0;
	unsigned long _N_time = 101, _N_spot = 101;		//time domain and spot domain size


	ExplicitGrid* exp_grid = new ExplicitGrid(_pde, _Smax, _N_spot, _N_time);
	
	std::cout << "Test 4: explicit grid and resolution of PDE: " << "Smax = 1, N_spot = " << _N_spot << ", N_time = " << _N_time << "\n";
	exp_grid->discretization();
	std::cout << "\n";
	std::cout << "Function discretization works well!" << "\n";
	std::cout << "\n";
	exp_grid->init_vector();

	std::cout << "Function init_vector works well!" << "\n";
	std::cout << "\n";
	exp_grid->init_condition();

	std::cout << "Function init_condition works well!" << "\n";
	std::cout << "\n";
	exp_grid->boudary_condition();

	std::cout << "Function boudary_condition works well!" << "\n";
	std::cout << "\n";
	exp_grid->calculation_all();

	std::cout << "Function calculation_all works well!" << "\n";
	std::cout << "\n";
	exp_grid->output_csv("pricingEDP");

	std::cout << "Function output_csv works well, file name is " << "pricingEDP" << "\n";
	std::cout << "\n";
	std::cout << "Test4 works well!" << "\n";
	std::cout << "/**************************************************************************************************/" << "\n";
	std::cout << "\n";
	std::cout << "\n";
	std::cout << "\n";

	/**************************************************************************************************/



	/**************************************************************************************************/
	// Test5: test result
	/**************************************************************************************************/
	BS_CloseForm* close_form = new BS_CloseForm(vanillaCall);

	std::cout << "Test 5: result comparison between BS CloseForm and BS PDE methode: " << std::endl;
	std::cout << "\n";
	std::cout << "BS close form, call premium is: " << close_form->pricing(0.90) << std::endl;
	std::cout << "\n";
	std::cout << "BS PDE, call premium is: " << exp_grid->pricing(0.90) << std::endl;
	std::cout << "\n";
	std::cout << "Test5 works well!" << "\n";
	std::cout << "/**************************************************************************************************/" << "\n";
	std::cout << "\n";
	std::cout << "\n";
	std::cout << "\n";

	return 0;
}