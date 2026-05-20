function updateBlockUserData(BlockName)
    
    if (evalin('base', 'exist(''config'') == 1'))
        bud.config = evalin('base','config');
    end
    if (evalin('base', 'exist(''Paths'') == 1'))
        bud.Paths = evalin('base','Paths');
    end
    if (evalin('base', 'exist(''DC_Bus'') == 1'))
        bud.DC_Bus = evalin('base','DC_Bus');
    end
    if (evalin('base', 'exist(''InputCircuit'') == 1'))
        bud.InputCircuit = evalin('base','InputCircuit');
    end
    if (evalin('base', 'exist(''Mechanical'') == 1'))
        bud.Mechanical = evalin('base','Mechanical');
    end
    if (evalin('base', 'exist(''Motor'') == 1'))
        bud.Motor = evalin('base','Motor');
    end
    if (evalin('base', 'exist(''Thermal'') == 1'))
        bud.Thermal = evalin('base','Thermal');
    end
    if (evalin('base', 'exist(''TimeSteps'') == 1'))
        bud.TimeSteps = evalin('base','TimeSteps');
    end
    if (evalin('base', 'exist(''Variant_Input_Circuit'') == 1'))
        bud.Variant_Input_Circuit = evalin('base','Variant_Input_Circuit');
    end
    if (evalin('base', 'exist(''Variant_Motor'') == 1'))
        bud.Variant_Motor = evalin('base','Variant_Motor');
    end
    if (evalin('base', 'exist(''Variant_Motor_Control'') == 1'))
        bud.Variant_Motor_Control = evalin('base','Variant_Motor_Control');
    end
    if (evalin('base', 'exist(''Variant_Sensor'') == 1'))
        bud.Variant_Sensor = evalin('base','Variant_Sensor');
    end
    current_bud = get_param(BlockName, 'UserData');
    bud.UUID = current_bud.UUID;
    set_param(BlockName, 'UserData', bud); 
end