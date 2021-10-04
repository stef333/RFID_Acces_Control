#include <stdint.h>
#include "stdbool.h"
#include <stdlib.h>

#include "timer.h"
#include "soft_timer.h"


#define SOFT_TIMER_BASE_CURRENT_TICK	get_tick_ms()	

/* Soft Timer allocation state type. */
typedef enum
{
    STATE_FREE,                                                         /**< The timer node is available. */
    STATE_ALLOCATED														/**< The timer node has been allocated. */
} timer_alloc_state_t;

/* Software timer node type. */
typedef struct
{
	timer_alloc_state_t         state;									/**< Timer allocation state. */
	soft_timer_mode_t           mode;                                   /**< Timer mode. */
	uint32_t                    ticks_at_start;                         /**< Number of ticks from previous timer interrupt to timer expiry. */
	uint32_t                    ticks_period;							/**< Timer period (for repeating timers). */
	bool                        is_running;                             /**< True if timer is running, False otherwise. */
	soft_timer_timeout_handler_t p_timeout_handler;                     /**< Pointer to function to be executed when the timer expires. */
	void *                      p_context;                              /**< General purpose pointer. Will be passed to the timeout handler when the timer expires. */
} timer_node_t;


static timer_node_t soft_timer_array[MAX_SOFT_TIMERS_NUM];

/* Set of available timer operation types. */
typedef enum
{
    TIMER_OP_TYPE_NONE,                                                /**< Invalid timer operation type. */
    TIMER_OP_TYPE_START,                                               /**< Timer operation type Start. */
    TIMER_OP_TYPE_STOP,                                                /**< Timer operation type Stop. */
    TIMER_OP_TYPE_STOP_ALL                                             /**< Timer operation type Stop All. */
} timer_user_op_type_t;


/**@brief Function for executing an SOFTWARE timeout handler.
 *
 * @param[in]  p_timer   Pointer to expired timer.
 */
static void timeout_handler_exec(timer_node_t * p_timer)
{
    p_timer->p_timeout_handler(p_timer->p_context);
}

/**@brief Function for checking for expired timers.
 */
void soft_timer_timeouts_check(void)
{
	uint32_t current_ticks = get_tick_ms();
	for (uint8_t i = 0; i < MAX_SOFT_TIMERS_NUM; i++)
    {
        if (soft_timer_array[i].state == STATE_ALLOCATED)
		{
			if (soft_timer_array[i].is_running)
			{
				/** 
				  * This (unsigned) implicit conversion is very important to avoid error during the tick overflow !!!
				  * 
				  */
				if ((uint32_t)(current_ticks - soft_timer_array[i].ticks_at_start) >= (uint32_t)soft_timer_array[i].ticks_period)
				{
					if (soft_timer_array[i].mode == SOFT_TIMER_MODE_REPEATED)
					{
						soft_timer_array[i].ticks_at_start = current_ticks;
					}
					else
					{
						soft_timer_array[i].is_running = false;
					}
					
					// Execute timer handler
					timeout_handler_exec(&soft_timer_array[i]);
					// break if only one timer handler execution per tick is allowed
					break;
				}
			}
		}
	}
}


void soft_timers_init(void)
{	
	for (uint8_t i = 0; i < MAX_SOFT_TIMERS_NUM; i++)
    {
		soft_timer_array[i].state = STATE_FREE;
        soft_timer_array[i].is_running = false;
    }
}


uint32_t soft_timer_create(	soft_timer_id_t     			p_timer_id,
							soft_timer_mode_t            	mode,
							soft_timer_timeout_handler_t 	timeout_handler)
{
    // Check state and parameters
    if (timeout_handler == NULL)
    {
        return TMR_FAIL;
    }
	
	if (p_timer_id < 0)
    {
        return TMR_FAIL;
    }  
	
	if (p_timer_id >= MAX_SOFT_TIMERS_NUM)
	{
		return TMR_FAIL;
	} 
    
    // Find free timer
    for (uint8_t i = 0; i < MAX_SOFT_TIMERS_NUM; i++)
    {
        if (soft_timer_array[i].state == STATE_FREE)
        {
			// Create timer
            soft_timer_array[i].state             = STATE_ALLOCATED;
            soft_timer_array[i].mode              = mode;
            soft_timer_array[i].p_timeout_handler = timeout_handler;
			
			return TMR_SUCCESS;
        }
    }
    // All timer nodes already allocated
    return TMR_FAIL;
}

uint32_t soft_timer_start(soft_timer_id_t timer_id, uint32_t timeout_ticks, void * p_context)
{
    
    // Check state and parameters
    if (soft_timer_array == NULL)
    {
        return TMR_FAIL;
    }
    if (timer_id >= MAX_SOFT_TIMERS_NUM)
    {
        return TMR_FAIL;
    }
	if (soft_timer_array[timer_id].state != STATE_ALLOCATED)
    {
        return TMR_FAIL;
    }
    if (timeout_ticks < SOFT_TIMER_MIN_TIMEOUT_TICKS)
	{
		return TMR_FAIL;
	}
	soft_timer_array[timer_id].is_running = false; // prevent handler execution if timer is already running
	soft_timer_array[timer_id].ticks_at_start = SOFT_TIMER_BASE_CURRENT_TICK; 
	soft_timer_array[timer_id].ticks_period = timeout_ticks;
	soft_timer_array[timer_id].p_context = p_context;
	soft_timer_array[timer_id].is_running = true;
	
    return TMR_SUCCESS;
}

uint32_t soft_timer_stop(soft_timer_id_t timer_id)
{
    // Check state and parameters
    if (timer_id >= MAX_SOFT_TIMERS_NUM)
    {
        return TMR_FAIL;
    }
    if (soft_timer_array[timer_id].state != STATE_ALLOCATED)
    {
        return TMR_FAIL;
    }
    
    soft_timer_array[timer_id].is_running = false;
	return TMR_SUCCESS;
}

uint32_t soft_timer_stop_all(void)
{
    // Check state
    if (soft_timer_array == NULL)
    {
        return TMR_FAIL;
    }
	
	for (uint8_t i = 0; i < MAX_SOFT_TIMERS_NUM; i++)
    {
        if (soft_timer_array[i].state == STATE_ALLOCATED)
        {
			soft_timer_array[i].is_running = false;
        }
    }
	
    return TMR_SUCCESS;
}

void soft_timer_change_period(soft_timer_id_t timer_id, uint16_t period)
{
	soft_timer_array[timer_id].ticks_period = period;
}

int8_t soft_timer_get_id(soft_timer_id_t *id)
{
	static soft_timer_id_t tmr_id = 0;

	//TODO decrease the tmr ID when timer is cleared
	if (tmr_id < MAX_SOFT_TIMERS_NUM)
	{
		*id = tmr_id++;
		return TMR_SUCCESS;
	}
	else
	{
		return TMR_FAIL;
	}
}
