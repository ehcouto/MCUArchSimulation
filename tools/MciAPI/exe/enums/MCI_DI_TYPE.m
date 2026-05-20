classdef(Enumeration) MCI_DI_TYPE < Simulink.IntEnumType
    % Class for handshaking between custom ENUM datatype and Simulinks
  enumeration
    MCI_DI_OVER_TORQUE(0)    
    MCI_DI_MOTOR_STOP(1)      
    MCI_DI_REACHED_TARGET_SPEED(2)
    MCI_DI_IDLE(3)                                      
    MCI_DI_MOTOR_RUNNING(4)      
    MCI_DI_RESIST_ESTIMATED(5)                             
    MCI_DI_NR_OF_DI(6)                                      
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

