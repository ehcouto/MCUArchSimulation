%% SPPMSM_Askoll_Bidirectional_Pump

Rs0 = 8.2;
Ls0 = 0.27;
NPP = 1;
PM_Flux_f01= 0.171;
Trp = 0.05;
alpha_s = 0.00386982;
d_magnet = 0.00386982;
Rs_Temperature_Ref = 22;
PM_Temperature_Ref = 22;
Jrotor = 2.5e-6;
Jadd = 0;
B = 1e-5;
theta_m_0 = 22*pi/180;
omega_m_start = 0;
TR = 0;
LsModel = 2;        %Ls saturation model 0 - no saturation/1 -  Ls=f(is,theta)/2 - Ls=f(StatorFlux)
Lsmin = 0.2;        %Minumum value for Ls
Imax = 2;           %Model 1
StatorFluxMax = 0.3; %Model 2