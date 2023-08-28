#include "delay.h"
#include "LCD.h"

/***************************************************************************************************
 *                                   Global variables                                              *
 ***************************************************************************************************/
Time time ;
uint8 lapOn;
Time lapTime;


/***************************************************************************************************
* Function Name:  systick_handler
* Parameters (in): None
* Return value: None
* Description: handler which will be executed each second
*
****************************************************************************************************/
void systick_handler(void)
{
    LCD_wite_cmd_data(LCD_CLEAR_COMMAND,CMD);
    LCD_wite_cmd_data(0x80,CMD);
    if(time.sec==59){
        time.sec=0;

        if(time.mins== 59){
            time.mins=0;
            time.hrs++;
        }
        else{
            time.mins++;
        }
    }
    else{
        time.sec++;
    }

    Print(time);
    if(lapOn==1){
       println();
       LCD_writ_string("L:");
        Print(lapTime);
    }
}


/***************************************************************************************************
* Function Name:  SYSTICK_init
* Parameters (in): None
* Return value: None
* Description: SYSTICK timer initialization
*
****************************************************************************************************/

void SYSTICK_init()
{
    NVIC_ST_RELOAD_R  =16000000-1;
    NVIC_ST_CURRENT_R =0;
    NVIC_ST_CTRL_R =0x07;
}

/***************************************************************************************************
* Function Name:  intToChar
* Parameters (in): uint8 int_num
* Return value: uint8 character
* Description: converts the given number to a character
*
****************************************************************************************************/
uint8 intToChar(uint8 int_num)
{

    return (int_num += '0');
}


/***************************************************************************************************
* Function Name:  Print
* Parameters (in): Time time
* Return value: None
* Description: print the given time in the format (hours:minutes:seconds)
*
****************************************************************************************************/
void Print(Time time)
{
    uint8 num,num_1st_digit;
    num=(time.hrs)/10;
    LCD_wite_cmd_data(intToChar(num),DATA);
    num_1st_digit=(time.hrs)%10;


    LCD_wite_cmd_data(intToChar(num_1st_digit),DATA);
    LCD_writ_string(":");
    num=(time.mins)/10;


    LCD_wite_cmd_data(intToChar(num),DATA);
    num_1st_digit=(time.mins)%10;
    LCD_wite_cmd_data(intToChar(num_1st_digit),DATA);
    LCD_writ_string(":");
    num=(time.sec)/10;


    LCD_wite_cmd_data(intToChar(num),DATA);
    num_1st_digit=(time.sec)%10;
    LCD_wite_cmd_data(intToChar(num_1st_digit),DATA);
    }
/***************************************************************************************************
* Function Name:  println
* Parameters (in): None
* Return value: None
* Description: inserts new line
*
****************************************************************************************************/
void println(void){
    LCD_writ_string("        ");
    LCD_writ_string("        ");
    LCD_writ_string("        ");
    LCD_writ_string("        ");
}

