@echo off
rem windows batch file to start matlab takes as input matlab batch file
set file=%1
matlab.exe -nosplash -nodisplay -r %file%
