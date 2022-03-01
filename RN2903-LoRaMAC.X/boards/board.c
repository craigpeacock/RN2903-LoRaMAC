
#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include "sx1276-board.h"
#include "board.h"

/*!
 * Flag to indicate if the MCU is Initialized
 */
static bool McuInitialized = false;

void BoardInitPeriph(void)
{
    printf("BoardInitPeriph()\r\n");
}

void BoardInitMcu(void)
{
   printf("BoardInitMcu()\r\n");
   if( McuInitialized == false )
    {

    }
    else
    {

    }   

    SX1276IoInit();

    if( McuInitialized == false )
    {
        McuInitialized = true;
        //SX1276IoDbgInit( );
        //SX1276IoTcxoInit( );
    }

}
