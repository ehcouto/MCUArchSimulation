
% Last Modified by v1.1 14-Feb-2019 16:08:20
%--------------------------------------------------------------------------
% Author:      Madhura Patil
% Date:        October 12th, 2018
%--------------------------------------------------------------------------

%--------------------------------------------------------------------------
% Description:  This Script is used to run and test performance of motor
% against defined speed and load torque.
% It checks the robusteness of the motor under test by generating the failure 
% values of the tests.
%--------------------------------------------------------------------------

%--------------------------------------------------------------------------
% Requirements to run the test 
%   Electrical Requirement:- Permanent Magnet Motor
%   Mechanical Requirement:- Dyno Load
%--------------------------------------------------------------------------

%--------------------------------------------------------------------------
% Please Note- Before running this script, Parameter_Initialization file has
%               to be updated to edit the parameters required to run the test. 
%--------------------------------------------------------------------------



%.......Opening the model model..........%
addpath('..\..\..\advanced_V_V\tests\parameter_variation\harness_model')
open('Harnes_Temp_Vary.slx');

Parameter_Initialization;

%.........To  create and name the folder by current date and time.......%
dname = uigetdir('C:\');
currDate = strrep(datestr(datetime), ':', '_');
bc=strcat(dname,'\',currDate);
d=char(bc);
mkdir(d)

%.......Parameter Intialization for the selection of Ts and Tr signalInput.....%
h1 = Simulink.findBlocks(gcs,'Name','Parameter Value');
h2 = Simulink.findBlocks(gcs,'Name','Temp Input');
%.......Parameter Intialization for the selection of Parameter (RS) signalInput.....%
if (strcmp(Automatic_Test.parameter_var,'Rs')) 
set_param(h1,'init_value','Motor.Electrical.Rs_a_Ref');
set_param(h2,'Init_Value','Motor.Electrical.Rs_a_Ref');
set_param(h2,'Temp_Ref','Motor.Mechanical.Rs_Temperature_Ref');
set_param(h2,'alpha','Motor.Electrical.alpha_s');
elseif(strcmp(Automatic_Test.parameter_var,'Flux'))
%.......Parameter Intialization for the selection of Parameter (Flux) signalInput.....%
set_param(h1,'init_value','Motor.Electrical.PM_Flux_f01');
set_param(h2,'Init_Value','Motor.Electrical.PM_Flux_f01');
set_param(h2,'Temp_Ref','Motor.Mechanical.PM_Temperature_Ref');
set_param(h2,'alpha','Automatic_Test.dm');
else
  msg='Please select type of variation either Rs or Flux in Automatic_Test.parameter_var in Parameter Intialization file.';
 error(msg)
end

%..........Creates an empty table to collect results....%
Results = table([],[],[],[],[],[],[],[],[], ...
'VariableNames',{'Speed_ref','Torque_ref', Automatic_Test.parameter_var,'Theta_error_mean', ...
    'Theta_error_std', 'Torque_error_mean', 'Torque_error_std', 'Speed_mean', 'Speed_std'});

%......Iteration.....%

for i= 1:length(Automatic_Test.Speed) 
    Automatic_Test.Speed_Ref=Automatic_Test.Speed(i);
     for j=1:length(Automatic_Test.Dyno_Load_Vector) 
           Automatic_Test.Dyno_Load=(Automatic_Test.Dyno_Load_Vector(j));
             
        %.....Simulate the Model....................%
        sim('Harnes_Temp_Vary.slx');
        
      
        
         %..... To collect statistics............. %
         if (strcmp(Automatic_Test.parameter_var,'Rs'))
         interval_index = get_intervals(Ts.signals.values');
        elseif(strcmp(Automatic_Test.parameter_var,'Flux'))
          interval_index = get_intervals(Tr.signals.values');
         end
         if interval_index
            [Theta_Error_mean_values,Theta_Error_std_values] = statistics(Theta_Error.Data, interval_index);
            %....Torque error....%
            [Torque_Error_mean_values,Torque_Error_std_values] = statistics(Torque_Error.Data, interval_index);
            %....Speed...........%
             [Speed_Plant_mean_values,Speed_Plant_std_values] = statistics(Speed_Plant.Data, interval_index);
        else
            %....Empty --> If steady state not reached...%
            Theta_Error_mean_values = NaN;
            Theta_Error_std_values = NaN;
            Torque_Error_mean_values= NaN;
            Torque_Error_std_values= NaN;
            Speed_Plant_mean_values= NaN;
            Speed_Plant_std_values= NaN;
        end
        
        %.......To collect the parameters values............%
         Speed_ref_prm=Automatic_Test.Speed_Ref *ones(size(Theta_Error_mean_values));   %.....Speed Value
         Dyno_ref_prm = Automatic_Test.Dyno_Load * ones(size(Theta_Error_mean_values)); %....Dyno Load Value
         
        %........To get the data of parameter variation.....%
        if (strcmp(Automatic_Test.parameter_var,'Rs'))
        step = Automatic_Test.Percentage_Variation*Motor.Electrical.Rs_a_Ref/100;
        Parameter_Var = (Motor.Electrical.Rs_a_Ref:step:(Motor.Electrical.Rs_a_Ref+step*(length(Theta_Error_mean_values)-1)));
        
        elseif(strcmp(Automatic_Test.parameter_var,'Flux'))
       
        step = Automatic_Test.Percentage_Variation*Motor.Electrical.PM_Flux_f01/100;
        Parameter_Var = (Motor.Electrical.PM_Flux_f01:step:(Motor.Electrical.PM_Flux_f01+step*(length(Theta_Error_mean_values)-1)));
        end
        
        %.........To update the results table..........%
        Results = [Results ; table(Speed_ref_prm',Dyno_ref_prm',Parameter_Var',Theta_Error_mean_values', ...
            Theta_Error_std_values',Torque_Error_mean_values',Torque_Error_std_values', ...
            Speed_Plant_mean_values',Speed_Plant_std_values', ...
        'VariableNames',{'Speed_ref','Torque_ref', Automatic_Test.parameter_var, 'Theta_error_mean', ...
            'Theta_error_std', 'Torque_error_mean', 'Torque_error_std', 'Speed_mean', 'Speed_std'})]

     
        %......Naming the figure file against speed and torque....%
       r=strcat('Speed_',num2str(Automatic_Test.Speed(i)),'_Load_',strrep(num2str(Automatic_Test.Dyno_Load_Vector(j)),'.','_')); 
       
        %..... To Plot the Speed, torque and theta error...........%
        y = figure('Name','Run','NumberTitle','off');
        subplot(2,2,1);
        plot(Speed);
        ylabel('Speed(rpm)')
        title('Speed Data')
        legend('Speed Ref','Speed real','Speed Est')
        grid on;
        subplot(2,2,2);
        plot(Torque_Data);
        ylabel('Torque(Nm)')
        title('Torque Data')
        legend('Torque','Torque Estimated')
        grid on;
        subplot(2,2,3);
        plot(Theta_Error);
        title('Theta Error')
        grid on;
        subplot(2,2,4);
        plot(Torque_Error);
        title('Torque Error')
        grid on;

         
        %.........To save the figures plotted in created folder as .fig file.....%
        FigPath=strcat(d,'\',r);
        saveas(y,fullfile(FigPath),'fig');
        close(y)
       
    end
end

%........To save the Report as .csv file in generated folder.......%
r1=strcat('Report','.csv');
FigPath1=strcat(d,'\',r1);
writetable(Results,FigPath1);

   
%......... Generation of output values ..........%

function [interval_index] = get_intervals(parameter_signal)
    parameter_signal_shifted = [parameter_signal(1) parameter_signal]; 
    parameter_signal = [parameter_signal parameter_signal(end)];
    index_signal = parameter_signal_shifted - parameter_signal;

    k=find(index_signal~=0);
    if k 
        %.....Adding first interval with nominal value.....%
        interval_index = [k(1)-(k(2)-k(1)) k];
    else
        interval_index = [];
    end
end

function [mean_values,std_values] = statistics(signal, interval_index)
    n=length(interval_index)-1;
    mean_values = zeros(1,n);
    std_values = zeros(1,n);
    for i=1:n
        interval=interval_index(i+1)-interval_index(i);  % To get the interval between change in two parameter values.

        start_1=interval_index(i)+floor(interval*0.2);   % To get the data after 0.2 seconds of interval begins
        final=interval_index(i+1)-floor(interval*0.01);  % To get the data before 0.01 seconds of interval stops.

        windowed_value=signal(start_1:final);
        mean_values(i)=mean(windowed_value);
        std_values(i)=std(windowed_value);
    end
end










         
         
         
         
         
  

       


        
        

