; -- Example3.iss --
;needs header files for xercesc and xalanc
; Same as Example1.iss, but creates some registry entries too.

; SEE THE DOCUMENTATION FOR DETAILS ON CREATING .ISS SCRIPT FILES!

[Setup]
AppName=iome
AppVerName=iome 1.5
DefaultDirName={pf}\iome
DefaultGroupName=iome
UninstallDisplayIcon={app}\bin\ioui.py



[Files]
Source: "src\tools\python\ioui.py"; DestDir: "{app}\bin"
Source: "bin\*"; DestDir: "{app}\bin"
Source: "lib\*"; DestDir: "{app}\lib"
Source: "src\examples\python\*"; DestDir: "{app}\src\examples\python"

Source: "src\examples\php\*"; DestDir: "{app}\src\examples\php"

Source: "src\examples\scilab\*"; DestDir: "{app}\src\examples\scilab"
Source: "src\examples\scilab\scilab_shallowwater\*"; DestDir: "{app}\src\examples\scilab\scilab_shallowwater"
Source: "src\examples\scilab\scilab_shallowwater\dx\*"; DestDir: "{app}\src\examples\scilab\scilab_shallowwater\dx"
Source: "src\examples\scilab\scilab_shallowwater\out\*"; DestDir: "{app}\src\examples\scilab\scilab_shallowwater\out"

Source: "src\examples\scilab\scilab_wave_ws\*"; DestDir: "{app}\src\examples\scilab\scilab_wave_ws"
Source: "src\examples\scilab\scilab_wave_ws\dx\*"; DestDir: "{app}\src\examples\scilab\scilab_wave_ws\dx"
Source: "src\examples\scilab\scilab_wave_ws\out\*"; DestDir: "{app}\src\examples\scilab\scilab_wave_ws\out"

Source: "src\examples\matlab\*"; DestDir: "{app}\src\examples\matlab"
Source: "src\examples\matlab\matlab_shallowwater\*"; DestDir: "{app}\src\examples\matlab\matlab_shallowwater"
Source: "src\examples\matlab\matlab_shallowwater\dx\*"; DestDir: "{app}\src\examples\matlab\matlab_shallowwater\dx"
Source: "src\examples\matlab\matlab_shallowwater\out\*"; DestDir: "{app}\src\examples\matlab\matlab_shallowwater\out"

Source: "src\examples\matlab\matlab_wave_ws\*"; DestDir: "{app}\src\examples\matlab\matlab_wave_ws"
Source: "src\examples\matlab\matlab_wave_ws\dx\*"; DestDir: "{app}\src\examples\matlab\matlab_wave_ws\dx"
Source: "src\examples\matlab\matlab_wave_ws\out\*"; DestDir: "{app}\src\examples\matlab\matlab_wave_ws\out"

Source: "src\examples\matlab\caiman-ws\*"; DestDir: "{app}\src\examples\matlab\caiman-ws"
Source: "src\examples\matlab\caiman-ws\caimanDir\*"; DestDir: "{app}\src\examples\matlab\caiman-ws\caimanDir"
Source: "src\examples\matlab\caiman-ws\testimages\*"; DestDir: "{app}\src\examples\matlab\caiman-ws\testimges"

Source: "src\examples\fortran\*"; DestDir: "{app}\src\examples\fortran"

Source: "src\examples\c\*"; DestDir: "{app}\src\examples\c"


Source: "include\iome\utils\*"; DestDir: "{app}\src\include\iome\utils"
Source: "include\iome\simulation\*"; DestDir: "{app}\src\include\iome\simulation"
Source: "include\iome\genericsimulationlib\*"; DestDir: "{app}\src\include\iome\genericsimulationlib"

Source: "src\tools\php\iome\*"; DestDir: "{app}\src\tools\php\iome"
Source: "src\tools\matlab\iome_toolbox\*"; DestDir: "{app}\src\tools\matlab\iome_toolbox"
Source: "src\tools\scilab\iome_toolbox\*"; DestDir: "{app}\src\tools\scilab\iome_toolbox"
Source: "src\tools\scilab\iome_toolbox\demos\*"; DestDir: "{app}\src\tools\scilab\iome_toolbox\demos"
Source: "src\tools\scilab\iome_toolbox\macros\*"; DestDir: "{app}\src\tools\scilab\iome_toolbox\macros"
Source: "src\tools\scilab\iome_toolbox\etc\*"; DestDir: "{app}\src\tools\scilab\iome_toolbox\etc"
Source: "src\tools\scilab\iome_toolbox\help\*"; DestDir: "{app}\src\tools\scilab\iome_toolbox\help"
Source: "src\tools\scilab\iome_toolbox\help\en_US\*"; DestDir: "{app}\src\tools\scilab\iome_toolbox\help\en_US"

Source: "src\tools\python\*"; DestDir: "{app}\src\tools\python"
Source: "src\tools\python\ZSI\*"; DestDir: "{app}\src\tools\python\ZSI"
Source: "src\tools\python\ZSI\twisted\*"; DestDir: "{app}\src\tools\python\ZSI\twisted"
Source: "src\tools\python\ZSI\wstools\*"; DestDir: "{app}\src\tools\python\ZSI\wstools"
Source: "src\tools\python\ZSI\generate\*"; DestDir: "{app}\src\tools\python\ZSI\generate"

Source: "src\tools\scilab\iome_toolbox\macros\*"; DestDir: "{app}\src\tools\scilab\iome_toolbox\macros"
Source: "src\tools\scilab\iome_toolbox\tests\unit_tests\*"; DestDir: "{app}\src\tools\scilab\iome_toolbox\tests\unit_tests"


Source: "Readme.txt"; DestDir: "{app}"; Flags: isreadme

[Icons]
Name: "{group}\iome"; Filename: "{app}\bin\ioui.py"

[Registry]
Root: HKLM; Subkey: "SYSTEM\CurrentControlSet\Control\Session Manager\Environment"; ValueType: string; ValueName: "IOME_HOME"; ValueData: "{app}"
Root: HKLM; Subkey: "SYSTEM\CurrentControlSet\Control\Session Manager\Environment"; ValueType: expandsz; ValueName: "PATH"; ValueData: "{olddata};%IOME_HOME%\bin"
Root: HKLM; Subkey: "SYSTEM\CurrentControlSet\Control\Session Manager\Environment"; ValueType: expandsz; ValueName: "PYTHONPATH"; ValueData: "{olddata};%IOME_HOME%\src\tools\python"
