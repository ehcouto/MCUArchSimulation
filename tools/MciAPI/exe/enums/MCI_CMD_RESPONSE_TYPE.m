classdef(Enumeration) MCI_CMD_RESPONSE_TYPE < Simulink.IntEnumType
    % Class for handshaking between custom ENUM datatype and Simulinks
  enumeration
    MCI_CMD_PARAM_NOT_LOADED(-5)  
    MCI_CMD_TIMEOUT(-4)           
    MCI_CMD_RAMP_OUT_OF_RANGE(-3) 
    MCI_CMD_SPEED_OUT_OF_RANGE(-2)
    MCI_CMD_DENIED(-1)            
    MCI_CMD_ACCEPTED(0)                        
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

