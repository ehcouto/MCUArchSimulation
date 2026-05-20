/** MOCKUP **/
/* 
calculates parameters for MCI Running Handler and Time Capture handlers 
according to MCI sfunction frequency value
*/

#include "Mcl_prv.h"

#define MCI_SFUN_FREQ_HZ                        (10000*4) // 100kHz FINN, 96kHz Yoda2

#define RUNNING_HANDLER_COUNTS                  MCI_SFUN_FREQ_HZ/MCISLFAC_FAST_HANDLER_FREQUENCY_HZ
//#define RUNNING_HANDLER_COUNTS                  SIMULATION_FREQUENCY_HZ/4800

#define GLOBAL_TIMER_SCALE                      MCISLFAC_TIMER_FREQ_HZ/MCI_SFUN_FREQ_HZ
//#define GLOBAL_TIMER_SCALE                      6000000/SIMULATION_FREQUENCY_HZ