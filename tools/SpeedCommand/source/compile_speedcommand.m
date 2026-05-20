function compile_speedcommand(Root_Path)

clear mex

current_path = pwd;
Ipath = [['-I', current_path, '\tools\MciAPI\ '],               ...
    ['-I', current_path, '\source\c_code\Mocks\ '],              ...
    ['-I', Root_Path,'\XCategory\Hbl\Mci\ '],              ...
    ['-I', Root_Path,'\XCategory\Driver\API\Micro\ '],              ...
    ['-I', Root_Path,'\ProjectSpecific\Driver\ '],              ...
    ['-I', Root_Path,'\ProjectSpecific\Mci\ ']              ...
    ];

[status, list] = dos([ 'dir '  current_path '\source\c_code\Mocks\ /s /b /ad  ']);
if ~strcmp(list ,'')
    result = textscan( list, '%s', 'delimiter', '\n' );
    fileList = result{1};
    for i=1:1:length(fileList)
        Ipath = [Ipath '-I' char(fileList(i)) '\ '];
    end
end

[status, list] = dos([ 'dir '  Root_Path '\ProjectSpecific\Mci\ /s /b /ad  ']);
if ~strcmp(list ,'')
    result = textscan( list, '%s', 'delimiter', '\n' );
    fileList = result{1};
    for i=1:1:length(fileList)
        Ipath = [Ipath '-I' char(fileList(i)) '\ '];
    end
end

[status, list] = dos([ 'dir '  Root_Path '\XCategory\Hbl\Mci\ /s /b /ad  ']);
if ~strcmp(list ,'')
    result = textscan( list, '%s', 'delimiter', '\n' );
    fileList = result{1};
    for i=1:1:length(fileList)
        Ipath = [Ipath '-I' char(fileList(i)) '\ '];
    end
end

Cpath = [current_path '\tools\SpeedCommand\source\speedcommand.c '];

eval(['mex -DCOMPILE_4_SIMULINK=1  -outdir ' [current_path '\tools\SpeedCommand\exe'] ' ' Ipath ' ' Cpath])
