%----------------------------------------------
%   CONT_POSITION_HIST
%
% Calculate accuracy of the SENSORS
%
%   Alon Slapak
%   4/11/2014
%
%----------------------------------------------
try
    format LONGG;
%----------------------------------------------
%   Files & Folders
%----------------------------------------------
Size_of_sensor_data     = 22;
Size_of_target_data     = 9;
CurrentDir              = pwd;
ResultsDir              = LOG_path;
ResultsFile             = SAMPLES_file;
if ~exist(ResultsDir,'dir'),
    error([ResultsDir ' does not exist.']);
end;
eval(['cd ' ResultsDir]);
%-------------------------------------------------
% Experiment directory
%-------------------------------------------------
if exist('expNum.txt','file'),
    load('expNum.txt');
else
    error('expNum.txt does not exist.');
end;
ExpDir = ['Exp_' num2str(expNum)];
%-------------------------------------------------
% Read file parameters
%-------------------------------------------------
eval(['cd ' ResultsDir '\' ExpDir])
fid = fopen(ResultsFile,'r');
counter = 1;
while (~feof(fid)),
    %-----------------------------
    % Read sensor data
    %-----------------------------
    temp = fread(fid, Size_of_sensor_data,'double');
    if (length(temp) == Size_of_sensor_data) 
        Sensor_data(counter,:) = temp;
    end;
    %-----------------------------
    % Read target data
    %-----------------------------
    temp = fread(fid, Size_of_target_data,'double');
    if (length(temp) == Size_of_target_data) 
        Target_data(counter,:) = temp;
    end;
    counter = counter + 1;
end
fclose(fid);
%==================================================
%==================================================
%
%
%               Formatting data
%
%
%=================================================
YAW             = Sensor_data(:,1);			% deg			Yaw angle relative to true north
PITCH           = Sensor_data(:,2);			% deg			Pitch angle relative to horizon
ROLL            = Sensor_data(:,3);			% deg			Pool angle relative to horizon
Latitude        = Sensor_data(:,4);			% deg			Estimated position in geodetic latitude
Longitude       = Sensor_data(:,5);			% deg			Estimated position in geodetic longitude
Altitude        = Sensor_data(:,6);			% m				Estimated height above ellipsoid. (WGS84)
VelocityX       = Sensor_data(:,7);			% m/s			Estimated velocity in NED frame. (North)
VelocityY       = Sensor_data(:,8);			% m/s			Estimated velocity in NED frame. (East)
VelocityZ       = Sensor_data(:,9);			% m/s			Estimated velocity in NED frame. (Down)
AccelX          = Sensor_data(:,10);			% m/s^2			Estimated acceleration in body frame. (X-axis)
AccelY          = Sensor_data(:,11);			% m/s^2			Estimated acceleration in body frame. (Y-axis)
AccelZ          = Sensor_data(:,12);			% m/s^2			Estimated acceleration in body frame. (Z-axis)
AngularRateX    = Sensor_data(:,13);           % rad/s			Estimated angular rate in body frame. (X-axis)
AngularRateY    = Sensor_data(:,14);           % rad/s			Estimated angular rate in body frame. (Y-axis)
AngularRateZ    = Sensor_data(:,15);           % rad/s			Estimated angular rate in body frame. (Z-axis)
time            = Sensor_data(:,16);			% sec			GPS time of week in seconds.
AttUncertainty  = Sensor_data(:,17);           % deg			Uncertainty in attitude estimate.
PosUncertainty  = Sensor_data(:,18);           % m				Uncertainty in position estimate.
VelUncertainty  = Sensor_data(:,19);           % m/s			Uncertainty in velocity estimate.
ROW_YAW         = Sensor_data(:,20);			% deg			Yaw angle 
ROW_PITCH       = Sensor_data(:,21);			% deg			Pitch angle 
ROW_ROLL        = Sensor_data(:,22);			% deg			Pool angle 

position_H      = Target_data(:,1);
position_V      = Target_data(:,2);
DOA_H           = Target_data(:,4);
DOA_V           = Target_data(:,5);
polarization_H  = Target_data(:,6);
polarization_V  = Target_data(:,7);
velocity_H      = Target_data(:,8);
velocity_V      = Target_data(:,9);


%==================================================
%
%
%               Processing data
%
%
%=================================================
%......................................
%               Attitude
%.......................................
Fig = figure('units','normalized','outerposition',[0 0 1 1]);
set(Fig,'WindowStyle','docked')

subplot(131);
plot(time-time(1),ROW_YAW);
xlabel('Time [Sec]');
ylabel('[Degs]')
title({'YAW';['Mean = ' num2str(mean(ROW_YAW)) ', std = ' num2str(std(ROW_YAW))]});
subplot(132);
plot(time-time(1),ROW_PITCH);
xlabel('Time [Sec]');
ylabel('[Degs]')
title({'PITCH';['Mean = ' num2str(mean(ROW_PITCH)) ', std = ' num2str(std(ROW_PITCH))]});
subplot(133);
plot(time-time(1),ROW_ROLL);
xlabel('Time [Sec]');
ylabel('[Degs]')
title({'ROLL';['Mean = ' num2str(mean(ROW_ROLL)) ', std = ' num2str(std(ROW_ROLL))]});

eval(['cd ' ResultsDir '\' ExpDir])
saveas(Fig,'Track_Attitude.fig' ,'fig');
eval(['cd ' CurrentDir]);

%......................................
%               GPS
%.......................................
Fig = figure('units','normalized','outerposition',[0 0 1 1]);
set(Fig,'WindowStyle','docked')

subplot(131);
plot(time-time(1),Latitude);
xlabel('Time [Sec]');
ylabel('[km]')
title({'Latitude';['Mean = ' num2str(mean(Latitude)) ', std = ' num2str(std(Latitude))]});
subplot(132);
plot(time-time(1),Longitude);
xlabel('Time [Sec]');
ylabel('[km]')
title({'Longitude';['Mean = ' num2str(mean(Longitude)) ', std = ' num2str(std(Longitude))]});
subplot(133);
plot(time-time(1),Altitude);
xlabel('Time [Sec]');
ylabel('[m]')
title({'Altitude';['Mean = ' num2str(mean(Altitude)) ', std = ' num2str(std(Altitude))]});

eval(['cd ' ResultsDir '\' ExpDir])
saveas(Fig,'Track_GPS.fig' ,'fig');
eval(['cd ' CurrentDir]);

%......................................
%               Velocity
%.......................................
Fig = figure('units','normalized','outerposition',[0 0 1 1]);
set(Fig,'WindowStyle','docked')

subplot(131);
plot(time-time(1),VelocityX);
xlabel('Time [Sec]');
ylabel('[m/Sec]')
title({'VelocityX';['Mean = ' num2str(mean(VelocityX)) ', std = ' num2str(std(VelocityX))]});
subplot(132);
plot(time-time(1),VelocityY);
xlabel('Time [Sec]');
ylabel('[m/Sec]')
title({'VelocityY';['Mean = ' num2str(mean(VelocityY)) ', std = ' num2str(std(VelocityY))]});
subplot(133);
plot(time-time(1),VelocityZ);
xlabel('Time [Sec]');
ylabel('[m/Sec]')
title({'VelocityZ';['Mean = ' num2str(mean(VelocityZ)) ', std = ' num2str(std(VelocityZ))]});

eval(['cd ' ResultsDir '\' ExpDir])
saveas(Fig,'Track_Velocity.fig' ,'fig');
eval(['cd ' CurrentDir]);


%==================================================
%==================================================
%
%
%      END OF  Processing data
%
%
%==================================================
%==================================================
catch err
    Error_message = err.message
    Error_line = err.stack.line
end
