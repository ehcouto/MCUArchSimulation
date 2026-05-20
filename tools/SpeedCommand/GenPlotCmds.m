function [table_pts, mci_cmds] = GenPlotCmds(table)
current_speed = 0;
current_time = 0;
table_pts = [0,0]; 
mci_cmds = [];
num_rows = size(table,1);
for i=1:num_rows
    %extract values from table and check the validity of string (not number) parameters
    target = eval_row(table, i, 1);
    accel = eval_row(table, i, 2);
    step_duration = eval_row(table, i, 3);
    ton = eval_row(table, i, 4);
    toff = eval_row(table, i, 5);
    
    %generate array of pts and cmds
    ton_cnt = 0;
    toff_cnt = 0;
    plato = 0;
    multiplier = 1;
    counter = 0;
    current_target = target;
    step_final_time = current_time + step_duration;
    STEP_TIME_INCREMENT = 0.01;
    for j=current_time:STEP_TIME_INCREMENT:step_final_time
        if(current_speed < current_target)
            if plato
                plato = 0;
                table_pts = [table_pts; current_speed, j];
                multiplier = 1;
                continue;
            end
            current_speed = current_speed + (accel * STEP_TIME_INCREMENT); %increase speed by accel (rpm/10^-2 s)
            if (current_speed >= current_target)
                current_speed = current_target;
                table_pts = [table_pts; current_speed, j];
            elseif (j == step_final_time) && (accel ~= 0 )
                table_pts = [table_pts; current_speed, j];
            end
        elseif (current_speed > current_target)
            if plato
                plato = 0;
                table_pts = [table_pts; current_speed, j];
                multiplier = -1;
                continue
            end
            current_speed = current_speed - (accel * STEP_TIME_INCREMENT); % decrease speed by accel (rpm/10^-2 s)
            if (current_speed <= current_target)
                current_speed = current_target;
                table_pts = [table_pts; current_speed, j];
            elseif (j == step_final_time) && (accel ~= 0 )
                table_pts = [table_pts; current_speed, j];
            end
        else
            plato = 1;
            if (j == step_final_time) && (accel ~= 0 )
                table_pts = [table_pts; current_speed, j];
            end
        end
        if ton
            if toff                             %both ton and toff defined
                switch (counter)
                    case 0
                    ton_cnt = ton_cnt + STEP_TIME_INCREMENT;
                
                    case 1
                    toff_cnt = toff_cnt + STEP_TIME_INCREMENT;
                end
                if (ton_cnt >= ton)
                    mci_cmds = [mci_cmds; current_target, accel, ton];
                    current_target = 0;
                    ton_cnt = 0;
                    counter = 1;
                elseif (j == step_final_time) && (current_target ~= 0)
                    remainder_time = rem(step_duration, (ton+toff));
                    if remainder_time == 0
                        current_time = step_final_time;
                        continue;
                    else
                        lst_time_cmd = remainder_time;
                    end
                    mci_cmds = [mci_cmds; current_target, accel, lst_time_cmd];
                end
                if (toff_cnt >= toff)
                    mci_cmds = [mci_cmds; current_target, accel, toff];
                    current_target =  multiplier * target;
                    
                    toff_cnt = 0;
                    counter = 0;
                elseif (j == step_final_time) && (current_target == 0)
                    remainder_time = rem(step_duration, (ton+toff));
                    if remainder_time == 0
                        current_time = step_final_time;
                        continue;
                    else
                        lst_time_cmd = remainder_time - ton;%remainder_time - ton;
                    end
                    mci_cmds = [mci_cmds; current_target, accel, lst_time_cmd];
                end
            else
                ton_cnt = ton_cnt + STEP_TIME_INCREMENT;       % only ton defined
                if (ton_cnt >= ton)
                    mci_cmds = [mci_cmds; current_target, accel, ton];
                    current_target = -current_target;
                    ton_cnt = 0;
                elseif (j == step_final_time)
                    mci_cmds = [mci_cmds; current_target, accel, ton];
                end
            end
        else
            if (j==step_final_time) && (accel~=0)
                mci_cmds = [mci_cmds; current_target, accel, step_duration];
            end
        end
        if (j >= step_final_time)
            current_time = step_final_time; 
        end
    end
    
end

function [result] = eval_row(table, row, col)
result = str2double(table(row,col));
    if isnan(result)
        if strcmp(table(row,col), '')
            result = 0;
        else
            try
                result = evalin('base', table{row,col});
            catch e
                msg = ['Speed Command: ' e.message];
                errordlg(msg);
                error(msg);
            end
         end
    end