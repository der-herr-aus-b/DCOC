//
//  main.c
//  DCOC_in_C
//
//  Created by Rounak on 29/6/16.
//  Copyright © 2016 Rounak. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //required for memcpy
#include <math.h>
#define PI = 3.14159 //for some reason can't use this in the code

//INIT

//need to specify length in 2nd argument
const float pi = 3.14159;
const float prob_matrix[][3] = {{0.5, 0.9, 0.4}, {0.1, 0.2, 0.7}, {0.3, 0.3, 0.4}};
const float del_t = 0.01;
const float u_space[] = {-0.01,0,0.01};
const float w_space[] = {-0.01,0,0.01};
const float x_min[] = {-pi/8,-1};
const float x_max[] = {pi/8,1};
const float step_size[] = {pi/20,0.1};


void pendulum_nonlinearmodel_ss(float X[], float U, float F, float del_t, float x_new[]);

void value_iteration(){
    
    //init stuff
    float stopping_criterion = 0.01;
    float *x1_space, *x2_space, ***V, ***V_old;
    int i,j,k;
    int x1_len = (x_max[0]-x_min[0])/step_size[0] + 1;
    int x2_len = (x_max[1]-x_min[1])/step_size[1] + 1;
    int w_len = sizeof(w_space)/sizeof(float);
    float x_new[] = {0,0};
    
    x1_space = (float *)(malloc(x1_len*sizeof(float)));
    for(i=0;i<x1_len;i++){
        x1_space[i] = x_min[0] + step_size[0]*i;
        //printf("%f ",x1_space[i]);
    }
    printf("\n");
    
    x2_space = (float *)(malloc(x2_len*sizeof(float)));
    for(i=0;i<x2_len;i++){
        x2_space[i] = x_min[1] + step_size[1]*i;
        //printf("%f ",x2_space[i]);
    }
    
    V = (float ***)(malloc(x1_len*sizeof(float*)));
    V_old = (float ***)(malloc(x1_len*sizeof(float*)));
    for(i=0;i<x1_len;i++){
        V[i] = (float **)(malloc(x2_len*sizeof(float*)));
        V_old[i] = (float **)(malloc(x2_len*sizeof(float*)));
        for(j=0;j<x2_len;j++){
            V[i][j]=(float *)(malloc(w_len*sizeof(float*)));
            V_old[i][j]=(float *)(malloc(w_len*sizeof(float*)));
            for(k=0;k<w_len;k++){
                V[i][j][k] = 0;
                V_old[i][j][k] = 1;
                
            }
        }
    }
    
    
    float a[] = {0,0};
    pendulum_nonlinearmodel_ss(&a[0], 1, 0, del_t, &x_new[0]);
    printf("array gotten %f,%f\n",x_new[0],x_new[1]);


    //V_old = memcpy(&V[0][0][0], &V_old[0][0][0], x1_len*x2_len*w_len*sizeof(float));
   


    
    
    printf("Value iteration Done\n");
    
}

void pendulum_nonlinearmodel_ss(float X[], float U, float F, float del_t, float x_new[]){
    
    float m = 0.2;
    float b = 0.001;
    float I = 0.006;
    float g = 9.8;
    float l = 0.3;
    float th = X[0];
    float th_ = X[1];
    float T = U;
    x_new[0] = X[0] + del_t* th_;
    x_new[1] = X[1] + del_t* (-m*g*l*sin(th) -b*th_ + F*l*cos(th) + T)/I; //cos and sin in radians
    
    
}



int main(int argc, const char * argv[]) {
    // Debug area
    
    printf("Hello, World!\n %.2f\n",2.0);
    
    
    //serious shit starts here:
    value_iteration();
    return 0;
}
