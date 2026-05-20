
% Last Modified by v1.1 14-Feb-2019 16:08:20
%--------------------------------------------------------------------------
% Author:      Madhura Patil
% Date:        Dec 17, 2018
%--------------------------------------------------------------------------

%--------------------------------------------------------------------------
% Description:  This Script is used to run and test performance of motor
% against defined speed and load torque.
% It checks the robustness of the motor under test by generating the failure 
% values of the tests.This script has been used to change the initial angle
% of the motor to check the sensitivity of the motor.
%--------------------------------------------------------------------------


%--------------------------------------------------------------------------
% Requirements to run the test 
%   Electrical Requirement:- Permanent Magnet Motor
%   Mechanical Requirement:- Dyno Load, Washer Load
% 
% This Test has been carried on Sim Arch .Please read the document guide in same folder. 
%--------------------------------------------------------------------------

%--------------------------------------------------------------------------
% Please Note- Before running this script, Parameter_Initialization_Initial_Angle.m file has
%               to be updated to edit the parameters required to run the test. 
%--------------------------------------------------------------------------



%.......Opening the model ..........%

open('MCU_Simulation_Architecture.slx')
Parameter_Intiatilization_Initial_Angle;

%..To name the folder by current date and time...%
dname = uigetdir('C:\');
currDate = strrep(datestr(datetime), ':', '_');
bc=strcat(dname,'\',currDate);
d=char(bc);
mkdir(d)

%..Creates an empty table to collect results....%

if (Automatic_Test.Variant=='Temperature ')
    
    
 Results = table([],[],[],[],[],...
           'VariableNames',{'Stream_Ver',Automatic_Test.Variant,'Resistance','Angle','Status'});
    
else
Results = table([],[],[],[],...
           'VariableNames',{'Stream_Ver',Automatic_Test.Variant,'Angle','Status'});
end

       
%..Selection of Test............................%

 if (Automatic_Test.Variant=='Load_Torque ')   
     Automatic_Test.Array=Automatic_Test.Dyno_Load_Vector;
     
      elseif(Automatic_Test.Variant=='Acceleration')
          Automatic_Test.Array=Automatic_Test.Acceleration_Vector;
          
       elseif(Automatic_Test.Variant=='Jdrum       ')
          Automatic_Test.Array=Automatic_Test.JDrum_Vector;

        elseif(Automatic_Test.Variant=='Damp        ')
          Automatic_Test.Array=Automatic_Test.Damp_Vector;

        elseif(Automatic_Test.Variant=='Temperature ')
          Automatic_Test.Array=Automatic_Test.Temperature_Vector;
 end




            

 for j=1:length(Automatic_Test.Array)
          if (Automatic_Test.Variant=='Load_Torque ')   
                Automatic_Test.Dyno_Load=Automatic_Test.Array(j);
                Automatic_Test.Test=Automatic_Test.Dyno_Load;
                
        elseif(Automatic_Test.Variant=='Acceleration')
                Automatic_Test.Acceleration= Automatic_Test.Array(j);
                Automatic_Test.Test=Automatic_Test.Acceleration;
                
         elseif(Automatic_Test.Variant=='Jdrum       ')
              Mechanical.JDrum= Automatic_Test.Array(j); 
             Automatic_Test.Test=Mechanical.JDrum;
             
        elseif(Automatic_Test.Variant=='Damp        ')
             Mechanical.damp= Automatic_Test.Array(j);
             Automatic_Test.Test=Mechanical.damp;
             
        elseif(Automatic_Test.Variant=='Temperature ')
            Thermal.Tstator= Automatic_Test.Array(j);
             Automatic_Test.Test=Thermal.Tstator;
                
          end  
          
    for m=1:length(Automatic_Test.ThetaElec) 
       Automatic_Test.Theta= Automatic_Test.ThetaElec(m) ;
        Automatic_Test.ThetaMech_degree=Automatic_Test.ThetaElec(m)/Motor.Electrical.p_Pole_Pairs; %...To convert electrical angle to corresponding Mechanical...%
         Automatic_Test.ThetaMech=(Automatic_Test.ThetaMech_degree*pi)/180;                        %...To convert Mechanical angle in degree to radians...% 
            
                
           sim('MCU_Simulation_Architecture.slx');
           
           %.......Values required to plot in report.....%
           Angle_Electrical= Automatic_Test.Theta; 
           Case=Automatic_Test.Test; 
           
           %......  Condition to Pass the status of the test........%
           
           Condition_Data1=find(Bed_Start.Data);
           Condition_Out1=any(Condition_Data1);
           Condition_Data2=find(Worse_Start.Data);
           Condition_Out2=any(Condition_Data2);
           Condition_Data3=find(Fail_1.Data);
           Condition_Out3=any(Condition_Data3);                                                                                                          
           Condition_Data4=find(Fail_2.Data);
           Condition_Out4=any(Condition_Data4);
          
           if(Condition_Out3)
           status='Fail_1';
           elseif(Condition_Out4)
           status='Fail_2';
           elseif (Condition_Out2)
          status='Worse ';
          elseif (Condition_Out1)
          status='Bad   ';
           else
          status='Pass  ';
           end
          Status=status;


  %......To plot the Report..............%
  
     if (Automatic_Test.Variant=='Temperature ')
         Automatic_Test.Resistance=Motor.Electrical.Rs_a_Ref*(1+(Motor.Electrical.alpha_s)*( Automatic_Test.Test-Motor.Mechanical.Rs_Temperature_Ref));% Calculation of resistance w.r.t change in temperature. 
         
          Results =[Results ; table(Automatic_Test.Stream,Case,Automatic_Test.Resistance,Angle_Electrical',Status,...
          'VariableNames',{'Stream_Ver',Automatic_Test.Variant,'Resistance','Angle','Status'})]
       
         
     else
           Results =[Results ; table(Automatic_Test.Stream,Case,Angle_Electrical',Status,...
          'VariableNames',{'Stream_Ver',Automatic_Test.Variant,'Angle','Status'})]
           
     end
      
 
        %......Naming the figure file against speed and torque....%
        r=strcat('Speed_',num2str(Automatic_Test.ThetaElec(m)),'_',Automatic_Test.Variant,'_',strrep(num2str(Automatic_Test.Test(j)),'.','_')); 
        
        %.........To Plot the Speed, torque and Theta error...........%
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
        grid on;
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















         
         
         
