%% Setup external code integration for C Caller usage 

%% Get the paths
SourceRoot = '..\source';
MockPath = 'source';
AdditionalIncl = '';

ExcludeModuleList = {'BoardDebugging' ...
    'MasterCommander' 'Driver' ...
    'SettingFile'   ...
    'FITMgr'  'Win'};

Ts=evalin('base','TimeSteps.ModelStep');
Sim_Freq = 1/Ts;
FSIM_DEF = ['-DFS_SIM=' num2str(Sim_Freq) ' '];
PreprocessorDefs   = ['SIL_EXTENDED= CMDMANAGER= COMPILE_4_SIMULINK=1 SIM_MODE=1 FS_SIM=' num2str(Sim_Freq) ' FAST_ADC_INIT= SKIP_MOTOR_MOVING_CHECK= FAR= '];

SetupParamsStruct.RootPath = SourceRoot;
SetupParamsStruct.MockPath = MockPath;
SetupParamsStruct.ExcludeModuleList = ExcludeModuleList;
SetupParamsStruct.AdditionalIncl = AdditionalIncl;
SetupParamsStruct.BaseDir = fileparts(which('MCU_Simulation_Architecture'));

CompilationParamsStruct = CompilationSetupCCaller(SetupParamsStruct);
PreprocessorDefs = strsplit(PreprocessorDefs);
PreprocessorDefs = strjoin(PreprocessorDefs, '\n');

%% Generate the configuration
% backup 
copyfile(which('ModelConfig_MCU_SimArch.mat'), 'ModelConfig_MCU_SimArch_bkp.mat')

% start from the currently used
ModelConfig_SimArch_ccaller = copy(ModelConfig_var);
ModelConfig_SimArch_ccaller.Name = 'ModelConfig_SimArch_ccaller';

% populate the configuration
ModelConfig_SimArch_ccaller.set_param("SimCustomHeaderCode", '#include "sim_wrapper.h"',...
    'SimUserIncludeDirs',  CompilationParamsStruct.IncludeFolders,  ...
    'SimUserSources', CompilationParamsStruct.SourceFiles, ...
    'SimUserDefines', PreprocessorDefs, ...
    'SimDebugExecutionForCustomCode', 'on', ...
    'SimAnalyzeCustomCode', 'off');

% Update model configuration file
save('ModelConfig_MCU_SimArch.mat',...
'ModelConfig_var', ...
'ModelConfig_MCU_SimArch', ...
'ModelConfig_SimArch_ccaller');


