function WinMsgs_out = generic_msgs_generator(WinMsgs_struct)
    [file,path] = uigetfile({'*.*'});
    if isequal(file,0)
       disp('User selected Cancel');
       WinMsgs_out = WinMsgs_struct;
       return;
    else
       disp(['User selected ', fullfile(path,file)]);
    end

    fileName = [path file];
    opts = detectImportOptions(fileName);
	opts.VariableTypes{6} = 'char';
    table = readtable(fileName,opts);
    
    PayloadMaxLength = 100 - 5; % Source Destination API Opcode CRC
    crc_dummy = 255;
    cmd_fb = 0;
    frag = 0;
    mmp = 0;

    sap = uint8(4 * ones(height(table),1));
    
    % create the header of the packet
    destination_source = uint8(table.('Dest') + table.('Source') .* (2^4));
    api = uint8(table.('API'));
    opcode_compl = uint8(table.('Opcode') + cmd_fb * (2^5) + frag * (2^6) + mmp * (2^7));
    
    
    % access all payloads
    payloads = table.('Payload');

    % Initialize a matrix to store the results
    payloadMatrix = zeros(length(payloads), PayloadMaxLength, 'uint8');
    
    sdu_length = zeros(length(payloads),1,'uint8');


    % Iterate over each Payload element
    for i = 1:length(payloads)
        % Split the string into parts
        bytes = str2double(strsplit(payloads{i}, '.'));
        
        % Fill the result matrix with the values, pad with zeros if necessary
        payloadMatrix(i, 1:length(bytes)+1) = uint8([bytes, crc_dummy]);
        sdu_length(i)=length(bytes)+2;
    end
    header = [destination_source sap sdu_length api opcode_compl];

    msgs.packets = [header, payloadMatrix];
    % adding zero time and create time series
    ts = timeseries([0:height(payloads)]', [0 ; table.("Time")]);
    ts = setinterpmethod(ts,'zoh');
    msgs.time = ts;    

    % create a variable in the workspace and assign to msgs
    % variable name is the same of the file
    [~, var,  ~] = fileparts(fileName);

    WinMsgs_struct.(var) = msgs;
    WinMsgs_out = WinMsgs_struct;

end




