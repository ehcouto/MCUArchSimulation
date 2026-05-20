clear mex

current_path = pwd;
Ipath = [['-I', current_path, '\source\c_code\Mocks\MCDriver\ '],               ...
    ['-I', current_path, '\source\c_code\Mocks\Micro\ '],               ...
    ['-I', current_path, '\tools\MciAPI\ '],               ...
    ['-I', Root_Path,'\XCategory\Hbl\Mci\ '],   ...
    ['-I', Root_Path,'\XCategory\Driver\API\Micro\ '],   ...
    ['-I', Root_Path,'\ProjectSpecific\Mci\ '],   ...
    ['-I', Root_Path,'\ProjectSpecific\Mci\Mcl\ '],   ...
    ['-I', Root_Path,'\ProjectSpecific\Driver\ ']   ... 
    
    ];


[status, list] = dos([ 'dir '  current_path '\source\c_code\Mocks\MCDriver\ /s /b /ad  ']);
if ~strcmp(list ,'')
    result = textscan( list, '%s', 'delimiter', '\n' );
    fileList = result{1};
    for i=1:1:length(fileList)
        Ipath = [Ipath '-I' char(fileList(i)) '\ '];
    end
end

[status, list] = dos([ 'dir '  current_path '\source\c_code\Mocks\Micro\ /s /b /ad  ']);
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

Cpath = [current_path '\tools\MciAPI\source\mci_run.c '];

eval(['mex -DCOMPILE_4_SIMULINK=1  -outdir ' [current_path '\tools\MciAPI\exe'] ' ' Ipath ' ' Cpath])

%     -I..\..\..\source\XCategory\Hbl\Mci\...
%     -I..\..\..\source\ProjectSpecific\Mci\...
%     -I..\..\..\source\XCategory\Driver\API\Micro\...
%     -I..\..\Mock_MCI...
%     -I..\..\..\source\ProjectSpecific\Driver\Micro...
%     -I..\..\..\source\ProjectSpecific\Mci\Mcl...
%     -I..\..\..\source\XCategory\Hbl\Mci\Mcl\MicroBlocks...
%     -I..\..\..\source\XCategory\Hbl\Mci\Mcl...
%     -I..\..\..\source\Category\Common\BoardDebugging