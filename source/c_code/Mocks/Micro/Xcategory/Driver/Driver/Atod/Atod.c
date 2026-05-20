/** MOCKUP **/

/* to read sensors data from Simulation Environment and pass to MCI */

//-------------------------------------- Include Files ----------------------------------------------------------------
#include "Atod.h"
#include "Sim.h"
#include "Mcl_prv.h"
//#include "MciSimple_prv.h"
//#include "MciSlfac_prv.h"

//#define MCI_CURRENT_CHANNEL                 ATOD_CH4
//#define MCI_VOLTAGE_CHANNEL                 ATOD_CH5
//#define MCI_HALL_CHANNEL                    ATOD_CH0

//-------------------------------------- Public Functions ----------------------------------------------------------------

uint16 Atod__Convert(ATOD_CHANNEL_DEF channel, ATOD_CHANNEL_RESOLUTION_DEF resolution)
{
    uint16 response;
    if(channel == MCI_CURRENT_CHANNEL)
    {
        response = Sim_Loop_Input[SIM_LOOP_IN_CURRENT];
    }
    else if(channel == MCI_VOLTAGE_CHANNEL)
    {
        response = Sim_Loop_Input[SIM_LOOP_IN_VOLTAGE];
    }
    else if(channel == MCI_HALL_CHANNEL)
    {
        response = Sim_Loop_Input[SIM_LOOP_IN_HALL];
    }
    return (response);
}

// DEBUG FUNCTIONS
void Atod_Output_Current(uint16 value)
{
  //Sim_Loop_Output[SIM_LOOP_OUT_CURRENT_DEBUG]=value;
}

void Atod_Output_Voltage(uint16 value)
{
  //Sim_Loop_Output[SIM_LOOP_OUT_VOLTAGE_DEBUG]=value;
}

void Atod_Output_Hall(uint16 value)
{
  //Sim_Loop_Output[SIM_LOOP_OUT_HALL_DEBUG]=value;
}

//----------------------------------------------------------------------------------------------------------------


