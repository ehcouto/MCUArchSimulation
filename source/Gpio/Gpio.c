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
#include "Micro.h"
#include "uc.h"

#include "Sim.h"
//-------------------------------------- PUBLIC (Variables) -----------------------------------------------------------


//-------------------------------------- PRIVATE (Variables, Constants & Defines) -------------------------------------
#ifndef GPIO_TABLE_LEN
    #define GPIO_TABLE_LEN  0
#endif

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
 */
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
void Gpio__PinConfig(GPIO_PORT_TYPE port,unsigned char pin,GPIO_PIN_MODE_TYPE type)
{
    //
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
void Gpio__PinWrite(GPIO_PORT_TYPE port,unsigned char pin,BOOL_TYPE value)
{
    int i = 0;
#if (GPIO_TABLE_LEN > 0)
    for (i = 0; i <GPIO_TABLE_LEN; i++)
    {
        if ( (SIM_GPIO_TABLE[i][0] == port) && (SIM_GPIO_TABLE[i][1] == pin) )
        {
            Sim_Loop_Output[SIM_GPIO_TABLE[i][2]] = (value);
        }
    }
#endif
}

//---------------------------------------------------------------------------------------------------------------------
/**
 *    @brief    This method reads from a Port bit.
 *    @param    port: Defines the specific port
 *    @param    pin:  Defines the specific pin
 *    @return   pin status ON or OFF
 */
BOOL_TYPE Gpio__PinRead(GPIO_PORT_TYPE port,unsigned char pin)
{
    unsigned char ret_val;
    int i = 0;

    ret_val = FALSE;
#if (GPIO_TABLE_LEN > 0)
    for (i = 0; i <GPIO_TABLE_LEN; i++)
    {
        if ( (SIM_GPIO_TABLE[i][0] == port) && (SIM_GPIO_TABLE[i][1] == pin) )
        {
            if  (Sim_Loop_Input[SIM_GPIO_TABLE[i][2]] == 0.0f)
            {
                ret_val = FALSE;
            }
            else
            {
                ret_val = TRUE;
            }
        }
    }
#endif
	return(ret_val);
}

//---------------------------------------------------------------------------------------------------------------------
/**
 *    @brief    This method configures an entire port
 *    @details  Port are configured to particular state as par the parameter are passed.
 *              Interrupt are disabled  before writing into register and enabled after writing
 *    @param    port: Defines the specific port
 *    @param    type: Defines the specific type the selected port will configure as
 */
void Gpio__PortConfig(GPIO_PORT_TYPE port,GPIO_PIN_MODE_TYPE type)
{
    //
}

//---------------------------------------------------------------------------------------------------------------------
/**
 *    @brief    This method writes to a port
 *    @param    port: Defines the specific port
 *    @param    mask: mask will specify which bit is to be affected of port(1 = will be affected, 0 = won't be affected)
 *    @param    value: Defines the value to be written on the port
 */
void Gpio__PortWrite(GPIO_PORT_TYPE port,PORT_DATA_TYPE mask, PORT_DATA_TYPE value)
{
    //
}

//---------------------------------------------------------------------------------------------------------------------
/**
 *    @brief    This method reads a port
 *    @param    port: Defines the specific port
 *    @return   read value of port
 */
PORT_DATA_TYPE Gpio__PortRead(GPIO_PORT_TYPE port)
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
 */
static unsigned char UpdateMaskedRegister(unsigned char current,unsigned char mask, unsigned char value)
{
    return(0);
}
