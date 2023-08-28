#include "stop_Watch.h"


void main()
{
    lapOn = 0;
    LCD_init();
    DIO_Init(PORTF_ID);
    DIO_configurePin(PORTF_ID, 0,  INPUT_PIN ,ENABLE,ENABLE);
    DIO_configurePin(PORTF_ID, 4,  INPUT_PIN ,ENABLE,ENABLE);
    LCD_wite_cmd_data(LCD_CLEAR_COMMAND,CMD);
    LCD_writ_string("  SW2 to start");
    while(1)
    {
        stopWatch();
    }

}
