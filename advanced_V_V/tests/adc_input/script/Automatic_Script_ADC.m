
% Last Modified by v1.1 14-Feb-2019 16:08:20
%--------------------------------------------------------------------------
% Author:      Madhura Patil
% Date:        Dec 12, 2018
%--------------------------------------------------------------------------

%--------------------------------------------------------------------------
% Description:  This Script is used to run and test performance of motor
% against defined speed and load torque.
% It checks the robusteness of the motor under test by generating the failure 
% values of the tests.In this test random noise has been added to Vdc and
% Iabc depending on selection of Test.
%--------------------------------------------------------------------------

%--------------------------------------------------------------------------
% Requirements to run the test 
%   Electrical Requirement:- Permanent Magnet Motor
%   Mechanical Requirement:- Dyno Load
%--------------------------------------------------------------------------

%--------------------------------------------------------------------------
% Please Note- Before running this script, Parameter_Initialization_ADC file has
%               to be updated to edit the parameters required to run the test. 
%--------------------------------------------------------------------------



%.......Opening the  model..........%

addpath('..\..\..\advanced_V_V\tests\adc_input\harness_model')
open('Harnes_ADC_Noise.slx');

Parameter_Intiatilization_ADC;

%.........To name the folder by current date and time.......%
dname = uigetdir('C:\');
currDate = strrep(datestr(datetime), ':', '_');
bc=strcat(dname,'\',currDate);
d=char(bc);
mkdir(d)

%.......Parameter Intialization for the selection of Volt and Iabc signal Input...........%
h1 = Simulink.findBlocks(gcs,'Name','Noise Value');

%.......Parameter Intialization for the selection of Volt signal Input.......%
if (strcmp(Automatic_Test.Noise_Var,'Volt_Noise_Power')) 
set_param(h1,'init_value','Automatic_Test.Volt');
elseif(strcmp(Automatic_Test.Noise_Var,'Ic_Noise_Power'))
%.......Parameter Intialization for the selection of Iabc signalInput.....%
set_param(h1,'init_value','Automatic_Test.Ic');
else
  msg='Please select type of variation either  Vdc or Iabc in Automatic_Test.Noise_var in Parameter Intialization file.';
 error(msg)
end

%..........Creates an empty table to collect results....%
if (strcmp(Automatic_Test.Noise_Var,'Volt_Noise_Power')) 
Results = table([],[],[],[],[],[],[],[],[],[], ...
'VariableNames',{'Speed_ref','Torque_ref', 'Voltage_Noise_mean','Voltage_Noise_std','Theta_error_mean', ...
    'Theta_error_std', 'Torque_error_mean', 'Torque_error_std', 'Speed_mean', 'Speed_std'});
elseif(strcmp(Automatic_Test.Noise_Var,'Ic_Noise_Power'))
Results = table([],[],[],[],[],[],[],[],[],[],[],[],[],[], ...
'VariableNames',{'Speed_ref','Torque_ref', 'Ia_Noise_mean','Ia_Noise_std','Ib_Noise_mean','Ib_Noise_std',...
'Ic_Noise_mean','Ic_Noise_std','Theta_error_mean', ...
    'Theta_error_std', 'Torque_error_mean', 'Torque_error_std', 'Speed_mean', 'Speed_std'});
end
%......Iteration.....%

for i=1:length(Automatic_Test.Speed)
    Automatic_Test.Speed_Ref=Automatic_Test.Speed(i);
     for j= 1:length(Automatic_Test.Dyno_Load_Vector) %1:1
           Automatic_Test.Dyno_Load=Automatic_Test.Dyno_Load_Vector(j);

        %.....Simulte the Model....................%
        sim('Harnes_ADC_Noise.slx');
      
        
         %..... To collect statistics............. %
         if (strcmp(Automatic_Test.Noise_Var,'Volt_Noise_Power')) 
         interval_index = get_intervals(V_Noise_Power.signals.values');
         elseif(strcmp(Automatic_Test.Noise_Var,'Ic_Noise_Power'))
          interval_index = get_intervals(Iabc_Noise_Power.signals.values');
         end
         
         if interval_index
            [Theta_Error_mean_values,Theta_Error_std_values] = statistics(Theta_Error.Data, interval_index);
            %....Torque error....%
            [Torque_Error_mean_values,Torque_Error_std_values] = statistics(Torque_Error.Data, interval_index);
            %....Speed...........%
             [Speed_Plant_mean_values,Speed_Plant_std_values] = statistics(Speed_Plant.Data, interval_index);
             %.......Voltage.....%
             if (strcmp(Automatic_Test.Noise_Var,'Volt_Noise_Power')) 
             [Voltage_Noise_mean_values,Voltage_Noise_std_values] = statistics(Vdc.Data, interval_index);
             elseif(strcmp(Automatic_Test.Noise_Var,'Ic_Noise_Power'))
              [Ia_Noise_mean_values,Ia_Noise_std_values] = statistics(Ia.Data, interval_index);%Iabc.signal1
              [Ib_Noise_mean_values,Ib_Noise_std_values] = statistics(Ib.Data, interval_index);%Iabc.signal1
              [Ic_Noise_mean_values,Ic_Noise_std_values] = statistics(Ic.Data, interval_index);%Iabc.signal1
              end
        else
            %....Empty --> If steady state not reached...%
            Theta_Error_mean_values = NaN;
            Theta_Error_std_values = NaN;
            Torque_Error_mean_values= NaN;
            Torque_Error_std_values= NaN;
            Speed_Plant_mean_values= NaN;
            Speed_Plant_std_values= NaN;
            Voltage_Noise_mean_values=NaN;
            Voltage_Noise_std_values=NaN;
            Ic_Noise_mean_values=NaN;
            Ic_Noise_std_values=NaN;
            
            
        end
        
        %.......To collect the parameters values............%
         Speed_ref_prm=Automatic_Test.Speed_Ref *ones(size(Theta_Error_mean_values)); %.....Speed Value
         Dyno_ref_prm = Automatic_Test.Dyno_Load * ones(size(Theta_Error_mean_values)); %....Dyno Load Value
          

        %.........To update the results table..........%
        if(strcmp(Automatic_Test.Noise_Var,'Volt_Noise_Power')) 
            
        Results = [Results ; table(Speed_ref_prm',Dyno_ref_prm',Voltage_Noise_mean_values',Voltage_Noise_std_values',Theta_Error_mean_values', ...
            Theta_Error_std_values',Torque_Error_mean_values',Torque_Error_std_values', ...
            Speed_Plant_mean_values',Speed_Plant_std_values', ...
        'VariableNames',{'Speed_ref','Torque_ref','Voltage_Noise_mean','Voltage_Noise_std','Theta_error_mean', ...
            'Theta_error_std', 'Torque_error_mean', 'Torque_error_std', 'Speed_mean', 'Speed_std'})];
        
        elseif(strcmp(Automatic_Test.Noise_Var,'Ic_Noise_Power'))
            
            Results = [Results ; table(Speed_ref_prm',Dyno_ref_prm',Ia_Noise_mean_values',Ib_Noise_std_values',Ic_Noise_mean_values',...
            Ic_Noise_std_values', Ic_Noise_mean_values', Ic_Noise_std_values',Theta_Error_mean_values', ...
            Theta_Error_std_values',Torque_Error_mean_values',Torque_Error_std_values', ...
            Speed_Plant_mean_values',Speed_Plant_std_values', ...
           'VariableNames',{'Speed_ref','Torque_ref', 'Ia_Noise_mean','Ia_Noise_std','Ib_Noise_mean','Ib_Noise_std',...
            'Ic_Noise_mean','Ic_Noise_std','Theta_error_mean', ...
              'Theta_error_std', 'Torque_error_mean', 'Torque_error_std', 'Speed_mean', 'Speed_std'})];
              end
  
    
              
       %.........To Plot the Speed, torque and theta error...........%
        %r=strcat('Speed_',num2str(Automatic_Test.Speed(i)),'_Load_',num2str(Automatic_Test.Dyno_Load_Vector(j)));
         r=strcat('Speed_',num2str(Automatic_Test.Speed(i)),'_Load_',strrep(num2str(Automatic_Test.Dyno_Load_Vector(j)),'.','_')); 
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

         
        %.........To save the figures plotted in created folder.....%
        FigPath=strcat(d,'\',r);
        saveas(y,fullfile(FigPath),'fig');
        close(y)
        
    end
end

%........To save the Report as .csv file in generated folder.......%
r1=strcat('Report','.csv');
FigPath1=strcat(d,'\',r1);
writetable(Results,FigPath1);

   
......... Generation of output values ..........%

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
    mean_values = zeros(1,n);                            % initializing mean value as zero
    std_values = zeros(1,n);                             % initializing std value as zero
    for i=1:n
        interval=interval_index(i+1)-interval_index(i);  % To get the interval between change in two parameter values.

        start_1=interval_index(i)+floor(interval*0.2);   % To get the data after 0.2 seconds of interval begins
        final=interval_index(i+1)-floor(interval*0.01);  % To get the data before 0.01 seconds of interval stops.

        windowed_value=signal(start_1:final);
        mean_values(i)=mean(windowed_value);
        std_values(i)=std(windowed_value);
    end
end










         
         
         
         
         
  

       


        
        

