#include "Kalman_Filter.h"

 
static long float Q_angle=0.001, Q_gyro=0.003, R_angle=1000, dt=0.024;
			//注意：dt的取值为kalman滤波器采样时间;
static float Pk[2][2] = { {1, 0 }, {0, 1 }};
static float Pdot[4] ={0,0,0,0};
static const char C_0 = 1;
float angle2, angle_dot; 		//外部需要引用的变量
static float q_bias, angle_err, PCt_0, PCt_1, E, K_0, K_1, t_0, t_1;

//-------------------------------------------------------
void Kalman_Filter(float angle_m,float gyro_m)			
{
	angle2+=(gyro_m-q_bias) * dt;
	Pdot[0]=Q_angle - Pk[0][1] - Pk[1][0];
	Pdot[1]=- Pk[1][1];
	Pdot[2]=- Pk[1][1];
	Pdot[3]=Q_gyro;
	
	Pk[0][0] += Pdot[0] * dt;
	Pk[0][1] += Pdot[1] * dt;
	Pk[1][0] += Pdot[2] * dt;
	Pk[1][1] += Pdot[3] * dt;
	
	angle_err = angle_m - angle2;
		PCt_0 = C_0 * Pk[0][0];
	PCt_1 = C_0 * Pk[1][0];
	
	E = R_angle + C_0 * PCt_0;

	K_0 = PCt_0 / E;
	K_1 = PCt_1 / E;

	t_0 = PCt_0;
	t_1 = C_0 * Pk[0][1];

	Pk[0][0] -= K_0 * t_0;
	Pk[0][1] -= K_0 * t_1;
	Pk[1][0] -= K_1 * t_0;
	Pk[1][1] -= K_1 * t_1;

	angle2	+= K_0 * angle_err;
	q_bias	+= K_1 * angle_err;
	angle_dot = gyro_m-q_bias;
}

