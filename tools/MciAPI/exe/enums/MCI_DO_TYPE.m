classdef(Enumeration) MCI_DO_TYPE < Simulink.IntEnumType
    % Class for handshaking between custom ENUM datatype and Simulinks
  enumeration
    MCI_DO_SET_DYN_BRAKE_ACTIVE(0)
    MCI_DO_FORCE_RES_MEAS(1)         
    MCI_DO_IMPROVE_SENSING(2)        
    MCI_DO_CLEAR_RES_ESTIMATED_FLAG(3)                               
    MCI_DO_NR_OF_DO(4)                
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

