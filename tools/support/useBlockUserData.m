function useBlockUserData(blockName)
    bud = get_param(blockName,'UserData');
    if ~isempty(bud)
        assignin('base','config',bud.config);
        assignin('base','Paths',bud.Paths);
        assignin('base','DC_Bus',bud.DC_Bus);
        assignin('base','InputCircuit',bud.InputCircuit);
        assignin('base','Mechanical',bud.Mechanical);
        assignin('base','Motor',bud.Motor);
        assignin('base','Thermal',bud.Thermal);
        assignin('base','Variant_Input_Circuit',bud.Variant_Input_Circuit);
        assignin('base','Variant_Motor',bud.Variant_Motor);
        assignin('base','Variant_Motor_Control',bud.Variant_Motor_Control);
        assignin('base','Variant_Sensor',bud.Variant_Sensor);
        assignin('base','TimeSteps',bud.TimeSteps);
        
    end
end