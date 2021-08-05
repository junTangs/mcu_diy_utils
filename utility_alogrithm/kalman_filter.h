
#ifndef __KALMAN_FILTER__H__
#define __KALMAN_FILTER__H__

typedef struct KalmanFilter
{

    float R; // measure noise R
    float Q; // process noise Q

    float xLast;
    float pLast;
        
}KalmanFilter_t;

 
void kalmanInit(KalmanFilter_t *pKalmanFilter,float R,float Q);

float kalmanCalculate(KalmanFilter_t *pKalmanFilter,float val);



#endif  //!__KALMAN_FILTER__H__