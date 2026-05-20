/**
 *    @file
 *    @brief    It includes the declarations for enumerations and methods used in ZeroCross GDM
 *
 *    @details  This file includes the declarations for enumerations "ZEROCROSS_EVENT_TYPE" - this depicts events generated when
 *              four angles (0, 180 on zeros, 90, 270 on peaks) or zero cross lost signal is detected,
 *              and declarations of all ZeroCross APIs
 *              Add descriptions of all selectable features to the following list:
 *
 *  ZC_ALLOWED_MIN_FREQUENCY	Minimum allowed ZeroCross frequency in Hz (default is 45)
 *  ZC_ALLOWED_MAX_FREQUENCY	Maximum allowed ZeroCross frequency in Hz (default is 65)
 *  ZC_ADVANCE_PULSE_DELAY		Timing between real Zero event and edge detected by ZeroCross signal in us
 *  ZC_HANDLER_TIMING_US        Set ZeroCross periodic timing reading in us; if 0 detects using External Interrupts
 *  ZC_TRIGGER_EDGE				Trigger event to detect ZeroCross zero degree event (EXTINT_TRG_RISE or EXTINT_TRG_FALL)
 *  ZC_DEBOUNCE_CYCLE			Debounce events before ZeroCross signal is considered valid
 *  ZC_MAX_CYCLE_TIMEOUT		Timeout for ZeroCross lost signal event
 *
 *  if ZC_HANDLER_TIMING_US is not 0 (ZeroCross polling every ZC_HANDLER_TIMING_US):
 *
 *  ZC_NUM_GPIO_REQUESTS		Enables Gpio Requests to trigger ON/OFF in ZeroCross angles (0 feature disabled)
 *  ZC_NUM_ATOD_REQUESTS		Enables Atod reading every ZC_HANDLER_TIMING_US
 *  ZC_ATOD_BUFFER_US			Provides Atod buffer reading in us
 *  ZC_FAST_HANDLER_CALL		Perform SRMain__FastTimerISR() call - MAIN_FAST_HANDLER_FEATURE should be set to ENABLED in SRMain_prv.h
 *                              * Please limit use of this feature to the least possible - better would be to keep it DISABLED *
 *
 * @brief  - Advance delay in micro-seconds
 *
 * @details - This configuration is very important.This configuration defines Timing gaps between Actual zero cross signal detected on main sin wave
 *            & actual Load firing edge with respect to that zero cross signal.
 *            This Load firing time is most of the time not match(Leading) with Actual Zero cross signal detected on main sin wave
 *
 * @note -    In below waveform there is a timing gap of T1,T3 between Actual Zero cross signal on mains Sin wave & Load firing edge.
 *            Loads are not firing exactly on that points where mains sin wave zero cross detect.This timing(T1,T3) get different with different hardware(Not fix).
 *            User should calculate this timing gap and assign the value on ZC_ADVANCE_PULSE_DELAY macro .
 *            this macro will take care to fire the loads on exact Zero cross signal on mains Sin wave.
 *            suppose T1 time gap is 4ms then define macro as below
 *
 *            #define ZC_ADVANCE_PULSE_DELAY          4000
 *
 *            if there is no any time gap between Actual Zero cross signal on mains Sin wave & Load firing edge . then Assign the macro as below
 *
 *            #define ZC_ADVANCE_PULSE_DELAY          0
 *
 *
 *
 *                            |   |               |   |    |               |     |
 *                            |   |<--triac on--->|   |    |<---triac on-->|     |
 *                            |   |               |   T2   |               |     |
 *                            |T1 |               |<------>|--triac off    |     |
 *                 triac off--|<->|               |   | T3 |               |<--->|--triac off
 *                            |   |               |   |    |       -       |     |
 *                            |   |               |   |    |   -       -   |     |
 *                            |   |               |   |    |-             -|     |
 *                            |   |               |   |  - |               |  -  |
 *                          - |   |               |   |-   |               |    -|
 *                     -------------------------------------------------------------------------- Sine Wave
 *                            | - |                  -|
 *                            |   -                -  |
 *                            |   | -           -     |
 *                            |   |    -      -       |
 *                            |   |        -          |
 *                            |                       |
 *                            |
 *                            |    ________________         _______________
 *                            |   |                |       |               |
 *                            |   |                |       |               |
 *                            |___|                |       |               |
 *                                                  -------                 -----------------ZeroCross Signal
 *
 *  @copyright  Copyright 2011-$Date: 2015/07/14 17:37:57EDT $. Whirlpool Corporation. All rights reserved - CONFIDENTIAL
 */
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------

#ifndef ZEROCROSS_H
	#define ZEROCROSS_H
#include "C_Extensions.h"
//#include "ZeroCross_prm.h"
//#include "ExtInterrupt.h"
#include "Timer.h"
#include "Gpio.h"
#include "Atod.h"

//=====================================================================================================================
//-------------------------------------- PUBLIC (Extern Variables, Constants & Defines) -------------------------------
//=====================================================================================================================

typedef enum ZEROCROSS_EVENT_ENUM
{
	ZEROCROSS_NO_EVENT = 0,
	ZEROCROSS_ANGLE_0_EVENT,
	ZEROCROSS_ANGLE_90_EVENT,
	ZEROCROSS_ANGLE_180_EVENT,
	ZEROCROSS_ANGLE_270_EVENT,
	ZEROCROSS_BLACKOUT_EVENT
} ZEROCROSS_EVENT_TYPE;

PACKED typedef struct
{
    uint16 Gpio_Id;
    BOOL_TYPE Active_value;    //! For Active High = 1, Active Low = 0
    uint8 Active_Degree;       //! Active Degree for Half semi wave
    uint8 Deactive_Degree;     //! De active Degree for Half semi wave..for continuous on set this value more than 180 degree
} ZEROCROSS_GPIO_REQUEST_TYPE;


#define ZEROCROSS_MINIMUM_ANGLE         0
#define ZEROCROSS_HALF_WAVE_ANGLE		180
#define ZEROCROSS_MAXIMUM_ANGLE         360

#define ZEROCROSS_ID_INVALID		0xFFFF

// Default is to use ExtInterrupt detection
#ifndef 	ZC_HANDLER_TIMING_US
    #define ZC_HANDLER_TIMING_US		0
#endif

// Advance pulse default is 0 - no delay
#ifndef		ZC_ADVANCE_PULSE_DELAY
	#define ZC_ADVANCE_PULSE_DELAY		0
#endif

// ZC Trigger Edge default is on Rising edge
#ifndef		ZC_TRIGGER_EDGE
	#define	ZC_TRIGGER_EDGE				EXTINT_TRG_RISE
#endif

// Debounce Cycle
#ifndef 	ZC_DEBOUNCE_CYCLE
    #define ZC_DEBOUNCE_CYCLE           4
#endif

// Timeout
#ifndef		ZC_MAX_CYCLE_TIMEOUT
	#define ZC_MAX_CYCLE_TIMEOUT		(ZC_DEBOUNCE_CYCLE * 4)
#endif

// ZC Invert Input
#ifndef		ZC_INVERT_INPUT_FEATURE
	#define	ZC_INVERT_INPUT_FEATURE DISABLED
#endif

// Gpio Requests feature is disabled by default
#ifndef		ZC_NUM_GPIO_REQUESTS
	#define ZC_NUM_GPIO_REQUESTS		0
#endif

// Atod Requests feature is disabled by default
#ifndef		ZC_NUM_ATOD_REQUESTS
	#define ZC_NUM_ATOD_REQUESTS		0
#else
	// Default buffer size is set to 10 ms
	#ifndef ZC_ATOD_BUFFER_US
		#define ZC_ATOD_BUFFER_US		10000
	#endif
#endif

// Minimum frequency allowed
#ifndef ZC_ALLOWED_MIN_FREQUENCY
#define ZC_ALLOWED_MIN_FREQUENCY        45
#endif

// Maximum frequency allowed
#ifndef ZC_ALLOWED_MAX_FREQUENCY
#define ZC_ALLOWED_MAX_FREQUENCY        65
#endif

// FastISR support
#ifndef	ZC_FAST_HANDLER_CALL
#define	ZC_FAST_HANDLER_CALL			DISABLED
#endif

//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================
//PASS_FAIL_TYPE ZeroCross__Config(EXTINT_CHNL_TYPE ext_chnl, GPIO_PORT_TYPE ext_port, uint8 ext_pin, uint8 ext_remap, TIMER_TYPE timer, TIMER_CHANNEL_TYPE timer_channel);
void ZeroCross__SignalEvent(void);
void ZeroCross__AsyncHandler(void);
ZEROCROSS_EVENT_TYPE ZeroCross__AngleEvent(void);
uint8 ZeroCross__GetFrequency(void);
uint32 ZeroCross__GetCycleCount(void);
uint16 ZeroCross__GetAngle(void);
ZEROCROSS_EVENT_TYPE ZeroCross__GetLastEvent(void);
uint16 ZeroCross__GetTimeFromLastEvent(void);

uint16 ZeroCross__RegisterGpioActivity(GPIO_PORT_TYPE port, uint8 pin);
PASS_FAIL_TYPE ZeroCross__ReleaseGpioActivity(uint16 gpio_id);
BOOL_TYPE ZeroCross__RequestGpioActivity(ZEROCROSS_GPIO_REQUEST_TYPE *gpio_activity);

uint16 ZeroCross__RegisterAtodActivity(ATOD_CHANNEL_DEF channel, ATOD_CHANNEL_RESOLUTION_DEF resolution);
PASS_FAIL_TYPE ZeroCross__ReleaseAtodActivity(uint16 atod_id);
BOOL_TYPE ZeroCross__IsAtodReadOverrun(uint16 atod_id);
uint16 ZeroCross__CopyAtodSamples(uint16 atod_id, uint16 *buffer, uint16 max_items);


#endif /*ZEROCROSS_H*/
