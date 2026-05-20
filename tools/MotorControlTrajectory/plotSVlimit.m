tmp = get(logsout,'Vdc');
Vdc = mean(tmp.Values.Data(1:1:end));

vdc_pk = Vdc;

tmp = get(logsout,'V Alpha Beta');
vAlfaBeta_Alpha_Real=  tmp.Values.Data(:,1);

tmp = get(logsout,'V Alpha Beta');
vAlfaBeta_Beta_Real=  tmp.Values.Data(:,2);

figure(2)
hold on

% Subscribed circle
plot(2/3*vdc_pk*cos(0:0.001:2*pi),2/3*vdc_pk*sin(0:0.001:2*pi),'-m');

% Inverter hexagon
X=[2/3*vdc_pk; 2/3*vdc_pk*cos(pi/3); -2/3*vdc_pk*cos(pi/3);-2/3*vdc_pk; -2/3*vdc_pk*cos(pi/3);2/3*vdc_pk*cos(pi/3);2/3*vdc_pk];
Y=[0; 2/3*vdc_pk*sin(pi/3); 2/3*vdc_pk*sin(pi/3);0; -2/3*vdc_pk*sin(pi/3);-2/3*vdc_pk*sin(pi/3);0];

plot(X,Y,'-b');

% Inscribed circle
plot(vdc_pk/sqrt(3)*cos(0:0.001:2*pi),vdc_pk/sqrt(3)*sin(0:0.001:2*pi),'-k');

% Vector to be generated
x = vAlfaBeta_Alpha_Real(1:1:end); 
y = vAlfaBeta_Beta_Real(1:1:end);
plot(x,y,'xr');

legend('Circumscribed Circle', 'Limit Hexagon', 'Inscribed circle', 'VAlfaBeta Real');
grid on

tmp = get(logsout,'Vdc');
Vdc = mean(tmp.Values.Data(1:1:end));

vdc_pk = Vdc;


tmp = get(logsout,'V Alpha Beta Ref');
vAlfaBeta_Alpha_Ref=  tmp.Values.Data(:,1);

tmp = get(logsout,'V Alpha Beta Ref');
vAlfaBeta_Beta_Ref=  tmp.Values.Data(:,2);


figure(3)
hold on

% Subscribed circle
plot(2/3*vdc_pk*cos(0:0.001:2*pi),2/3*vdc_pk*sin(0:0.001:2*pi),'-m');

% Inverter hexagon
X=[2/3*vdc_pk; 2/3*vdc_pk*cos(pi/3); -2/3*vdc_pk*cos(pi/3);-2/3*vdc_pk; -2/3*vdc_pk*cos(pi/3);2/3*vdc_pk*cos(pi/3);2/3*vdc_pk];
Y=[0; 2/3*vdc_pk*sin(pi/3); 2/3*vdc_pk*sin(pi/3);0; -2/3*vdc_pk*sin(pi/3);-2/3*vdc_pk*sin(pi/3);0];

plot(X,Y,'-b');

% Inscribed circle
plot(vdc_pk/sqrt(3)*cos(0:0.001:2*pi),vdc_pk/sqrt(3)*sin(0:0.001:2*pi),'-k');

% Vector to be generated
x = vAlfaBeta_Alpha_Ref(1:1:end); 
y = vAlfaBeta_Beta_Ref(1:1:end);
plot(x,y,'xr');

legend('Circumscribed Circle', 'Limit Hexagon', 'Inscribed circle', 'VAlfaBeta Reference');
grid on
