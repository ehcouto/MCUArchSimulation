function run_rect_xml(filename)
c=xmlread(filename);

s={ 'R_line'...
    'L_line'...
    'C_buscap'...
    'R_diode'...
    'R_buscap'...
    'V_knee'...
    'G_off'...
    'L_pfc'...
    'R_pfc'...
    'Vr'...
    'Vdc_i'...
    'freq'...
    'C1'...
    'C2'...
    'Cvolt'...
    'Vcc'...
    'ADCBit'...
    'PGA_Gain'};
s1={'BoardVariant'};

inverter_prm={ 'Vce'...
    'Vfd'...
    'RonT'...
    'RonD'...
    'Rshunt'...
    'tdt'...
    'tau'};


z={'0'};
[a b]=size(s);
[a1 b1]=size(s1);
[a2,b2]=size(inverter_prm);
evalin('base','InputCircuit=struct;');
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
    if ~isempty(node)
        h(i)= str2double(char(node.getTextContent));
        m(i)= node.getNodeName;
    else
        if strcmp(m(i),'PGA_Gain')
            % default value is 1 - no internal PGA for ADC sensing
            h(i) = 1.0;
        end 
    end
    assignin('base','temp',h(i));
    assignin('base','temp_string',m(i));
    evalin('base','InputCircuit.(char(temp_string))=temp;');
    
end
evalin('base','clear temp');
evalin('base','clear temp_string');
%% Loading Inverter parameters
evalin('base','InverterParams=struct;');
entries =c.getChildNodes;
friendlyInfo = entries.item(0).getChildNodes;
node = friendlyInfo.getFirstChild;
for i=1:1:b2
    m(i)=inverter_prm(i);
    friendlyInfo = entries.item(0).getChildNodes;
    node = friendlyInfo.getFirstChild;
    while ~isempty(node)
        if strcmpi(node.getNodeName, inverter_prm(i))
            break;
        else
            node = node.getNextSibling;
        end
    end
    if ~isempty(node)
        h(i)= str2double(char(node.getTextContent));
        m(i)= node.getNodeName;

        assignin('base','temp',h(i));
        assignin('base','temp_string',m(i));
        evalin('base','InverterParams.(char(temp_string))=temp;');
    end
    
    
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

