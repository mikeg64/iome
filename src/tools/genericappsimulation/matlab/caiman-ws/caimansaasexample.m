
path(path,'../caimanDir')
%open the file generated
%portfile='ioserverinfo.txt';                            %add comment if  we are not running standalone
%portfile='ioserverinfo.txt';                      %remove comment if  we are not running standalone
portfile='mysim0_port.txt';
fd=fopen(portfile);
%res=mfscanf(fd,'%d %d %s')
res=textscan(fd,'%d %s');
fclose(fd);
%port=res(1) id=res(2) hostname=res(3)
%elist=iome(res(3),res(1),res(2));
elist=iome('localhost',res{1},0);
%readsimulation('simfile.xml',elist);

setpref('Internet','SMTP_Server','mailhost.shef.ac.uk');
setpref('Internet','E_mail','m.griffiths@sheffield.ac.uk');


%get the parameters from the server
try
    userEmail=getparamstring('useremail',elist);
    imageFile=getparamstring('imagefile',elist);
    jobtype=getparamstring('jobtype',elist);
    outputCode=jobtype;
catch
    display('Failed to get parameters from local iome server');
    exitiome(elist);
    simulationstatus(elist);
    exit();       
end




try
    %myftp=ftp('cpaneldev.shef.ac.uk','cs1mkg','Ambodach1');
    %cd(myftp,'public_html/iometest/uploads');
    %mget(myftp, imageFile);
    %delete(myftp, imageFile);
    %close(myftp);
    %testData = ulrwrite(imageLocation2,'testData.jpg');
    [dataIn]                            = imread(imageFile);
    [rows,cols,levs]                    = size(dataIn);
    ImageName                           = imageFile;
catch
    outputCode                          = 'E2';
    disp('error while reading');
end



%--------------------------------------------------------------------------------------------------
% 4 Select the algorithm for processing MI - migration SH - shading PE - permeability VT - Vessel
% Tracing, ME - Merge of RGB Channels
%--------------------------------------------------------------------------------------------------
if ~strcmp(outputCode(1),'E')
        switch outputCode
            case 'ME'
                try
                    [dataOut,nameFileBlue,nameFileGreen,nameFileRed]    = mergeRGBchannels(newImageName{kk,1}(1:end,1:end,:));
                catch
                    outputCode              = 'EME';
                end
            case 'SH'
                try
                    [dataOut]               = shadingCorrection(dataIn(1:end,1:end,:));
		    outputMessage = 'Shading Correction Completed Successfuly';
                catch
                    outputCode              = 'ESH';
                end
            case 'MI'
                try
                    [data_stats,dataOut]    = cellMigration(dataIn(1:1:end,1:1:end,:));
                    extraData               = data_stats;
                catch
                    outputCode              = 'EMI';
                end
            case 'VT'
                try
                    scaleSpaceDims          = 1:10;
                    [finalRidges,finalStats,networkP,dataOut1,dataOut] =  scaleSpaceLowMem(dataIn,scaleSpaceDims,1.75);
                    extraData               = networkP;
                catch
                    outputCode              = 'EVT';
                end
            otherwise
                %the case is not covered, generate an error
                outputCode                  = 'E4';
        end
end

%email output to user
if ~strcmp(outputCode(1),'E')
             %prepare the results only if there were no errors on the way
            imageNameOut                   = strcat(ImageName,'.jpg');
            if isa(dataOut,'uint8')
                imwrite(dataOut,imageNameOut,'jpg');

            else
                imwrite(dataOut/255,imageNameOut,'jpg');
            end
            %--------------------------------------------------------------------------------------------------
            % 5 email results to the user
            %--------------------------------------------------------------------------------------------------
            try
                sendmail(userEmail,'Results from Caiman',outputMessage,{imageNameOut});
            catch
                %getpref('Internet')
                outputCode              = 'E1';
                outputMessage       = createOutputMessage(outputCode);
                sendmail(userEmail,'Results from Caiman',outputMessage);                
            end
            %--------------------------------------------------------------------------------------------------
            % 6 delete image file
            %--------------------------------------------------------------------------------------------------
            delete(imageNameOut);   
else
            outputMessage       = createOutputMessage(outputCode);
            sendmail(userEmail,'Results from Caiman ',outputMessage);    
end

try
   exitiome(elist);
catch
   display('Unable to close IOME'); 
end

try
    simulationstatus(elist);
catch
    display('iome server closed!');
end

exit();

