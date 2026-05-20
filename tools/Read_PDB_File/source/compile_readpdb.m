current_path = pwd;
Ipath = ['-I', current_path, '\tools\MciAPI\ '];

Cpath = [pwd '\tools\Read_PDB_File\source\read_pdb_vars.c '];
LPath = [pwd '\tools\Read_PDB_File\exe'];
eval(['mex -DSIM_MODE=1 -g -outdir ' [pwd '\tools\Read_PDB_File\exe'] ' -L' LPath ' ' Ipath ' ' Cpath ' -lReadPdb']);
%eval(['mex -DSIM_MODE=1 -g -outdir ' pwd ' ' Ipath ' ' Cpath]);

%!Dia2Dump.exe -g -t C:\Data\Projects\MBCD_Transient_Simulation_Architecture\read_pdb_vars.mexw64.pdb >read_pdb_vars.xml

clear Cpath;
clear LPath;
clear Ipath;