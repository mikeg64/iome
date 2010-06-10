
%-------- Script that will do all the image processing inside SUILVEN ----------------------------
%--------       1 Reads the images to process (this list has been generated at the unix command line)
%--------       2 Loop over the List of images, compare with the ones that have been processed before
%--------       3 If they are new, then Read the images themselves from the webserver otherwise skip
%--------       4 Select the particular algorithm to run: shading, migration, ...
%--------       5 Email the results to the user
%--------       6 Write a list with the images already processed         
%--------       7 Delete the list of images to process                   

%--------------------------------------------------------------------------------------------------
%   1   set and open IOME settings
%--------------------------------------------------------------------------------------------------

try
   %tttt1=pwd;disp(tttt1)
   path(path,'../caimanDir')
   %open the file generated
   %portfile = 'ioserverinfo.txt';                            %add comment if  we are not running standalone
   %portfile = 'ioserverinfo.txt';                      %remove comment if  we are not running standalone
   portfile                = 'mysim0_port.txt';
   fd                      = fopen(portfile);
   %res = mfscanf(fd,'%d %d %s')
   res                     = textscan(fd,'%d %s');
   fclose(fd);
   %port                   = res(1) id = res(2) hostname = res(3)
   %elist                  = iome(res(3),res(1),res(2));
   elist                   = iome('localhost',res{1},0);
   %readsimulation('simfile.xml',elist);

   setpref('Internet','SMTP_Server','mailhost.shef.ac.uk');
   %setpref('Internet','E_mail','m.griffiths@sheffield.ac.uk');
   setpref('Internet','E_mail','c.reyes@sheffield.ac.uk');
catch
    outputCode                          = 'E2a';
end

%--------------------------------------------------------------------------------------------------
%   2   get the parameters from the server
%--------------------------------------------------------------------------------------------------

try
    userEmail           = getparamstring('useremail',elist);
    imageFile           = getparamstring('imagefile',elist);
    jobtype             = getparamstring('jobtype',elist);
    outputCode          = jobtype;
    disp(userEmail);
    disp(imageFile);
catch
    outputCode                          = 'E2b';
    display('Failed to get parameters from local iome server');
    exitiome(elist);
    exitiome(elist);
    exit();       
end



%--------------------------------------------------------------------------------------------------
% 3 the input file is read from imageFile
%--------------------------------------------------------------------------------------------------

try
    %myftp = ftp('cpaneldev.shef.ac.uk','cs1mkg','*******');
    %cd(myftp,'public_html/iometest/uploads');
    %mget(myftp, imageFile);
    %delete(myftp, imageFile);
    %close(myftp);
    %testData = ulrwrite(imageLocation2,'testData.jpg');
    [dataIn]                            = imread(strcat('http://carlos-reyes.staff.shef.ac.uk/caiman/imageUploads/',imageFile));
    %[dataIn]                            = imread(strcat(imageFile));
    [rows,cols,levs]                    = size(dataIn); %#ok<NASGU>
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
%             case 'ME'
%                 try
%                     [dataOut,nameFileBlue,nameFileGreen,nameFileRed]    = mergeRGBchannels(newImageName{kk,1}(1:end,1:end,:));
%                 catch
%                     outputCode              = 'EME';
%                 end
            case 'SH'
                try

                    [rows,cols,levs]                = size(dataIn);
                    RCL                             = rows*cols*levs;
                    if (RCL)<1e6
                        subSampL=1;
                    elseif (RCL)<3e6
                        subSampL=2;
                    elseif (RCL)<12e6
                        subSampL=4;
                    else
                        subSampL=8;
                    end
                    [dataOutS,errSurfaceS]          = shadingCorrection(dataIn(1:subSampL:end,1:subSampL:end,:));

		    if subSampL==1
                        errSurfaceS2                 = errSurfaceS;
                    else
                        filtG = gaussF(3,3,1);
                        for counterL=1:levs
                            errSurfaceS2(:,:,counterL)  = imfilter(expandu(errSurfaceS(:,:,counterL),log2(subSampL)),filtG); %#ok<AGROW>
                        end
                    end
                    dataOut                         = double(dataIn)-errSurfaceS2(1:rows,1:cols,:);
                    avChannels                      = mean(mean(dataOut));
                    maxAvChannel                    = max(avChannels);
                    for counterL=1:levs
                        dataOut(:,:,counterL)       = maxAvChannel*(dataOut(:,:,counterL)/avChannels(counterL));
                    end
                    dataOut(dataOut>255)            = 255;
                    dataOut(dataOut<0)              = 0;
                    %[dataOut]               = shadingCorrection(dataIn(1:end,1:end,:));
                    %outputMessage = 'Shading Correction Completed Successfuly';
                catch
                    outputCode              = 'ESH';
                end
            case 'SE'
                try
                    [finalCells,statsObjects,dataOut]       = regionGrowingCells(dataIn);
                    [avThickness,stdThickness,propLumen]    = findWallThickness(finalCells);
                    tempProps                               = regionprops(finalCells,'Perimeter','FilledArea','EquivDiameter');
                    %statsObjects.avThickness                = avThickness;
                    %statsObjects.stdThickness               = stdThickness;
                    %statsObjects.propLumen                  = propLumen;
                    extraData.statsObjects                  = statsObjects;
                    extraData.avThickness                   = avThickness;
                    extraData.temp                          = tempProps;
                    st2P                                = [tempProps.Perimeter]';
                    st2A                                = [statsObjects.Area]';
                    st2FA                               = [tempProps.FilledArea]';
                    if st2FA>0
                        st2RA                               = ((st2FA-st2A)./st2FA)';
                        extraData.luVA                  = mean(st2RA);
                        extraData.roundness             = mean(st2P./(sqrt(4*pi*st2FA)));
                    else
                        extraData.luVA                  = 0;
                        extraData.roundness             = 0;
                    end 
                catch
                    outputCode              = 'ESE';
                end
            case 'LA'
                try
                    %dataOut = dataIn;
                    dataOut                 = removeLineArtifact(dataIn);
                catch
                    outputCode              = 'ELA';
                end
            case 'QH'
                try
                    %dataOut = dataIn;
                    extraData               = quantifyHeartSprouts(dataIn);
                catch
                    outputCode              = 'EQH';
                end
            case 'MI'
                try
                    %dataOut = dataIn;
                    [data_stats,dataOut]    = cellMigration(dataIn(1:1:end,1:1:end,:));
                    extraData               = data_stats;
                catch
                    outputCode              = 'EMI';
                end
            case 'VT'
                try
		    %dataOut= dataIn;
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
        if ~exist('extraData','var')
            outputMessage       = createOutputMessage(outputCode);
        else
            %if ~exist('avThickness','var')
                outputMessage       = createOutputMessage(outputCode,extraData);
            %else
            %   outputMessage       = createOutputMessage(outputCode,extraData,avThickness);
            %end

        end
        [q1,q2]=urlread('http://carlos-reyes.staff.shef.ac.uk/caiman/clearOldFiles.php?idTimeTC=10');
end

%email output to user
if ~strcmp(outputCode(1),'E')
             %prepare the results only if there were no errors on the way
            %if there is a dataOut, prepare the image to attach, otherwise just send the email
            if exist('dataOut','var')
              %imageNameOut                   = strcat(ImageName,'.jpg');
              imageNameOut                   = strcat(ImageName(11:end));
              if isa(dataOut,'uint8')
                  if strcmp(imageNameOut(end-2:end),'tif')
                    imwrite(dataOut,imageNameOut,'tif','resolution',150);                  
                  else
                    imwrite(dataOut,imageNameOut,'jpg');
                  end
              else
                  if strcmp(imageNameOut(end-2:end),'tif')
                    imwrite(dataOut/255,imageNameOut,'tif','resolution',150);
                  else
                    imwrite(dataOut/255,imageNameOut,'jpg');
                  end
              end
              %--------------------------------------------------------------------------------------------------
              % 5 email results to the user
              %--------------------------------------------------------------------------------------------------
              try
                  sendmail(userEmail,'Results from Caiman',outputMessage,{imageNameOut});
              catch
                  %getpref('Internet')
                  outputCode                  = 'E1';
                  outputMessage               = createOutputMessage(outputCode);
                  sendmail(userEmail,'Results from Caiman',outputMessage);                
              end
            else
                               sendmail(userEmail,'Results from Caiman',outputMessage);
            end
            %--------------------------------------------------------------------------------------------------
            % 6 delete image file
            %--------------------------------------------------------------------------------------------------
            delete(imageNameOut);   
else
            outputMessage                   = createOutputMessage(outputCode);
            sendmail(userEmail,'Results from Caiman ',outputMessage);    
end

try
   exitiome(elist);
catch
   display('Unable to close IOME'); 
end

try
    exitiome(elist);
catch
    display('iome server closed!');
end

exit();

