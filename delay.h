
#ifndef DELAY_H_
#define DELAY_H_

/*******************************************************************************
 *                                includes                                     *
 *******************************************************************************/
#include "std_types.h"
#include "hw_gpio.h"
#include "bitwise_operations.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define COUNT_FLAG          16
#define FREQ_FACTOR_ms      4000
#define FREQ_FACTOR_us      4


/*******************************************************************************
 *                               Type Definitions                              *
 *******************************************************************************/
typedef struct {
    uint8 sec;
    uint8 mins;
    uint8 hrs;
}Time;

/*******************************************************************************
 *                               extern variables                              *
 *******************************************************************************/
extern uint8 lapOn;
extern Time lapTime;
extern Time time ;
extern int sec_counter;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

void SYSTICK_init(void);
uint8 intToChar(uint8 int_num);
void Print(Time time);
void println(void);

#endif /* DELAY_H_ */
