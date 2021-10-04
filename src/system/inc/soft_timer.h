/*
 * timer.h
 *
 * Created: 2/10/2021 8:34:08 PM
 *  Author: Radovan
 */ 


#ifndef SOFT_TIMER_H_
#define SOFT_TIMER_H_

#define TMR_SUCCESS		0
#define TMR_FAIL		1

#define MAX_SOFT_TIMERS_NUM				10
#define SOFT_TIMER_TICK_MS				1
#define SOFT_TIMER_MIN_TIMEOUT_TICKS	10

/**@brief Timer id type. */
typedef uint32_t soft_timer_id_t;

/**@brief Software timeout handler type. */
typedef void (*soft_timer_timeout_handler_t)(void * p_context);


/**@brief Timer modes. */
typedef enum
{
    SOFT_TIMER_MODE_SINGLE_SHOT,                 /**< The timer will expire only once. */
    SOFT_TIMER_MODE_REPEATED                     /**< The timer will restart each time it expires. */
} soft_timer_mode_t;


void soft_timers_init(void);

void soft_timer_timeouts_check(void);

/**@brief Function for creating a timer instance.
 *
 * @param[out] p_timer_id        Id of the newly created timer.
 * @param[in]  mode              Timer mode.
 * @param[in]  timeout_handler   Function to be executed when the timer expires.
 *
 * @retval     0	Timer was successfully created.
 * @retval     1   	Invalid parameter, or maximum number of timers has already been reached.
 */
uint32_t soft_timer_create( soft_timer_id_t              p_timer_id,
                            soft_timer_mode_t            mode,
                            soft_timer_timeout_handler_t timeout_handler);
						  
/**@brief Function for starting a timer.
 *
 * @param[in]  timer_id        Id of timer to start.
 * @param[in]  timeout_ticks   Number of ticks to timeout event
 * @param[in]  p_context       General purpose pointer. Will be passed to the timeout handler when the timer expires.
 *
 * @retval     0   Timer was successfully started.
 * @retval     1   Invalid parameter, or software timer module has not been initialized, or timer has not been created.
 */
uint32_t soft_timer_start(soft_timer_id_t timer_id, uint32_t timeout_ticks, void * p_context);

/**@brief Function for stopping the specified timer.
 *
 * @param[in]  timer_id   Id of timer to be stopped.
 *
 * @retval     0   Timer was successfully stopped.
 * @retval     1   Invalid parameter, software timer module has not been initialized, or timer has not been created.
 */
uint32_t soft_timer_stop(soft_timer_id_t timer_id);

/**@brief Function for stopping all running timers.
 *
 * @retval     0   All timers were successfully stopped.
 * @retval     1   Software timer module has not been initialized.
 */
uint32_t soft_timer_stop_all(void);

void soft_timer_change_period(soft_timer_id_t timer_id, uint16_t period);

int8_t soft_timer_get_id(soft_timer_id_t *tmr_id);


#endif /* SOFT_TIMER_H_ */
