
#include "timer.h"

void RtcInit( void );
uint32_t RtcSetTimerContext( void );
uint32_t RtcGetMinimumTimeout( void );
uint32_t RtcMs2Tick( TimerTime_t milliseconds );
void RtcSetAlarm( uint32_t timeout );
void RtcStopAlarm( void );
uint32_t RtcGetTimerElapsedTime( void );

