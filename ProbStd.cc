#include <iostream>
#include <cmath>
#include <string.h>
#include<float.h>
#include<complex.h>
#include <vector>
#include<gsl/gsl_complex.h>
#include<gsl/gsl_complex_math.h>
#include<gsl/gsl_matrix.h>
#include<gsl/gsl_blas.h>
#include <globes/globes.h>
#include<fstream>

using namespace std;

char AEDLFILE[] = "DUNE_GLoBES.glb";


int main(int argc, char * argv[])
{

	glbInit(argv[0]);
	glbInitExperiment(AEDLFILE, &glb_experiment_list[0], &glb_num_of_exps);

	ofstream outstd;

	outstd.open("probability_DUNE.dat");

    //char* MYFILE="log.dat";
    //FILE* stream;
    //if(strlen(MYFILE)>0) stream=fopen(MYFILE, "w");
    //    else stream = stdout;
	
	double dm21 = 7.55e-5;
	double dm31 = 2.50e-3;
	double theta12 = asin(sqrt(0.320));
	double theta23 = asin(sqrt(0.547));
	double theta13 = asin(sqrt(0.02160));
	double deltacp = -0.68 * M_PI;

    cout << "dm21 = " << dm21 << endl;
    cout << "dm31 = " << dm31 << endl;
    cout << "theta12 = " << theta12 << " (" << pow(sin(theta12),2) << ")" << endl;
    cout << "theta23 = " << theta23 << " (" << pow(sin(theta23),2) << ")" << endl;
    cout << "theta13 = " << theta13 << " (" << pow(sin(theta13),2) << ")" << endl;
    cout << "deltacp = " << deltacp << endl;
    cout << "Pi = " << M_PI << endl;

	/* Define "true" oscillation parameter vector */
	glb_params true_values = glbAllocParams();

    glbDefineParams(true_values,theta12,theta13,theta23,deltacp,dm21,dm31);

    glbPrintParams(stdout,true_values);
	
	glbSetDensityParams(true_values, 1.0, GLB_ALL);

	glbSetOscillationParameters(true_values);
	glbSetRates();

	double energy, prob;
	double emin= 0.25 ; //GeV
	double emax=8 ; //GeV
	double step= 1000;
	//double L = 1300; // km

	for (energy=emin;energy<=emax;energy+=(emax-emin)/step)
	{
	  glbSetOscillationParameters(true_values);
	  //prob=glbVacuumProbability(2,1,+1,energy,L); 
	  prob=glbProfileProbability(0,2,1,+1,energy);
	  outstd<<energy<<"  "<<prob<<endl;
	}


	outstd.close();
	glbFreeParams(true_values);
 	return 0;

}