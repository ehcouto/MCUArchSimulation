/** MOCKUP **/

#include "SettingFile.h"
 
     ParamDATA_TYPE* GetParam(void)
      {
     ParamDATA_TYPE param;
           
     param.P_Gain                     =1.7*16384;//2.27*1024//1.7*16384
     param.I_Gain                     =0.03*16384;//0.05*1024//0.03*16384
     param.D_Gain                     =0.01*16384;//0.01*16384
     param.Output_Min                 = 0.2*16384;//0.2*16384
     param.Output_Max                 = 1*16384;//1*16384
     param.DC_Offset                  =0 ; 
             
     return (&param);
    }
