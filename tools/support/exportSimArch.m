function exportSimArch(simArchName)
outputports = [string('PwmDuties'),...
    string('PwmStatus'),...
    string('Iabc_ADC_Data'),...
    string('Vdc_ADC_Data'),...
    string('Vdc'),...
    string('Vpole'),...
    string('InputCurrent'),...
    string('Torque'),...
    string('Iabc'),...
    string('ThetaFlux'),...
    string('OmegaFlux'),...
    string('ElMotorPower'),...
    string('OmegaRotMech'),...
    string('SensorProcessedOutput')];

del_annotations = [string('PIL Serial Configuration'), ...
    string('Signal Grouping and Processing'), ...
    string('Simulation Performance'), ...
    string('Ratio between real time and simulated time'), ...
    string('Motor Control Transient Simulation Architecture'),...
    string('Input Circuit Model'),...
    string('Motor Control Algorithm'),...
    string('Inverter'),...
    string('Motor Electrical+ Mechanics Model'),...
    string('Sensors'),...
    string('ADC Model'),...
    string('Drum Speed Reference Command')];

del_subsystems = [string('Signal Processing'), ...
    string('Simulation Performance'), ...
    string('Display'), ...
    string('ExportModelBlk'),...
    string('ReloadVars'),...
    string('config_sub_sys'),...
    string('Signal Builder1'),...
    string('Ts'),...
    string('Tr'),...
    string('speedcommand_sf')];

if evalin('base','Variant_Motor_Control') ~= 2
    del_subsystems = [del_subsystems, string('serialconfig_ss')];
end

fmu_path = {};
model_refs = find_mdlrefs('MCU_Simulation_Architecture');
for j = 1 : length( model_refs )
    load_system( model_refs{j} )
    original_sfuns = find_system( model_refs{j}, 'findall', 'on', 'blocktype', 'S-Function' );
    for k = 1 : length(original_sfuns)
        if( strcmp( get_param( original_sfuns(k), 'FunctionName' ),'sfun_fmurun' ) == 1 )
            fmu_path{end+1} = FMIKit.getUnzipDirectory( original_sfuns(k) );
        end
    end
    %bdclose( model_refs{j} );
end
assignin('base', 'fmu_path', fmu_path);

srcFileName = which('MCU_Simulation_Architecture');
dstFileName = [pwd '\exported_models\' simArchName '.slx'];

if( exist(  simArchName , 'file' ) == 4 )
    if( bdIsLoaded( simArchName ) )
        bdclose( simArchName );   % Close the old model if its open before attempting to delete it
    end;
    delete( dstFileName );
end;

PreLoad = get_param('MCU_Simulation_Architecture', 'PreLoadFcn');
Init = get_param('MCU_Simulation_Architecture', 'InitFcn');
Close = get_param('MCU_Simulation_Architecture', 'CloseFcn');
PostLoad = get_param('MCU_Simulation_Architecture', 'PostLoadFcn');
% Remove callbacks before copying the model, so that they are not called
% when the new model is loaded.
set_param('MCU_Simulation_Architecture', 'PreLoadFcn', ''); 
set_param('MCU_Simulation_Architecture', 'InitFcn', '');
set_param('MCU_Simulation_Architecture', 'CloseFcn', '');
set_param('MCU_Simulation_Architecture', 'PostLoadFcn', '');
save_system('MCU_Simulation_Architecture');

copyfile(srcFileName, dstFileName, 'f');

set_param('MCU_Simulation_Architecture', 'PreLoadFcn', PreLoad);
set_param('MCU_Simulation_Architecture', 'InitFcn', Init);
set_param('MCU_Simulation_Architecture', 'CloseFcn', Close);
set_param('MCU_Simulation_Architecture', 'PostLoadFcn', PostLoad);
save_system('MCU_Simulation_Architecture');

load_system(simArchName);   %Load new model and start customization
SimArchHandle = get_param(simArchName, 'Handle');
SimArchAnnotations = find_system(SimArchHandle,'FindAll','on','Type','annotation');

for k = 1 : length(SimArchAnnotations)
    for l = 1 : length(del_annotations)
        if(contains(get_param(SimArchAnnotations(k), 'Name'),del_annotations(l))==1)
            delete(SimArchAnnotations(k));
            break;
        end;
    end;
end;

del_line = get_param([simArchName '/Simulation Performance'], 'LineHandles'); % Maybe there is a better way to delete lines
delete_line(del_line.Outport(1));

for k = 1 : length(del_subsystems)
    ssName = [simArchName '/' del_subsystems(k).char];
    delete_block(ssName);
end;

overrideMotor = evalin('base', 'Variant_Motor');
overrideInCircuit =  evalin('base', 'Variant_Input_Circuit');
overrideSensor = evalin('base','Variant_Sensor');
overrideMotorControl = evalin('base', 'Variant_Motor_Control');

set_param([simArchName '/INPUT Circuit Model'], 'OverrideUsingVariant', ['Variant_Input_Circuit==' num2str(overrideInCircuit)]);
set_param([simArchName '/Motor Coupled With Mechanics/Motor+Mechanical Models'], 'OverrideUsingVariant', ['Variant_Motor==' num2str(overrideMotor)]);
set_param([simArchName '/Motor Control Algorithm/WINDY CIM_BPM'], 'OverrideUsingVariant', ['Variant_Motor_Control==' num2str(overrideMotorControl)]);
%set_param([simArchName '/Model Variants'], 'OverrideUsingVariant', ['Variant_Sensor==' num2str(overrideSensor)]);

% set_param([simArchName '/INPUT Circuit Model'], 'Variant', 'off');
% set_param([simArchName '/Motor Electrical Model/Motor+Mechanical Models'], 'Variant', 'off');
% set_param([simArchName '/Motor Control Algorithm/WINDY CIM_BPM'], 'Variant', 'off');
% set_param([simArchName '/Model Variants'], 'Variant', 'off');
save_system(simArchName);
bdclose(simArchName);

%Remove Model References to avoid mixing variables in 'Base Workspace'
new_models = Replace_MdlRef_SubSys(simArchName);
new_srcFile = which(new_models{1});
delete(dstFileName);
copyfile(new_srcFile,dstFileName, 'f');
delete(new_srcFile);

%Replace FMUs by regular S-Functions
load_system(simArchName); %reload system, but now it has no reference models.
sfunctions = find_system(simArchName, 'findall', 'on', 'blocktype', 'S-Function');

%assignin('base', 'sfunctions', sfunctions);
for k = 1 : length(sfunctions)
    if( strcmp( get_param( sfunctions(k), 'FunctionName' ),'sfun_fmurun' ) == 1 )
        set_param( sfunctions(k), 'LinkStatus', 'none' );
        sfun_params = get_param( sfunctions(k), 'Parameters' );
        for l = 1 : length(fmu_path)
            if( contains( fmu_path{l}, FMIKit.getUnzipDirectory( sfunctions(k) ) ) ) 
                sfun_params = strrep( sfun_params, 'FMIKit.getUnzipDirectory(gcb)', [ '''' fmu_path{l} ''''] );
                break;
            end
        end
        set_param( sfunctions(k), 'Parameters', sfun_params);
        set_param( sfunctions(k), 'CloseFcn', '' );
        set_param( sfunctions(k), 'DeleteFcn', '' );
        set_param( sfunctions(k), 'DestroyFcn', '' );
        set_param( sfunctions(k), 'LoadFcn', '' );
        set_param( sfunctions(k), 'OpenFcn', '' );
        set_param( sfunctions(k), 'ModelCloseFcn', '' );
        sfun_mask = Simulink.Mask.get( sfunctions(k) );
        sfun_mask.delete;
    end
    if( strcmp( get_param( sfunctions(k), 'FunctionName' ),'sfun_motor_control' ) == 1 )
        MotorControlInit = ['clear mex' newline ...
                            'CompileStruct.Root_Path_flag=config.Root_Path_flag;' newline ...
                            'CompileStruct.Root_Path=Paths.Root_Path;' newline ...
                            'CompileStruct.Object_Path=Paths.Object_Path;' newline ...
                            'CompileStruct.Fast_ADC_Initialization_Flag=config.Fast_ADC_Initialization_Flag;' newline ...
                            'CompileStruct.Skip_Motor_Moving_Handler_Flag=config.Skip_Motor_Moving_Handler_Flag;' newline ...
                            'CompileStruct.Setting_File_Flag=config.Setting_File_Flag;' newline ...
                            'blk_msk = fileparts(fileparts(fileparts(fileparts(gcb))));' newline ...
                            'sablk_ud = get_param(blk_msk,''UserData'')' newline ...
                            'msk = Simulink.Mask.get(blk_msk)' newline ...
                            'if ( (strcmp(msk.getParameter(''recompile_sfun'').Value, ''on'') == 1) || (exist(''SimArchUID'')==0) || ( strcmp(SimArchUID, sablk_ud.UUID) == 0 ) )' newline ...
                            '    Compile_Link_MCU(CompileStruct);' newline ...
                            '    assignin(''base'',''SimArchUID'', sablk_ud.UUID);' newline ...
                            'end' newline ...
                            'clear blk_msk' newline ...
                            'clear sablk_ud' newline...
                            'clear msk'];
        set_param( sfunctions(k), 'InitFcn', MotorControlInit );
    end
    if( strcmp( get_param( sfunctions(k), 'FunctionName' ),'serial_sf' ) == 1 )
        set_param( sfunctions(k), 'InitFcn', '');
        set_param( sfunctions(k), 'Parameters', 'get_param([fileparts(fileparts(fileparts(fileparts(gcb)))) ''/serialconfig_ss''], ''com_port''), get_param([fileparts(fileparts(fileparts(fileparts(gcb)))) ''/serialconfig_ss''], ''baudrate''), steps'); 
    end
end

%Add output ports to external harness
from_h1 = 2320;
from_h2 = 2415;
from_v1 = 1582;
from_v2 = 1608;
out_h1 = from_h1 + 140;
out_h2 = from_h2 + 90;
out_v1 = from_v1 + 3;
out_v2 = from_v2 - 3;
for k = 1 : length( outputports )
    from_name = ['From_' outputports(k).char];
    out_name = outputports(k).char;
    
    add_block('simulink/Signal Routing/From',[simArchName '/' from_name]);
    set_param([simArchName '/' from_name], 'Position', [from_h1, from_v1, from_h2, from_v2]);
    set_param([simArchName '/' from_name], 'Gototag', outputports(k).char);

    add_block('simulink/Sinks/Out1', [simArchName '/' out_name]);
    set_param([simArchName '/' out_name], 'Position', [out_h1, out_v1, out_h2, out_v2]);
    if( strcmp(outputports(k).char, 'PwmDuties') == 1 )
        set_param([simArchName '/' out_name], 'OutDataTypeStr', 'Bus: PwmDutyBus');
    elseif( strcmp(outputports(k).char, 'Vpole') == 1 )
        set_param([simArchName '/' out_name], 'OutDataTypeStr', 'Bus: XabcBus');
    elseif( strcmp(outputports(k).char, 'Iabc') == 1 )
        set_param([simArchName '/' out_name], 'OutDataTypeStr', 'Bus: XabcBus');
    elseif( strcmp(outputports(k).char, 'Iabc_ADC_Data') == 1 )
        set_param([simArchName '/' out_name], 'OutDataTypeStr', 'Bus: XabcBus');
    end
    
    add_line(simArchName, [from_name '/1'], [out_name '/1']);
    
    from_v1 = from_v1 + 50;
    from_v2 = from_v2 + 50;
    out_v1 = out_v1 + 50;
    out_v2 = out_v2 + 50;
end
blocks = find_system(simArchName, 'SearchDepth', '1');
bh = [];
for i = 2:length(blocks)
bh = [bh get_param(blocks{i}, 'handle')];
end
Simulink.BlockDiagram.createSubSystem(bh);
subSys = [simArchName '/Subsystem'];%find_system(simArchName, 'type', 'block');
set_param(subSys, 'Name', [simArchName '_blk']);
subSys = [simArchName '/' simArchName '_blk'];
lines = find_system(simArchName, 'Findall', 'on', 'SearchDepth', '1', 'Type', 'Line');
for i=1:length(lines)
    delete_line(lines(i));
end
outputPorts = find_system(simArchName, 'Findall', 'on', 'SearchDepth', '1', 'BlockType', 'Outport');
for i=1:length(outputPorts)
    delete(outputPorts(i));
end

%Create callbacks
LoadFcn = ['addpath(''' [pwd '\tools'] ''');' newline ...
            'addpath(''' [pwd '\tools\MciAPI'] ''');' newline ...
            'addpath(''' [pwd '\tools\MciAPI\exe'] ''');' newline ...
            'addpath(''' [pwd '\tools\MciAPI\exe\enums'] ''');' newline ...
            'addpath(''' [pwd '\tools\Read_PDB_File'] ''');' newline ...
            'addpath(''' [pwd '\tools\Read_PDB_File\exe'] ''');' newline ...
            'addpath(''' [pwd '\tools\SpeedCommand'] ''');' newline ...
            'addpath(''' [pwd '\tools\SpeedCommand\exe'] ''');' newline ...
            'addpath(''' [pwd '\tools\SpeedCommand\view'] ''');' newline ...
            'addpath(''' [pwd '\tools\support'] ''');' newline ...
            'addpath(''' [pwd '\tools\FMIKit_for_Simulink'] ''');' newline ...
            newline ...
            'addpath(''' [pwd '\source\c_code'] ''');' newline ...
            newline ...
            'addpath(''' [pwd '\exe'] ''');' newline ...
            newline ...
            'useBlockUserData(gcb);']; 
Init_Fcn = ['evalin(''base'', ''smlarch_need_reset = 6;'');' newline 'Duty.A = 0;' newline 'Duty.B = 0;' newline 'Duty.C = 0;' newline 'Simulink.Bus.createObject(Duty);' newline 'PwmDutyBus = slBus1;' newline 'assignin(''base'', ''PwmDutyBus'', PwmDutyBus);' newline 'clear slBus1;' newline 'clear Duty;' newline...
        newline ...
        'BusInit;' newline ...
        newline ...
        'this_ud = get_param(gcb, ''UserData'');' newline...
        'if(  (exist(''SimArchUID'')) && ( strcmp(SimArchUID, this_ud.UUID) == 1) )' newline...
        'updateBlockUserData(gcb);' newline...
        'end' newline...
        'useBlockUserData(gcb);' newline ...
        newline...
        'if ( evalin(''base'', ''exist(''''steps'''') == 1'') && evalin(''base'', ''exist(''''drumspeedblk'''') ~= 1'') )' newline ...
        '    transmission = evalin(''base'',''Motor.Mechanical.TR'');' newline ...
        '    steps = evalin(''base'', ''steps'');' newline ...
        '    for i = 1:size(steps,1) ' newline ...
        '        steps(i,1) = steps(i,1) * transmission;' newline ...
        '        steps(i,2) = steps(i,2) * transmission;' newline ...
        '    end' newline ...
        '    clear transmission;' newline ...
        'end'];
set_param(subSys, 'InitFcn', Init_Fcn);
set_param(subSys, 'LoadFcn', LoadFcn);

%Create Mask
mskobj = Simulink.Mask.create(subSys);
mskobj.addParameter('Type', 'checkbox', 'Prompt', 'Recompile', 'Name', 'recompile_sfun');

%
if isempty(get_param(subSys,'UserData'))
    set_param(subSys, 'UserDataPersistent','on');
end


%Add unique ID to block's data
ud = get_param(subSys, 'UserData');
ud.UUID = char(java.util.UUID.randomUUID);
set_param(subSys, 'UserData', ud);
updateBlockUserData(subSys);
set_param(subSys, 'Position', '[345 884 625 1391]');

%Input for torque
set_param([subSys '/In3'], 'Name', 'Load Torque'); %input ports are automatically added when the subsys is created

modelws = get_param(simArchName, 'modelworkspace');
modelws.clear;
save_system(simArchName);
bdclose(simArchName);
















