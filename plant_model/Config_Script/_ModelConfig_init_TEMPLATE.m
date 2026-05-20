% Steps required to assign a configuration set to the model

%% 1) Loading apprioriate model configuration set to the base workspace
% Syntax: 
% load('Config_Set_Name.mat')
% where Config_Set_Name is selected by the user from the Config_Set folder

%% 2) Assing loaded Configuration to the target one
% Syntax:
% ModelConfig_var = Config_Set_Name;
% where Config_Set_Name is loaded to the base workspace in the previous
% section

%% Example for MCU SimArch
% load('ModelConfig_MCU_SimArch.mat')
% ModelConfig_var = ModelConfig_MCU_SimArch