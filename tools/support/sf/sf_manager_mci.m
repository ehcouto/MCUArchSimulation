% checking if Python SF Utilities are available
if (isfield(Paths,'Python_SF_Utilities'))
    % need to temporary change directory to python module path
    restore_dir = pwd;

    temp_dir = [restore_dir '\temp_SF'];

    path_SF_utils = [restore_dir Paths.Python_SF_Utilities(2:end)];

    % prepare arguments for python script
    sf_bin = [Paths.Setting_File_Path];
    sf_csv = [temp_dir '\temp_sf.csv'];
    sf_type= 'UNIFIED';
    sf_bin_new = [temp_dir '\temp_sf.bin'];

    % checking if it is the first time execution: no table, no temp_sf folder
    if exist('Motor_Control_Parameters','var')
        % table exists
        cd(temp_dir)

        % check if the table original sf is matching with the one used in
        % simulation
        if (strcmp(table_sf_bin,Paths.Setting_File_Path))
            %copy the existing csv
            cp_csv = [temp_dir '\temp_sf_copy.csv'];
            copyfile(sf_csv, cp_csv);
            
            % generate csv from the table
            writetable(Motor_Control_Parameters,sf_csv);
    
            % check if the table has been modified (comparing with the previous
            % csv file
            if not(system(['fc  ', 'temp_sf_copy.csv', ' ', 'temp_sf.csv']))
                % file compare returning 0, the table is not modified remove copy file
                delete(cp_csv);
                clear("cp_csv");
            else
                cd(restore_dir);
                cd(path_SF_utils);
                warning("parameters table has been modified");
                warning("generating new setting file");
                % the table is different
                % generate the new setting file based on new table
                func = 'generate_bin';
                % sf file absolute path
                args = ['''' func ''' ''' sf_bin ''' ''' sf_csv ''' ''' sf_type ''' ''' sf_bin_new];
                pyrunfile(['matlab_sf_mgr.py '  args '''']);
    
                % update setting file location
                Paths.Setting_File_Path = [temp_dir '\temp_sf.bin'];
                sf_bin = [Paths.Setting_File_Path];
                % regenerate the csv and the table from the setting file
                func = 'generate_table';
                args = ['''' func ''' ''' sf_bin ''' ''' sf_csv ''' ''' sf_type]
                pyrunfile(['matlab_sf_mgr.py '  args '''']);
                % create the matlab table from the csv file
                % Open the file and read the data as a table, specifying data types for each column
                opts = detectImportOptions(sf_csv);
                opts.VariableTypes = {'string', 'string', 'string', 'string', 'string'};
                Motor_Control_Parameters = readtable(sf_csv, opts);
                try
                    Motorparams = update_motorparam_struct(Motor_Control_Parameters);
                catch ME
                     warning('Problem using function update_motorparam_struct.  Not found in main_model.');
                end
                
            end
        else
            cd(path_SF_utils);
            warning("parameters table is not matching with setting file");
            warning("generating new table");
            func = 'generate_table';
            args = ['''' func ''' ''' sf_bin ''' ''' sf_csv ''' ''' sf_type];
            pyrunfile(['matlab_sf_mgr.py '  args '''']);

            % create the matlab table from the csv file
            % Open the file and read the data as a table, specifying data types for each column
            opts = detectImportOptions(sf_csv);
            opts.VariableTypes = {'string', 'string', 'string', 'string', 'string'};
            Motor_Control_Parameters = readtable(sf_csv, opts);
            try
                Motorparams = update_motorparam_struct(Motor_Control_Parameters);
            catch ME
                warning('Problem using function update_motorparam_struct.  Not found in main_model.');
            end
        end
    else
        cd(path_SF_utils);
        warning("first execution: creating parameters table")
        % no table --> 
        % create a temporary folder in main_model directory
        mkdir(temp_dir);
        
        % generate the csv from the current setting file
        func = 'generate_table';
        args = ['''' func ''' ''' sf_bin ''' ''' sf_csv ''' ''' sf_type];
        pyrunfile(['matlab_sf_mgr.py '  args '''']);

        % create the matlab table from the csv file
        % Open the file and read the data as a table, specifying data types for each column
        opts = detectImportOptions(sf_csv);
        opts.VariableTypes = {'string', 'string', 'string', 'string', 'string'};
        Motor_Control_Parameters = readtable(sf_csv, opts);
        try
            Motorparams = update_motorparam_struct(Motor_Control_Parameters);
        catch ME
            warning('Problem using function update_motorparam_struct.  Not found in main_model.');
        end
    end

    % store the path of the sf bin
    table_sf_bin = Paths.Setting_File_Path;
      
    cd(restore_dir);
else
    warning('Setting File python utilities are not available');
end

clear("args");
clear("func");

clear("restore_dir");
clear('temp_dir');
clear("path_SF_utils");

clear('sf_bin','sf_csv','sf_type','sf_bin_new');


