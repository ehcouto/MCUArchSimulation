
% Last Modified by v1.1 14-Feb-2019 16:08:20
%--------------------------------------------------------------------------
% Author:      Madhura Patil
% Date:       October 12th, 2018
%--------------------------------------------------------------------------


%--------------------------------------------------------------------------
% Parameter Initialization 
%    Description:  This Function is used to load the parameters variable given 
%    to simulink Model  used for testing the sBPm by varying  resistance and flux 
%    and thus interns temperature of stator and rotor temperature is varied.
%--------------------------------------------------------------------------

%--------------------------------------------------------------------------
% PLEASE NOTE -This script is used in Automatic_script_Temp.m file for calling parameters.
%--------------------------------------------------------------------------

%--------------------------------------------------------------------------
% Edit the below parameters to modify the response. 
%--------------------------------------------------------------------------

addpath(genpath(pwd));
%......Input Parametr value..........%
Automatic_Test.Speed=[500;5000;1200];              % .....To enter Speed values(rpm)............................%
Automatic_Test.Dyno_Load_Vector=[0.5;0.8;1.3];     % .....To enter Dyno Load values(Nm).........................%
Automatic_Test.Accerelation=500;                   % .....To enter Accerelation of Speed(m/s)...................%
Automatic_Test.Speed_Tolerance=20;                 % .....To enter Speed Tolerance in(%).......................... %
Automatic_Test.Percentage_Variation=-50;            %......To enter the Percentage Variation of the parameter....%

%...Flag setting for selection of variation of parameter......%

%Uncomment either one of it as per the selection of test,that is by  varying Flux or Resistance.

%Automatic_Test.parameter_var= 'Flux';
 Automatic_Test.parameter_var= 'Rs'; 



%.......Demagnetisation value........%
Automatic_Test.dm=-0.0021;


%......Input Parametr value to Matlab Functions..........%

%......Status Function........................%
Automatic_Test.Status_Time_Check=2;           %...Status time check in (sec) will wait after the ref and estimated speeds are reach and accordingly sends the status to either 1 or 0.        
Automatic_Test.Status_Tolerance=0.05;         %...Status Tolerance time in (sec) gives the vicinity time for estimated speed(plant),such that if it is within the tolerance value status can be activated.


%......Dyno Input Function....................%
Automatic_Test.Dyno_Step_Size=0.001;          %...Dyno Step Size value in (sec) is assigned to generate the ramp input of dyno load before reaching stable value.

%......Parameter Input Function...............%
Automatic_Test.Para_time_check=2;             %...Generation of Prameter input signal will begin after Para time check(sec) that is ,once Dyno load input is stable after Para time check parametr input signal begins.

