function varargout = SpeedCommandView(varargin)
% SPEEDCOMMANDVIEW MATLAB code for SpeedCommandView.fig
%      SPEEDCOMMANDVIEW, by itself, creates a new SPEEDCOMMANDVIEW or raises the existing
%      singleton*.
%
%      H = SPEEDCOMMANDVIEW returns the handle to a new SPEEDCOMMANDVIEW or the handle to
%      the existing singleton*.
%
%      SPEEDCOMMANDVIEW('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in SPEEDCOMMANDVIEW.M with the given input arguments.
%
%      SPEEDCOMMANDVIEW('Property','Value',...) creates a new SPEEDCOMMANDVIEW or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before SpeedCommandView_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to SpeedCommandView_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help SpeedCommandView

% Last Modified by GUIDE v2.5 01-May-2017 13:16:13

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @SpeedCommandView_OpeningFcn, ...
                   'gui_OutputFcn',  @SpeedCommandView_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before SpeedCommandView is made visible.
function SpeedCommandView_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to SpeedCommandView (see VARARGIN)

% Choose default command line output for SpeedCommandView
handles.output = hObject;
if isempty(get_param(gcb,'UserData'))
    set_param(gcb, 'UserDataPersistent','on');
    handles.ud.table_pts = [];
    handles.ud.table = get(handles.uitable1,'Data');
    set_param(gcb, 'UserData', handles.ud);
else
    saved_data = get_param(gcb, 'UserData');
    handles.ud.table_pts = saved_data.table_pts;
    set(handles.uitable1,'Data',saved_data.table);
    table2plot = handles.ud.table_pts;
    plot(handles.axes1, table2plot(:,2), table2plot(:,1));
end
% Update handles structure
guidata(hObject, handles);

% UIWAIT makes SpeedCommandView wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = SpeedCommandView_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% Get default command line output from handles structure
varargout{1} = handles.output;



function edit1_Callback(hObject, eventdata, handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% Hints: get(hObject,'String') returns contents of edit1 as text
%        str2double(get(hObject,'String')) returns contents of edit1 as a double


% --- Executes during object creation, after setting all properties.
function edit1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbutton1.
function pushbutton1_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
handles.ud.table = get(handles.uitable1,'Data');
set_param(gcb, 'UserData', handles.ud);
guidata(hObject, handles);
close(ancestor(hObject,'figure'));



% --- Executes on button press in pushbutton2.
function pushbutton2_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
close(ancestor(hObject,'figure'));


% --- Executes on button press in pushbutton3.
function pushbutton3_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.pushbutton2, 'Enable', 'off');
handles.ud.table = get(handles.uitable1,'Data');
set_param(gcb, 'UserData', handles.ud);
set(handles.pushbutton5, 'Enable', 'on');
guidata(hObject, handles);



% --------------------------------------------------------------------
function uipushtool2_ClickedCallback(hObject, eventdata, handles)
% hObject    handle to uipushtool2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes when entered data in editable cell(s) in uitable1.
function uitable1_CellEditCallback(hObject, eventdata, handles)
% hObject    handle to uitable1 (see GCBO)
% eventdata  structure with the following fields (see MATLAB.UI.CONTROL.TABLE)
%	Indices: row and column indices of the cell(s) edited
%	PreviousData: previous data for the cell(s) edited
%	EditData: string(s) entered by the user
%	NewData: EditData or its converted form set on the Data property. Empty if Data was not changed
%	Error: error string when failed to convert EditData to appropriate value for Data
% handles    structure with handles and user data (see GUIDATA)
table = get(handles.uitable1,'Data');
[t_pts, m_cmds] = GenPlotCmds(table);
assignin('base', 't_plot', t_pts);
assignin('base', 'm_cmds', m_cmds);

if (~isempty(t_pts))
    plot(handles.axes1, t_pts(:,2), t_pts(:,1));
end
handles.ud.table_pts = t_pts;
assignin('base', 'steps', m_cmds);
set(handles.pushbutton2, 'Enable', 'on');
set(handles.pushbutton3, 'Enable', 'on');
set(handles.pushbutton5, 'Enable', 'off');
guidata(hObject, handles);


% --- Executes on button press in pushbutton4.
function pushbutton4_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
filter_spec = '*.mat';
dlg_title = 'Load speed profile';
[file, path] = uigetfile(filter_spec, dlg_title);
if (file ~= 0)
    full_path = fullfile(path, file);
    evalin('base', ['load(''' full_path ''')']);
    load_flag = evalin('base', 'exist(''temp_struct'',''var'') == 1');
    if (load_flag)
        temp_struct = evalin('base', 'temp_struct');
        handles.ud.table_pts = temp_struct.table_pts;
        set(handles.uitable1,'Data',temp_struct.table);
        table2plot = handles.ud.table_pts;
        plot(handles.axes1, table2plot(:,2), table2plot(:,1));
        evalin('base', 'clear temp_struct');
        set(handles.pushbutton5, 'Enable', 'off');
    else
        errordlg('Could not load file.');
    end
end
guidata(hObject, handles);


% --- Executes on button press in pushbutton5.
function pushbutton5_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
assignin('base', 'temp_struct', get_param(gcb, 'UserData'));
filter_spec = '*.mat';
dlg_title = 'Save speed profile';
[file, path] = uiputfile(filter_spec, dlg_title);
if (file ~= 0)
    full_path = char(fullfile(path, file));
    evalin('base', ['save(''' full_path ''', ''temp_struct'')']);
    evalin('base', 'clear temp_struct');
else
    errordlg('Could not save file.');
end
guidata(hObject, handles);
