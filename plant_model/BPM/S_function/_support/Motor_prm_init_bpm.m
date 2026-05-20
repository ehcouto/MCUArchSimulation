%% parsing new and old param structures

% Core parameters
% Electrical
Motor_prm.Electrical.Rs_0 = Motor.Electrical.Rs_a_Ref;
Motor_prm.Electrical.Ld_0 = Motor.Inductance_Variation.Ld_a0;
Motor_prm.Electrical.Lq_0 = Motor.Inductance_Variation.Lq_b0;
Motor_prm.Electrical.NPP = Motor.Electrical.p_Pole_Pairs;
Motor_prm.Electrical.PM_flux_h1_0 = Motor.Electrical.PM_Flux_f01;
% Electrical
Motor_prm.Mechanical.Jrotor = Motor.Mechanical.Jrotor;
Motor_prm.Mechanical.B = Motor.Mechanical.B;
Motor_prm.Mechanical.TR = Motor.Mechanical.TR;
% Thermal
Motor_prm.Thermal.Temp_stator_0 = Motor.Mechanical.Rs_Temperature_Ref;
Motor_prm.Thermal.Temp_rotor_0 = Motor.Mechanical.PM_Temperature_Ref;
Motor_prm.Thermal.Rs_alpha = Motor.Electrical.alpha_s; % resistance temp coef
Motor_prm.Thermal.PM_alpha = 0.206e-2;

% Advanced Parameters
% Inductance saturation
Motor_prm.Inductance_Variation.Ld_a = [Motor.Inductance_Variation.Ld_a0...
    Motor.Inductance_Variation.Ld_a1 Motor.Inductance_Variation.Ld_a2 Motor.Inductance_Variation.Ld_a3...
    Motor.Inductance_Variation.Ld_a4 Motor.Inductance_Variation.Ld_a5 Motor.Inductance_Variation.Ld_a6 Motor.Inductance_Variation.Ld_a7];
Motor_prm.Inductance_Variation.Lq_b = [Motor.Inductance_Variation.Lq_b0...
    Motor.Inductance_Variation.Lq_b1 Motor.Inductance_Variation.Lq_b2 Motor.Inductance_Variation.Lq_b3...
    Motor.Inductance_Variation.Lq_b4 Motor.Inductance_Variation.Lq_b5 Motor.Inductance_Variation.Lq_b6 Motor.Inductance_Variation.Lq_b7];
Motor_prm.Inductance_Variation.Ipk = [Motor.Inductance_Variation.I_pk0 Motor.Inductance_Variation.I_pk1...
    Motor.Inductance_Variation.I_pk2 Motor.Inductance_Variation.I_pk3 Motor.Inductance_Variation.I_pk4...
    Motor.Inductance_Variation.I_pk5 Motor.Inductance_Variation.I_pk6 Motor.Inductance_Variation.I_pk7];

% Power Loss
Motor_prm.Power_Loss.Speed = [Motor.Power_Loss.Rot_Loss_Speed0, (Motor.Power_Loss.Rot_Loss_Speed1 + 0.1)...
    (Motor.Power_Loss.Rot_Loss_Speed2 + 0.2), (Motor.Power_Loss.Rot_Loss_Speed3 + 0.3)...
    (Motor.Power_Loss.Rot_Loss_Speed4 + 0.4), (Motor.Power_Loss.Rot_Loss_Speed5 + 0.5)...
    (Motor.Power_Loss.Rot_Loss_Speed6 + 0.6), (Motor.Power_Loss.Rot_Loss_Speed7 + 0.7)];

% for i=1:7
%     if (Motor_prm.Power_Loss.Speed(i) < Motor_prm.Power_Loss.Speed(i+1))
%         index = i+1
%     end
% end
% index
% 
% k = 0;
% for i=(index+1):8
%     k = k + 1;
%     Motor_prm.Power_Loss.Speed(i) = Motor_prm.Power_Loss.Speed(i) + 0.1 * k;
% end

% Motor_prm.Power_Loss.Speed = [Motor.Power_Loss.Rot_Loss_Speed0, (Motor.Power_Loss.Rot_Loss_Speed1)...
%     (Motor.Power_Loss.Rot_Loss_Speed2), (Motor.Power_Loss.Rot_Loss_Speed3)...
%     (Motor.Power_Loss.Rot_Loss_Speed4), (Motor.Power_Loss.Rot_Loss_Speed5)...
%     (Motor.Power_Loss.Rot_Loss_Speed6), (Motor.Power_Loss.Rot_Loss_Speed7)];

Motor_prm.Power_Loss.Power = [Motor.Power_Loss.Rot_Loss_Power0 Motor.Power_Loss.Rot_Loss_Power1...
    Motor.Power_Loss.Rot_Loss_Power2 Motor.Power_Loss.Rot_Loss_Power3...
    Motor.Power_Loss.Rot_Loss_Power4 Motor.Power_Loss.Rot_Loss_Power5...
    Motor.Power_Loss.Rot_Loss_Power6 Motor.Power_Loss.Rot_Loss_Power7];

Motor_prm.Power_Loss.Flag = Motor.Power_Loss.Rot_Loss_Flag;
