function  CompileLink( ParamsStruct )
% Description: Implements the makefile to create the desired object code
%       to be used in the simulation environment.
%
%  ParamsStruct - fields description:
%  EntrySfunFile:     Name of the sfunction used in simulation (full path)
%  MexOutputFolder:   Output folder for the mex file (full path) 
%  SourceFiles:       Array of files to be compiled
%  IncludeFolders:    Array of paths of folders to be included in the compilation 
%  PreprocessorDefs:  String with the required Pre-processor Definitions
%  Coverage:          Coverage option [enable \ disable]
%  PDB:               Generation of PDB file [enable \ disable] - Required
%                     for ReadPDB functionality


SourceFiles      = [ParamsStruct.SourceFiles];
[~,sfun_name,~] = fileparts(ParamsStruct.EntrySfunFile);
% Starts the chronograph
tic

% Shows the the compilation date and time
disp('MCU motor control code compilation - started at:'); display(datestr(now));
disp(' ');
    
disp('Compiling OBJs of the MCU code...');


% Delete pdb and xml files if they exist
oldfile = [ParamsStruct.MexOutputFolder '\\' sfun_name '.mexw64.pdb'];
if (exist(oldfile, 'file') == 2)
    delete(oldfile);
end
oldfile = [ParamsStruct.MexOutputFolder '\\' sfun_name '.xml'];
if (exist(oldfile, 'file') == 2)
    delete(oldfile);
end

if (strcmp(ParamsStruct.Coverage, 'DISABLE'))
    eval(['mex ' ParamsStruct.PreprocessorDefs ' -v -g -outdir ' ParamsStruct.MexOutputFolder ' -output ' sfun_name ' ' ParamsStruct.IncludeFolders ' ' SourceFiles])
else
    eval(['slcovmex ' ParamsStruct.PreprocessorDefs ' -v -g -outdir ' ParamsStruct.MexOutputFolder ' -output ' sfun_name ' ' ParamsStruct.IncludeFolders ' ' SourceFiles])
end


disp('MEX file has been created succesfully! '); disp(' ');disp(' ');
toc; disp(' ');disp(' ');


if strcmp(ParamsStruct.PDB, 'ENABLE')
    %Parse global variables' data into an xml file
    eval(['!tools\Dia2Dump.exe -g -t ' pwd '\' ParamsStruct.MexOutputFolder '\' sfun_name '.mexw64.pdb >exe\' sfun_name '.xml']);
    eval(['xml_workaround(' '''' ParamsStruct.MexOutputFolder '\' sfun_name '.xml'')']);
end