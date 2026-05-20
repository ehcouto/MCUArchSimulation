function varargout = Signal_Inspector(varargin)
% SIGNAL_INSPECTOR MATLAB code for Signal_Inspector.fig
%      SIGNAL_INSPECTOR, by itself, creates a new SIGNAL_INSPECTOR or raises the existing
%      singleton*.
%
%      H = SIGNAL_INSPECTOR returns the handle to a new SIGNAL_INSPECTOR or the handle to
%      the existing singleton*.
%
%      SIGNAL_INSPECTOR('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in SIGNAL_INSPECTOR.M with the given input arguments.
%
%      SIGNAL_INSPECTOR('Property','Value',...) creates a new SIGNAL_INSPECTOR or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before Signal_Inspector_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to Signal_Inspector_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help Signal_Inspector

% Last Modified by GUIDE v2.5 26-Apr-2018 14:47:48

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
    'gui_Singleton',  gui_Singleton, ...
    'gui_OpeningFcn', @Signal_Inspector_OpeningFcn, ...
    'gui_OutputFcn',  @Signal_Inspector_OutputFcn, ...
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


% --- Executes just before Signal_Inspector is made visible.
function Signal_Inspector_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to Signal_Inspector (see VARARGIN)

% Choose default command line output for Signal_Inspector
handles.output = hObject;

% if isempty(get_param(gcb, 'UserData'))
%     set_param(gcb, 'UserDataPersistent','on');
%     set(handles.Tshaft,'Value','Max');
% else

%--- Extraction of Previous Stored State Information ---%
saveddata = get_param(gcb, 'UserData');


%---Control Signal Checkboxes States---%

% Voltage Signals
s1=saveddata.state.Vd;
s2=saveddata.state.Vq;
s3=saveddata.state.Vs;
s4=saveddata.state.Vsfw;

% Current Signals
s5=saveddata.state.IdRef;
s6=saveddata.state.id;
s7=saveddata.state.IqRef;
s8=saveddata.state.iq;
s9=saveddata.state.Imr;

% PWM Signals
s10=saveddata.state.PWM_Duties;
s11=saveddata.state.PWM_Status;
s12=saveddata.state.Sector;

% Fault Signals
s13=saveddata.state.Fault;
s14=saveddata.state.SR_Fault;

% Mechanical Signals
s15=saveddata.state.TorqueRef;
s16=saveddata.state.Torque;
s17=saveddata.state.OmegaRotRef;
s18=saveddata.state.OmegaRotEst;
s19=saveddata.state.ErrorSpeed;
s20=saveddata.state.ThetaFluxEst;

%---- System Models Checboxes States ----%

% Input Circuit Signals
s21=saveddata.state.Vdc;

% Inverter Signals
s22=saveddata.state.Vpole;

% Motor + Mechanical Signals
s23=saveddata.state.Iabc;
s24=saveddata.state.Tshaft;
s25=saveddata.state.Motor_Input;
s26=saveddata.state.Motor_Speed;
s27=saveddata.state.Flux_Position;
s28=saveddata.state.Flux_Speed;
s29=saveddata.state.Vphase;


%---Dummy---%
% s1=0;
% s2=0;
% s3=0;
% s4=0;
% s5=0;
% s6=0;
% s7=0;
% s8=0;
% s9=0;
% s10=0;
% s11=0;
% s12=0;
% s13=0;
% s14=0;
% s15=0;
% s16=0;
% s17=0;
% s18=0;
% s19=0;
% s20=0;
% s21=0;
% s22=0;
% s23=0;
% s24=0;
% s25=0;
% s26=0;
% s27=0;
% s28=0;
% s29=0;


%-- Restore Signal Status---%

%--- Control ---%

% Voltage
set(handles.Vd,'Value',s1);
set(handles.Vq,'Value',s2);
set(handles.Vs,'Value',s3);
set(handles.Vsfw,'Value',s4);

% Current
set(handles.IdRef,'Value',s5);
set(handles.id,'Value',s6);
set(handles.IqRef,'Value',s7);
set(handles.iq,'Value',s8);
set(handles.Imr,'Value',s9);

% PWM 
set(handles.PWM_Duties,'Value',s10);
set(handles.PWM_Status,'Value',s11);
set(handles.Sector,'Value',s12);

% Fault
set(handles.Fault,'Value',s13);
set(handles.SR_Fault,'Value',s14);

% Mechanical
set(handles.TorqueRef,'Value',s15);
set(handles.Torque,'Value',s16);
set(handles.OmegaRotRef,'Value',s17);
set(handles.OmegaRotEst,'Value',s18);
set(handles.ErrorSpeed,'Value',s19);
set(handles.ThetaFluxEst,'Value',s20);

%--- System Models ---%

% Input Circuit
set(handles.Vdc,'Value',s21);

% Inverter
set(handles.Vpole,'Value',s22);

% Motor + Mechanical System
set(handles.Iabc,'Value',s23);
set(handles.Tshaft,'Value',s24);
set(handles.Motor_Input,'Value',s25);
set(handles.Motor_Speed,'Value',s26);
set(handles.Flux_Position,'Value',s27);
set(handles.Flux_Speed,'Value',s28);
set(handles.Vphase,'Value',s29);



% end

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes Signal_Inspector wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = Signal_Inspector_OutputFcn(hObject, eventdata, handles)
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in inspect.
function inspect_Callback(hObject, eventdata, handles)
% hObject    handle to inspect (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
Simulink.sdi.view;

% --- Executes on button press in id.
function id_Callback(hObject, eventdata, handles)
% hObject    handle to id (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of id
control=get_param('MCU_Simulation_Architecture/Motor Control Algorithm/WINDY CIM_BPM','PortHandles');
if (get(hObject,'Value') == get(hObject,'Max'))
    Simulink.sdi.markSignalForStreaming(control.Outport(5),'on');
    
else
    Simulink.sdi.markSignalForStreaming(control.Outport(5),'off');
end

% --- Executes on button press in Iabc.
function Iabc_Callback(hObject, eventdata, handles)
% hObject    handle to Iabc (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of Iabc
current=get_param('MCU_Simulation_Architecture/Motor Coupled With Mechanics','PortHandles');
if (get(hObject,'Value') == get(hObject,'Max'))
    Simulink.sdi.markSignalForStreaming(current.Outport(2),'on');
    
else
    Simulink.sdi.markSignalForStreaming(current.Outport(2),'off');
end


% --- Executes on button press in iq.
function iq_Callback(hObject, eventdata, handles)
% hObject    handle to iq (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of iq
control=get_param('MCU_Simulation_Architecture/Motor Control Algorithm/WINDY CIM_BPM','PortHandles');
if (get(hObject,'Value') == get(hObject,'Max'))
    Simulink.sdi.markSignalForStreaming(control.Outport(6),'on');
    
else
    Simulink.sdi.markSignalForStreaming(control.Outport(6),'off');
end

% --- Executes on button press in Tshaft.
function Tshaft_Callback(hObject, eventdata, handles)
% hObject    handle to Tshaft (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of Tshaft
torque=get_param('MCU_Simulation_Architecture/Motor Coupled With Mechanics','PortHandles');
if (get(hObject,'Value') == get(hObject,'Max'))
    Simulink.sdi.markSignalForStreaming(torque.Outport(1),'on');
    
else
    Simulink.sdi.markSignalForStreaming(torque.Outport(1),'off');
end

% --- Executes on button press in ok.
function ok_Callback(hObject, eventdata, handles)
% hObject    handle to ok (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

%---- Control Signal States -----%

%Voltage Signals CheckBoxes States
handles.state.Vd=get(handles.Vd,'Value');
handles.state.Vq=get(handles.Vq,'Value');
handles.state.Vs=get(handles.Vs,'Value');
handles.state.Vsfw=get(handles.Vsfw,'Value');

% Current Signals CheckBoxes States
handles.state.id=get(handles.id,'Value');
handles.state.iq=get(handles.iq,'Value');
handles.state.IdRef=get(handles.IdRef,'Value');
handles.state.IqRef=get(handles.IqRef,'Value');
handles.state.Imr=get(handles.Imr,'Value');

% PWM Signal CheckBoxes States
handles.state.PWM_Duties=get(handles.PWM_Duties,'Value');
handles.state.PWM_Status=get(handles.PWM_Status,'Value');
handles.state.Sector=get(handles.Sector,'Value');

% Fault Signals CheckBoxes States
handles.state.Fault=get(handles.Fault,'Value');
handles.state.SR_Fault=get(handles.SR_Fault,'Value');

% Mechanical Signals CheckBoxes States
handles.state.TorqueRef=get(handles.TorqueRef,'Value');
handles.state.Torque=get(handles.Torque,'Value');
handles.state.OmegaRotRef=get(handles.OmegaRotRef,'Value');
handles.state.OmegaRotEst=get(handles.OmegaRotEst,'Value');
handles.state.ErrorSpeed=get(handles.ErrorSpeed,'Value');
handles.state.ThetaFluxEst=get(handles.ThetaFluxEst,'Value');

%--- System Model Signal States ----%

% Input Circuit Model Signals States
handles.state.Vdc=get(handles.Vdc,'Value');

% Inverter Model Signals States
handles.state.Vpole=get(handles.Vpole,'Value');

% Motor + Mechanical Model Signals States
handles.state.Iabc=get(handles.Iabc,'Value');
handles.state.Tshaft=get(handles.Tshaft,'Value');
handles.state.Motor_Input=get(handles.Motor_Input,'Value');
handles.state.Motor_Speed=get(handles.Motor_Speed,'Value');
handles.state.Flux_Position=get(handles.Flux_Position,'Value');
handles.state.Flux_Speed=get(handles.Flux_Speed,'Value');
handles.state.Vphase=get(handles.Vphase,'Value');
guidata(hObject, handles);
set_param(gcb, 'UserData', handles);
close(ancestor(hObject,'figure'));


% --- Executes on button press in cancel.
function cancel_Callback(hObject, eventdata, handles)
% hObject    handle to cancel (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
close(ancestor(hObject,'figure'));


% --- Executes on button press in IqRef.
function IqRef_Callback(hObject, eventdata, handles)
% hObject    handle to IqRef (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of IqRef
control=get_param('MCU_Simulation_Architecture/Motor Control Algorithm/WINDY CIM_BPM','PortHandles');
if (get(hObject,'Value') == get(hObject,'Max'))
    Simulink.sdi.markSignalForStreaming(control.Outport(4),'on');
    
else
    Simulink.sdi.markSignalForStreaming(control.Outport(4),'off');
end

% --- Executes on button press in IdRef.
function IdRef_Callback(hObject, eventdata, handles)
% hObject    handle to IdRef (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of IdRef
control=get_param('MCU_Simulation_Architecture/Motor Control Algorithm/WINDY CIM_BPM','PortHandles');
if (get(hObject,'Value') == get(hObject,'Max'))
    Simulink.sdi.markSignalForStreaming(control.Outport(3),'on');
    
else
    Simulink.sdi.markSignalForStreaming(control.Outport(3),'off');
end

% --- Executes on button press in Imr.
function Imr_Callback(hObject, eventdata, handles)
% hObject    handle to Imr (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of Imr
control=get_param('MCU_Simulation_Architecture/Motor Control Algorithm/WINDY CIM_BPM','PortHandles');
if (get(hObject,'Value') == get(hObject,'Max'))
    Simulink.sdi.markSignalForStreaming(control.Outport(7),'on');
    
else
    Simulink.sdi.markSignalForStreaming(control.Outport(7),'off');
end

% --- Executes on button press in Vd.
function Vd_Callback(hObject, eventdata, handles)
% hObject    handle to Vd (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of Vd
control=get_param('MCU_Simulation_Architecture/Motor Control Algorithm/WINDY CIM_BPM','PortHandles');
if (get(hObject,'Value') == get(hObject,'Max'))
    Simulink.sdi.markSignalForStreaming(control.Outport(9),'on');
    
else
    Simulink.sdi.markSignalForStreaming(control.Outport(9),'off');
end

% --- Executes on button press in Vq.
function Vq_Callback(hObject, eventdata, handles)
% hObject    handle to Vq (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of Vq
control=get_param('MCU_Simulation_Architecture/Motor Control Algorithm/WINDY CIM_BPM','PortHandles');
if (get(hObject,'Value') == get(hObject,'Max'))
    Simulink.sdi.markSignalForStreaming(control.Outport(10),'on');
    
else
    Simulink.sdi.markSignalForStreaming(control.Outport(10),'off');
end

% --- Executes on button press in Vs.
function Vs_Callback(hObject, eventdata, handles)
% hObject    handle to Vs (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of Vs
control=get_param('MCU_Simulation_Architecture/Motor Control Algorithm/WINDY CIM_BPM','PortHandles');
if (get(hObject,'Value') == get(hObject,'Max'))
    Simulink.sdi.markSignalForStreaming(control.Outport(11),'on');
    
else
    Simulink.sdi.markSignalForStreaming(control.Outport(11),'off');
end

% --- Executes on button press in Vsfw.
function Vsfw_Callback(hObject, eventdata, handles)
% hObject    handle to Vsfw (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of Vsfw
control=get_param('MCU_Simulation_Architecture/Motor Control Algorithm/WINDY CIM_BPM','PortHandles');
if (get(hObject,'Value') == get(hObject,'Max'))
    Simulink.sdi.markSignalForStreaming(control.Outport(12),'on');
    
else
    Simulink.sdi.markSignalForStreaming(control.Outport(12),'off');
end

% --- Executes on button press in TorqueRef.
function TorqueRef_Callback(hObject, eventdata, handles)
% hObject    handle to TorqueRef (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of TorqueRef
control=get_param('MCU_Simulation_Architecture/Motor Control Algorithm/WINDY CIM_BPM','PortHandles');
if (get(hObject,'Value') == get(hObject,'Max'))
    Simulink.sdi.markSignalForStreaming(control.Outport(2),'on');
    
else
    Simulink.sdi.markSignalForStreaming(control.Outport(2),'off');
end

% --- Executes on button press in Torque.
function Torque_Callback(hObject, eventdata, handles)
% hObject    handle to Torque (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of Torque
control=get_param('MCU_Simulation_Architecture/Motor Control Algorithm/WINDY CIM_BPM','PortHandles');
if (get(hObject,'Value') == get(hObject,'Max'))
    Simulink.sdi.markSignalForStreaming(control.Outport(14),'on');
    
else
    Simulink.sdi.markSignalForStreaming(control.Outport(14),'off');
end

% --- Executes on button press in OmegaRotEst.
function OmegaRotEst_Callback(hObject, eventdata, handles)
% hObject    handle to OmegaRotEst (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of OmegaRotEst
control=get_param('MCU_Simulation_Architecture/Motor Control Algorithm/WINDY CIM_BPM','PortHandles');
if (get(hObject,'Value') == get(hObject,'Max'))
    Simulink.sdi.markSignalForStreaming(control.Outport(13),'on');
    
else
    Simulink.sdi.markSignalForStreaming(control.Outport(13),'off');
end

% --- Executes on button press in OmegaRotRef.
function OmegaRotRef_Callback(hObject, eventdata, handles)
% hObject    handle to OmegaRotRef (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of OmegaRotRef
control=get_param('MCU_Simulation_Architecture/Motor Control Algorithm/WINDY CIM_BPM','PortHandles');
if (get(hObject,'Value') == get(hObject,'Max'))
    Simulink.sdi.markSignalForStreaming(control.Outport(17),'on');
    
else
    Simulink.sdi.markSignalForStreaming(control.Outport(17),'off');
end

% --- Executes on button press in ErrorSpeed.
function ErrorSpeed_Callback(hObject, eventdata, handles)
% hObject    handle to ErrorSpeed (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of ErrorSpeed
control=get_param('MCU_Simulation_Architecture/Motor Control Algorithm/WINDY CIM_BPM','PortHandles');
if (get(hObject,'Value') == get(hObject,'Max'))
    Simulink.sdi.markSignalForStreaming(control.Outport(16),'on');
    
else
    Simulink.sdi.markSignalForStreaming(control.Outport(16),'off');
end

% --- Executes on button press in ThetaFluxEst.
function ThetaFluxEst_Callback(hObject, eventdata, handles)
% hObject    handle to ThetaFluxEst (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of ThetaFluxEst
control=get_param('MCU_Simulation_Architecture/Motor Control Algorithm/WINDY CIM_BPM','PortHandles');
if (get(hObject,'Value') == get(hObject,'Max'))
    Simulink.sdi.markSignalForStreaming(control.Outport(8),'on');
    
else
    Simulink.sdi.markSignalForStreaming(control.Outport(8),'off');
end

% --- Executes on button press in PWM_Duties.
function PWM_Duties_Callback(hObject, eventdata, handles)
% hObject    handle to PWM_Duties (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of PWM_Duties
control=get_param('MCU_Simulation_Architecture/Motor Control Algorithm/WINDY CIM_BPM','PortHandles');
if (get(hObject,'Value') == get(hObject,'Max'))
    Simulink.sdi.markSignalForStreaming(control.Outport(1),'on');
    
else
    Simulink.sdi.markSignalForStreaming(control.Outport(1),'off');
end

% --- Executes on button press in PWM_Status.
function PWM_Status_Callback(hObject, eventdata, handles)
% hObject    handle to PWM_Status (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of PWM_Status
control=get_param('MCU_Simulation_Architecture/Motor Control Algorithm/WINDY CIM_BPM','PortHandles');
if (get(hObject,'Value') == get(hObject,'Max'))
    Simulink.sdi.markSignalForStreaming(control.Outport(20),'on');
    
else
    Simulink.sdi.markSignalForStreaming(control.Outport(20),'off');
end

% --- Executes on button press in Sector.
function Sector_Callback(hObject, eventdata, handles)
% hObject    handle to Sector (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of Sector
control=get_param('MCU_Simulation_Architecture/Motor Control Algorithm/WINDY CIM_BPM','PortHandles');
if (get(hObject,'Value') == get(hObject,'Max'))
    Simulink.sdi.markSignalForStreaming(control.Outport(15),'on');
    
else
    Simulink.sdi.markSignalForStreaming(control.Outport(15),'off');
end

% --- Executes on button press in SR_Fault.
function SR_Fault_Callback(hObject, eventdata, handles)
% hObject    handle to SR_Fault (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of SR_Fault
control=get_param('MCU_Simulation_Architecture/Motor Control Algorithm/WINDY CIM_BPM','PortHandles');
if (get(hObject,'Value') == get(hObject,'Max'))
    Simulink.sdi.markSignalForStreaming(control.Outport(19),'on');
    
else
    Simulink.sdi.markSignalForStreaming(control.Outport(19),'off');
end

% --- Executes on button press in Fault.
function Fault_Callback(hObject, eventdata, handles)
% hObject    handle to Fault (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of Fault

control=get_param('MCU_Simulation_Architecture/Motor Control Algorithm/WINDY CIM_BPM','PortHandles');
if (get(hObject,'Value') == get(hObject,'Max'))
    Simulink.sdi.markSignalForStreaming(control.Outport(18),'on');
    
else
    Simulink.sdi.markSignalForStreaming(control.Outport(18),'off');
end
% --- Executes on button press in Vpole.
function Vpole_Callback(hObject, eventdata, handles)
% hObject    handle to Vpole (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of Vpole
Vpole=get_param('MCU_Simulation_Architecture/Inverter','PortHandles');
if (get(hObject,'Value') == get(hObject,'Max'))
    Simulink.sdi.markSignalForStreaming(Vpole.Outport(1),'on');
    
else
    Simulink.sdi.markSignalForStreaming(Vpole.Outport(1),'off');
end

% --- Executes on button press in Vdc.
function Vdc_Callback(hObject, eventdata, handles)
% hObject    handle to Vdc (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of Vdc
Vdc=get_param('MCU_Simulation_Architecture/INPUT Circuit Model','PortHandles');
if (get(hObject,'Value') == get(hObject,'Max'))
    Simulink.sdi.markSignalForStreaming(Vdc.Outport(1),'on');
    
else
    Simulink.sdi.markSignalForStreaming(Vdc.Outport(1),'off');
end

% --- Executes on button press in Motor_Input.
function Motor_Input_Callback(hObject, eventdata, handles)
% hObject    handle to Motor_Input (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of Motor_Input
power=get_param('MCU_Simulation_Architecture/Motor Coupled With Mechanics','PortHandles');
if (get(hObject,'Value') == get(hObject,'Max'))
    Simulink.sdi.markSignalForStreaming(power.Outport(5),'on');
    
else
    Simulink.sdi.markSignalForStreaming(power.Outport(5),'off');
end

% --- Executes on button press in Motor_Speed.
function Motor_Speed_Callback(hObject, eventdata, handles)
% hObject    handle to Motor_Speed (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of Motor_Speed
% speed=get_param('MCU_Simulation_Architecture/Motor Electrical Model ','PortHandles');
% if (get(hObject,'Value') == get(hObject,'Max'))
%     Simulink.sdi.markSignalForStreaming(speed.Outport(6),'on');
%     
% else
%     Simulink.sdi.markSignalForStreaming(speed.Outport(6),'off');
% end
if (get(hObject,'Value') == get(hObject,'Max'))
   Simulink.sdi.markSignalForStreaming('MCU_Simulation_Architecture/Signal Processing/Mux5',1,'on');  
    else
   Simulink.sdi.markSignalForStreaming('MCU_Simulation_Architecture/Signal Processing/Mux5',1,'off'); 
end

% --- Executes on button press in Flux_Position.
function Flux_Position_Callback(hObject, eventdata, handles)
% hObject    handle to Flux_Position (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of Flux_Position
flux_position=get_param('MCU_Simulation_Architecture/Motor Coupled With Mechanics','PortHandles');
if (get(hObject,'Value') == get(hObject,'Max'))
    Simulink.sdi.markSignalForStreaming(flux_position.Outport(3),'on');
    
else
    Simulink.sdi.markSignalForStreaming(flux_position.Outport(3),'off');
end

% --- Executes on button press in Flux_Speed.
function Flux_Speed_Callback(hObject, eventdata, handles)
% hObject    handle to Flux_Speed (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of Flux_Speed
flux_speed=get_param('MCU_Simulation_Architecture/Motor Coupled With Mechanics','PortHandles');
if (get(hObject,'Value') == get(hObject,'Max'))
    Simulink.sdi.markSignalForStreaming(flux_speed.Outport(4),'on');
    
else
    Simulink.sdi.markSignalForStreaming(flux_speed.Outport(4),'off');
end

% --- Executes on button press in Vphase.
function Vphase_Callback(hObject, eventdata, handles)
% hObject    handle to Vphase (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of Vphase
vphase=get_param('MCU_Simulation_Architecture/Motor Coupled With Mechanics/Bus Selector','PortHandles');
if (get(hObject,'Value') == get(hObject,'Max'))
    Simulink.sdi.markSignalForStreaming(vphase.Outport(1),'on');
    Simulink.sdi.markSignalForStreaming(vphase.Outport(2),'on');
    Simulink.sdi.markSignalForStreaming(vphase.Outport(3),'on');
else
    Simulink.sdi.markSignalForStreaming(vphase.Outport(1),'off');
    Simulink.sdi.markSignalForStreaming(vphase.Outport(2),'off');
    Simulink.sdi.markSignalForStreaming(vphase.Outport(3),'off');
end


% --- Executes on button press in Te.
function Te_Callback(hObject, eventdata, handles)
% hObject    handle to Te (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of Te
te=get_param('MCU_Simulation_Architecture/Motor Coupled With Mechanics','PortHandles');
if (get(hObject,'Value') == get(hObject,'Max'))
    Simulink.sdi.markSignalForStreaming(te.Outport(7),'on');
    
else
    Simulink.sdi.markSignalForStreaming(te.Outport(7),'off');
end