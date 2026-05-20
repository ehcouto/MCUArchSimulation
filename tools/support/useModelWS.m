function useModelWS(modelName)
    mws = get_param(modelName, 'modelworkspace');
    if (mws.hasVariable('config'))
        assignin('base','config',mws.getVariable('config'));
    end
    if (mws.hasVariable('Paths'))
        assignin('base','Paths',mws.getVariable('Paths'));
    end
    if (mws.hasVariable('DC_Bus'))
        assignin('base','DC_Bus',mws.getVariable('DC_Bus'));
    end
    if (mws.hasVariable('InputCircuit'))
        assignin('base','InputCircuit',mws.getVariable('InputCircuit'));
    end
    if (mws.hasVariable('Mechanical'))
        assignin('base','Mechanical',mws.getVariable('Mechanical'));
    end
    if (mws.hasVariable('Motor'))
        assignin('base','Motor',mws.getVariable('Motor'));
    end
    if (mws.hasVariable('Thermal'))
        assignin('base','Thermal',mws.getVariable('Thermal'));
    end
    if (mws.hasVariable('Variant_Input_Circuit'))
        assignin('base','Variant_Input_Circuit',mws.getVariable('Variant_Input_Circuit'));
    end
    if (mws.hasVariable('Variant_Motor'))
        assignin('base','Variant_Motor',mws.getVariable('Variant_Motor'));
    end
    if (mws.hasVariable('Variant_Motor_Control'))
        assignin('base','Variant_Motor_Control',mws.getVariable('Variant_Motor_Control'));
    end
    if (mws.hasVariable('Variant_Sensor'))
        assignin('base','Variant_Sensor',mws.getVariable('Variant_Sensor'));
    end
    if (mws.hasVariable('TimeSteps'))
        assignin('base','TimeSteps',mws.getVariable('TimeSteps'));
    end
end