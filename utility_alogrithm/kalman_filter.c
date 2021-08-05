#include "kalman_filter.h"



void kalmanInit(KalmanFilter_t *pKalmanFilter,float R,float Q)
{
    pKalmanFilter->pLast = 0;
    pKalmanFilter->xLast = 0;
    pKalmanFilter->R = R;
    pKalmanFilter->Q = Q;
    return ;
}

float kalmanCalculate(KalmanFilter_t *pKalmanFilter,float val)
{

    float xMid ;
    float xNow;

    float pMid;
    float pNow;

    float kg;

    xMid = pKalmanFilter->xLast;
    pMid = pKalmanFilter->pLast+pKalmanFilter->Q;

    kg = pMid/(pMid+pKalmanFilter->R);
    xNow = xMid + kg*(val-xMid);
    pNow = (1-kg)*pMid;
    pKalmanFilter->pLast = pNow;
    pKalmanFilter->xLast = xNow;

    return xNow;

}