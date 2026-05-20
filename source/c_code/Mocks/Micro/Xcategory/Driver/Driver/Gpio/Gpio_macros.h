/** MOCKUP **/

/**
 *  @file       Gpio_macros.h
 *  @brief      Thre's a default for each register which is applied to the register when Gpio__Initialize and
 *              Gpio__RefreshConfig are called.
 *              -If the DEFAULT register is not defined, the specific register is not affected.
 *              -If the DEFAULT register is defined and the MASK is not defined for that specific port the register
 *               will be fully overwritten by the default.
 *              -If the DEFAULT register is defined and MASK is also defined for that specific port,
 *               the register will be affected by the DEFAULT value only on the bits set to 1 in the MASK define.
 *  $Header: embedded_source/Library/Driver/Gpio/Gpio_macros.h 1.1 2014/07/14 14:07:27EDT MARCELO CAMPOS SILVA (SILVAMC) Exp  $
 *
 *  @copyright  *****  Copyright 2011-2012.  Whirlpool Corporation.  All rights reserved - CONFIDENTIAL  *****
 */
#ifndef GPIO_MACROS_H_
	#define GPIO_MACROS_H_

#include "Gpio.h"

//=====================================================================================================================
//-------------------------------------- PUBLIC (Extern Variables, Constants & Defines) -------------------------------
//=====================================================================================================================
//extern const unsigned char GPIO_SET_MASK[];
//extern const unsigned char GPIO_CLR_MASK[];

//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================
#define GPIO__PIN_SET(PORT, PORTBIT)                //{((PORT)->DR.BYTE) |=GPIO_SET_MASK[PORTBIT];}
#define GPIO__PIN_CLR(PORT, PORTBIT)                //{((PORT)->DR.BYTE) &=GPIO_CLR_MASK[PORTBIT];}
#define GPIO__PIN_TOGGLE(PORT, PORTBIT)             //   {((PORT)->DR.BYTE) ^= GPIO_SET_MASK[PORTBIT];}


#define GPIO__PORT_SET(PORT,MASK)                   //{((PORT)->DR.BYTE) |= (MASK);}
#define GPIO__PORT_CLR(PORT,MASK)                   //{((PORT)->DR.BYTE) &= ~(MASK);}

#define GPIO__PIN_READ(PORT, PORTBIT)               Gpio__PinRead((PORT), (PORTBIT))
#define GPIO__PORT_READ(PORT)                       0 //((PORT)->PORT.BYTE)

//((REGDEF_LO volatile __data13 *)PORT + 2)
#define GPIO__PIN_COFIG_I_FLOAT(PORT, PORTBIT)      //{((PORT)->DDR.BYTE) &= GPIO_CLR_MASK[PORTBIT];  ((PORT)->ICR.BYTE) &= GPIO_CLR_MASK[PORTBIT];}
#define GPIO__PIN_COFIG_I_PULLUP(PORT, PORTBIT)     //{((PORT)->DDR.BYTE) &= GPIO_CLR_MASK[PORTBIT];  ((PORT)->ICR.BYTE) &= GPIO_CLR_MASK[PORTBIT];}
#define GPIO__PIN_COFIG_O_PUSHPULL(PORT, PORTBIT)   //{((PORT)->DDR.BYTE) |= GPIO_SET_MASK[PORTBIT];  ((PORT)->ICR.BYTE) &= GPIO_CLR_MASK[PORTBIT];}
#define GPIO__PIN_COFIG_O_OPENDRAIN(PORT, PORTBIT)  //{((PORT)->DDR.BYTE) |= GPIO_SET_MASK[PORTBIT];  ((PORT)->ICR.BYTE) &= GPIO_CLR_MASK[PORTBIT];}

#endif // GPIO_MACROS_H_


