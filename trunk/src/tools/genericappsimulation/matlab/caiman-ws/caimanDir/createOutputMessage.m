function outputMessage = createOutputMessage(caseRoutine,extraData)


switch caseRoutine
    case 'ME'
        %Merging colour channels
        outputMessage{1}    = 'The image with the RGB channels is attached.';
        outputMessage{2}    = ' ';
    case 'SH'
        %shading correction
        outputMessage{1}       = 'The image with shading removed is attached.';
        outputMessage{2}       = ' ';
    case 'MI'
        %Migration assays
        data_stats          = extraData;
        outputMessage{1}    = 'The image with boundaries of the cell migration is attached.';
        outputMessage{3}    = strcat('Total Area            = ',      num2str(data_stats.area(1)),' [pix]');
        outputMessage{4}    = strcat('Relative Area         = ',   num2str(data_stats.area(2),3),' [%]');
        if isfield(data_stats,'maxDist')
            outputMessage{5}    = strcat('Minimum Distance  = ',num2str(data_stats.minimumDist,4),' [pix]');
            outputMessage{6}    = strcat('Maximum Distance  = ',num2str(data_stats.maxDist,4),' [pix]');
            outputMessage{7}    = strcat('Average Distance  = ',num2str(data_stats.avDist,4),' [pix]');
            outputMessage{8}    = ' ';
            outputMessage{9}    = ' ';
            outputMessage{10}   = ' ';
        else
            outputMessage{5}    = ' ';
            outputMessage{6}    = 'Distances were not obtained as the wound appeared to be closed at least from one position. ';
            outputMessage{7}    = ' ';
            outputMessage{8}    = ' ';
        end
        outputMessage{2}    = ' ';
    case 'VT'
        %Vessel tracing
        networkP            = extraData;
        outputMessage{1}    = 'The image with traced vasculature is attached.';
        outputMessage{2}    = 'Top 10 vessels labelled in green, Top 11-50 in yellow and the rest in black.';
        outputMessage{4}    = strcat('Num. Vessels               = ', num2str(networkP.numVessels,4),' ');
        outputMessage{5}    = strcat('Total Length               = ', num2str(networkP.totLength,4),' [pix]');
        outputMessage{6}    = strcat('Average Diameter           = ', num2str(networkP.avDiameter,4),' [pix]');
        outputMessage{7}    = strcat('Average Length             = ', num2str(networkP.avLength,4),' [pix]');
        outputMessage{8}    = strcat('Total Length (top 10)      = ', num2str(networkP.totLength_top10,4),' [pix]');
        outputMessage{9}    = strcat('Average Diameter (top 10)  = ', num2str(networkP.avDiameter_top10,4),' [pix]');
        outputMessage{10}   = strcat('Average Length (top 10)    = ', num2str(networkP.avLength_top10,4),' [pix]');
        outputMessage{3}    = ' ';
        outputMessage{11}   = ' ';
        outputMessage{12}   = ' ';
    case 'E1'
        % Error 1, email cannot be sent
        outputMessage{1}    = 'Email could not be sent!';
        outputMessage{2}    = ' ';
        outputMessage{3}    = ' ';
    case 'E2'
        %Error 2 image could not be read
        outputMessage{1}    = 'The format of the image could not be read';
        outputMessage{2}    = ' ';
        outputMessage{3}    = ' ';
    case 'E3'
        %Error 3 email of user not understood
        outputMessage{1}    = 'The email of the user could not be read';
        outputMessage{2}    = ' ';
        outputMessage{3}    = ' ';
    case 'E4'
        %Error 4 subroutine not recognised
        outputMessage{1}    = 'The subroutine was not recognised.';
        outputMessage{2}    = ' ';
        outputMessage{3}    = ' ';
    case 'E5'
        %Any other error
        outputMessage{1}    = 'There was an unrecognised error.';
        outputMessage{2}    = ' ';
        outputMessage{3}    = ' ';
    case 'EVT'
        %Any other error
        outputMessage{1}    = 'There was an error in the Vessel Tracing subroutine.';
        outputMessage{2}    = ' ';
        outputMessage{3}    = ' ';
    case 'EME'
        %Any other error
        outputMessage{1}    = 'There was an error in the Channel Merging subroutine.';
        outputMessage{2}    = ' ';
        outputMessage{3}    = ' ';
    case 'EMI'
        %Any other error
        outputMessage{1}    = 'There was an error in the Migration Measurement subroutine.';
        outputMessage{2}    = ' ';
        outputMessage{3}    = ' ';
    case 'ESH'
        %Any other error
        outputMessage{1}    = 'There was an error in the Shading subroutine.';
        outputMessage{2}    = ' ';
        outputMessage{3}    = ' ';

        
        
        
end
