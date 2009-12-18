function varargout = sunami2(varargin)
% sunami M-File for sunami.fig
%      sunami, by itself, creates a new sunami or raises the existing
%      singleton*.
%
%      H = sunami returns the handle to a new sunami or the handle to
%      the existing singleton*.
%
%      sunami('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in sunami.M with the given input arguments.
%
%      sunami('Property','Value',...) creates a new sunami or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before sunami_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to sunami_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

%DS ---------------------------------
% Internal data structures:
% handles.heightpar = height of disturbance [ hmin hmax currentheight ] 
%  handles.xpar =  x coordinate of the disturbance [currentx xmin xmax ]
%  handles.ypar =  y coordinate of the disturbance [currenty ymin ymax ]
%  Auxiliary routines :
%  genfilnam ( parent_directory , number ) : Generates name of the 
%                                           steering file.
 
%DS ---------------------------------
% Edit the above text to modify the response to help sunami

% Last Modified by GUIDE v2.5 04-Dec-2009 13:41:52

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @sunami_OpeningFcn, ...
                   'gui_OutputFcn',  @sunami_OutputFcn, ...
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


% --- Executes just before sunami is made visible.
function sunami_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to sunami (see VARARGIN)

% Choose default command line output for sunami
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes sunami wait for user response (see UIRESUME)
% uiwait(handles.figure1);
%DS initialise IOME 
% We are assuming that the server is started earlier on 'localhost'
% and port=8080 and its id =0 .
% We just get the structure via  [elist]=iome(server,port,id) ;
   elist=iome('localhost',8080,0)
   handles.elist = elist ;
   guidata(hObject, handles);
% --- Outputs from this function are returned to the command line.
function varargout = sunami_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in update.
function update_Callback(hObject, eventdata, handles)
% hObject    handle to update (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%DS this is the update-simulation call-back.
%DS When activated this will;
%DS - readin control-parameters from iome-server
%DS - readin the simulation graph-data.
%DS - activate a repeat-loop of displaying the visualisation.
%DS - We will need a structure for all control and data variables. 
%DS           [h  , hmin , hmax] 
% We need iome server to supply the following three variables.
 heightpar = [ 1000.0 , 100.0 , 10060.0 ];
 freqpar = [ 0.05 0.0 0.2 ] ;
 xpar = [ 0.5  0.0  1.0 ]; % x , xmin ,xmax 
 ypar = [ 0.5  0.0  1.0 ] ; % y , ymin ymax
 handles.freqpar = freqpar ;
 handles.heightpar = heightpar; 
 handles.xpar =xpar ;
 handles.ypar =ypar ;
 guidata(hObject, handles);
  
% getparamdouble( height ... ) 
% getparamvec .....  
 set( handles.xslider , 'Min' , xpar(2) );
 set( handles.xslider , 'Max' , xpar(3) );
 set( handles.xslider , 'Value' , xpar(1) );
 
set( handles.yslider , 'Min' , ypar(2) );
 set( handles.yslider , 'Max' , ypar(3) );
 set( handles.yslider , 'Value' , ypar(1) );
% readin the data file. 
% the first line is skipped. space limited. 

 %   1 to 96 is the full range 
% draw the plot for the first instance....


for i= 1:22
%  nn=num2str(i);
%  filna=[fprefx nn fsuffx]
   filna=genfilnam( 'tmp/' , i ) ;
 
  
   A= importdata(filna , ' ' , 1 );
%  A= importdata('t20.out' , ' ' , 1 );
  AA= A.data ;  clear A ;
  [ n m ] = size(AA)      
  height=AA(:,3:3:m );
  % uvector 
% u = AA( :,1,1:3:m) ;
% v = AA( :,2,1:3:m) ;

% h vector
 
  
% height contains the heights. 
% get handle to plot object.
  if i == 1  
      
      hmax=max( max( height) )  ;
      hmin=min(min(height) ) ;
      deltah = ( hmax - hmin ).*0.3 ;
      hmin= hmin - deltah ;
      hmax = hmax + deltah ;
       h = handles.mainplot ;
%  h2 =pcolor(h, height) ; shading('interp') ;
       h2 = surf(h , height ) ; shading( 'interp') ; 
        set (h , 'ZLimMode' , 'manual' ) ;
       set ( h , 'ZGrid' , 'off' ) ;
        set( h , 'ZLim' ,[  hmin  hmax ] ) ;
  end 

  
  set( h2 , 'ZData' , height )
  pause( 20/60 );
end

function outnam = genfilnam( directory , inum )
fprefx= 'tsteer1s' ;
if directory == ' ' 
    frefx='tsteer1s' ;
else
    fprefx = [ directory '/tsteer1s' ] ;
end
fsuffx ='.out';
nn= num2str(inum) ;
outnam = [ fprefx nn fsuffx ]; 

% --- Executes on slider movement.
function disp1_Callback(hObject, eventdata, handles)
% hObject    handle to disp1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider
  heightpar = handles.heightpar;
  heightparam(1)=0.0
  heightpar(1)= get(hObject , 'Value' ) 
  handles.heightpar = heightpar; 
  elist = handles.elist ;
  setparamdouble ( 'amplitude' , heightpar(1) , elist ) ;
  
  guidata(hObject, handles);
  

% --- Executes during object creation, after setting all properties.
function disp1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to disp1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --------------------------------------------------------------------
function File_Callback(hObject, eventdata, handles)
% hObject    handle to File (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function exit_Callback(hObject, eventdata, handles)
% hObject    handle to exit (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

close(ancestor(hObject, 'figure'))


% --- Executes on slider movement.
function xslider_Callback(hObject, eventdata, handles)
% hObject    handle to xslider (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider
  xpar= handles.xpar ;
  xpar(1)= get(hObject , 'Value' );
  elist = handles.elist ;
  setparamdouble ( 'sx' , xpar(1) , elist ) ;
  guidata(hObject, handles);
   

% --- Executes during object creation, after setting all properties.
function xslider_CreateFcn(hObject, eventdata, handles)
% hObject    handle to xslider (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function yslider_Callback(hObject, eventdata, handles)
% hObject    handle to xslider (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider
  ypar = handles.ypar ;
  handles.ypar(1)= get(hObject , 'Value' );
  elist = handles.elist ;
  setparamdouble ( 'sx' , ypar(1) , elist ) ;
  guidata(hObject, handles);
   
  
  
% --- Executes during object creation, after setting all properties.
function yslider_CreateFcn(hObject, eventdata, handles)
% hObject    handle to xslider (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function freqslider_Callback(hObject, eventdata, handles)
% hObject    handle to freqslider (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider
 heightpar = handles.freqpar;
  freqparam(1)=0.0
  freqpar(1)= get(hObject , 'Value' ) 
  handles.freqpar = freqpar; 
  elist = handles.elist ;
  setparamdouble ( 'frequency' , freqpar(1) , elist ) ;
  
  guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function freqslider_CreateFcn(hObject, eventdata, handles)
% hObject    handle to freqslider (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on button press in finishstr.
function finishstr_Callback(hObject, eventdata, handles)
% hObject    handle to finishstr (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

 setintparam('finishsteering' , 1 , elist ) 
