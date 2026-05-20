%% ------------------------------------------------------------------------
% XAlphaBeta Struct Initialization
% typedef struct
% {  
%    double Alpha;
%    double Beta;
% }XAlphaBeta
% -------------------------------------------------------------------------
XAlphaBeta.Alpha = 0;
XAlphaBeta.Beta  = 0;
%--------------------------------------------------------------------------
Simulink.Bus.createObject(XAlphaBeta)
XAlphaBetaBus = slBus1;
clear slBus1
clear XAlphaBeta
%% ------------------------------------------------------------------------
% Xdq Struct Initialization
% typedef struct
% {  
%    double D;
%    double Q;
% }Xdq
% -------------------------------------------------------------------------
Xdq.D = 0;
Xdq.Q = 0;
% -------------------------------------------------------------------------
Simulink.Bus.createObject(Xdq)
XdqBus = slBus1;
clear slBus1
clear Xdq
%% ------------------------------------------------------------------------
% Xabc Struct Initialization
% typedef struct
% {  
%    double A;
%    double B;
%    double C;
% }Xdq
% -------------------------------------------------------------------------
Xabc.A = 0;
Xabc.B = 0;
Xabc.C = 0;
% -------------------------------------------------------------------------
Simulink.Bus.createObject(Xabc)
XabcBus = slBus1;
clear slBus1
clear Xabc
%% ------------------------------------------------------------------------
% SinCos Struct Initialization
% typedef struct
% {  
%    double Cos;
%    double Sin;
% }SinCos% ----------------------------------------------------------------
SinCos.Cos = 0;
SinCos.Sin = 0;
% -------------------------------------------------------------------------
Simulink.Bus.createObject(SinCos)
SinCosBus = slBus1;
clear slBus1
clear SinCos
% % -------------------------------------------------------------------------
% % -------------------------------------------------------------------------
% % Mech1state Struct Initialization
% % typedef struct
% % {  
% %    double OmegaRotMech;
% %    double ThetaRotMech;
% % }PMSMparams
% % -------------------------------------------------------------------------
% Mech1state.OmegaMech  = 0;
% Mech1state.ThetaMech = 0;
% % -------------------------------------------------------------------------
% Simulink.Bus.createObject(Mech1state)
% Mech1stateBus = slBus1;
% clear slBus1
% % -------------------------------------------------------------------------
% % -------------------------------------------------------------------------
% % Mech1params Struct Initialization
% % typedef struct
% % {  
% %    double J;
% %    double Ts;
% % }PMSMparams
% % -------------------------------------------------------------------------
% Mech1params.J  = 0;
% Mech1params.Ts = -1;
% % -------------------------------------------------------------------------
% Simulink.Bus.createObject(Mech1params)
% Mech1paramsBus = slBus1;
% clear slBus1
% % -------------------------------------------------------------------------
% % PMSMparams Struct Initialization
% % typedef struct
% % {  
% %    double Rs;
% %    double Ld;
% %    double Lq;
% %    double p;
% %    double Pghim;
% %    double LdSat;
% %    double Ts;
% % }PMSMparams
% % -------------------------------------------------------------------------
% PMSMparams.Rs    = 0;
% PMSMparams.Ld    = 0;
% PMSMparams.Lq    = 0;
% PMSMparams.p     = 0;
% PMSMparams.Phim  = 0;
% PMSMparams.LdSat = 0;
% PMSMparams.Ts    = -1;
% % -------------------------------------------------------------------------
% Simulink.Bus.createObject(PMSMparams)
% PMSMparamsBus = slBus1;
% clear slBus1
% % -------------------------------------------------------------------------
% % PSMSstate Struct Initialization
% % typedef struct
% % {  
% %    double Isd;
% %    double Isq;
% % }PSMSstate
% % -------------------------------------------------------------------------
% PSMSstate.Isd = 0;
% PSMSstate.Isq = 0;
% % -------------------------------------------------------------------------
% Simulink.Bus.createObject(PSMSstate)
% PSMSstateBus = slBus1;
% clear slBus1
% %% ------------------------------------------------------------------------
% % -------------------------------------------------------------------------
% % ACIMparams Struct Initialization
% % typedef struct
% % {  
% %    double Rs;
% %    double Ld;
% %    double Lq;
% %    double p;
% %    double Pghim;
% %    double LdSat;
% %    ACIMparams Ts;
% % }PMSMparams
% % -------------------------------------------------------------------------
% ACIMparams.Rs = 0;
% ACIMparams.Rr = 0;
% ACIMparams.Ls = 0;
% ACIMparams.Lr = 0;
% ACIMparams.Lm = 0;
% ACIMparams.p  = 0;
% ACIMparams.Ts = -1;
% % -------------------------------------------------------------------------
% Simulink.Bus.createObject(ACIMparams)
% ACIMparamsBus = slBus1;
% clear slBus1
% % -------------------------------------------------------------------------
% % ACIMstate Struct Initialization
% % typedef struct
% % {  
% %    double Isd;
% %    double Isq;
% %    double Phird;
% %    double OmegaFlux;
% %    double ThetaFlux;
% % }ACIMstate
% % -------------------------------------------------------------------------
% ACIMstate.Isd       = 0;
% ACIMstate.Isq       = 0;
% ACIMstate.Phird     = 0;
% ACIMstate.OmegaFlux = 0;
% ACIMstate.ThetaFlux = 0;
% % -------------------------------------------------------------------------
% Simulink.Bus.createObject(ACIMstate)
% ACIMstateBus = slBus1;
% clear slBus1
% %% ------------------------------------------------------------------------
% % TOparams Struct Initialization
% % typedef struct
% % {  
% %    double Kp;
% %    double Ki;
% %    double Ts;
% % }TOparams
% % -------------------------------------------------------------------------
% Tachoparams.Clock       = 0;
% Tachoparams.p           = 0;
% Tachoparams.Ts          = 0;
% Tachoparams.tmr_bits    = 0;
% Tachoparams.wmax        = 0;
% Tachoparams.freq_tmr    = 0;
% 
% 
% 
% % -------------------------------------------------------------------------
% Simulink.Bus.createObject(Tachoparams)
% TachoparamsBus = slBus1;
% clear slBus1
% 







