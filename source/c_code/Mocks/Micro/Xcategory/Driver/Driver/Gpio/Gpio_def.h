/** MOCKUP **/

/**
 *  @file
 *  @defgroup   CLASS_B
 *
 *  @brief      Basic description of file contents
 *
 *  $Header: Gpio_def.h 1.4 2015/07/20 14:06:27EDT MANOEL GARBUIO DE SOUZA (SOUZAMG) Exp  $
 *
 *  @copyright  *****  Copyright 2011-2012.  Whirlpool Corporation.  All rights reserved - CONFIDENTIAL  *****
 */
#ifndef GPIO_DEF_H_
    #define GPIO_DEF_H_


typedef enum
{
    PORT0,
    PORT1,
    PORT2,
    PORT3,
    PORT4,
    PORT5,
    PORTA=10,
    PORTB,
    PORTC,
    PORTD,
    PORTE,
    PORTF,
    PORTH=16,
    PORTJ,
    GPIO_PORT_NUM,
    PORT_NULL = 255
}GPIO_PORT_TYPE;


#endif // GPIO_DEF_H_


