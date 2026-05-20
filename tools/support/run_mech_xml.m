function run_mech_xml(filename)
c=xmlread(filename);

s={ 'belt_ratio'...
    'JDrum'...
    'damp'...
    'm_unb'...
    'r_unb'...
    'M_D'...
    'M'...
    'R_Drum'...
    'R_J'...
    'CF'};

s1={'MechanicalVariant'};

z={'0'};
[a b]=size(s);
[a1 b1]=size(s1);
evalin('base','Mechanical=struct;');
entries =c.getChildNodes;
friendlyInfo = entries.item(0).getChildNodes;
node = friendlyInfo.getFirstChild;
for i=1:1:b
    m(i)=s(i);
    friendlyInfo = entries.item(0).getChildNodes;
    node = friendlyInfo.getFirstChild;
    while ~isempty(node)
        if strcmpi(node.getNodeName, s(i))
            break;
        else
            node = node.getNextSibling;
        end
    end
     h(i)= str2double(char(node.getTextContent));
    assignin('base','temp',h(i));
    m(i)= node.getNodeName;
    assignin('base','temp_string',m(i));
    evalin('base','Mechanical.(char(temp_string))=temp;');
    
end
evalin('base','clear temp');
evalin('base','clear temp_string');
%% Loading Mechanical Variant Information
for i=1:1:b1
    m(i)=s1(i);
    friendlyInfo = entries.item(0).getChildNodes;
    node = friendlyInfo.getFirstChild;
    while ~isempty(node)
        if strcmpi(node.getNodeName, s1(i))
            break;
        else
            node = node.getNextSibling;
        end
    end
    z(i)= node.getTextContent;
    assignin('base','temp',char(z(i)));
    m(i)= node.getNodeName;
    assignin('base','temp_string',m(i));
    evalin('base','config.(char(temp_string))=temp;');
    
end
evalin('base','clear temp');
evalin('base','clear temp_string');

end