#include "pid.h"


void pidInitInc(PID_t *pPID,float kp,float ki,float kd,float targetVal)
{
    // set parameters of pid handler
    pPID->kp = kp;
    pPID->ki = ki;
    pPID->kd = kd;
    pPID->targetVal =targetVal;

    pPID->lastError = 0;
    pPID->prevError = 0;

    return;
    
}

void pidInit(PID_t *pPID,float kp,float ki,float kd,float targetVal,float integralUpperLimit,float integralLowerLimit)
{
    // set parameters of pid handler
    pPID->kp = kp;
    pPID->ki = ki;
    pPID->kd = kd;
    pPID->targetVal =targetVal;

    pPID->integralLowerLimit = integralLowerLimit;
    pPID->integralUpperLimit = integralUpperLimit;

    pPID->errorIntegral = 0;
    pPID->lastError = 0;
    pPID->prevError = 0;

    return;
    

}

float pidCalculateInc(PID_t *pPID,float val)
{
    float ret = 0;
    float error = 0;

    // error  = target - actual
    error = pPID->targetVal - val;

    // increase pid
    ret = (pPID->kp)*((error)-(pPID->lastError))\
            +(pPID->ki)*(error)\
            +(pPID->kd)*((error)-2*(pPID->lastError)+(pPID->prevError));
    
    // storge last error and previous error
    pPID->prevError = pPID->lastError;
    pPID->lastError = error;

    return ret;
}


float pidCalculate(PID_t *pPID,float val)
{
    float ret = 0;
    float error = 0;

    // error  = target - actual
    error = pPID->targetVal - val;

    // error integral
    pPID->errorIntegral += error;

    // limit error integral 
    pPID->errorIntegral = (pPID->errorIntegral - pPID->integralUpperLimit)>0?\
    pPID->integralUpperLimit:pPID->errorIntegral;

    pPID->errorIntegral = (pPID->errorIntegral - pPID->integralLowerLimit)<0?\
    pPID->integralUpperLimit:pPID->errorIntegral;


    ret = (pPID->kp)*(error)+(pPID->ki)*(pPID->errorIntegral)+(pPID->kd)*(pPID->lastError - error);

    pPID->lastError = error;

    return ret;
}

void pidSetTarget(PID_t *pPID,float targetVal)
{
    pPID->targetVal = targetVal;
}