function xml_workaround(xml_file)
    fid  = fopen(xml_file,'r');
    f=fread(fid,'*char')';
    fclose(fid);
    f = strrep(f,'<anonymous-tag>','anonymous-tag');
    f = strrep(f,'<unnamed-tag>','unnamed-tag');
    fid  = fopen(xml_file,'w');
    fprintf(fid,'%s',f);
    fclose(fid);
end