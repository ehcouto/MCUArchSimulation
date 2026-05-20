#ifndef DWT_MACROS_H_
#define DWT_MACROS_H_


#define DWT_BASE    ((uint32)0xE0001000)

/* DWT Register Definition */
 /* DWT (Data Watchpoint and Trace) registers, only exists on ARM Cortex with a DWT unit */
  #define DWT_CONTROL             (*((volatile uint32*)0xE0001000))
    /*!< DWT Control register */
  #define DWT_CYCCNTENA_BIT       (1UL<<0)
    /*!< CYCCNTENA bit in DWT_CONTROL register */
  #define DWT_CYCCNT              (*((volatile uint32*)0xE0001004))
    /*!< DWT Cycle Counter register */
  #define DEMCR                   (*((volatile uint32*)0xE000EDFC))
    /*!< DEMCR: Debug Exception and Monitor Control Register */
  #define DEMCR_TRCENA_BIT              (1UL<<24)
    /*!< Trace enable bit in DEMCR register */



/* DWT Macros for Code profiling */
#define DWT__InitCycleCounter() \
  DEMCR |= DEMCR_TRCENA_BIT
  /*!< TRCENA: Enable trace and debug block DEMCR (Debug Exception and Monitor Control Register */

#define DWT__ResetCycleCounter() \
  DWT_CYCCNT = 0
  /*!< Reset cycle counter */

#define DWT__EnableCycleCounter() \
  DWT_CONTROL |= DWT_CYCCNTENA_BIT
  /*!< Enable cycle counter */

#define DWT__DisableCycleCounter() \
  DWT_CONTROL &= ~DWT_CYCCNTENA_BIT
  /*!< Disable cycle counter */

#define DWT__GetCycleCounter() \
  DWT_CYCCNT
  /*!< Read cycle counter register */




/* USAGE EXAMPLE */

/*
uint32_t cycles;            // number of cycles

DWT__InitCycleCounter();    // enable DWT hardware
DWT__ResetCycleCounter();   // reset cycle counter
DWT__EnableCycleCounter();  // start counting
foo();                      // call function and count cycles
cycles = DWT__GetCycleCounter(); // get cycle counter
DWT__DisableCycleCounter(); // disable counting if not used any more
*/
#endif
