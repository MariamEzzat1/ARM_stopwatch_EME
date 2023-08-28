
#include "stop_watch.h"

/***************************************************************************************************
 *                                   Global variables                                              *
 ***************************************************************************************************/

counter_Mode mode=IDLE; /*initial mode of the stop-watch*/

/***************************************************************************************************
* Function Name: stopWatch
* Parameters (in): None
* Return value: None
* Description:includes the handling of the stop watch states and different inputs As
*                             switch 0 is used for start and pause
*                             switch 4 is used for lap and reset
*
****************************************************************************************************/
void stopWatch(void){
    uint32 i;
            switch (mode)
            {
            case IDLE:
                if(  Get_Bit(GPIO_PORTF_DATA_R,0)==0 )          /*Start condition*/
                {
                    for (i=0;i<50*3100;i++){}   /*to handle the bouncing effect of the push button */
                    SYSTICK_init();
                    mode=START;
                    LCD_wite_cmd_data(LCD_CLEAR_COMMAND,CMD);
                    LCD_writ_string("00:00:00");
                    LCD_wite_cmd_data(0xC0, CMD);
                }
                break;

            case   START:
                if( Get_Bit(GPIO_PORTF_DATA_R,0)==0 )           /*pause condition*/
                {
                    for (i=0;i<50*3100;i++){}
                    Clear_Bit(NVIC_ST_CTRL_R,0);
                    mode=STOP;
                }
                else if( Get_Bit(GPIO_PORTF_DATA_R,4)==0)       /*lap condition*/
                {
                    for (i=0;i<50*3100;i++){}
                    lapOn = 1;   /*lap button detection flag*/

                    if(lapOn){
                    lapTime.hrs = time.hrs;     /*Saves the lap time*/
                    lapTime.mins = time.mins;
                    lapTime.sec = time.sec;

                    println();
                    Print(time);
                    LCD_writ_string("L:");
                    Print(lapTime);
                    }

                }

                break;

            case STOP:
                if(  Get_Bit(GPIO_PORTF_DATA_R,0)==0 )  /*RESUME condition*/
                {
                    for (i=0;i<50*3100;i++){}
                    Set_Bit(NVIC_ST_CTRL_R,0);
                    mode=START;
                }
                else if( Get_Bit(GPIO_PORTF_DATA_R,4)==0)   /*RESET condition*/
                {
                    for (i=0;i<50*3100;i++){}
                    NVIC_ST_CURRENT_R =0;
                    lapOn=0;

                    LCD_wite_cmd_data(LCD_CLEAR_COMMAND,CMD);
                    time.hrs=0;
                    time.mins=0;
                    time.sec=0;
                    SYSTICK_init();
                    mode =START;
                }
                break;
            }
}


