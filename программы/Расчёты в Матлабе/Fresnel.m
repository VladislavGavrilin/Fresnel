function Fresnel
% Created 13.09.11 
% Performing calculations Fresnel=>Far.
%
% Spacing of reconstruction is the same as in nearFieldData.
%
% Near field must have 'x_amount' sections,
% In az-direction, 'y_amount' points are used for recontruction.
% When 'y_amount' is not available (at the edges), 
%   only available points are used.

nearFileName = 'design/projects/antenna5GHz_offset/near20_7_spacing2.0.dat';
farFileName = 'design/projects/antenna5GHz_offset/far.dat';
% nearFileName = 'design/projects/near60_5.dat';
% farFileName = 'design/projects/far.dat';
ampColumn = 3;  % index of amplitude column in the file
isEl = false;   % only to transpose the Design data (no corrections)

% d_x = 0;% shifts of rotation center
% d_y = 0;
% d_z = 0;

% D = 700; - antenna diameter
lambda = 6;  %3 wavelength
r = 2000; % frensel zone point taken
d_azimuthRad = 2*pi/180; %1.1 in radians
d_elevationRad = 2*pi/180;

tx = lambda/d_elevationRad; % x-length of antenna rectangle
ty = lambda/d_azimuthRad;

x_amount = 7; % amount of points in x-dimension of an array of angles
y_amount = 31;
x_amount2 = floor(x_amount/2);
y_amount2 = floor(y_amount/2);

% calculating k_mn
counter = 0;
k_x = zeros(1,x_amount);
for m = -(x_amount2):x_amount2
    counter = counter+1;
    k_x (counter) = k_n_old(2*pi/lambda,tx,r,inf,m);
end

counter = 0;
k_y = zeros(1,y_amount);
for n = -(y_amount2):y_amount2
    counter = counter+1;
    k_y (counter) = k_n_old(2*pi/lambda,ty,r,inf,n);
end

% Reading Fresnel data
[data angles] = ReadData(nearFileName,ampColumn,isEl);
if (size(data,2)~=x_amount)
    error('Wrong x_amount parameter, or wrong data file');
end
% [data, angles] = PhaseCorrection(data,angles);
azPointsCount = numel(angles);

% convolution along El-axis (x-axis)
dataAz = zeros(azPointsCount,1);
for i = 1:azPointsCount
    dataAz(i) = sum(data(i,:).*k_x);
%     dataAz(i) = sum(abs(data(i,:).*k_x)); % a test
end

% convolution along Az-axis (y-axis)
dataFar = zeros(size(dataAz));
for i = 1:azPointsCount
    ang = angles(i);
    for k = -y_amount2:y_amount2
        ang_k = ang + k*d_azimuthRad*180/pi;
        if ang_k<angles(1) || ang_k>angles(end)
            val = 0;
        else
            val = interp1(angles,dataAz,ang_k);
        end
        dataFar(i) = dataFar(i) + val*k_y(k+y_amount2+1);
%         dataFar(i) = dataFar(i) + abs(val*k_y(k+y_amount2+1)); % a test
    end
end

% plot reconstructed and direct RP
figure
rpFar = 20*log10(abs(dataFar));%angle(dataFar*exp(1j*120*pi/180))*180/pi;%
plot(angles,rpFar,'r')
% plot far zone
if ~isempty(farFileName)
    fData = importdata(farFileName);
    fData = fData.data;
    ampFarDesign = fData(:,ampColumn+1); %+2 - amp/phase
    angFarDesign = fData(:,1);
    if isEl==true
        angFarDesign = fData(:,2);
    end
    hold on
    plot(angFarDesign,ampFarDesign)
    hold off
end
legend('восстановленная ДН', 'расчётная ДН')
xlabel('Азимут, град.'), ylabel('КНД, дБи') % ylabel('Фаза, град.')
set(gca,'xlim',[-10,10])

% plot Fresnel and far
figure, plot(angFarDesign,ampFarDesign,'linewidth',1.5), hold all
leg{1} = 'ДН';
for i = x_amount2+1:x_amount
    num = i - x_amount2 - 1; % for legend
    rpFren = 20*log10(abs(data(:,i)));
%     rpFren = angle(data(:,i))*180/pi;
    plot(angles,rpFren)
    leg{num+2} = ['сечение ', num2str(num)];
end
hold off
legend(leg)
xlabel('Азимут, град.'), ylabel('КНД, дБи')
set(gca,'xlim',[-10,10])

% plot section of k_mn
figure
plot(-y_amount2:y_amount2,20*log10(abs(k_y)),'k-o')
xlabel('m'), ylabel('k_m, дБ')
% set(gca,'xlim',[-10,10])
% figure,plot(-y_amount2:y_amount2,angle(k_y)*180/pi,'k-o')


    function [data, angles] = PhaseCorrection(data,angles)
        % change phase of the data
        % to compensate the shift of rotation center
        
        for iEl = 1:x_amount
              % old one
            az = angles;
            el = (iEl-x_amount2-1)*d_elevationRad*180/pi;  % +beta0
            x=r*sind(el);
            y=r*cosd(el)*sind(az);
            z=r*cosd(el)*cosd(az);
            
            r_t=sqrt((x-d_x).^2+(y-d_y).^2+(z-d_z).^2);
            
            data(:,iEl) = data(:,iEl).*exp(-1j*2*pi*(r_t-r)/lambda);

%             % for z-shift
%             az = angles;
%             el = (iEl-x_amount2-1)*d_elevationRad*180/pi;  % +beta0
%             x=r*sind(el);
%             y=r*cosd(el)*sind(az);
%             z=r*cosd(el)*cosd(az)+d_z;
%             
%             r1 = r+d_z;
%             rToSmall = sqrt(x.*x+y.*y+z.*z);
%             r_t=-rToSmall+r1;
%             
%             data(:,iEl) = data(:,iEl).*exp(-1j*2*pi*(r_t-r)/lambda);
        end
    end

end

function [data angles] = ReadData(fileName,colNumber,isEl)
% Reading rp from Design input file
% colNumber is index of amplitude column in the file
% (hor=>3, vert=>5)

fData = importdata(fileName);
fData = fData.data;
angles = fData(:,1); %*(100/104)  -  for z-shift
amp = fData(:,colNumber);
phase = fData(:,colNumber+1);

% find length
for i=2:numel(angles)
    if angles(i)==angles(1)
        nEl = i-1;
        break;
    end
end
angles = angles(1:nEl);

amp = reshape(amp,nEl,numel(amp)/nEl);
amp = 10.^(amp/20);
phase = reshape(phase,nEl,numel(amp)/nEl);
phase = phase*pi/180;
data = amp.*exp(1j*phase);

if isEl==true
    % transpose
    data = data.';
    
    nAz = numel(fData(:,2))/nEl;
    angles = fData(:,2);
    angles = reshape(angles,[nEl nAz]);
    angles = angles(1,:).';
end

end

