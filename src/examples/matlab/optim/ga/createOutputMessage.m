function outputMessage = createOutputMessage(caseRoutine,extraData)


switch caseRoutine
    
    case 'GA'
        if exist('extraData','var')
            outputMessage{1}    = 'The image with heart sprouts has been quantified. Ratio is Sprouts / Total.';
            outputMessage{3}    = strcat('minimum obtained:',      num2str(extraData.bestpar));
            outputMessage{4}    = strcat('corresponding value by f:',      num2str(extraData.numelbestnewpop));
            outputMessage{5}    = strcat('evaluation number      = ',      num2str(extraData.evaluationnumber));
            outputMessage{6}    = ' ';
        end        
    
    case 'E1'
        % Error 1, email cannot be sent
        outputMessage{1}    = 'Email could not be sent!';
        outputMessage{2}    = ' ';
        outputMessage{3}    = ' ';
    case 'E2a'
        %Error 2 image could not be read
        outputMessage{1}    = 'Error in the first part of the iome E2a';
        outputMessage{2}    = ' ';
        outputMessage{3}    = ' ';
     case 'E2b'
        %Error 2 image could not be read
        outputMessage{1}    = 'E2b';
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
    case 'ESE'
        %Any other error
        outputMessage{1}    = 'There was an error in the Endothelial Cell segmentation subroutine.';
        outputMessage{2}    = ' ';
        outputMessage{3}    = ' ';


        
        
        
end
