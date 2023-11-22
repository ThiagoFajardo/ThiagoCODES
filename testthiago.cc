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

//#define GLB_SIGMA_E 6

using namespace std;

char AEDLFILE[] = "DUNE_GLoBES.glb";

const int GLB_SIGMA_E = 6;
double dm21;
double dm31;
double theta12;
double theta23;
double theta13;
double deltacp;
double sigma_E;

/*Armazena os parametros de oscilação na estrutura internas*/	
int my_set_oscillation_parameters(glb_params p, void* user_data)
{
	theta12    = glbGetOscParams(p, GLB_THETA_12);
	theta13    = glbGetOscParams(p, GLB_THETA_13);
	theta23    = glbGetOscParams(p, GLB_THETA_23);
	deltacp    = glbGetOscParams(p, GLB_DELTA_CP);
	dm21       = glbGetOscParams(p, GLB_DM_21) * 1.0e-18;   /* Convert to GeV^2 */
	dm31       = glbGetOscParams(p, GLB_DM_31) * 1.0e-18;   /* Convert to GeV^2 */

	/*Parametro não padrão*/
	sigma_E    = glbGetOscParams(p, GLB_SIGMA_E);

	return 0;
}

/*Le as oscilações fudamentais e atribui-as a p*/
int my_get_oscillation_parameters(glb_params p, void *user_data)
{
	glbSetOscParams(p, theta12, GLB_THETA_12);
	glbSetOscParams(p, theta13, GLB_THETA_13);
	glbSetOscParams(p, theta23, GLB_THETA_23);
	glbSetOscParams(p, deltacp, GLB_DELTA_CP);
	glbSetOscParams(p, dm21*1.0e18, GLB_DM_21);  /* Convert to eV^2 */
	glbSetOscParams(p, dm31*1.0e18, GLB_DM_31);  /* Convert to eV^2 */
	glbSetOscParams(p, sigma_E, GLB_SIGMA_E);

	return 0;
}

/*Calcula a matriz de oscilação e devolve em P -
	- P[3][3] ---- Matriz 3x3*/
int my_probability_matrix(double P[3][3], int cp_sign, double E, int psteps, const double *lengths, const double
*densities, double filter_sigma, void* user_data)
{
	int i, j;
	double L, Delta21, Delta31, Delta32;
	double D21, D31, D32, s13, c13, s12, c12, t;
	
	/* Deixa todas as probabilidades como zero inicialmente */
	for (i=0; i < 3; i++) 
	for (j=0; j < 3; j++) 
	P[i][j] = 0.0;
	
	/* Calcula toda a baseline */
	L = 1300; 
	for (i=0; i < psteps; i++) L += lengths[i];
	L = GLB_KM_TO_EV(L) * 1.0e9; /* Convert to GeV−1 */

	/* Computa P_mm */
	s12 = sin(theta12);
	c12 = cos(theta12);
	s13 = sin(theta13);
	c13 = cos(theta13);
	t = L / (4.0 * E);
	Delta21 = dm31 * t;
	Delta31 = dm21 * t;
	Delta32 = Delta31 - Delta21;
	//double sigma_E = 3.24;
	t = M_SQRT2 * sigma_E/ E;
	D21 = exp(-pow( Delta21 * t , 2));
	D31 = exp(-pow( Delta31 * t , 2));
	D32 = exp(-pow( Delta32 * t, 2));
	P[1][1] = pow(pow(c13,2),2) * ( 1 - 2.0*pow(s12*c12,2)*(1 - D21*cos(2.0*Delta21)) )
	+ 2.0*pow(s13*c13,2) * ( D31*pow(c12,2)*cos(2.0*Delta31)
	+ D32*pow(s12,2)*cos(2.0*Delta32) )
	+ pow(pow(s13,2),2);

	return 0;
}


int main(int argc, char * argv[])
{
/*Define os parametros padrão*/
double true_dm21 = 7.56e-5;
double true_dm31 = 2.437e-3;
double true_theta12 = asin(sqrt(0.307));
double true_theta23 = asin(sqrt(0.534));
double true_theta13 = asin(sqrt(2.20e-2));
double true_deltacp = 1.23;

/*Define um parametro não padrão sigma_E - propagação de energia*/
double true_sigma_E = 0.0;



glbInit(argv[0]);

/*Registra a probabilidade da engine para a simulação*/
glbRegisterProbabilityEngine (7,
	&my_probability_matrix, 
	&my_set_oscillation_parameters,&my_get_oscillation_parameters, NULL);

/*Inicia o experimento*/
glbInitExperiment(AEDLFILE, &glb_experiment_list[0], &glb_num_of_exps);

ofstream outstdmuvac, outstdmuprof,outstdchi2;


/*Arquivo de entrada chi2*/
outstdchi2.open("betachi2.dat");

/*Arquivos de entrada norm*/
outstdmuvac.open("data_test1.dat");
outstdmuprof.open("data_test.dat");



/*Retorna o numero de parâmetros de oscilação*/
int glbGetNumOfOscParams();

/* Define  parametros e vetores de projeção */
glb_params true_values = glbAllocParams();
glb_params test_values = glbAllocParams();
glb_projection th13_sigma_projection = glbAllocProjection();

glbDefineParams(true_values,true_theta12,true_theta13,true_theta23,true_deltacp,true_dm21,true_dm31);
glbSetDensityParams(true_values, 1.0, GLB_ALL);
glbSetOscParams(true_values,true_sigma_E,GLB_SIGMA_E);

/*Computa os dados simulados*/
glbSetOscillationParameters(true_values);
glbSetRates();
glbCopyParams(true_values,test_values);

/*Seta duas projeções de parametros em theta13 e sigma_E */
glbDefineProjection(th13_sigma_projection, GLB_FREE, GLB_FIXED, GLB_FIXED,
GLB_FIXED, GLB_FREE, GLB_FREE);
glbSetDensityProjectionFlag(th13_sigma_projection, GLB_FIXED, GLB_ALL);
glbSetProjectionFlag(th13_sigma_projection, GLB_FIXED, GLB_SIGMA_E);
glbSetProjection(th13_sigma_projection);

double energy,probmuprof,probmuvac; 
double emin = 0.25 ; //GeV
double emax = 10 ; //GeV
double thetheta13, x, y, res;
double step = 3000;

/* Compute chi^2 sem as correlações */
for(x=0; x < 0.8+0.01;  /*quantidade de valores*/ x+=0.005)        /* th13 loop */
for(y=0.0; y < 0.010+0.001; y+=0.001)   /* sigame_E loop */
{
	/* Seta o vetor dos valores que vão filtrar os test_values */
	thetheta13=asin(sqrt(x))/2.0;
	glbSetOscParams(test_values,thetheta13,GLB_THETA_13);
	glbSetOscParams(test_values,y,GLB_SIGMA_E);
	
	/* Compute Chi^2 com os sistematicos apenas*/
	res=glbChiSys(test_values,GLB_ALL,GLB_ALL);
	outstdchi2<<thetheta13<<"   "<<y<<"   "<<res<<endl;
}

for (energy=emin;energy<=emax;energy+=(emax-emin)/step)
{
	/*Neutrinos*/
	/*Vacuo*/
	probmuvac=glbVacuumProbability(2,2,+1,energy,1300);
	outstdmuvac<<energy<<"  "<<probmuvac<<endl;

	/*Matéria*/
	probmuprof=glbProfileProbability(0,2,2,+1,energy);
	outstdmuprof<<energy<<"  "<<probmuprof <<"  "<< GLB_THETA_13 << endl;

}
/*Fecha arquivo chi2*/
outstdchi2.close();

/*Fecha arquivo de saida norm*/
outstdmuprof.close();



/*Destroi os parametros e vetores de projeção*/
glbFreeParams(true_values);
glbFreeParams(test_values);
glbFreeProjection(th13_sigma_projection);
return 0;

}
