%Plot Id Iq working point on DTC

% Close figures
try
close('1')
close('2')
end



%read CSV
R1 = 1;
C1 = 1;

filename = 'h38_17500rpm.txt';

M = tdfread(filename,'\t');

sample_steady = 2;
sample_end = 5000;

Id = zeros(sample_end,1);
Iq = zeros(sample_end,1);

Vs_lim = zeros(sample_end,1);
speed = zeros(sample_end,1);

for i = [sample_steady:sample_end]
Id(i) = str2num(M.rotor_curr_id(i,:));
Iq(i) = str2num(M.rotor_curr_iq(i,:));
speed(i) = str2num(M.Mcl_Quantities0x2ESpeed_Rot_Mech(i,:));
Vs_lim(i) = str2num(M.Mcl_IO0x2EVdc(i,:));
end

%Id = id.data;
%Iq = iq.data

% Parameters
Is_max = 6;
lambda_m = 0.0687;
id_braking = 0;
Ld = 0.0212;
Lq = 0.0299;
p = 4;
Rs = 3.375;
%Vs_lim = DC_Bus.Const_Vbus / sqrt(3)* 0.9; % depends on fieldweakening strategy

Vs_lim = Vs_lim(sample_end)/sqrt(3);

speed = speed(sample_end)

we = 2*pi*p*speed / 60;


Torque_last = 1.5*p*(lambda_m*Iq(sample_end) + (Ld-Lq)*Id(sample_end)*Iq(sample_end))

id_torque =  [-20:0.01:20];

i = 0;
for id_t = id_torque
i = i +1;    
iq_torque(i) = Torque_last/( 1.5*p*(lambda_m + (Ld-Lq)*id_t));
end

% Id Iq characteristic
% MTPV ellipses calculation
% flux limit

% Voltage Limit equation
% Vd^2 + Vq^2 <= VsLim^2
% (Rs*Id-we*(Lq*Iq))^2 + (Rs*Iq + we(Ld*Id + Phim))^2 <= VsLim^2
% Semimajor axis calculation -> Iq = 0
a = we^2*Ld^2 + Rs^2;
b = (2*Ld*lambda_m) * (we^2);
c = (we*lambda_m)^2 - Vs_lim^2;
delta = b^2 - 4*a*c;
lambda_lim_1 = (- b + sqrt(delta)) / (2*a);
lambda_lim_2 = (- b - sqrt(delta)) / (2*a);
lambda_lim = min(lambda_lim_1, lambda_lim_2);
Semimajor_axis = abs(lambda_lim+lambda_m/Ld);


i = 1;

iq_v = 0;


for id_v = [lambda_lim_2:0.01:lambda_lim_1]
    
    

% Semiminor axis calculation -> Id = -lambda/ld
a = we^2*Lq^2 + Rs^2;
b = -2*Rs*id_v*we*Lq + 2*Rs*we*(Ld*id_v+lambda_m);
c = (Rs*id_v)^2 +(we*(Ld*id_v+lambda_m))^2- Vs_lim^2;

delta = b^2 - 4*a*c;
iq_v(1,i) = (- b + sqrt(delta)) / (2*a); %Iq positive
iq_v(2,i) = (- b - sqrt(delta)) / (2*a); %Iq negative
%lambda_lim = mean([abs(lambda_lim_1), abs(lambda_lim_2)]);

%iq_center = lambda_lim_1+lambda_lim_2; % Iq ellipse center is not perfectly zero 

%Semiminor_axis = lambda_lim;

i = i +1;
end

VoltageLim_x_comp = [[lambda_lim_2:0.01:lambda_lim_1],[lambda_lim_1:-0.01:lambda_lim_2]];
VoltageLim_y_comp = [iq_v(1,:),iq_v(2,:)];


% maximum torque
max_torque = 3/2 * p / Ld * lambda_lim * lambda_m;
% ellipses
%[VoltageLim_x_comp, VoltageLim_y_comp]  = calculateEllipse(-lambda_m/Ld, iq_center, Semimajor_axis , Semiminor_axis);
% Short circuit current
sc_current = -lambda_m / Ld;
[VoltageLim_x,VoltageLim_y]  = calculateEllipse(-lambda_m/Ld, 0, Vs_lim/(Ld*we) , Vs_lim/(Lq*we));

% Is max 
[CurrentLim_x, CurrentLim_y]  = calculateEllipse(0, 0, Is_max, Is_max);

% MTPA
if Ld == Lq
iq_MTPA = [-20:0.01:20];
id_MTPA= 0*iq_MTPA;
id_MTPV = sc_current;
else    
k_MTPA = lambda_m/(2*(Lq-Ld));
iq_MTPA = [-20:0.01:20];
id_MTPA= k_MTPA - sqrt(k_MTPA^2 + iq_MTPA.^2);

%wrong equation, MTPV is not a shifted MTPA
%id_MTPV= sc_current + k_MTPA - sqrt(k_MTPA^2 + iq_MTPA.^2);

%Fixed equation
id_MTPV = (-lambda_m*((2*Ld-Lq)/(2*(Ld-Lq))) -0.5*sqrt((lambda_m*Lq/(Ld-Lq))^2 + 4*(Lq*iq_MTPA).^2))/(Ld)

end


% Plot settings
figure(1)
plot(Id(sample_steady:sample_end),Iq(sample_steady:sample_end),'-b'); % DTC trajectory
hold on;
% plot(VoltageLim_x, VoltageLim_y); % Voltage limit (R_s = 0)
% hold on;
plot(id_torque, iq_torque); % torque curve
hold on;
plot(VoltageLim_x_comp, VoltageLim_y_comp,'-k'); % Voltage limit 
hold on;
plot(sc_current*ones(200), [-99:1:100],'g'); % MTPV

hold on;
plot(CurrentLim_x, CurrentLim_y,'-r'); % Current limit
hold on;



    

plot(id_MTPA, iq_MTPA); % MTPA
plot(id_MTPV, iq_MTPA); % MTPV



legend('DTC trajectory','Last Torque Curve', 'Voltage limit', 'Short Circuit', 'Current limit', 'MTPA', 'MTPV');
s = strcat('Speed = ', num2str(speed), ' rpm');
title({'Id Iq characteristics', s});
xlabel('I_d');
ylabel('I_q');
% annotations
v_dc_str = strcat('V_{dc} = ', num2str(DC_Bus.Const_Vbus), ' V');
v_s_lim_str = strcat('V_{s_{lim}} = ', num2str(Vs_lim), ' V');
text(5, 0, v_dc_str);
text(5, -2, v_s_lim_str);
max_axis_current = 10;
XMIN =-max_axis_current;
XMAX =max_axis_current;
YMIN =-max_axis_current; 
YMAX =max_axis_current;
axis([XMIN XMAX YMIN YMAX]);
grid on;

%plotSVlimit;


tmp = get(logsout,'Vd_real');
Vd = tmp.Values.Data(:);
tmp = get(logsout,'Vq_real');
Vq = tmp.Values.Data(:);


Id = Id(sample_end)
Iq = Iq(sample_end)
Vd = Vd(sample_end)
Vq = Vq(sample_end)




