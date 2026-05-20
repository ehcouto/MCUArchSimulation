classdef(Enumeration) MCI_AO_TYPE < Simulink.IntEnumType
    % Class for handshaking between custom ENUM datatype and Simulinks
  enumeration
    MCI_AO_SPEED_LOOP_PROP_GAIN_S16(0)  
    MCI_AO_SPEED_LOOP_INT_GAIN_S16(1)   
    MCI_AO_SPEED_LOOP_GAIN_TABLE_INDEX(2)
    MCI_AO_SPEED_FIR_TAPS_TABLE_INDEX(3)                                  
    MCI_AO_SOFTSTART_COUNTER_INDEX(4)   
    MCI_AO_SPEED_LIMIT_INDEX(5)         
    MCI_AO_MCL_PARAMETERS_ADDRESS(6)    
    MCI_AO_ADD_DELTA_SPEED_REF_S16(7)                                    
    MCI_AO_MOTOR_TEMPERATURE_S16(8)                                       
    MCI_AO_NR_OF_AO(9)                                                    
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

