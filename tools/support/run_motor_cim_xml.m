function run_motor_cim_xml(filename)
c=xmlread(filename);
%--- Electrical Parameter---%
s1={ 'Rs'...
    'Rr'...
    'Ls'...
    'Lr'...
    'Lm'...
    'p'...
    'alpha_s'...
    'Conn'...
    'alpha_r'};
%---Mechanical Parameters---%
s2={ 'TsRef'...
    'TrRef'...
    'Jrotor'...
    'Jadd'...
    'TR'};
%---Power Loss Parameters----%
s3={'f_offset_rotlosses'...
    'f_rot_losses'...
    'Time_to_Turn_ON_Rot_Losses'};

%---Motor Variant Details----%
s4={'MotorVariant'};

[a1 b1]=size(s1);
[a2 b2]=size(s2);
[a3 b3]=size(s3);
[a4 b4]=size(s4);
z={'0'};
evalin('base','Motor=struct;');
entries =c.getChildNodes;
friendlyInfo = entries.item(0).getChildNodes;
node = friendlyInfo.getFirstChild;

%% Loading Electrical Parameter Structure
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
  h(i)= str2double(char(node.getTextContent));
    assignin('base','temp',h(i));
    m(i)= node.getNodeName;
    assignin('base','temp_string',m(i));
    evalin('base','Motor.Electrical.(char(temp_string))=temp;');
    
end
evalin('base','clear temp');
evalin('base','clear temp_string');
%% Loading Mechanical Parameter Structure
for i=1:1:b2
    m(i)=s2(i);
    friendlyInfo = entries.item(0).getChildNodes;
    node = friendlyInfo.getFirstChild;
    while ~isempty(node)
        if strcmpi(node.getNodeName, s2(i))
            break;
        else
            node = node.getNextSibling;
        end
    end
  h(i)= str2double(char(node.getTextContent));
    assignin('base','temp',h(i));
    m(i)= node.getNodeName;
    assignin('base','temp_string',m(i));
    evalin('base','Motor.Mechanical.(char(temp_string))=temp;');
    
end
evalin('base','clear temp');
evalin('base','clear temp_string');
%% Loading Power Loss Parameter Structure
for i=1:1:b3
    m(i)=s3(i);
    friendlyInfo = entries.item(0).getChildNodes;
    node = friendlyInfo.getFirstChild;
    while ~isempty(node)
        if strcmpi(node.getNodeName, s3(i))
            break;
        else
            node = node.getNextSibling;
        end
    end
  h(i)= str2double(char(node.getTextContent));
    assignin('base','temp',h(i));
    m(i)= node.getNodeName;
    assignin('base','temp_string',m(i));
    evalin('base','Motor.Power_Loss.(char(temp_string))=temp;');
    
end
evalin('base','clear temp');
evalin('base','clear temp_string');
%% Loading Motor Variant Information
for i=1:1:b4
    m(i)=s4(i);
    friendlyInfo = entries.item(0).getChildNodes;
    node = friendlyInfo.getFirstChild;
    while ~isempty(node)
        if strcmpi(node.getNodeName, s4(i))
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

