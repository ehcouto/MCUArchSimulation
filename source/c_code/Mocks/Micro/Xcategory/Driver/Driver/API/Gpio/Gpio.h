/** MOCKUP **/

/**
 *  @file       Gpio.h
 *  @brief      Generic Gpio API define
 *
 *  $Header: embedded_source/Library/Driver/Gpio/Gpio.h 1.1 2014/07/14 14:07:31EDT MARCELO CAMPOS SILVA (SILVAMC) Exp  $
 *
 *------------------- Copyright 2011.  Whirlpool Corporation.  All rights reserved - CONFIDENTIAL ---------------------
 *
 */
 
#ifndef GPIO_H                                      // Ensure this file is not compiled again
#define GPIO_H  
// after we compile it the first time
#include "C_Extensions.h"
#include "Gpio_macros.h"
#include "Gpio_def.h"


//=====================================================================================================================
//-------------------------------------- PUBLIC (Extern Variables, Constants & Defines) -------------------------------
//=====================================================================================================================
typedef enum
{
    INPUT_FLOAT,
    INPUT_PULLUP,
    INPUT_PULLDOWN,
    INPUT_ANALOG,
    SPECIAL_FUNCTION_OPEN_DRAIN,
    SPECIAL_FUNCTION_PUSH_PULL,
    OUTPUT_PUSHPULL,
    OUTPUT_OPEN_DRAIN,
    PIN_TYPE_NUM
} GPIO_PIN_MODE_TYPE;

// PACKED typedef struct
// {
//     GPIO_PORT_TYPE port;
// 	uint8 pin;
// 	GPIO_PIN_MODE_TYPE type;
// }GPIO_PORTBIT_TYPE;

//#define PORT_DEF  volatile GPIO_TYPE *
#define PORT_DATA_TYPE  unsigned char
//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================
// void Gpio__Initialize(void);
// void Gpio__RefreshConfig(void);
// 
void Gpio__PinConfig(GPIO_PORT_TYPE port,uint8 pin,GPIO_PIN_MODE_TYPE type);
void Gpio__PinWrite(GPIO_PORT_TYPE port,uint8 pin,BOOL_TYPE value);
BOOL_TYPE Gpio__PinRead(GPIO_PORT_TYPE port,uint8 pin);


#endif


