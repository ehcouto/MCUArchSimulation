/**
 *    @file
 *    @defgroup   CLASS_B
 *    @brief    Contains controller specific definition for RX66T
 *
 *  @section    Applicable_Documents
 *                  List here all the applicable documents if needed. <tr>
 *
 *    $Header: $
 *
 *    @copyright  Copyright 2016.  Whirlpool Corporation.  All rights reserved - CONFIDENTIAL
 */
//-------------------------------------- Include Files ----------------------------------------------------------------
#ifndef MICRO_DEFS_H_
    #define MICRO_DEFS_H_

//=====================================================================================================================
//-------------------------------------- PUBLIC (Extern Variables, Constants & Defines) -------------------------------
//=====================================================================================================================
#include "uc.h"

typedef enum
{
    MICRO_HI_CLOCK,
    MICRO_HE_CLOCK,
    MICRO_LI_CLOCK
} MICRO_CLOCK_SOURCE_TYPE;

typedef struct
{
    uint32 XTAL_Frequency;          // XTAL or HOCO Clock Frequency.......24MHz (e.g.)
    uint32 BASECLK_Frequency;       // Base Clock Freq............. 120to240Mhz (e.g.)
    uint32 SYSCLK_Frequency;        // Internal Clock Frequency....... ..160MHz (e.g.)
    uint32 PCLKA_Frequency;         // Peripheral Clock Frequency........120MHz (e.g.)
    uint32 PCLKB_Frequency;         // Peripheral Clock Frequency.........60MHz (e.g.)
    uint32 PCLKC_Frequency;         // Peripheral Clock Frequency........160MHz (e.g.)
    uint32 PCLKD_Frequency;         // Peripheral Clock Frequency......8to60MHz (e.g.)
    uint32 FLASH_Frequency;         // Peripheral Clock Frequency......4to60MHz (e.g.)
    uint32 BCLK_Frequency;          // Peripheral Clock Frequency.........60MHz (e.g.)
    MICRO_CLOCK_SOURCE_TYPE ClockSource;
} MICRO_CLOCK_DEF;

#ifndef istate_t
    typedef uint32 istate_t;
#endif

/**
 * @brief The MICRO_DECLARE_INTERRUPT_CONTEXT_LOCAL() macro defines a local variable of the type istate_t
 * @details The local variable will be used to keep the interrupt context in a local scope. The call for this macro should be placed
 * only once in the top of the function along with the local variables declaration.
 * @note
 * <pre>
 * void Function (void)
 * {
 *      variables declaration...
 *      <B>MICRO_DECLARE_INTERRUPT_CONTEXT_LOCAL();</B>
 *
 *      code...
 *      MICRO_SAVE_INTERRUPT_CONTEXT_LOCAL();
 *      protected code 1...
 *      MICRO_RESTORE_INTERRUPT_CONTEXT_LOCAL();
 *
 *      code...
 *      MICRO_SAVE_INTERRUPT_CONTEXT_LOCAL();
 *      protected code 2...
 *      MICRO_RESTORE_INTERRUPT_CONTEXT_LOCAL();
 * }
 * </pre>
 */
#define MICRO_DECLARE_INTERRUPT_CONTEXT_LOCAL()     istate_t local_interrupt_context;

/**
 * @brief The MICRO_SAVE_INTERRUPT_CONTEXT_LOCAL macro saves the interrupt context into the local variable and disable interrupts
 * @details This macro requires the macro MICRO_DECLARE_INTERRUPT_CONTEXT_LOCAL() to be added in the top of the function in order to
 * declare the local variable used to keep the interrupt context.
 * @note
 * <pre>
 * void Function (void)
 * {
 *      variables declaration...
 *      MICRO_DECLARE_INTERRUPT_CONTEXT_LOCAL();
 *
 *      code...
 *      <B>MICRO_SAVE_INTERRUPT_CONTEXT_LOCAL();</B>
 *      protected code 1...
 *      MICRO_RESTORE_INTERRUPT_CONTEXT_LOCAL();
 *
 *      code...
 *      <B>MICRO_SAVE_INTERRUPT_CONTEXT_LOCAL();</B>
 *      protected code 2...
 *      MICRO_RESTORE_INTERRUPT_CONTEXT_LOCAL();
 * }
 * </pre>
 */
#define MICRO_SAVE_INTERRUPT_CONTEXT_LOCAL()        {   local_interrupt_context = __get_interrupt_state(); \
                                                        __disable_interrupt();}

/**
 * @brief The MICRO_RESTORE_INTERRUPT_CONTEXT_LOCAL() macro restores the I bit in the PSW register so restabilishing the interrupt context
 * @details This macro requires the macro MICRO_DECLARE_INTERRUPT_CONTEXT_LOCAL() to be added in the top of the function in order to
 * declare the local variable used to keep the interrupt context.
 * @note
 * <pre>
 * void Function (void)
 * {
 *      variables declaration...
 *      MICRO_DECLARE_INTERRUPT_CONTEXT_LOCAL();
 *
 *      code...
 *      MICRO_SAVE_INTERRUPT_CONTEXT_LOCAL();
 *      protected code 1...
 *      <B>MICRO_RESTORE_INTERRUPT_CONTEXT_LOCAL();</B>
 *
 *      code...
 *      MICRO_SAVE_INTERRUPT_CONTEXT_LOCAL();
 *      protected code 2...
 *      <B>MICRO_RESTORE_INTERRUPT_CONTEXT_LOCAL();</B>
 * }
 * </pre>
 */
#define MICRO_RESTORE_INTERRUPT_CONTEXT_LOCAL()     {   if (local_interrupt_context & 0x00010000) \
                                                        { \
                                                            __enable_interrupt(); \
                                                        } \
                                                    }
//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================

#endif // MICRO_DEFS_H_
