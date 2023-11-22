#include <iostream>
#include <cmath>
#include <string.h>
#include <float.h>
#include <complex.h>
#include <vector>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>
#include <globes/globes.h>
#include <fstream>
#include <string>
#include <algorithm>
#include <sys/stat.h>
#include <filesystem>
#define GLB_SIGMA_E 6

extern "C"
{
    #include "bsm.h"
}
using namespace std;

char AEDLFILE[] = "DUNE_GLoBES.glb";
int main(int argc, char * argv[])
{
    glbInit(argv[0]);
    glbInitExperiment(AEDLFILE, &glb_experiment_list[0], &glb_num_of_exps);
    
    ofstream outBSMn;
    ofstream outBackup;
    //ofstream outstdchi2;

    /*Arquivo de entrada chi2*/
    //outstdchi2.open("betachi2.dat");

    outBSMn.open("./BSMprob_mue/BSMprobability_cmueDUNE.dat");
    
    
    /*nome base para criação de todos arquivos e pastas
    o restante nome_novo etc. para os especificos*/
    ifstream in;
    string nome_base = "./BSMprob_mue/BSM_mue";
    string nome_novo;
    string nome_temp;
    string backup_string;
    string str_temp;
    int contador_dat = 0;
    int contador_arquivos = 0;
    double dm21 = 7.42e-5;
    double dm31 = 2.515e-3;
    double theta12 = asin(sqrt(0.304));
    double theta23 = asin(sqrt(0.573));
    double theta13 = asin(sqrt(0.0222));
    double deltacp = -0.68 * M_PI;    

    //double chi2;

    bsm_init_probability_engine_3();
    glbRegisterProbabilityEngine(8 * 9 - 3,
                               &bsm_probability_matrix,
                               &bsm_set_oscillation_parameters,
                               &bsm_get_oscillation_parameters,
                               NULL);
    /* Define "true" oscillation parameter vector */
    glb_params true_values = glbAllocParams();
    //glb_params fit_values = glbAllocParams();

    //glbCopyParams(true_values,test_values);
    for(unsigned int i=0; i < 69; i++)
    {
    glbSetOscParams(true_values, 0.0, i);
    //chi2 = glbChiSys(fit_values,0,0);
    }
    glbDefineParams(true_values,theta12,theta13,theta23,deltacp,dm21,dm31);
    /*Termos para Matriz a*/
    double abs_a_ee = 0;
    double abs_a_mue = 0;//-2.0e-23 / 1.0e-9;
    double arg_a_mue =  0;
    double abs_a_etau = 0;
    double arg_a_etau = 0;
    double abs_a_mumu = 0;
    double abs_a_mutau = 0;
    double arg_a_mutau = 0;
    double abs_a_tautau = 0;

    /*Termos para Matriz c*/
    double abs_c_ee = 0;
    double abs_c_mue = -2.0e-32 / 1.0e-9;
    double arg_c_mue = 0;
    double abs_c_etau = 0;
    double arg_c_etau = 0;
    double abs_c_mumu = 0;
    double abs_c_mutau = 0;
    double arg_c_mutau = 0;
    double abs_c_tautau = 0;

    double matriz_a[3][3];
    matriz_a[0][0] = abs_a_ee;
    matriz_a[0][1] = abs_a_mue;
    matriz_a[1][0] = arg_a_mue;
    matriz_a[0][2] = abs_a_etau;
    matriz_a[2][0] = arg_a_etau;
    matriz_a[1][1] = abs_a_mumu;
    matriz_a[1][2] = abs_a_mutau;
    matriz_a[2][1] = arg_a_mutau;
    matriz_a[2][2] = abs_a_tautau;

    double matriz_c[3][3];
    matriz_c[0][0] = abs_c_ee;
    matriz_c[0][1] = abs_c_mue;
    matriz_c[1][0] = arg_c_mue;
    matriz_c[0][2] = abs_c_etau;
    matriz_c[2][0] = arg_c_etau;
    matriz_c[1][1] = abs_c_mumu;
    matriz_c[1][2] = abs_c_mutau;
    matriz_c[2][1] = arg_c_mutau;
    matriz_c[2][2] = abs_c_tautau;

    /*Backup das Matrizes principais*/
    double matriz_a_backup[3][3];
    double matriz_c_backup[3][3];

    /*Se diferente = 1 uma nova pasta sera criada*/
    bool diferente = 0;

    while(1){
        nome_temp = nome_base;
        nome_temp += std::to_string(contador_arquivos);
        nome_temp += ".dat";
        in.open(nome_temp);
        if(in){
            contador_arquivos++;
            /* Passa os dados do .dat para uma string */
            ifstream f(nome_temp);
            if(f) {
                ostringstream ss;
                ss << f.rdbuf(); //reading data
                backup_string = ss.str();
            }

        /*contadores*/
            contador_dat = 0;
            contador_arquivos = 0;
            str_temp.clear();

            /*Transforma o str em matriz double*/
            /*MATRIZ A*/
            for (size_t i = 0; i < 3; i++)
            {
                for (size_t j = 0; j < 3; j++)
                {
                    while(backup_string[contador_dat] != ' '){
                        str_temp.push_back(backup_string[contador_dat]);
                        contador_dat++;
                        //cout << str_temp << endl;
                    }
                    if(backup_string[contador_dat] == ' '){
                        contador_dat++;
                        matriz_a_backup[i][j] = std::stod(str_temp);
                        //cout << matriz_a_backup[i][j] << endl;
                        str_temp.clear();
                    }
                }
            }
            /*MATRIZ C*/
            for (size_t i = 0; i < 3; i++)
            {
                for (size_t j = 0; j < 3; j++)
                {
                    while(backup_string[contador_dat] != ' '){
                        str_temp.push_back(backup_string[contador_dat]);
                        contador_dat++;
                        //cout << str_temp << endl;
                    }
                    if(backup_string[contador_dat] == ' '){
                        contador_dat++;
                        matriz_c_backup[i][j] = std::stod(str_temp);
                        //cout << matriz_c_backup[i][j] << endl;
                        str_temp.clear();
                    }
                }
            }

            /*Compara o backup com os dados novos e indica se há alteração*/
            /*1 para diferente 0 para igual*/
            
            for (size_t i = 0; i < 3; i++){
                for (size_t j = 0; j < 3; j++){
                    if(matriz_a[i][j] != matriz_a_backup[i][j] ||
                        matriz_c[i][j] != matriz_c_backup[i][j]){
                        diferente = 1;
                    }
                }
            }
        }
        else break;
        in.close();
    }
    /*Contador de quantos arquivos já existem*/
    
    
    contador_arquivos = 0;
    /*Gera a pasta e o arquivo novos se os dados forem diferentes dos antigos */
    //for (size_t i = 0; i < count; i++)
    //{
        if(diferente){
            while (1){
                nome_temp = nome_base;
                nome_temp += std::to_string(contador_arquivos);
                nome_temp += ".dat";
                in.open(nome_temp);
                if(in){
                    contador_arquivos++;
                }
                else break;
                in.close();
            }
            nome_novo = nome_base;
            nome_novo += std::to_string(contador_arquivos);
            nome_novo += ".dat";
            outBackup.open(nome_novo);
            //mkdir("nome_novo", 0775);
    
            std::string string_a;
            for (size_t i = 0; i < 3; i++){
                for (size_t j = 0; j < 3; j++){
                    outBackup<<matriz_a[i][j]<<" ";
                }
            }
            outBackup<<endl;
            for (size_t i = 0; i < 3; i++){
                for (size_t j = 0; j < 3; j++){
                    outBackup<<matriz_c[i][j]<<" ";
                }
            }
        }
    //}
    
    


    //double matriz_a_aux[3][3];
    //double matriz_c_aux[3][3];
    //############ LIV Parameter #################################//
    glbSetOscParams(true_values, abs_a_ee, 51);  // a_ee
    glbSetOscParams(true_values, abs_a_mue, 52);  // a_mue magnitude
    glbSetOscParams(true_values, arg_a_mue, 53);  // a_mue phase
    glbSetOscParams(true_values, abs_a_etau, 54);  // a_etau
    glbSetOscParams(true_values, arg_a_etau, 55);  // a_etau phase
    glbSetOscParams(true_values, abs_a_mumu, 56);  // a_mumu
    glbSetOscParams(true_values, abs_a_mutau, 57);  // a_mutau
    glbSetOscParams(true_values, arg_a_mutau, 58);  // a_mutau phase
    glbSetOscParams(true_values, abs_a_tautau, 59);  // a_tautau
    glbSetOscParams(true_values, abs_c_ee, 60);  // c_ee
    glbSetOscParams(true_values, abs_c_mue, 61);  // c_mue magnitude
    glbSetOscParams(true_values, arg_c_mue, 62);  // c_mue phase
    glbSetOscParams(true_values, abs_c_etau, 63);  // c_etau
    glbSetOscParams(true_values, arg_c_etau, 64);  // c_etau phase
    glbSetOscParams(true_values, abs_c_mumu, 65);  // c_mumu
    glbSetOscParams(true_values, abs_c_mutau, 66);  // c_mutau
    glbSetOscParams(true_values, arg_c_mutau, 67);  // c_mutau phase
    glbSetOscParams(true_values, abs_c_tautau, 68);  // c_tautau
    glbSetDensityParams(true_values,1.0,GLB_ALL);
    glb_params input_errors = glbAllocParams();
    glbSetDensityParams(input_errors, 0.05, GLB_ALL);
    glbSetInputErrors(input_errors);
    glbSetOscillationParameters(true_values);
    glbSetRates();
    double energy, prob_BSM;
    double emin= 0.25 ; //GeV
    double emax=8 ; //GeV
    double step= 1000;
    //double L = 1300; // km

    
    /*Gera o resultado do .dat*/
    
    /* Compute chi^2 sem as correlações */
    //double thetheta13, x, y, res;

    //for(x=0; x < 0.8+0.01;  /*quantidade de valores*/ x+=0.005)        /* th13 loop */
    //for(y=0.0; y < 0.010+0.001; y+=0.001)   /* sigame_E loop */
    //{
	    /* Seta o vetor dos valores que vão filtrar os test_values */
	    //thetheta13=asin(sqrt(x))/2.0;
	    //glbSetOscParams(fit_values,thetheta13,GLB_THETA_13);
	    //glbSetOscParams(fit_values,y,GLB_THETA_13);
	
	    /* Compute Chi^2 com os sistematicos apenas*/
	    //res=glbChiSys(fit_values,GLB_ALL,GLB_ALL);
	    //outstdchi2<<thetheta13<<"   "<<y<<"   "<<res<<endl;
    //}

    for (energy=emin;energy<=emax;energy+=(emax-emin)/step)
    {
    glbSetOscillationParameters(true_values);
    //prob_BSM=glbVacuumProbability(2,1,+1,energy,L);
    prob_BSM=glbProfileProbability(0,2,1,+1,energy);
    outBSMn<<energy<<"  "<<prob_BSM<<endl;
    }


    outBSMn.close();
    outBackup.close();
    //outstdchi2.close();
    glbFreeParams(true_values);
    return 0;
}
//int p = find(bsm_param_strings[801].begin(),bsm_param_strings[801].end(),"ABS_A_V_MUE");
    //cout << p << endl;
//for (int p=0;p<69;p++){
    //  cout << p << " " <<  bsm_param_strings[p] << endl;
    //}