#ifndef COMPILER_DEFS_H_
#define COMPILER_DEFS_H_


#define LITTLE_ENDIAN

#ifdef BIG_ENDIAN
    #undef BIG_ENDIAN
#endif





//! Define a macro for zero-page memory
#define TINY

//! Define a macro for non-zero-page memory
#define NEAR

//! Define a macro for far address memory
#define FAR

#define inline

#define INTERRUPT_DIRECTIVE

    // define a macro for packed data
    #define PACKED
    #define ENABLE_INTERRUPTS()
    #define DISABLE_INTERRUPTS()
    #define SERVICE_WATCHDOG()
    #define SERVICE_WATCHDOG_STARTUP()
    #define LOW_POWER_MODE()
    #define SYSTEM_RESET()
    #define RESET_STACK_POINTER()
    #define NOP()
    #define NO_INIT
    #define __no_init
    


    #define __UNSIGNED_CHAR_MAX__   (0xFF)

    #define __SIGNED_CHAR_MAX__    (127)
    #define __SIGNED_CHAR_MIN__    (-128)

    #define __UNSIGNED_SHORT_MAX__ (0xFFFF)

    #define __SIGNED_SHORT_MAX__    (32767)
    #define __SIGNED_SHORT_MIN__    (-32768)

    #define __UNSIGNED_LONG_MAX__   (0xFFFFFFFF)
	#define __SIGNED_LONG_MIN__		(-2147483647)
	#define __SIGNED_LONG_MAX__		( 2147483647)

	#define __disable_interrupt()
	#define __enable_interrupt()


#endif