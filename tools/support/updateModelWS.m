function updateModelWS(modelName)
    mws = get_param(modelName, 'modelworkspace');
    if (evalin('base', 'exist(''config'') == 1'))
        mws.assignin('config', evalin('base','config'));
    end
    if (evalin('base', 'exist(''Paths'') == 1'))
        mws.assignin('Paths', evalin('base','Paths'));
    end
    if (evalin('base', 'exist(''DC_Bus'') == 1'))
        mws.assignin('DC_Bus', evalin('base','DC_Bus'));
    end
    if (evalin('base', 'exist(''InputCircuit'') == 1'))
        mws.assignin('InputCircuit', evalin('base','InputCircuit'));
    end
    if (evalin('base', 'exist(''Mechanical'') == 1'))
        mws.assignin('Mechanical', evalin('base','Mechanical'));
    end
    if (evalin('base', 'exist(''Motor'') == 1'))
        mws.assignin('Motor', evalin('base','Motor'));
    end
    if (evalin('base', 'exist(''Thermal'') == 1'))
        mws.assignin('Thermal', evalin('base','Thermal'));
    end
    if (evalin('base', 'exist(''TimeSteps'') == 1'))
        mws.assignin('TimeSteps', evalin('base','TimeSteps'));
    end
    if (evalin('base', 'exist(''Variant_Input_Circuit'') == 1'))
        mws.assignin('Variant_Input_Circuit',evalin('base','Variant_Input_Circuit'));
    end
    if (evalin('base', 'exist(''Variant_Motor'') == 1'))
        mws.assignin('Variant_Motor', evalin('base','Variant_Motor'));
    end
    if (evalin('base', 'exist(''Variant_Motor_Control'') == 1'))
        mws.assignin('Variant_Motor_Control', evalin('base','Variant_Motor_Control'));
    end
    if (evalin('base', 'exist(''Variant_Sensor'') == 1'))
        mws.assignin('Variant_Sensor', evalin('base','Variant_Sensor'));
    end
     if(bdIsLoaded(modelName))
%         save_system(modelName);
     end
end