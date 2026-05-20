
% Last Modified by v1.1 14-Feb-2019 16:08:20
%--------------------------------------------------------------------------
% Author:      Madhura Patil
% Date:        Dec 12, 2018
%--------------------------------------------------------------------------


%--------------------------------------------------------------------------
% Parameter Initialization 
%    Description:  This Function is used to load the parameters variable given 
%    to simulink Model  used for testing the sBPm by adding  noise on Vdc
%    and Iabc.
%   
%--------------------------------------------------------------------------

%--------------------------------------------------------------------------
% PLEASE NOTE -This script is used in Automatic_script_ADC.m file for calling parameters.
%--------------------------------------------------------------------------

%--------------------------------------------------------------------------
% Edit the below parameters to modify the response.%
%--------------------------------------------------------------------------



addpath(genpath(pwd));

%......Input Parametr value..........%
Automatic_Test.Speed=[500;5500;1200];           % .....To enter Speed values(rpm)............................%
Automatic_Test.Dyno_Load_Vector=[0.5;0.85;1.3];      % .....To enter Dyno Load values(Nm).........................%
Automatic_Test.Accerelation=500;                % .....To enter Accerelation of Speed(m/s)...................%
Automatic_Test.Speed_Tolerance=30;              % .....To enter Speed Tolerance(%).......................... %
Automatic_Test.Percentage_Variation_Noise=50;   %......To enter the percentage variation of noise signal.....%  

%...Flag setting for selection of variation of parameter......%

%Uncomment either one of it as per the selection of test,that is adding noise on Vdc or Iabc

Automatic_Test.Noise_Var= 'Volt_Noise_Power';             %...To conduct test by imposing noise on Voltage...........%
%Automatic_Test.Noise_Var= 'Ic_Noise_Power';                %...To conduct test by imposing noise on 3 Currents...........%
 
%........Intiatialization of voltage and current noise power...........%
 Automatic_Test.Ic=30;
 Automatic_Test.Volt=50;


%......Input Parametr value to Matlab Functions..........%

%......Status Function........................%
Automatic_Test.Status_Time_Check=2;           %...Status time check in (sec) will wait after the ref and estimated speeds are reach and accordingly sends the status value.        
Automatic_Test.Status_Tolerance=0.05;         %...Status Tolerance value gives the vicinity value for estimated speed(plant),such that if it is within the tolerance value status can be activated.


%......Dyno Input Function....................%
Automatic_Test.Dyno_Step_Size=0.001;          %...Dyno Step Size in (sec) is assigned to generate the ramp input of dyno load before reaching stable value.

%......Parameter Input Function...............%
Automatic_Test.Para_time_check=2;             %...Generation of Prameter input signal  will begin after Para time check(sec) that is ,once Dyno load input is stable after Para time check parametr input signal begins.

