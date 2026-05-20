function CompilationParamsStruct = CompilationSetup( ParamsStruct )
% Description: Setup for the compilation project
%       to be used in the simulation environment.
%
%  CompilationParamsStruct - fields description:
%  SourceFiles:       Array of files to be compiled
%  IncludeFolders:    Array of paths of folders to be included in the compilation 
%
%  ParamsStruct  - fields description:
%  RootPath:          Path of the Root Source folder
%  MockPath:          Path of the Folder with Mockups
%  AdditionalIncl:    Path for additional include folders
%  ExcludeModuleList: Modules to be excluded from compilation (from the
%                     root) 
%  IncludeModuleList: Modules to be included from compilation (from the
%                     root)
%  BaseDir:           Path to the base directory. If provided, all paths
%  will be relative to this directory, otherwise, absolute paths are
%  generated
%  CCallerFormat:     If true, will provide paths compatible with CCaller
%  Only 1 among Exclude \ Include Module list shall be provided

%Extract Structure Parameters
RootPath            = ParamsStruct.RootPath;
MockPath            = ParamsStruct.MockPath;
if isfield(ParamsStruct,'BaseDir')
    RelativePaths   = true;
    BaseDir         = ParamsStruct.BaseDir;
else
    RelativePaths   = false;
end
if isfield(ParamsStruct,'ExcludeModuleList')
    ModuleList   = ParamsStruct.ExcludeModuleList;
    ModuleListType   = 'EXCLUDE';
else
    ModuleList   = ParamsStruct.IncludeModuleList;
    ModuleListType   = 'INCLUDE';
end
if isfield(ParamsStruct,'CCallerFormat')
    CCallerFormat = ParamsStruct.CCallerFormat;
else
    CCallerFormat = false;
end

AdditionalIncl      = ParamsStruct.AdditionalIncl;

% Creating the array of source files
[status, list_source_mocks] = dos([ 'dir '  MockPath '\*.c /s /b ']);
Cpath = regexprep(list_source_mocks, '\s+', ' ');


[status, list_source] = dos([ 'dir '  RootPath '\*.c /s /b ']);
% processing is needed in order to exclude the undesired modules 
source_cell = strsplit(list_source, '\n');
% removing the last element
source_cell(end) = [];

% removing\adding the modules to be excluded\including
for i=1:1:length(source_cell) 
    tmp = regexp(char(source_cell(i)),'\','split');
    % removing ".c" from the last element
    tmp{end} = tmp{end}(1:length(tmp{end})-2);
    
    if (strcmp(ModuleListType,'EXCLUDE')) 
        if (not(ismember(tmp,ModuleList)))
            Cpath = [Cpath ' ' char(source_cell(i))];  
        end
    else
        if (sum(ismember(tmp,ModuleList)))
            Cpath = [Cpath ' ' char(source_cell(i))];  
        end
    end
end

% generate relative paths if needed
if RelativePaths
    cpath_cell = strsplit(Cpath);
    for i=1:1:length(cpath_cell)
        el = char(cpath_cell(i));
        cpath_cell(i) = cellstr(relativepath(el, BaseDir));
    end
    Cpath = [strjoin(cpath_cell, '\n')];
end

% creating the array of include folders - Mock Path
[status, list_include] = dos([ 'dir '  MockPath '\*.h /s /b ']);
% processing is needed in order to exclude the undesired modules 
include_cell = strsplit(list_include, '\n');
% removing the last element
include_cell(end) = [];

incl_cell_norep = {};
for i=1:1:length(include_cell)
    tmp = char(include_cell(i));
    tmp = tmp(1:find(tmp == '\', 1, 'last'));
    if RelativePaths
        tmp = relativepath(tmp, BaseDir);
    end
    if not(ismember(tmp, incl_cell_norep))   %skip duplication
        incl_cell_norep(end+1) = {tmp};
    end
end


% creating the array of include folders - source
[status, list_include] = dos([ 'dir '  RootPath '\*.h /s /b ']);
% processing is needed in order to exclude the undesired modules 
include_cell = strsplit(list_include, '\n');
% removing the last element
include_cell(end) = [];

for i=1:1:length(include_cell)
    tmp = char(include_cell(i));
    tmp = tmp(1:find(tmp == '\', 1, 'last'));
    if RelativePaths
        tmp = relativepath(tmp, BaseDir);
    end
    if not(ismember(tmp, incl_cell_norep))   %skip duplication
        incl_cell_norep(end+1) = {tmp};
    end
end

if CCallerFormat
    Ipath = [strjoin(incl_cell_norep, '\n')];
else
    Ipath = ['-I' strjoin(incl_cell_norep, ' -I')];
end

% adding additional include paths
if CCallerFormat
    for i=1:1:length(AdditionalIncl)
        Ipath = [Ipath newline char(AdditionalIncl(i))];
    end
else
    for i=1:1:length(AdditionalIncl)
        if not(isempty(AdditionalIncl{i}))
            Ipath = [Ipath ' -I' char(AdditionalIncl(i)) ' '];
        end
    end
end

CompilationParamsStruct.SourceFiles     = Cpath;
CompilationParamsStruct.IncludeFolders  = Ipath;


return;
