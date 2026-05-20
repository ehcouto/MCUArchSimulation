[file,path] = uigetfile({'*.xls;*.xlsx', 'Excel Files (*.xls,*.xlsx)'});
if isequal(file,0)
   disp('User selected Cancel');
   return;
else
   disp(['User selected ', fullfile(path,file)]);
end

sheets = Get_xlsfinfo(fullfile(path,file));
disp('Found ' + string(length(sheets)) + ' sheet(s)');

% Prepare the name for ".mat" file
[~, Matname,  ~] = fileparts(file);
Matname = strcat(Matname,".mat");

% Check if there's already been created the same file before
check = 0;
while isfile(fullfile(path,Matname)) 
    if (check < 1)
        % File exists.
        disp("File already exists." + newline + "Deleting the file.");
        delete(fullfile(path,Matname));
        check =+ 1;
    else
        disp('Cannot delete the file, please do it manually and rerun the script.');
        return;
    end
end

disp('Creating a new MAT file.');

% Create ".mat" file for test cases
TCmatfile = matfile(fullfile(path,Matname),'Writable',true);

fprintf('Converting sheets into test scenarios: ');

for v = 1:length(sheets)
    % Display current queue and check the amount of signs to overwrite in next
    % iteration
    CharNum = fprintf('%d/%d',v,length(sheets));

    % Read a tab from the file
    T1 = readtable(fullfile(path,file),"Sheet",v,'PreserveVariableNames',true);
    % Copy columns' names of variables
    Header = T1.Properties.VariableNames;
    % Change the data into array
    MyExcel = table2array(T1);
    % Delete rows with 'NaN'
    MyExcel = MyExcel(~any(ismissing(MyExcel),2),:);
    % Check the size of the array
    [NoOfRows,NoOfCols] = size(MyExcel);
    
    % Create dataset for test cases
    TestCase = Simulink.SimulationData.Dataset();
    % Fill the dataset with the data from test case
    for c = 2:NoOfCols
        TestCase = addElement(TestCase, timeseries(MyExcel(:,c),MyExcel(:,1)), string(Header(c)));
    end
    % Assign the sheet's name to the database
    TCName = sheets{v};
    ds.(TCName) = TestCase;
    % Save the dataset under the name of Excel tab the test case was taken
    % from
    %save(fullfile(path,Matname),'-struct','ds',TestName,'-append')
    TCmatfile.(TCName) = ds.(TCName);
    
    if v == length(sheets)
        % Go to a new line after completing the process
        fprintf('\n'); 
        disp('Mat File Created: ' + Matname);
    else
        % Erase the displayed counter for next iteration
        fprintf(repmat('\b', 1, CharNum));
    end
end

function [Sheets_Names] = Get_xlsfinfo(file_name)
%%********************************************************************************
%   Name          : Get_xlsfinfo

%*********************************************************************************
% Open the Excel file (*.xls or *.xlsx).
Excel = actxserver('Excel.Application');
Excel.Workbooks.Open(file_name);
% Finding the Sheets.
workSheets = Excel.sheets;
for i = 1:workSheets.Count
    sheet = get(workSheets,'item',i);
    Sheets_Names{i} = sheet.Name;
end
Excel.DisplayAlerts = 0;
% Close Excel Sheet
Excel.ActiveWorkbook.Close;
% quit Excel Object
Excel.Quit;
Excel.delete;
end