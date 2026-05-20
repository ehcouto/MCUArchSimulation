%% Creating a structure for Compressor model parameters
% Regime
Compressor.inputChambers.reg = 0; %Regime 0-fully developed cyclic, 1-fully developed cyclic
% Operation condition
Compressor.inputChambers.T_e = -23.3 + 273.15;%249.85; %Evaporator temperature [K]
Compressor.inputChambers.T_c = 54.4 + 273.15;%327.55; %Condenstation temperature [K]
Compressor.inputChambers.T_sl = 32.2 + 273.15;%305.35; %Gas temperature in the compressor inlet (suction line) [K]
Compressor.inputChambers.F_sh = 0.25; %Superheating factor [K]

% Startup - considered only if reg = 1
Compressor.inputChambers.p_eq = 150000; %Equalized pressure [Pa]
Compressor.inputChambers.del_suc = 0.9; %Factor that reflects the delay to reach the stabilized condition (suction)
Compressor.inputChambers.t_i_suc = 2; %Time necessary to reach the (1+(1-del_suc))*p_e [s]
Compressor.inputChambers.del_dis = 0.998; %Factor that reflects the delay to reach the stabilized condition (discharge)
Compressor.inputChambers.t_i_dis = 2; %Time necessary to reach the del_dis*p_c [s]

% Reciprocating compressor (a combination of Cylinder model, automatic
% valves and reciprocating mechanism)
Compressor.mechanical.p_start = 58427; %Start value of pressure inside of compression chamber [Pa]
Compressor.mechanical.t_mec = 0; %Time to reach a fluid film lubrication [s]
Compressor.mechanical.f_mec_bon = 0.3; %Factor with 'dry' bearings (boundary friction/lubrication)
Compressor.mechanical.f_mec_flu = 0.03; %Factor with a fluid film (fluid film friction/lubrication)

% Compressor Data (parameters that characterize each compressor model)
Compressor.mechanical.l_conrod = 0.04; %Connection rod length [m] X
Compressor.mechanical.stroke = 0.0189; %Stroke [m] X
Compressor.mechanical.bore = 0.0243; %Bore [m] X
Compressor.mechanical.d_m = 0; %Piston pin offset [m] X
Compressor.mechanical.rho_pis = 7850; %Piston density [kg/m3] X
Compressor.mechanical.J = 0.000273; %Moment of inertia [kg.m2] X
Compressor.mechanical.c = 0.02762; %Clearance ratio
Compressor.mechanical.d_sv = 0.0073; %Suction valve orifice diameter [m] X
Compressor.mechanical.c_sv = 0.048; %Effective flow area coefficient - Suction valve
Compressor.mechanical.d_dv = 0.0043; %Discharge valve orifice diameter [m] X

%run('Compressor_set_params.m')