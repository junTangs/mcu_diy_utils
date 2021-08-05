/**
 * @file fsm.h
 * @author Richard Tang (richard_tang_98@163.com)
 * @brief 
 * @version 0.1
 * @date 2021-08-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef __FSM__H__
#define __FSM__H__
#include "stdint.h"
#include "stdlib.h"

/**
 * @brief 
 * 
 */
typedef struct Status
{

    int id; 
    void (*inAction)(void *param);
    void (*outAction)(void *param);
} Status_t;

/**
 * @brief 
 * 
 */
typedef struct Transition
{
    int eventId;
    Status_t *fromStatus;
    Status_t *toStatus;

} Transition_t;

/**
 * @brief 
 * 
 */
typedef struct FSM
{
    int transNum;
    int initStatusId;
    int currentStatusId;
    Transition_t *table;
} FSM_t;


#define newFSMTable(name) (Transition_t ##name[])


/**
 * @brief 
 * 
 * @param pFSM 
 * @param transNum 
 * @param table 
 * @param initStatusId
 */
void fsmInit(FSM_t *pFSM,int transNum,Transition_t *table,int initStatusId);

/**
 * @brief 
 * 
 * @param pFsm 
 * @param eventID 
 * @param param 
 */
void fsmRun(FSM_t *pFSM, int eventId, void *param);

/**
 * @brief 
 * 
 */
void fsmReset(FSM_t *pFSM);

#endif //!__FSM__H__