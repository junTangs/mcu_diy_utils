
#ifndef __PID_H__
#define __PID_H__


#define PID_FLOAT_ESP (1e-3)

typedef struct PID{
    float kp; //kp
    float ki; //ki
    float kd; //kd

    float lastError;//last error e(k-1)
    float prevError;// previous error e(k-2)

    float targetVal; // target value 

    float errorIntegral; // error integral \sum{e}
    float integralUpperLimit;// integral upper limit
    float integralLowerLimit;// integral lower limit

}PID_t ;

void pidInitInc(PID_t *pPID,float kp,float ki,float kd,float targetVal);

void pidInit(PID_t *pPID,float kp,float ki,float kd,float targetVal,float integralUpperLimit,float integralLowerLimit);


float pidCalculateInc(PID_t *pPID,float val);

float pidCalculate(PID_t *pPID,float val);

void pidSetTarget(PID_t *pPID,float targetVal);



#endif