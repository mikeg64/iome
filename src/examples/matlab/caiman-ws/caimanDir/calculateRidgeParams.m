function [networkProperties,dataOut3,dataOut4]=calculateRidgeParams(finalRidges,finalStats,dataIn)



[rows,cols,levs]                        = size(finalRidges); %#ok<NASGU>


%
if ~exist('pixCalibration','var'); pixCalibration=1.75; end
%%
numRidges                               = size(finalStats,1);
top10                                   = max(1,numRidges-9):numRidges;
top50                                   = max(1,numRidges-49):numRidges-10;

indexTop10                              = finalStats(top10,4);
indexTop50                              = finalStats(top50,4);

% to calculate the CORRECT length, get the perimeter of an area, as the area is actually just the
% distance over one of the sides, it does not take into account the slope
fRidges2d                               = sum(finalRidges,3);
actualLength                            = regionprops(fRidges2d,'perimeter','area');

finalStats(:,2)                         = ceil([actualLength(1:numRidges).Perimeter]/2);

%% Final Stats from the image
%Number of vessels
numLongVessels                                  = sum(finalStats(:,2)>20);
totLength                                       = sum(finalStats(:,2));

networkProperties.numVessels                    = numRidges;
networkProperties.totLength                     = sum(finalStats(:,2));
networkProperties.avDiameter                    = mean(finalStats(:,5));
networkProperties.avLength                      = mean(finalStats(:,2));

networkProperties.totLength_top10               = sum(finalStats(indexTop10,2));
networkProperties.avDiameter_top10              = mean(finalStats(indexTop10,5));
networkProperties.avLength_top10                = mean(finalStats(indexTop10,2));


networkProperties.numLongVessels                = numLongVessels;
networkProperties.numVesselsPerArea_um2         = numRidges/(rows*pixCalibration)/(cols*pixCalibration);
networkProperties.numLongVesselsPerArea_um2     = numLongVessels/(rows*pixCalibration)/(cols*pixCalibration);


%Length of vessels
top50length                                     = mean(finalStats(finalStats([top10 top50],4),2));
networkProperties.avLengthTop_um                = pixCalibration*top50length;
networkProperties.totLengthPerArea_um2          = totLength/rows/cols/pixCalibration;

%width of vessels
top50width                                      = mean(finalStats(finalStats([top10 top50],4),5));
networkProperties.avDiameterTop_um              = pixCalibration*top50width;

%Covered area mask for all vessels
[relAreaCovered,dataOut3]                       = vesselAreaMask(finalRidges,finalStats,dataIn);
networkProperties.relAreaCovered                = relAreaCovered;

if nargout>2
    %Covered area mask for top 50 vessels
    if numRidges>50
        %indexStats                                  = finalStats(max(1,numRidges-49):numRidges,4);
        %indexStats(indexStats<1)                    = [];
        %finalRidges                                 = bwlabeln(ismember(finalRidges,[top10 top50])>0);%.*finalRidges;
        [relAreaCoveredtop50,dataOut4]              = vesselAreaMask(finalRidges,finalStats,dataIn,[indexTop10; indexTop50]);
        networkProperties.relAreaCoveredtop50       = relAreaCoveredtop50;
    else
        dataOut4                                    = dataOut3;
        networkProperties.relAreaCoveredtop50       = relAreaCovered;
    end
    
end




