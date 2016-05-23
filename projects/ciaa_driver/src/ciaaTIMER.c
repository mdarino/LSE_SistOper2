



#include "ciaaTIMER.h"
#include "os.h"               /* <= operating system header */


void ciaaTIMER1Init(void)
{
   Chip_TIMER_Init(LPC_TIMER1);
   Chip_TIMER_PrescaleSet(LPC_TIMER1,
         Chip_Clock_GetRate(CLK_MX_TIMER1) / 1000000 - 1 );
   Chip_TIMER_MatchEnableInt(LPC_TIMER1, 0);
   Chip_TIMER_ResetOnMatchEnable(LPC_TIMER1, 0);
   Chip_TIMER_StopOnMatchDisable(LPC_TIMER1, 0);
   //Chip_TIMER_SetMatch(LPC_TIMER1, 0, 1000);
   NVIC_EnableIRQ(TIMER1_IRQn);
}

void ciaaTIMER1Enable(void)
{
   Chip_TIMER_Enable(LPC_TIMER1);
}

void ciaaTIMER1Disable(void)
{
   Chip_TIMER_Disable(LPC_TIMER1);
}


void ciaaTIMER1Set(uint32_t usec)
{
   Chip_TIMER_SetMatch(LPC_TIMER1, 0, usec);
   Chip_TIMER_Reset(LPC_TIMER1);
   Chip_TIMER_Enable(LPC_TIMER1);
}


bool ciaaTIMER1Match(uint8_t match){
   return Chip_TIMER_MatchPending(LPC_TIMER1,match);
}


void ciaaTIMER1ClearMatch(uint8_t match){
   Chip_TIMER_ClearMatch(LPC_TIMER1,match);
}


// 
// 
// void ciaaTIMER1Set(uint32_t usec)
// {
//    Chip_TIMER_SetMatch(LPC_TIMER1, 0, usec);
//    Chip_TIMER_Reset(LPC_TIMER1);
//    Chip_TIMER_Enable(LPC_TIMER1);

//    WaitEvent(evTIMER1);
//    ClearEvent(evTIMER1);
//    Chip_TIMER_Disable(LPC_TIMER1);

// }




//copiar en la app 

/* Handler de interrupción del Timer 1 */
/*
void TIMER1_IRQHandler(void)
{
   if (Chip_TIMER_MatchPending(LPC_TIMER1, 0)) {
      SetEvent(evTIMER1);      
   }
   Chip_TIMER_ClearMatch(LPC_TIMER1, 0);
}


*/