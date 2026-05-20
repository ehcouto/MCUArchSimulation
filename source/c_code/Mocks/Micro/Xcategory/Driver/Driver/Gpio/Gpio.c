/** MOCKUP **/

/**
 *  @file       Gpio.c
 *  @brief      Gpio module implemented for Renesas Rx62x family.
 *
 *  @details    Gpio GDM implementation for Rx62x Controllers
 *
 *  $Header: embedded_source/Library/Driver/Gpio/Gpio.c 1.1 2014/07/14 14:07:30EDT MARCELO CAMPOS SILVA (SILVAMC) Exp  $
 *
 *  @copyright  *****  Copyright 2011-2012.  Whirlpool Corporation.  All rights reserved - CONFIDENTIAL  *****
 */

//-------------------------------------- Include Files ----------------------------------------------------------------
#include "C_Extensions.h"
#include "Gpio.h"
#include "Sim.h"

#include "Mcl_prv.h"
#include "Mci_prm.h"

//#define MCL__INIT_TRIAC()                           Gpio__PinConfig(MOTOR_GPIO_PORT, MOTOR_GPIO_PIN, OUTPUT_PUSHPULL);
//#define MCL__SET_TRIAC_ON()                         Gpio__PinWrite(MOTOR_GPIO_PORT, MOTOR_GPIO_PIN, MOTOR_TRIAC_ON_STATE)
//#define MCL__SET_TRIAC_OFF()                        Gpio__PinWrite(MOTOR_GPIO_PORT, MOTOR_GPIO_PIN, !MOTOR_TRIAC_ON_STATE)
//#define MCL__READ_TRIAC_STATE()                     Gpio__PinRead(MOTOR_GPIO_PORT, MOTOR_GPIO_PIN)

//-------------------------------------- PUBLIC (Variables) -----------------------------------------------------------


//-------------------------------------- PRIVATE (Variables, Constants & Defines) -------------------------------------

//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================

//---------------------------------------------------------------------------------------------------------------------
/**
 *    @brief    It Initializes the module Gpio and its variables
 *    @details  Assigns default configuration to port register and calls to Gpio__RefreshConfig
 *              to set default configuration for data direction register of ports as specified
 *              the Gpio_prm.h file
 */
/*
void Gpio__Initialize(void)
{
    //
}

//---------------------------------------------------------------------------------------------------------------------
/**
 *    @brief    This method refreshes the default configuration of the port bits.
 *    @details  Configures port data direction registers as specified in the Gpio_prm.h file
 *              Interrupt are disabled before assigning value to register and enabled after
 *              value is assigned
 
void Gpio__RefreshConfig(void)
{
    //
}

//---------------------------------------------------------------------------------------------------------------------
/**
 *    @brief    This method configures port pin to particular state
 *    @details  Port pin are configured particular state as par the parameter are passed.
 *              Interrupt are disabled  before writing into register and enabled after writing
 *    @param    port: Defines the specific port
 *    @param    pin:  Defines the specific pin
 *    @param    type: Defines the specific type the selected pin will configure as
*/ 
void Gpio__PinConfig(GPIO_PORT_TYPE port,uint8 pin,GPIO_PIN_MODE_TYPE type)
{
    //#define MCL__INIT_TRIAC()  Gpio__PinConfig(MOTOR_GPIO_PORT, MOTOR_GPIO_PIN, OUTPUT_PUSHPULL);
    /*
    if(port==MOTOR_GPIO_PORT)
    {
        //;
    }
    */
}

//---------------------------------------------------------------------------------------------------------------------
/**
 *    @brief    This method writes in a Port bit
 *    @details  Interrupt are disabled before assigning value to register and enabled after
 *              value is assigned
 *    @param    port: Defines the specific port
 *    @param    pin :  Defines the specific pin
 *    @param    value: Defines the value to be written on the port-bit
*/ 
void Gpio__PinWrite(GPIO_PORT_TYPE port,uint8 pin,BOOL_TYPE value)
{
    if(port==MOTOR_GPIO_PORT)
    {
        Sim_Loop_Output[SIM_LOOP_OUT_TRIG]=value;
    }
}

//---------------------------------------------------------------------------------------------------------------------
/**
 *    @brief    This method reads from a Port bit.
 *    @param    port: Defines the specific port
 *    @param    pin:  Defines the specific pin
 *    @return   pin status ON or OFF
 */
BOOL_TYPE Gpio__PinRead(GPIO_PORT_TYPE port,uint8 pin)
 {
	BOOL_TYPE response;
    
    if(port==MOTOR_GPIO_PORT)
    {
        response = Sim_Loop_Output[SIM_LOOP_OUT_TRIG];
    }
	return (response);
    
    //#define MCL__READ_TRIAC_STATE()                     Gpio__PinRead(MOTOR_GPIO_PORT, MOTOR_GPIO_PIN)

}

//---------------------------------------------------------------------------------------------------------------------
/**
 *    @brief    This method configures an entire port
 *    @details  Port are configured to particular state as par the parameter are passed.
 *              Interrupt are disabled  before writing into register and enabled after writing
 *    @param    port: Defines the specific port
 *    @param    type: Defines the specific type the selected port will configure as
 
void Gpio__PortConfig(PORT_DEF port,PIN_TYPE_DEF type)
{
    
}

//---------------------------------------------------------------------------------------------------------------------
/**
 *    @brief    This method writes to a port
 *    @param    port: Defines the specific port
 *    @param    mask: mask will specify which bit is to be affected of port(1 = will be affected, 0 = won't be affected)
 *    @param    value: Defines the value to be written on the port
 
void Gpio__PortWrite(PORT_DEF port,PORT_DATA_TYPE mask, PORT_DATA_TYPE value)
{
    //
}

//---------------------------------------------------------------------------------------------------------------------
/**
 *    @brief    This method reads a port
 *    @param    port: Defines the specific port
 *    @return   read value of port
 
PORT_DATA_TYPE Gpio__PortRead(PORT_DEF port)
{
    return(0);
}


//=====================================================================================================================
//-------------------------------------- Private Functions ------------------------------------------------------------
//=====================================================================================================================

//---------------------------------------------------------------------------------------------------------------------
/**
 *    @brief    This method updates a byte based on a mask
 *    @param    current: port data directions current value
 *    @param    mask: mask will specify which bit is to be affected of port(1 = will be affected, 0 = won't be affected
 *    @param    value: new value to be set port data direction register
 *    @return   unsigned char updated register
 
static unsigned char UpdateMaskedRegister(unsigned char current,unsigned char mask, unsigned char value)
{
    return(0);
}
*/