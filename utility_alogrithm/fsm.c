#include "fsm.h"



void fsmInit(FSM_t *pFSM,int transNum,Transition_t *table,int initStatusId)
{
    pFSM->transNum = transNum;
    pFSM->currentStatusId = initStatusId;
    pFSM->initStatusId = initStatusId;
    pFSM->table = table;

}


void fsmRun(FSM_t *pFSM, int eventId, void *param)
{
    // search fsm table , find the tarnsition
    for(int i = 0;i < pFSM->transNum;i++)
    {
        if(pFSM->table[i].eventId == eventId && pFSM->currentStatusId == pFSM->table[i].fromStatus->id)
        {
            // trigge out action of nowStatus
            if(pFSM->table[i].fromStatus->outAction!= NULL)
            {
                pFSM->table[i].fromStatus->outAction(param);
            }

            // set current status
            pFSM->currentStatusId = pFSM->table[i].toStatus->id;

            // trigge in action status
            if(pFSM->table[i].toStatus->inAction != NULL)
            {
                pFSM->table[i].toStatus->inAction(param);
            }
						
						return;
            

        }
    }
}


void fsmReset(FSM_t *pFSM)
{
    pFSM->currentStatusId = pFSM->initStatusId;
}