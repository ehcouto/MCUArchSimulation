function  Compile_Link_MCI( CompileStruct )
% Description: Implements the makefile to create the whole MCI+SR Code
%       compilation used by the simulation. The purpose of this simulation
%       is to embedded the production target code into the
%       Matlab\Simulation enviroment.
%--------------------------------------------------------------------------
% Author:      Alessio Beato/Chinmay Kirtane/Luigi Fagnano/Marcelo Campos Silva
% Date:        September 07th, 2017
%--------------------------------------------------------------------------

% Version adjusted for Single Phase Motor Simulation Architecture
%--------------------------------------------------------------------------
% Author:      Szymon Bednarz/
% Date:        November, 2020
%--------------------------------------------------------------------------

clear mex;
clc;

%Fetch Current Directory Path
current_path=pwd;

%Extract Structure Parameters
%%Root_Path=CompileStruct.Root_Path;

Root_Path = evalin('base','Root_Path');

%mex_obj_folder = 'mcu_temp_obj';  
mex_target_file = 'sfun_motor_control';

% Starts the chronograph
tic

% Shows the the compilation date and time
display('MCI motor control code compilation - started at:'); display(datestr(now));
display(' ');

Ipath = [['-I', current_path, 'source\C_code\ '], ...
        ['-I', current_path, '\tools\MciAPI\ '], ...
        ['-I', Root_Path,'\Category\Hbl\all\'],...
        ['-I', Root_Path,'\ProjectSpecific\Hbl\all\Config\'],... 
        ['-I', Root_Path,'\ProjectSpecific\Application\all\'],... 
    ['-I', Root_Path,'\ '],   ...
    ];

[status, list] = dos([ 'dir '  current_path '\source\C_code\ /s /b /ad  ']);
if((status==0)&&(not(isempty(list))))
    result = textscan( list, '%s', 'delimiter', '\n' );
    fileList = result{1};
    for i=1:1:length(fileList)
        Ipath = [Ipath '-I' char(fileList(i)) '\ '];
    end
end

[status, list] = dos([ 'dir '  Root_Path '\ProjectSpecific\Hbl\all\Config\ /s /b /ad  ']);
if((status==0)&&(not(isempty(list))))
    result = textscan( list, '%s', 'delimiter', '\n' );
    fileList = result{1};
    for i=1:1:length(fileList)
        Ipath = [Ipath '-I' char(fileList(i)) '\ '];
    end
end

[status, list] = dos([ 'dir '  Root_Path '\ProjectSpecific\Application\all\ /s /b /ad  ']);
if((status==0)&&(not(isempty(list))))
    result = textscan( list, '%s', 'delimiter', '\n' );
    fileList = result{1};
    for i=1:1:length(fileList)
        Ipath = [Ipath '-I' char(fileList(i)) '\ '];
    end
end

[status, list] = dos([ 'dir '  Root_Path '\Category\Hbl\all\ /s /b /ad  ']);
if((status==0)&&(not(isempty(list))))
    result = textscan( list, '%s', 'delimiter', '\n' );
    fileList = result{1};
    for i=1:1:length(fileList)
        Ipath = [Ipath '-I' char(fileList(i)) '\ '];
    end
end


% ------------------- Populating Cpath -----------------------------------

Source_Path = [current_path '\source\C_code'];
Cpath = [current_path '\source\C_code\SIL_Sfunction\' mex_target_file '.c'];
[status, list] = dos([ 'dir '  Source_Path '\*.c /s /b ']);
if((status==0)&&(not(isempty(list))))
	result = textscan( list, '%s', 'delimiter', '\n' );
	fileList = result{1};
	for i=1:1:length(fileList)
    	Cpath = [Cpath ' ' char(fileList(i))];  
	end
end

Source_Path = [Root_Path,'\Category\Hbl\all\Mci'];
[status, list] = dos([ 'dir '  Source_Path '\*.c /s /b ']);
if((status==0)&&(not(isempty(list))))
    result = textscan( list, '%s', 'delimiter', '\n' );
    fileList = result{1};
    for i=1:1:length(fileList)
        Cpath = [Cpath ' ' char(fileList(i))];
    end
end

Source_Path = [Root_Path,'\ProjectSpecific\Application\all\MCUDebug'];
[status, list] = dos([ 'dir '  Source_Path '\*.c /s /b ']);
if((status==0)&&(not(isempty(list))))
    result = textscan( list, '%s', 'delimiter', '\n' );
    fileList = result{1};
    for i=1:1:length(fileList)
        Cpath = [Cpath ' ' char(fileList(i))];
    end
end

[status, list] = dos([ 'dir '  Root_Path '\ProjectSpecific\Hbl\all\Config\Mci /s /b /ad  ']);
if((status==0)&&(not(isempty(list))))
    result = textscan( list, '%s', 'delimiter', '\n' );
    fileList = result{1};
    for i=1:1:length(fileList)
        Ipath = [Ipath '-I' char(fileList(i)) '\ '];
    end
end


%--------------------------- Ready to compile ------------------


% defines for scheduler mock-up
%Ts=evalin('base','TimeSteps.ModelStep');
Ts = evalin('base','Ts_SIM');
Scheduler_Sim_Psc = num2str(fix(250/(Ts*1e6))-1);
% check if we need an extra dummy interrupt slot (10KHz)
SCHEDULER_DEF = ['-DSCHEDULER_SIM_PRESCALER=', Scheduler_Sim_Psc, ' ']; 
if (Ts == 1e-4)
    SCHEDULER_DEF = [SCHEDULER_DEF, '-DSIM_DUMMY_TASK= '];
end
    INIT_DEF = [''];

%eval(['mex -DCOMPILE_4_SIMULINK=1 -DSIM_MODE=1 -DMICRO_H= -DSRMICRO_H= ' SCHEDULER_DEF INIT_DEF PARAMETERS_DEF ' -DFAR= -v -g -c -outdir ' mex_obj_folder ' ' Ipath ' ' Cpath])
sfun_output = 'exe';
if (exist('exe\sfun_motor_control.mexw64.pdb', 'file') == 2)
    delete('exe\sfun_motor_control.mexw64.pdb');
end
if (exist('exe\sfun_motor_control.xml', 'file') == 2)
    delete('exe\sfun_motor_control.xml');
end
eval(['mex -DCOMPILE_4_SIMULINK=1 -DSIM_MODE=1 -DMICRO_H= -DSRMICRO_H= ' SCHEDULER_DEF INIT_DEF  ' -DFAR= -v -g -outdir ' sfun_output ' ' Ipath ' ' Cpath])
    
% Dummy space in the workspace.
% display(' ');display(' ');
% Object_Path=[current_path,'\' mex_obj_folder];
 
% display('Linking all obj into the MEX file...'); display(' ');
%  %Create a list of object files to be linked
%  Opath = [];
%  [status, list]=dos([ 'dir ' Object_Path '\*.obj /s /b  | findstr /v "' mex_target_file]);
% result = textscan( list, '%s', 'delimiter', '\n' );
% fileList = result{1};
% for i=1:1:length(fileList)
%         Opath = [Opath ' ' char(fileList(i))];  
% end

% eval(['mex -DCOMPILE_4_SIMULINK=1 -g ' mex_obj_folder '\' mex_target_file '.obj ' Opath])


display('Embedded MEX file is created succesfully! '); display(' ');display(' ');
toc; display(' ');display(' ');

%Parse global variables' data into an xml file
eval(['!tools\Dia2Dump.exe -g -t ' pwd '\exe\sfun_motor_control.mexw64.pdb >exe\sfun_motor_control.xml'])
%eval(['!tools\Dia2Dump.exe -g -t ' pwd '\exe\sfun_Extraction.mexw64.pdb >exe\GlobalVariables.xml'])


%% FIX issue with VS2017
%option 1 - VK
%Fix anonymous-tag in xml
% fid = fopen('exe\sfun_motor_control.xml','r+') ;
% f = fread(fid) ;
% fclose(fid) ;
% delete('exe\sfun_motor_control.xml');
% f = strrep(f,'<anonymous-tag>','anonymous-tag') ;
% fid = fopen('exe\sfun_motor_control.xml','wt') ;
% fwrite(fid,f) ;
% fclose(fid) ;

% option 2 - TS
fid = fopen('exe\sfun_motor_control.xml','r');
f = fread(fid);
fclose(fid);
f = strrep(f,'<anonymous-tag>', 'anonymous-tag');
fid = fopen(which('sfun_motor_control.xml'),'w');
fprintf(fid,'%s',f);
fclose(fid);



