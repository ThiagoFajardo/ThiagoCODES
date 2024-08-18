#include <iostream>
#include <cmath>
#include <string>
#include<float.h>
#include<complex.h>
#include <vector>
#include<gsl/gsl_complex.h>
#include<gsl/gsl_complex_math.h>
#include<gsl/gsl_matrix.h>
#include<gsl/gsl_blas.h>
#include <globes/globes.h>
#include<fstream>
#include <iomanip>

#include <algorithm>

extern "C"
{
	#include "bsm.h"
}


using namespace std;

char AEDLFILE[] = "./lib/DUNE_GLoBES.glb";


int main(int argc, char * argv[])
{

	glbInit(argv[0]);
	glbInitExperiment(AEDLFILE, &glb_experiment_list[0], &glb_num_of_exps);

	ofstream outstd_e, outstd_mu, outbsm_e, outbsm_mu, outfilt_e, outfilt_mu;

	outfilt_e.open("prob_out_e.dat");
	outfilt_mu.open("prob_out_mu.dat");
	outstd_e.open("prob_STD_e.dat");
	outstd_mu.open("prob_STD_mu.dat");
    outbsm_e.open("prob_BSM_e.dat");
    outbsm_mu.open("prob_BSM_mu.dat");
	

    //char* MYFILE="log.dat";
    //FILE* stream;
    //if(strlen(MYFILE)>0) stream=fopen(MYFILE, "w");
    //    else stream = stdout;
	
	double dm21 = 7.41e-5;//double theta12  = 33.45*M_PI/180.0;// asin(sqrt(0.320));
  	double dm31 = 2.498e-3;//double theta13  = 8.62*M_PI/180.0;//asin(sqrt(0.02160));
	double theta12 = 33.45*M_PI/180;//double theta23  = 42.1*M_PI/180.0;//asin(sqrt(0.547));
	double theta23 = 42.1*M_PI/180;//double deltacp  = 230*M_PI/180.0;//-0.68 * M_PI;
  	double theta13 = 8.62;//double dm21     = 7.42e-5;//7.55e-5;
	double deltacp = 230*M_PI/180;//double dm31     = 2.51e-3;//2.50e-3;

    //int n_bins = glbGetNumberOfBins(0);

    bsm_init_probability_engine_3();

	glbRegisterProbabilityEngine(8 * 9 - 3,
                               &bsm_probability_matrix,
							   &bsm_set_oscillation_parameters,
  							   &bsm_get_oscillation_parameters,
  							   NULL);

	/* Define "true" oscillation parameter vector */
	glb_params true_values = glbAllocParams();
	//glb_params input_errors = glbAllocParams();	

    for(unsigned int i=0; i < 69; i++){
	    glbSetOscParams(true_values, 0.0, i);
	}
	

    glbDefineParams(true_values,theta12,theta13,theta23,deltacp,dm21,dm31);
    glbSetDensityParams(true_values, 1.0, GLB_ALL);
	glbSetOscillationParameters(true_values);    

	glbSetRates();

	double energy, prob_e, prob_mu, probBSM_e, probBSM_mu;
	double emin= 0.25 ; //GeV
	double emax= 8.0 ; //GeV
	double step= 1000;


    /*STD*/ 
	for (energy=emin;energy<=emax;energy+=(emax-emin)/step)
	{
	  glbSetOscillationParameters(true_values);
	  prob_e=glbProfileProbability(0,2,1,+1,energy);
      prob_mu=glbProfileProbability(0,2,2,+1,energy);
	 
	  outstd_e<<energy<<"  "<<prob_e<<endl;
	  outstd_mu<<energy<<"  "<<prob_mu<<endl;
	}


	glb_params test_values = glbAllocParams();
    for(unsigned int i=0; i < 69; i++){

	    glbSetOscParams(test_values, 0.0, i);
	
    }
	

    glbDefineParams(test_values,theta12,theta13,theta23,deltacp,dm21,dm31);
    glbSetDensityParams(test_values, 1.0, GLB_ALL);
	glbSetRates();

	double a,b;
	double bi = -24;
	double bf = -21;
	double ai = 0;
	double af = 10;
	double points = 500;
	double y;
	double x;

	/*BSM*/

    for(b=bi; b<bf; b++)
    for(a=ai;a<af;a=a+(af-ai)/points){

			glbSetOscParams(test_values,a*pow(10,b)*1.0e9, 56);
            glbSetOscillationParameters(test_values);
			glbSetRates();

            for (energy=emin;energy<=emax;energy+=(emax-emin)/step){

                probBSM_e=glbProfileProbability(0,2,1,+1,energy);
                probBSM_mu=glbProfileProbability(0,2,2,+1,energy);
                outbsm_e <<energy<<"  "<<probBSM_e<<endl;
				outbsm_mu <<energy<<"  "<<probBSM_mu<<endl;

            }

            //for(int i=0; i<n_bins;i++){
            		y = ((probBSM_e*100) /prob_e)-100;
            		x = ((probBSM_mu*100)/prob_mu)-100;
					
				if(y > 10){
				
				outfilt_e<< a <<"  "<< b <<"  "<< y << endl;
				
				}
				if(x < -10){
				outfilt_mu<< a <<"  "<< b <<"  "<< x << endl;
				}
            //}
    }
    

	outstd_e.close();
 	outfilt_e.close();
	outbsm_e.close();
	glbFreeParams(true_values);
 	return 0;

}