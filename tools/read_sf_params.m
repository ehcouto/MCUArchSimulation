function read_sf_params(file)
    text = fileread(file);
    expr = '//([A-Za-z0-9\s\(\)\[\]\-])+\s=\s*([0-9\.eE\+\-])+';
    [parameters, matches]= regexp(text, expr, 'match', 'tokens');
    for i=1:size(parameters,2)
        char_set = ["[", "]", "(", ")", " ", "-"];
        param_name = replace(matches{i}{1}, char_set, '_');
        evalin('base', ['Mcl_prm.' param_name '=' matches{i}{2} ';']);
    end
end