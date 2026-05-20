%% Mock-up of the UI for Single Phase Motor Simulation Architecture
%%14/01/2021 - v2

%% ------ Simulation -------------------
SimTime = 1.2;          %simulation time

%% -----  Sample Times -----------------
% -------- Main Model ------------------
SIM_F = 10000*4;           %frequency FINN
%SIM_F = 9.6e4;        %frequency Yoda2
Ts_SIM = 1/SIM_F;      %step size

% Plant Models
Ts_Model = Ts_SIM;
% Sensors
Ts_Sensor = Ts_SIM;

% --------- Controls -------------------
% MCI sfunction
MCI_F = SIM_F;            %frequency FINN
%MCI_F = 9.6e4;         %frequency Yoda2
Ts_MCI_F = 1/MCI_F;     %step size

% MCI Zero Cross handler
MCI_ZC = 10000;          %frequency FINN
%MCI_ZC = MCI_F;        %frequency Yoda2
Ts_MCI_ZC = 1/MCI_ZC;   %step size

%% Motor type selection
% 11 - PMSM(FMU)
% 12 - PMSM(sfunction)
% 2 - PSC

MotorType = 11; %use 11 as default
%% Rotor position sensor
% 1 - sensorless, 2 - hall sensor

Position_Sensor = 1;
switch Position_Sensor
    case 1
        disp('Sensorless mode selected')
    case 2
        disp('Hall Sensor selected')
    otherwise
        disp('Please select a Board')
end

%% Board Parameters - to load the data use BoardParam variable
% BoardParam = 1 - FINN_AC120V
% BoardParam = 2 - Yoda2_AC120V
% BoardParam = 3 - Vostok_AC120V
% BoardParam = 4 - Mirim_AC120V

BoardParam = 3;
switch BoardParam
    case 1
        run('FINN_AC120.m'); disp('FINN board was selected')
    case 2
        run('Yoda2_AC120.m'); disp('Yoda2 board was selected')
    case 3
        run('Vostok_AC120.m'); disp('Vostok board was selected')
    case 4
        run('Mirim_AC120.m'); disp('Mirim board was selected')
    otherwise
        disp('Please select a Board')
end

%% Motor Parameters - to load the data use MotorBoard variable
%% Single Phase PMSM
% MotorParam = 1 - SPPMSM_Hanyu
% MotorParam = 2 - SPPMSM_Askoll

MotorParam = 1;
switch MotorParam
    case 1
        run('SPPMSM_Hanyu_W10797913_Wash_Pump_Dish.m'); disp('SPPMSM_Hanyu_W10797913_Wash_Pump_Dish motor was selected')
    case 2
        run('SPPMSM_Askoll_Bidirectional_Pump.m'); disp('SPPMSM_Askoll_Bidirectional_Pump motor was selected')
    otherwise
        disp('Please select a Motor')
end
%% Single Phase PSC
% MotorParam = 1 -
% MotorParam = 2 -

%% Motor Model Counfiguration 
Tol_Model = 1e-5; %Solver tolerance for FMU