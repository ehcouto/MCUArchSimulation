%% SPPMSM_Hanyu_W10797913_Wash_Pump_Dish

Rs0 = 8.5;
Ls0 = 0.145;
NPP = 1;
PM_Flux_f01= 0.182;
Trp = 0.008;
alpha_s = 0.00386982;
d_magnet = 0.00386982;
Rs_Temperature_Ref = 22;
PM_Temperature_Ref = 22;
Jrotor = 1e-5;
Jadd = 0;
B = 5e-5;
theta_m_0 = 174*pi/180;
omega_m_start = 0;
TR = 0;
LsModel = 2;         %Ls saturation model 0 - no saturation/1 -  Ls=f(is,theta)/2 - Ls=f(StatorFlux)
Lsmin = 0.05;        %Minumum value for Ls
Imax = 1.0;          %Model 1
StatorFluxMax = 0.277; %Model 2