%iteration algorithm for spliting one Const block into several blocks in
%order to enable parameters tunability

% input - number of parameters

s_fun_par_count = 88
%s_fun_lib_block_name = 'bpm_dq_S_noH_D_RL_Dyno_10k'
%s_fun_lib_block_name = 'bpm_dq_S_noH_D_RL_Dyno_cont'
%s_fun_lib_block_name = 'bpm_dq_S_noH_D_RL_U_Dyno_xk'
%s_fun_lib_block_name = 'bpm_dq_S_noH_noD_RL_U_Dyno_xk_hs'
%s_fun_lib_block_name = 'bpm_dq_S_noH_D_RL_U_Dyno_cont'

%HA_Spin
%s_fun_lib_block_name = 'bpm_dq_S_noH_D_RL_U_HA_Spin_xk'
%s_fun_lib_block_name = 'bpm_dq_S_noH_noD_RL_U_HA_Spin_xk_hs'

%VA_Agitation
s_fun_lib_block_name = 'bpm_dq_S_noH_D_RL_U_VA_Agitation_xk'

%creating a mux block
%add_block('simulink/Signal Routing/Mux', 'SPPMSM_sfun_cont_4/SPPMSM_sfun_cont_4/mux2', 'Inputs', num2str(s_fun_par_count), 'Position', '[93, 35, 98, 211]');
add_block('simulink/Signal Routing/Mux', [s_fun_lib_block_name,'/',s_fun_lib_block_name,'/mux2'], 'Inputs', num2str(s_fun_par_count), 'Position', '[143, 85, 148, 261]');

% creating a const blocks and connecting with mux inputs
for i=1:s_fun_par_count
    add_block('simulink/Sources/Constant', [s_fun_lib_block_name,'/',s_fun_lib_block_name,'/MapleSimParameters',num2str(i)], 'Value', ['Par',num2str(i)], 'Position', '[260, 150, 315, 166]');
    add_line([s_fun_lib_block_name,'/',s_fun_lib_block_name], ['MapleSimParameters',num2str(i),'/1'], ['mux2/',num2str(i)], 'autorouting', 'on');
end
% connecting mux out with s-funtion input
add_line([s_fun_lib_block_name,'/',s_fun_lib_block_name], 'mux2/1', 'sfn/2', 'autorouting', 'on');

clear s_fun_par_count
clear s_fun_lib_block_name
