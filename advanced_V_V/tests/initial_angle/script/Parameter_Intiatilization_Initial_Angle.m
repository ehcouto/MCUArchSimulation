
% Last Modified by v1.1 14-Feb-2019 16:08:20
%--------------------------------------------------------------------------
% Author:      Madhura Patil
% Date:        Dec 24, 2018
%--------------------------------------------------------------------------


%--------------------------------------------------------------------------
% Parameter Initialization 
%    Description:  This Function is used to load the parameters variable given 
%    to simulink Model  used for testing the sBPm by varying  initiaal
%    angle and thus interns checking the robustness of the controller.
%    
%--------------------------------------------------------------------------

%--------------------------------------------------------------------------
% PLEASE NOTE -This script is used in Automatic_script_Angle.m file for calling parameters.
%--------------------------------------------------------------------------

%--------------------------------------------------------------------------
% Info -This script is used to test the performance of motor while changing intial angle of the motor.
%  In this test  ilteration of Initial angle is fixed along with that one
%  has to chose Mechanical Model Varient that is either between Dyno load or Mechanical Load. 
%
% For  Case A :  Carried on                  :- Dyno Load
%                Control Varient             :- Initial angle
%                Dyno load Parameter         :- 1)Load Torque
%                                               2)Accerlation
% For  Case B :  Carried on                  :- Mechanical Load
%                Control Varient             :- Initial angle
%                Mechanical load Parameter   :- 1)Jdrum             
%                                               2)Damp
%                                               3)Accerlation
%                                               4)Resistance
%PLEASE NOTE - 1)For this test always first varient is Initial angle. And the
%                other varietns depending on type of Mechanical Model Varient has chosen.
%               2)Second varient has to be either one of the parameter listed
%               above in Case A, b and C.
%--------------------------------------------------------------------------











%--------------------------------------------------------------------------
% Edit the below parameters to modify the response. 
%--------------------------------------------------------------------------

addpath(genpath(pwd));
% --------------------------------------------------------------------------
%                         STEP-1
%...Selection of  stream version  against the type of the test ................%
% --------------------------------------------------------------------------
    
 Automatic_Test.Stream='04_Dyno';           %.... Uncomment the stream version which is in use.....%
%Automatic_Test.Stream='03_Mech';            %.... Uncomment the stream version which is in use.....%
%Automatic_Test.Stream='04_Mech';            %.... Uncomment the stream version which is in use.....%
 
%                         STEP-1A
%...Selection of Type of Mechanical model Variant ................%
%...Uncomment  either one of depending on type of selection of Load.
% --------------------------------------------------------------------------
Variant_Motor=3;                         % ......For Dyno Load..........%
%Variant_Motor=4;                         %......For Mechanical Looad....%
%--------------------------------------------------------------------------
%                         STEP-1B
%...Selection of  Stream version  ................%
%...Uncomment  either one of depending on type of selection of Load.
% --------------------------------------------------------------------------
Paths.Root_Path='C:\Data\Nucleus_Dev\Streams\00.04.00\Windy_sBpm_Floating\source';
%Paths.Root_Path='C:\Data\Nucleus_Dev\Streams\00.03.00\Windy_sBpm_Floating\source';




%                                STEP-2
%-----------------------------------------------------------------------------
%.......Input the range of Initial angle ..............%
%-----------------------------------------------------------------------------

Automatic_Test.PosAng=180;                     % ......To enter positive electrical angle in degree.........%
Automatic_Test.NegAng=-180;                    % ......To enter negative electrical angle in degree.........%
Automatic_Test.Interval=30;                    % ......To enter  interval value.............................%
Automatic_Test.ThetaElec=Automatic_Test.NegAng:Automatic_Test.Interval:Automatic_Test.PosAng; %...Generates array of an angle......%

%                                STEP-1
%-----------------------------------------------------------------------------------------------------------
%...Selection of  Second varient against type of the test(Dyno_Load,Acceleration,Jdrum,Damp,Resistance) ..%
%-----------------------------------------------------------------------------------------------------------

Automatic_Test.Variant='Load_Torque ';             %.... Uncomment the Variant which is in use.....%
%Automatic_Test.Variant='Jdrum       ';            %.... Uncomment the Variant which is in use.....%
%Automatic_Test.Variant='Damp        ';            %.... Uncomment the Variant which is in use.....%
%Automatic_Test.Variant='Temperature ';            %.... Uncomment the Variant which is in use.....%


%                                STEP-3
%------------------------------------------------------------------------------------------------------------------------------------------
%...Depending on type of test COMMENT the variant which is going to test against the Initial angle%
%....NOTE- When the test is carried out varying one parameter, other
%          parameter should be given as their nominal/standard values.
%------------------------------------------------------------------------------------------------------------------------------------------
%Automatic_Test.Dyno_Load=0.1;
Thermal.Tstator=22;
Mechanical.JDrum=0.0637;                
Mechanical.damp=0.28;  

%                                STEP-4
%------------------------------------------------------------------------------------------------------------------------------------------
%...Depending on Case choose only one variant either(Dyno_Load,Acceleration,Jdrum,Damp,Resistance) that has to varied along with Initial angle.......%
%------------------------------------------------------------------------------------------------------------------------------------------

 Automatic_Test.Dyno_Load_Vector=[0.5;0.85;1.3;1.7];   %.....To enter Dyno Load values(Nm).Dyno load Parameter_Load Torque ..................%
                                                             %Note:-This variant has to be varied only when test is performed on Dyno Load..........%
 Automatic_Test.Acceleration_Vector=400;               
 Automatic_Test.Temperature_Vector=700;                                               
 Automatic_Test.JDrum_Vector=3.6;
 Automatic_Test.Damp_Vector=5;
                                                 
                                                     
                                                     
                                                     


%                                STEP-6
%--------------------------------------------------------------------------
%.....................Input Parametr value....................%
%--------------------------------------------------------------------------

Automatic_Test.Speed=400;                        % .....To enter Speed values(rpm)............................%
Automatic_Test.Accerelation=400;                 % .....To enter Accerelstion values(rpm)............................%
Automatic_Test.Speed_Tolerance=80;               % .....To enter Speed Tolerance(%) for failure_1 conditions (Out of bound)....%
Automatic_Test.Speed_Tolerance_1=3;              % .....To enter Speed Tolerance(%) for failure_2 conditions(For oscillatory failure)....%

%                                STEP-7
%--------------------------------------------------------------------------
%.......Input Time Check values to Matlab Functions..........%
%--------------------------------------------------------------------------
 Automatic_Test.Status_Time_Check=0.03;            %...Status time check in (sec) will wait after the ref and estimated speeds are reach and accordingly sends the status value.        
 Automatic_Test.Para_time_check_1=0.3;             %...It is the time in sec , which is used in condition block to check if the speed is unbounded for more than para time check_1(for Failure_1  condition)
 Automatic_Test.Para_time_check_2=2.5;             %...It is the time in sec , which is used in condition block to check if the speed is unbounded for more than para time check(For Startup condition)
 Automatic_Test.Para_time_check_3=3.5;             %...It is the time in sec , which is used in condition block to check if the speed is unbounded for more than para time check_2(For Failure_2 condition)




  








































