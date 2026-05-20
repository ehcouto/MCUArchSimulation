/** MOCKUP **/

//#include "MotorClosedLoopControl.h"
//#include "PSCMotorLoad_Defs.h"
#include "C_Extensions.h"

   //MOTOR_CLOSED_LOOP_PARAM_TYPE param={200,{2324.48,51.48,0,1400,320,0}};

 typedef struct
{
    sint16    P_Gain;                //<! Proportional gain, fixed point, base 1024
    sint16    I_Gain;                //<! Integral gain, fixed point, base 1024
    sint16    D_Gain;                //<! Derivative gain, fixed point, base 1024
    sint16    Output_Min;            //<! Minimum output expected
    sint16    Output_Max;            //<! Maximum output expected
    uint8     DC_Offset;             //<! Offset to be applied in the result
   
}ParamDATA_TYPE;// struct is aliased by ParamDATA_TYPE
extern ParamDATA_TYPE* GetParam(void);
//extern void GetParam(ParamDATA_TYPE* param);
