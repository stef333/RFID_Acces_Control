/** Generated by YAKINDU Statechart Tools code generator. */


#include "../src/sc_types.h"

#include "rfid_sm.h"

/*! \file Implementation of the state machine 'rfid_sm'
*/

#ifndef SC_UNUSED
#define SC_UNUSED(P) (void)(P)
#endif

/* prototypes of all internal functions */
static void enact_main_region_rfid_r1_INIT(Rfid_sm* handle);
static void enseq_main_region_rfid_r1_INIT_default(Rfid_sm* handle);
static void enseq_main_region_default(Rfid_sm* handle);
static void exseq_main_region_rfid_r1_INIT(Rfid_sm* handle);
static void exseq_main_region(Rfid_sm* handle);
static void react_main_region__entry_Default(Rfid_sm* handle);






void rfid_sm_init(Rfid_sm* handle)
{
	sc_integer i;
	
	for (i = 0; i < RFID_SM_MAX_ORTHOGONAL_STATES; ++i)
	{
		handle->stateConfVector[i] = Rfid_sm_last_state;
	}
	
				
	
	
	
	handle->isExecuting = bool_false;
}

void rfid_sm_enter(Rfid_sm* handle)
{
	/* Activates the state machine. */
	if (handle->isExecuting == bool_true)
	{ 
		return;
	} 
	handle->isExecuting = bool_true;
	/* Default enter sequence for statechart rfid_sm */
	enseq_main_region_default(handle);
	handle->isExecuting = bool_false;
}

void rfid_sm_exit(Rfid_sm* handle)
{
	/* Deactivates the state machine. */
	if (handle->isExecuting == bool_true)
	{ 
		return;
	} 
	handle->isExecuting = bool_true;
	/* Default exit sequence for statechart rfid_sm */
	exseq_main_region(handle);
	handle->isExecuting = bool_false;
}


sc_boolean rfid_sm_is_active(const Rfid_sm* handle)
{
	sc_boolean result = bool_false;
	sc_integer i;
	
	for(i = 0; i < RFID_SM_MAX_ORTHOGONAL_STATES; i++)
	{
		result = result || handle->stateConfVector[i] != Rfid_sm_last_state;
	}
	
	return result;
}

/* 
 * Always returns 'false' since this state machine can never become final.
 */
sc_boolean rfid_sm_is_final(const Rfid_sm* handle)
{
	SC_UNUSED(handle);
	return bool_false;
}

sc_boolean rfid_sm_is_state_active(const Rfid_sm* handle, Rfid_smStates state)
{
	sc_boolean result = bool_false;
	switch (state)
	{
		case Rfid_sm_main_region_rfid :
			result = (sc_boolean) (handle->stateConfVector[SCVI_RFID_SM_MAIN_REGION_RFID] >= Rfid_sm_main_region_rfid
				&& handle->stateConfVector[SCVI_RFID_SM_MAIN_REGION_RFID] <= Rfid_sm_main_region_rfid_r1_INIT);
			break;
		case Rfid_sm_main_region_rfid_r1_INIT :
			result = (sc_boolean) (handle->stateConfVector[SCVI_RFID_SM_MAIN_REGION_RFID_R1_INIT] == Rfid_sm_main_region_rfid_r1_INIT
			);
			break;
		default:
			result = bool_false;
			break;
	}
	return result;
}





/* implementations of all internal functions */

/* Entry action for state 'INIT'. */
static void enact_main_region_rfid_r1_INIT(Rfid_sm* handle)
{
	SC_UNUSED(handle);
	/* Entry action for state 'INIT'. */
	main_sm_init_interface();
}

/* 'default' enter sequence for state INIT */
static void enseq_main_region_rfid_r1_INIT_default(Rfid_sm* handle)
{
	/* 'default' enter sequence for state INIT */
	enact_main_region_rfid_r1_INIT(handle);
	handle->stateConfVector[0] = Rfid_sm_main_region_rfid_r1_INIT;
}

/* 'default' enter sequence for region main region */
static void enseq_main_region_default(Rfid_sm* handle)
{
	/* 'default' enter sequence for region main region */
	react_main_region__entry_Default(handle);
}

/* Default exit sequence for state INIT */
static void exseq_main_region_rfid_r1_INIT(Rfid_sm* handle)
{
	/* Default exit sequence for state INIT */
	handle->stateConfVector[0] = Rfid_sm_last_state;
}

/* Default exit sequence for region main region */
static void exseq_main_region(Rfid_sm* handle)
{
	/* Default exit sequence for region main region */
	/* Handle exit of all possible states (of rfid_sm.main_region) at position 0... */
	switch(handle->stateConfVector[ 0 ])
	{
		case Rfid_sm_main_region_rfid_r1_INIT :
		{
			exseq_main_region_rfid_r1_INIT(handle);
			break;
		}
		default: break;
	}
}

/* Default react sequence for initial entry  */
static void react_main_region__entry_Default(Rfid_sm* handle)
{
	/* Default react sequence for initial entry  */
	enseq_main_region_rfid_r1_INIT_default(handle);
}




