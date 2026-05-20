clc;
clear;

%SourceRoot = uigetdir;
%[sFunName,sFunPath,~] = uigetfile('*.c', 'sFunction');

SourceRoot = 'C:\Data\HA2021\Colorado_Mcu_sBPM_DD_unified\source';
%SourceRoot = 'C:\Data\HA2021\Windy_Mcu_sBPM\source';
sFunPath = 'C:\Data\HA2021\HA_MCU_Sim_Arch\source\c_code\SIL_Sfunction\';
sFunName = 'sfun_motor_control.c';
sFunFull = [sFunPath sFunName];
OutPath = 'C:\Users\BEATOA\Documents\MATLAB\Miscellaneous\Compile\test';
MockPath = 'C:\Data\HA2021\HA_MCU_Sim_Arch\source\c_code';
AdditionalIncl = {'C:\Data\HA2021\HA_MCU_Sim_Arch\tools\MciAPI'};

% ExcludeModuleList = ["Beagle" "Extraction" "ParamEst" "ParamEstExc" "BoardDebugging" ...
%     "MasterCommander" "Driver" "Mode" ...
%     "API003Disc" "API004Debug" "API005LowLevel" "API007Data" "API009System" "API010PollVar" "API011AppCtr" ...
%     "API013RemoteFunction" "API018Diagnostic" "API019ProductInfo" ...
%     "SFUpdater" ...
%     "Service"];

ExcludeModuleList = {'Beagle' 'Extraction' 'ParamEst' 'ParamEstExc' 'BoardDebugging' ...
    'MasterCommander' 'Driver' 'Mode' ...
    'API003Disc' 'API004Debug' 'API005LowLevel' 'API007Data' 'API009System' 'API010PollVar' 'API011AppCtr' ...
    'API013RemoteFunction' 'API018Diagnostic' 'API019ProductInfo' ...
    'SFUpdater' 'SettingFile' 'ProductInfo' ...
    'Service' 'FITMgr' 'SRMain' ...
    'API007App' 'McuStandby' 'ModeManagement' 'RemoteFunctions' 'AccelBaseline' 'Accelerometer' sFunName};

SetupParamsStruct.RootPath = SourceRoot;
SetupParamsStruct.MockPath = MockPath;
SetupParamsStruct.ExcludeModuleList = ExcludeModuleList;
SetupParamsStruct.AdditionalIncl = AdditionalIncl;


CompilationParamsStruct = CompilationSetup(SetupParamsStruct);

ParamsStruct.EntrySfunFile      = sFunFull;
ParamsStruct.MexOutputFolder    = OutPath;
ParamsStruct.SourceFiles        = CompilationParamsStruct.SourceFiles;
ParamsStruct.IncludeFolders     = CompilationParamsStruct.IncludeFolders;
ParamsStruct.PreprocessorDefs   = '-DSIL_EXTENDED=  -DCOMPILE_4_SIMULINK=1  -DSIM_MODE=1  -DREVEALSIMPLE=  -DMICRO_H=  -DSRMICRO_H=  -DFS_SIM=16000  -DSCHEDULER_SIM_PRESCALER=3  -DFAST_ADC_INIT=  -DSKIP_MOTOR_MOVING_CHECK=  -DMCI_LOADER=  -DFAR= ';
ParamsStruct.Coverage           = 'DISABLE';
ParamsStruct.PDB                = 'DISABLE';

CompileLink(ParamsStruct);


