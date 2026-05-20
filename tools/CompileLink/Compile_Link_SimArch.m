function  Compile_Link_SimArch( CompileStruct )
% Description: Implements the makefile to create the whole MCI+SR Code
%       compilation used by the simulation. The purpose of this simulation
%       is to embedded the production target code into the
%       Matlab\Simulation enviroment.
%--------------------------------------------------------------------------
% Author:      Alessio Beato
% Date:        October 14th, 2022
%--------------------------------------------------------------------------


%% Extract Structure Parameters
%Root_Path_flag=CompileStruct.Root_Path_flag;
Root_Path=CompileStruct.Root_Path;
Fast_ADC_Initialization_Flag=CompileStruct.Fast_ADC_Initialization_Flag;
Skip_Motor_Moving_Handler_Flag=CompileStruct.Skip_Motor_Moving_Handler_Flag;
Setting_File_Flag = CompileStruct.Setting_File_Flag;


%% Temporary support for MotorSelector Module (unified DD\sBPM)
addpath(genpath(Root_Path));
if not(isempty(which('MotorSelector.c')))
    MOTOR_SELECTOR_DEF = '-DMOTOR_SELECTOR= ';
else
    MOTOR_SELECTOR_DEF = '';
end
rmpath(genpath(Root_Path));


%% Other definitions
% defines for fast initialization
if strcmp(Fast_ADC_Initialization_Flag,'Set')
    INIT_DEF = '-DFAST_ADC_INIT= ';
else
    INIT_DEF = '';
end
if strcmp(Skip_Motor_Moving_Handler_Flag,'Set')
    INIT_DEF = [INIT_DEF, '-DSKIP_MOTOR_MOVING_CHECK= '];
end

% defines for Setting File
if strcmp(Setting_File_Flag,'Set')
   SETTING_FILE_DEF = '';
else
   SETTING_FILE_DEF = '-DMCI_INTERNAL_PARAMS= ';
end


% define for Simulation Frequency
Ts=evalin('base','TimeSteps.ModelStep');
Sim_Freq = 1/Ts;
FSIM_DEF = ['-DFS_SIM=' num2str(Sim_Freq) ' ']; 


%% Preparing for Compilation set-up

SourceRoot = Root_Path;
sFunPath = 'source\SIL_Sfunction\';
sFunName = 'sfun_motor_control.c';
sFunFull = [sFunPath sFunName];
OutPath = 'exe';
MockPath = 'source';
AdditionalIncl = {'tools\MciAPI'};


IncludeModuleList = {'Mci' 'SRMotorSafetyMgr' 'MciParametersLoader' ...
                        'MotorSelector'  'SRData' 'Crc16' ...
                        'SRTaskSequence' 'SRException' 'SRIsrMonitor' 'SRFlow'};


SetupParamsStruct.RootPath = SourceRoot;
SetupParamsStruct.MockPath = MockPath;
SetupParamsStruct.IncludeModuleList = IncludeModuleList;
SetupParamsStruct.AdditionalIncl = AdditionalIncl;


CompilationParamsStruct = CompilationSetup(SetupParamsStruct);



ParamsStruct.EntrySfunFile      = sFunFull;
ParamsStruct.MexOutputFolder    = OutPath;
ParamsStruct.SourceFiles        = CompilationParamsStruct.SourceFiles;
ParamsStruct.IncludeFolders     = CompilationParamsStruct.IncludeFolders;
ParamsStruct.PreprocessorDefs   = ['-DCOMPILE_4_SIMULINK=1  -DSIM_MODE=1 ' FSIM_DEF '-DFAR= ' INIT_DEF SETTING_FILE_DEF MOTOR_SELECTOR_DEF];
ParamsStruct.Coverage           = 'DISABLE';
ParamsStruct.PDB                = 'ENABLE';

CompileLink(ParamsStruct);

