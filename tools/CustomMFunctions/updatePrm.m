function updatePrm(value, name)
% Updates value in simple variable and struct up to x.y.z format

structNames = strsplit(name, '.');
structName = structNames{1};    
S = evalin('base', structName);

if length(structNames)>1
    S_original = evalin('base', structName);
    
    for ii = 2:length(structNames)-1
        S = S.(structNames{ii});
    end
    S.(structNames{end}) = value;
    if length(structNames)>2
        S = subsasgn(S_original, struct('type', '.', 'subs', structNames{end-1}), S);
    end
else
    % String is not in the format structName.fieldName
    S = value;
end

assignin('base', structName, S);

end

