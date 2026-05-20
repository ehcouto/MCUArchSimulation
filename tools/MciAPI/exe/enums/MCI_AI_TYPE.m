classdef(Enumeration) MCI_AI_TYPE < Simulink.IntEnumType
    % Class for handshaking between custom ENUM datatype and Simulinks
  enumeration
    MCI_AI_TARGET_SPEED_RPM_S16(0)   
    MCI_AI_SPEED_REFERENCE_RPM_S16(1)    
    MCI_AI_ACTUAL_SPEED_S16(2)           
    MCI_AI_SPEED_ERROR_RPM_S16(3)                                           
    MCI_AI_MEAN_SPEED_S16(4)             
    MCI_AI_RMS_MOTOR_CURRENT_S16(5)     
    MCI_AI_ACTIVE_POWER_S16(6)           
    MCI_AI_SHAFT_POWER_S16(7)                                               
    MCI_AI_MOTOR_TEMP_S16(8)            
    MCI_AI_STATOR_TEMP_S16(9)            
    MCI_AI_LOAD_TORQUE_S16(10)            
    MCI_AI_SHAFT_POSITION_DEG_S16(11)                                        
    MCI_AI_BUS_CURRENT_S16(12)           
    MCI_AI_BUS_VOLTAGE_S16(13)            
    MCI_AI_INVERTER_TEMP_S16(14)          
    MCI_AI_INVERTER_TEMP_RAW_DATA(15)                                       
    MCI_AI_VOLTAGE_PHASE_A_S16(16)        
    MCI_AI_VOLTAGE_PHASE_B_S16(17)        
    MCI_AI_VOLTAGE_PHASE_C_S16(18)        
    MCI_AI_SPEED_LOOP_GAIN_TABLE_INDEX(19)                                  
    MCI_AI_CURR_PHASE_A_S16(20)           
    MCI_AI_CURR_PHASE_B_S16(21)           
    MCI_AI_CURR_PHASE_C_S16(22)          
    MCI_AI_STATOR_RESISTANCE_S16(23)
    MCI_AI_INTERNAL_MCI_STATE(24)
    MCI_AI_NR_OF_AI(25)          
   end
   methods (Static = true)
        function retVal = getHeaderFile()
            % GETHEADERFILE  File where type is defined for generated code.
            %   If specified, this file is #included where needed in the code.
            %   Otherwise, the type is written out in the generated code.
            retVal = 'Mci.h';
        end
    end
end

