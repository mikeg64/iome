function [finalRidges,finalStats,networkProperties,dataOut,dataOut2,dataOut3,dataOut4] =  scaleSpaceLowMem(dataIn,scaleSpaceRange,pixCalibration)
%function finalRidges,finalStats,networkProperties,dataOut,dataOut2] = scaleSpace(dataIn,scaleSpaceRange,pixCalibration)
%------- A scale space analysis of ridges after Lindeberg's algorithm
%------- VARARGIN   :   dataIn              = image to be analysed for ridges on scale space
%-------                scaleSpaceRange     = the scales to process, a good analysis for vessels is (1:38)
%-------                pixCallibration     = used to calibrate the pixels to meters 1.75 for x 20
%------- ARGOUT     :   finalRidges         = data reduced in dimensions by uniform pyramid
%-------                finalStats          = data labelled from the threshold and small regions removed
%-------                networkProperties   = [1 Saliency 2 Length 3 Width (scale) 4 index Saliency(after ranking) 5 2.4*Width (calibrated) ]
%-------                dataOut             = original image with the ridges overlaid, top 10 dark green, top 40 light green
%-------                dataOut2            = idem but all ridges in black

%------ no input data is received, error -------------------------
if nargin<1; help scaleSpace;  finalRidges=[]; return; end;

%% Pre-processing of the image to enhance the saturation channel of a H,S,V, version of the original image
% usual dimension check
[rows,cols,levs]                        =   size(dataIn);

%correction of background
%[dataRGB_EQ]                            = shadingCorrection(dataIn);
dataRGB_EQ                              = dataIn;



%keep the input data for the final image overlay,
%the 255- is used to obtain the DARK ridges
if levs>1;
    dataOut                             = dataIn(2:end-1,2:end-1,:);
    dataIn                              = rgb2gray(uint8(255-dataRGB_EQ));
else
    dataOut                             = 255-dataRGB_EQ(2:end-1,2:end-1,:);
end

%selection of the Scale Space Range
if ~exist('scaleSpaceRange','var');     scaleSpaceRange= 1:30; end
sizeScaleSpace                          = length(scaleSpaceRange);

dataIn                                  = double(dataIn);

%clear the noise from the edges with a median filter on the values that are NOT within 0.2-99.8%
dataIn                                  = removeImageOutliers(dataIn);

%% Generate Scale space
% For each position in the scale scale range, generate a gaussian filter with the corresponding standard deviation.
% Apply the gaussian to the input data to create a Low pass version of the original imae, the stack of results
% corresponds to the scale Space of the image. scaleSpaceRange corresponds to the STANDARD DEVIATION
%
%  L_x3(rows,cols-1,sizeScaleSpace)       = 0;
% L_xx3(rows,cols-2,sizeScaleSpace)       = 0;
%  L_y3(rows-1,cols,sizeScaleSpace)       = 0;
% L_yy3(rows-2,cols,sizeScaleSpace)       = 0;
% L_xy3(rows-1,cols-1,sizeScaleSpace)     = 0;


disp('          Generate Scale Space');
disp('          Calculate derivatives in the gradient direction');

disp('          Generate Ridge Surfaces');
N_norm_L(rows,cols,sizeScaleSpace) =0;
for k= 1:sizeScaleSpace
    % %%
    kk=8;
    % generate first the gaussian filter according to the scale (STD) and the scaleSpace
    filtg                               =  gaussF(kk*scaleSpaceRange(k),kk*scaleSpaceRange(k),1,scaleSpaceRange(k),scaleSpaceRange(k),1);
    % Calculate spatial derivatives of scale space through a convolution with the derived filter
    L_scaleSpace                        = imfilter(dataIn,filtg   ,'replicate','conv'); %#ok<AGROW>
    L_x3                                = diff(L_scaleSpace,1,2);
    L_xx3                               = diff(L_x3        ,1,2);
    L_y3                                = diff(L_scaleSpace,1,1);
    L_yy3                               = diff(L_y3        ,1,1);
    L_xy3                               = diff(L_x3        ,1,1);


    %compensate the differences in sizes by replicating first/last column/row

    L_x (:,2:cols)                      = L_x3(:,:);
    L_x (:,1)                           = L_x (:,2);

    L_xx(:,2:cols-1)                    = L_xx3;
    L_xx(:,1)                           = L_xx3(:,1);
    L_xx(:,cols)                        = L_xx3(:,end); %#ok<AGROW>

    L_y (2:rows,:)                      = L_y3;
    L_y (1,:)                           = L_y(2,:);

    L_yy(2:rows-1,:)                    = L_yy3;
    L_yy(1,:)                           = L_yy3(1,:);
    L_yy(rows,:)                        = L_yy3(end,:); %#ok<AGROW>

    L_xy(2:rows,2:cols)                 = L_xy3;
    L_xy(1,:)                           = L_xy(2,:);
    L_xy(:,1)                           = L_xy(:,2);

    L_xy2(:,:)                          = L_xy(:,:).^2;


    % the scale parameter "t" on the papers, corresponds to the VARIANCE to obtain proportional values square scaleSpaceRange


    scaleParam                          = repmat((scaleSpaceRange(k)).^2,[rows cols 1]);

    %% Calculate derivatives in the gradient direction  equations 37, 38

    delta=1e-10;

    denomBeta                               = sqrt(((L_xx - L_yy ).^2) + 4*L_xy2 );
    denomBeta(denomBeta==0)                 = delta;
    cosBeta2                                =(0.5*(1+((L_xx  - L_yy )./denomBeta ) ));
    sinBeta                                 = sign(L_xy ).*sqrt((0.5*(1-((L_xx  - L_yy )./denomBeta ) )));

    L_p                                     = sinBeta.*(L_x) - (sqrt(cosBeta2)).*L_y;
    L_q                                     = (sqrt(cosBeta2)).*(L_x) + sinBeta.*L_y;


    L_pp                                    = ((sinBeta).^2).*L_xx +   cosBeta2.*L_yy     - 2*(sqrt(cosBeta2)).*sinBeta.*L_xy;
    L_qq                                    =   cosBeta2.*L_xx     + ((sinBeta).^2).*L_yy + 2*(sqrt(cosBeta2)).*sinBeta.*L_xy;


    %% equation 41

    L_pq                                    = (sqrt(cosBeta2)).*sinBeta.*((L_xx - L_yy)) - (cosBeta2  - ((sinBeta).^2)).*L_xy; %#ok<NASGU>

    %comparison of the absolute values of L_pp and L_qq
    Lqq_ge_Lpp                              = (abs(L_qq)>=abs(L_pp));
    Lpp_ge_Lqq                              = (abs(L_pp)>=abs(L_qq));


    %% Aproximate to Zero
    % The process requires the derivatives to be equal to zero (a maximum or a minimum) and the
    % second derivative to be negative (a maximum) BUT the numerical method does not reaches this level of precision,
    % therefore the level of zero is determined from the zero cross from positive to negative
    % % Calculate regions near zero or lower than zero
    L_p_NearZero                            = zerocross((L_p>0)-0.5);  %#ok<AGROW>
    L_q_NearZero                            = zerocross((L_q>0)-0.5); %#ok<AGROW>

    %% Unwrapping of the Angles!!!!
    % A VERY important issue arises with the angles calculated (sinBeta, cosBeta) in which the angles may
    % generate a false zero crossing, while -0.3 -0.2 -0.1 0 0.1 0.2 ... is a real case of zero crossing, it
    % may happen that the angle grows out of bounds 0.75 0.85 0.95  -0.95 -0.85 and it was still growing.
    % Just detect those changes and remove the zero crossings
    L_p_x                                   = abs(diff(L_p,1,2))>0.4;
    L_p_y                                   = abs(diff(L_p,1,1))>0.4;
    L_p_noRidge                             = zeros(rows,cols,1);
    L_p_noRidge(1:end-1,:)                  = L_p_y;
    L_p_noRidge(:,1:end-1)                  = L_p_noRidge(:,1:end-1)|L_p_x;
    L_p_noRidge                             = imdilate(L_p_noRidge,ones(2));
    L_p_NearZero                            = (L_p_NearZero&(1-L_p_noRidge));

    L_q_x                                   = abs(diff(L_q,1,2))>0.4;
    L_q_y                                   = abs(diff(L_q,1,1))>0.4;
    L_q_noRidge                             = zeros(rows,cols,1);
    L_q_noRidge(1:end-1,:)                  = L_q_y;
    L_q_noRidge(:,1:end-1)                  = L_q_noRidge(:,1:end-1)|L_q_x;
    L_q_noRidge                             = imdilate(L_q_noRidge,ones(2));
    L_q_NearZero                            = (L_q_NearZero&(1-L_q_noRidge));


    %%
    L_pp_negative                           = (L_pp<0);
    L_qq_negative                           = (L_qq<0);



    %% Calculate Ridges Eq 42
    ridges1                                 = (L_p_NearZero&L_pp_negative&Lpp_ge_Lqq);
    ridges2                                 = (L_q_NearZero&L_qq_negative&Lqq_ge_Lpp);

    %clear L_p* L_q*  Lpp_* Lqq_*% L_y*


    %% Calculate influence of eigen matrices on ridges and remove isolated pixels (in a single level)

    ridgesInScale                           = ridges1(2:rows-1,2:cols-1) + ridges2(2:rows-1,2:cols-1);
    ridgeSurface(:,:,k)                     = bwmorph(ridgesInScale,'clean') ; %#ok<AGROW>

    %clear ridgesInScale


    %% For the strength of the Ridges the following norms are calculated (eqs 50, 51 Lindeberg Edge Ridge)
    N_norm_L(:,:,k)                         = (scaleParam.^(3.5)).*( ((L_xx + L_yy).^2).*(((L_xx - L_yy).^2) + 4*L_xy2 ))  ;



end


%% Label ridges to remove the smallest ones those with less than 25 voxels (over several scales)
[ridgeSurfaceL]                         = bwlabeln(ridgeSurface);

%clear ridgeSurface ridges1 ridges2 ridges3 ridges4

propsRidges                             = regionprops(ridgeSurfaceL,'Area');
ridgeSurfaceL2                          = ismember(ridgeSurfaceL,find([propsRidges.Area] > 2));

%clear ridgeSurfaceL
%clear L_xx L_yy L_xy2  numerBeta









clear L_scaleSpace
clear filtg* L_*3

%%  *A* Maximum value over scale, not just the highest value
% and the derivatives with respect to scaleinstead of eq 44 just get max!!!
disp('          Calculate Ridge Strength');


%% Find Maxima over the Norm that determines the ridge strength

N_ridgeStrength(rows,cols,sizeScaleSpace) =0;

% %to avoid maxima due to noise, remove everything that is less than 1/100 of max
maxN_norm_L                             = repmat(max(N_norm_L,[],3),[1 1 sizeScaleSpace]) ;
N_norm_L(N_norm_L<(maxN_norm_L/100))    = 0;

clear maxN_norm_L
%%
delta                                   = 1e-10;
% first and second derivatives
N_norm_L_t                              = diff(N_norm_L,1,3);
N_norm_L_tt                             = diff(N_norm_L_t,1,3);
%find the zero crossings
tempN_norm                              =-0.5+(N_norm_L_t>0)+delta;
N_norm_L_tZero                          = abs((sign(tempN_norm(:,:,1:end-1))-sign(tempN_norm(:,:,2:end))));
%to be a maximum the second derivative must be negative
N_ridgeStrength(:,:,2:sizeScaleSpace-1) = N_norm_L_tZero.*(N_norm_L_tt<0);
%%
clear tempN_norm N_norm_L_tZero N_norm_L_tt N_norm_L_t


%% Remove double maxima, keep the place where the norm in bigger

N_norm_L_Strength                       = N_norm_L.*N_ridgeStrength/2;
%add delta to last level to avoid a maximum in the lowest level
N_norm_L_Strength(:,:,sizeScaleSpace)   = N_norm_L_Strength(:,:,sizeScaleSpace)+delta;

[maxVal_N_norm,maxPos_N_norm]           = max (N_norm_L_Strength,[],3);

for k9= 1:sizeScaleSpace
    N_ridgeStrength2(:,:,k9)             = (maxPos_N_norm==k9); %#ok<AGROW>

end


clear scaleParam max*_N_norm N_ridgeStrength N_norm_L_Strength
%% Calculate Ridge Strength
if pixCalibration==7
%    A_ridgeSurface (:,:,2:sizeScaleSpace-1) = ridgeSurfaceL2(:,:,3:end)&imdilate(N_ridgeStrength2(2:rows-1,2:cols-1,2:end-1),ones(3,3,3));
    A_ridgeSurface                          = ridgeSurfaceL2&imdilate(N_ridgeStrength2(2:rows-1,2:cols-1,:),ones(3,3,5));
    %A_ridgeSurface(1,1,sizeScaleSpace)=0;
else
    A_ridgeSurface                          = ridgeSurfaceL2&imdilate(N_ridgeStrength2(2:rows-1,2:cols-1,:),ones(3,3,3));
end
clear ridgeSurfaceL2 N_ridgeStrength2;
%%
%A_ridgeSurface=ridgeSurfaceL2&A_ridgeStrength(1:rows-3,2:cols-2,:);


%% Clean the RidgeSurface from the small ridges, those with areas less than 20 pixels (over all scales)

%before, dilate the surface to be labelled as some clear ridges may be unconnected by a pixel and
%otherwise would be removed
[A_ridgeSurfaceL]                       = bwlabeln(imdilate(A_ridgeSurface(:,:,1:end),ones(3,3,1)));
%now thin the labelled ridges level by level
for k10= 1:sizeScaleSpace
     A_ridgeSurfaceL1(:,:,k10)          = bwmorph(A_ridgeSurfaceL(:,:,k10)>0,'thin',3);%#ok<AGROW>
end
[A_ridgeSurfaceL1]                      = bwlabeln(A_ridgeSurfaceL1);


propsRidgesA                            = regionprops(A_ridgeSurfaceL1,'Area');
A_ridgeSurfaceL2                        = ismember(A_ridgeSurfaceL1,find([propsRidgesA.Area] > 10));
[A_ridgeSurfaceL3,numRidgesA3]          = bwlabeln(A_ridgeSurfaceL2(:,:,1:end));
%propsRidgesA3=regionprops(A_ridgeSurfaceL3,'Area');

clear A_ridgeSurface
clear A_ridgeSurfaceL
clear A_ridgeSurfaceL2

%% Flatten the ridge Surface as there may be a lot of elements that coincide over scale

scaleMatrix                             = repmat(permute(scaleSpaceRange,[1 3 2] )  ,[rows-2,cols-2, 1]);
A_ridgeSurfaceL4                        = zeros(size(A_ridgeSurfaceL3));

%
for counterRidge=1:numRidgesA3
    %counterRidge=147;
    %process each ridge individually, select ridges
    tempRidge                           = (A_ridgeSurfaceL3==counterRidge);
    %project to 2D
    tempRidgeProj                       = sum(tempRidge,3);
    %Find positions of the ridge in the 2D Projection
    [tempR,tempC,tempV]                 = find(tempRidgeProj); %#ok<NASGU>
    %ranges in columns and rows, this will ease the computation as the following steps
    %are not processed on the whole data set, but only the range
    R_range                             = max(1,min(tempR)-1):min(1+max(tempR),rows-2);
    C_range                             = max(1,min(tempC)-1):min(1+max(tempC),cols-2);
    R_rangeSize                         = size(R_range,2);
    C_rangeSize                         = size(C_range,2);
    %Blur the projected region and later thin it, this will remove extra pixels of a thick ridge
    tempRidgeProjG                      = (imfilter(tempRidgeProj(R_range,C_range),gaussF(5,5,1),'replicate'));
    tempRidgeProjT                      = bwmorph(tempRidgeProjG>0,'thin','inf');
    %brake connected ridges ???? Still unsure if this is correct, connected
    %ridges are actually 2 ridges, and if connected they can be much stronger than single ones
    %-------------------------------------------------------------------
    %%%%%%%%%%%%%%%%%%%% BranchPoints is the single most time consuming line, remove for the moment
    %-------------------------------------------------------------------

    %[BranchPoints1]         = BranchPoints(tempRidgeProjT);
    %tempRidgeProjT2           = bwmorph(tempRidgeProjT&(~BranchPoints1),'clean');
    tempRidgeProjT2                     = tempRidgeProjT;


    %dilate the Original ridge and project it to 2D this will be used to calculate
    %at which level the ridge is placed
    tempRidgeDil                        = imdilate(tempRidge(R_range,C_range,:),ones(3,3,3));
    tempRidgeDilProj                    = sum(tempRidgeDil,3);
    %remove zeros from computation (denominator later on)
    tempRidgeDilProj(tempRidgeDilProj==0)    = inf;
    %multiply with scaleMAtrix that keeps the scale at which the ridge occur
    tempRidgeDilProjW                   = sum(tempRidgeDil.*scaleMatrix(R_range,C_range,:),3);
    tempRidgeDilProjW                   = round(tempRidgeDilProjW./tempRidgeDilProj);

    tempRidgeDilProjW2                  = tempRidgeDilProjW.*tempRidgeProjT2;
    %
    %replace the ridge in its correct position and correct value
    %find position of NEW thinned ridge
    [indexTempRidgeFin]                 = find(tempRidgeDilProjW2);
    %the index is in 2D thus elevate at proper scale
    indexTemp2                          = (indexTempRidgeFin+ R_rangeSize*C_rangeSize*(tempRidgeDilProjW2(indexTempRidgeFin)-min(scaleSpaceRange)));
    % a temporary volume with same size as the ranges
    qq                                  = zeros(R_rangeSize,C_rangeSize,sizeScaleSpace);
    try
        qq(indexTemp2)                  = counterRidge;
    catch

    end
    %add the new ridge with what was there before
    A_ridgeSurfaceL4(R_range,C_range,:) = A_ridgeSurfaceL4(R_range,C_range,:)+qq;
    %
end

clear A_ridgeSurfaceL3


%%
[A_ridgeSurfaceL5,numRidgesA5]          = bwlabeln(A_ridgeSurfaceL4>0); %#ok<NASGU>
propsRidgesA5                           = regionprops(A_ridgeSurfaceL5,'Area');
A_ridgeSurfaceL5                        = ismember(A_ridgeSurfaceL5,find([propsRidgesA5.Area] > 15));



% For all those ridges that contain branches, break and remove small sections (up to 11 pixels) sequentially and
% finally break into sections so that no ridge contains branching points
[A_ridgeSurfaceL5,numRidgesA5]          = removeBranchRidges(A_ridgeSurfaceL5);

%[A_ridgeSurfaceL5,numRidgesA5]          = bwlabeln(A_ridgeSurfaceL5>0);
propsRidgesA5                           = regionprops(A_ridgeSurfaceL5,'Area');

clear A_ridgeSurfaceL4



%% Calculate Ridge Saliency Eqs 58-60 as the sum of the strength
disp('          Calculate Ridge Saliency');

if numRidgesA5==0
    %This is the case where no ridges were detected, fill with zeros and return
    dataOut2=dataOut;
    finalStats=[];
    finalRidges=[];
    networkProperties.numVessels                    = 0;
    networkProperties.totLength                     = 0;
    networkProperties.avDiameter                    = 0;
    networkProperties.avLength                      = 0;

    networkProperties.totLength_top10               = 0;
    networkProperties.avDiameter_top10              = 0;
    networkProperties.avLength_top10                = 0;

else
    %This is the case when Ridges WERE detected, Process
    ridgeSaliency(numRidgesA5)              = 0;
    ridgeWidth(numRidgesA5)                 = 0;
    %A_norm_Red                              = A_norm_L(1:rows-2,1:cols-2,:);
    A_norm_Red                              = N_norm_L(1:rows-2,1:cols-2,:);


    

    for counterRidge=1:numRidgesA5
        %process each ridge individually, select ridges
        tempRidge                           = (A_ridgeSurfaceL5==counterRidge);
        %project to 2D
        tempRidgeProj                       = sum(tempRidge,3);
        %Find positions of the ridge in the 2D Projection
        [tempR,tempC,tempV]                 = find(tempRidgeProj); %#ok<NASGU>
        %ranges in columns and rows, this will ease the computation as the following steps
        %are not processed on the whole data set, but only the range
        R_range                             = max(1,min(tempR)-1):min(1+max(tempR),rows-2);
        C_range                             = max(1,min(tempC)-1):min(1+max(tempC),cols-2);
        tempRidge2                          = tempRidge(R_range,C_range,:);
        tempSaliency                        = tempRidge2.*A_norm_Red(R_range,C_range,:);
        tempWidth                           = tempRidge2.*scaleMatrix(R_range,C_range,:);
        tempWidth2                          = tempWidth(find(tempWidth)); %#ok<FNDSB>
        ridgeSaliency(counterRidge)         = sum(tempSaliency(:));
        ridgeWidth(counterRidge)            = mean(tempWidth2(:));
    end
    
    ridgeLength                             = [propsRidgesA5.Area];
   
    ridgeWidthCalib                         = 2.4*ridgeWidth;
    %ridgesNotTooWide                        = (ridgeLength./(ridgeWidthCalib/2))>1;
    %[sortedSaliency,indexSaliency]          = (sort(ridgeSaliency(ridgesNotTooWide)));    
    [sortedSaliency,indexSaliency]          = (sort(ridgeSaliency));    
    
    
         

    disp('          Calculate Final Metrics');


    finalStats                              = [ridgeSaliency; ridgeLength; ridgeWidth; indexSaliency; ridgeWidthCalib]';
    
    %before determining the order of the saliency, Discard ALL ridges that are too short but very wide
    [finalRidges,finalStats]                = removeThickRidges(A_ridgeSurfaceL5,finalStats); 
    
    %remove all weak ridges, i.e. those with less than 5 in saliency
    
    finalRidges=bwlabeln(ismember(finalRidges,find(finalStats(:,1)>5)));
    finalStats(finalStats(:,1)<=5,:)=[];
    [sortedSaliency,indexSaliency]          = (sort(finalStats(:,1)));
    finalStats(:,4)=indexSaliency;
    
    %calculate the ridge parameters (av length, width, total length ...) and generate the mask of the area
    [networkProperties,dataOut3,dataOut4]   = calculateRidgeParams(finalRidges,finalStats,dataRGB_EQ);
     
    %generate the output images with the vessels overlaid
    [dataOut,dataOut2]                      = calculateDataOut(finalRidges,finalStats,dataOut);

    
    %%
%     numRidges                               = size(finalStats,1);
%     top10                                   = max(1,numRidges-9):numRidges;
%     top50                                   = max(1,numRidges-49):numRidges-10;
%     finalRidges_50                          = imdilate(sum(ismember(finalRidges,finalStats(top50,4)),3),ones(2));
%     finalRidges_10                          = imdilate(sum(ismember(finalRidges,finalStats(top10,4)),3),ones(3));
%     finalRidges_all                         = (repmat(sum(finalRidges,3),[1 1 3]))>0;
% 
%     %% Generate the Output image with the traces overlaid
% 
%     
%     
%     %dataOut2=dataOut;
%     if isa(dataOut,'uint8')
%         if levs>1;
%             dataOut(:,:,1)                  = dataOut(:,:,1).*uint8(1-finalRidges_10)  + uint8(finalRidges_10)*0.9*min(dataOut(:));
%             dataOut(:,:,2)                  = dataOut(:,:,2).*uint8(1-finalRidges_50)  + uint8(finalRidges_50)*1.1*max(dataOut(:));
%             dataOut2                        = dataOut;
%             dataOut2                        = dataOut2.*uint8(1-finalRidges_all)  ;
%         else
%             dataOut                         = dataOut.*uint8(1-finalRidges_10)  + uint8(finalRidges_10)*1.1*max(dataOut(:));
%             dataOut                         = dataOut.*uint8(1-finalRidges_50)  + uint8(finalRidges_50)*0.9*min(dataOut(:));
%             dataOut2                        = dataOut;
%             dataOut2                        = dataOut2.*uint8(1-finalRidges_all(:,:,1)) ;
%         end
%     else
%         if levs>1;
%             dataOut(:,:,1)                  = dataOut(:,:,1).*(1-finalRidges_10)  + (finalRidges_10)*0.9*min(dataOut(:));
%             dataOut(:,:,2)                  = dataOut(:,:,2).*(1-finalRidges_50)  + (finalRidges_50)*1.1*max(dataOut(:));
%             dataOut2                        = dataOut;
%             dataOut2                        = dataOut2.*uint8(1-finalRidges_all)  ;
%         else
%             dataOut                         = dataOut.*(1-finalRidges_10)  + (finalRidges_10)*1.1*max(dataOut(:));
%             dataOut                         = dataOut.*(1-finalRidges_50)  + (finalRidges_50)*0.9*min(dataOut(:));
%             dataOut2                        = dataOut;
%             dataOut2                        = dataOut2.*(1-finalRidges_all(:,:,1)) ;
%         end
%     end
    %% Final Stats from the image
    %Number of vessels
%     numLongVessels                                  = sum(finalStats(:,2)>20);
%     totLength                                       = sum(finalStats(:,2));
% 
%     networkProperties.numVessels                    = numRidges;
%     networkProperties.totLength                     = sum(finalStats(:,2));
%     networkProperties.avDiameter                    = mean(finalStats(:,5));
%     networkProperties.avLength                      = mean(finalStats(:,2));
% 
%     networkProperties.totLength_top10               = sum(finalStats(finalStats(top10,4),2));
%     networkProperties.avDiameter_top10              = mean(finalStats(finalStats(top10,4),5));
%     networkProperties.avLength_top10                = mean(finalStats(finalStats(top10,4),2));
% 
% 
%     networkProperties.numLongVessels                = numLongVessels;
%     networkProperties.numVesselsPerArea_um2         = numRidges/(rows*pixCalibration)/(cols*pixCalibration);
%     networkProperties.numLongVesselsPerArea_um2     = numLongVessels/(rows*pixCalibration)/(cols*pixCalibration);
% 
% 
%     %Length of vessels
%     top50length                                     = mean(finalStats(finalStats([top10 top50],4),2));
%     networkProperties.avLengthTop_um                = pixCalibration*top50length;
%     networkProperties.totLengthPerArea_um2          = totLength/rows/cols/pixCalibration;
% 
%     %width of vessels
%     top50width                                      = mean(finalStats(finalStats([top10 top50],4),5));
%     networkProperties.avDiameterTop_um              = pixCalibration*top50width;
%     
%     
%     networkProperties.relAreaCovered                = relAreaCovered;

end