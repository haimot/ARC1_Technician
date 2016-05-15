%----------------------------------------------
%   SERVICE_READ_SCRIPT_DATA_RD
%
%
%   1 - Read main_config_message
%   2 - Save sensor data in text file
%   3 - save config parameters in text file
%   4 - Read RD map file
%   
%   Alon Slapak17.11.2014
%
%   Improvements:
%   Ronen: read RD map instead of raw samples
%
%
%----------------------------------------------

%-------------------------------------------------
% Extruct MAIN_config_message values
%-------------------------------------------------
MAIN_config_message = double(MAIN_config_message);
Profile_AD9910A = MAIN_config_message(1);
Profile_AD9910B = MAIN_config_message(2);
chip_length_AD9910A = MAIN_config_message(3);
chip_length_AD9910B = MAIN_config_message(4);
IF_SELECT_TX1 = MAIN_config_message(5);
IF_SELECT_TX2 = MAIN_config_message(6);
IF_SELECT_TX3 = MAIN_config_message(7);
IF_SELECT_PROBE = MAIN_config_message(8);
IO_UPDATE_rate = MAIN_config_message(9);
TX_ON1 = MAIN_config_message(10);
TX_ON2 = MAIN_config_message(11);
TX_ON3 = MAIN_config_message(12);
PROBE_ON = MAIN_config_message(13);
TX_LO_TR = MAIN_config_message(14);
ANT_SAMPLE_SELECT = MAIN_config_message(15);
ATTN_TX1 = MAIN_config_message(16);
ATTN_TX2 = MAIN_config_message(17);
ATTN_TX3 = MAIN_config_message(18);
ATTN_RX1 = MAIN_config_message(19);
ATTN_RX2 = MAIN_config_message(20);
ATTN_RX3 = MAIN_config_message(21);
ATTN_RX4 = MAIN_config_message(22);
AD9910_Set_aux_dac_A = MAIN_config_message(23);
AD9910_Set_aux_dac_B = MAIN_config_message(24);
Number_of_buffers = MAIN_config_message(25);
Buffer_length = MAIN_config_message(26);
FIFO_length = MAIN_config_message(27);
IO_UPDATE_ON = MAIN_config_message(28);
MODE = MAIN_config_message(29);
%-------------------------------------------------
% Parameters
%-------------------------------------------------
PCIE_NUMBER_PULSES  = Number_of_buffers;
PCIE_BUFFSIZE       = Buffer_length;
SIZE                = PCIE_BUFFSIZE*PCIE_NUMBER_PULSES*4;
Fs                  = 50e6;
%----------------------------------------------
%   Files & Folders
%----------------------------------------------
CurrentDir   = pwd;
ResultsDir = LOG_path;
ResultsFile = SAMPLES_file;
SavedConfigFile = 'samples.ini';
if ~exist(ResultsDir,'dir'),
    eval(['mkdir ' ResultsDir]);
end;
eval(['cd ' ResultsDir]);
%-------------------------------------------------
%   Save SENSOR data
%-------------------------------------------------
fid = fopen('SENSOR.txt','wt');
fprintf(fid,'YAW = %f\n',SENSOR_data(1));
fprintf(fid,'PITCH = %f\n',SENSOR_data(2));
fprintf(fid,'ROLL = %f\n',SENSOR_data(3));
fprintf(fid,'Latitude = %f\n',SENSOR_data(4));
fprintf(fid,'Longitude = %f\n',SENSOR_data(5));
fprintf(fid,'Altitude = %f\n',SENSOR_data(6));
fprintf(fid,'VelocityX = %f\n',SENSOR_data(7));
fprintf(fid,'VelocityY = %f\n',SENSOR_data(8));
fprintf(fid,'VelocityZ = %f\n',SENSOR_data(9));
fprintf(fid,'AccelX = %f\n',SENSOR_data(10));
fprintf(fid,'AccelY = %f\n',SENSOR_data(11));
fprintf(fid,'AccelZ = %f\n',SENSOR_data(12));
fprintf(fid,'AngularRateX = %f\n',SENSOR_data(13));
fprintf(fid,'AngularRateY = %f\n',SENSOR_data(14));
fprintf(fid,'AngularRateZ = %f\n',SENSOR_data(15));
fprintf(fid,'time = %f\n',SENSOR_data(16));
fprintf(fid,'AttUncertainty = %f\n',SENSOR_data(17));
fprintf(fid,'PosUncertainty = %f\n',SENSOR_data(18));
fprintf(fid,'VelUncertainty = %f\n',SENSOR_data(19));
fprintf(fid,'ROW_YAW = %f\n',SENSOR_data(20));
fprintf(fid,'ROW_PITCH = %f\n',SENSOR_data(21));
fprintf(fid,'ROW_ROLL = %f\n',SENSOR_data(22));
fclose(fid);
%-------------------------------------------------
%   Save parameters file
%-------------------------------------------------
fid = fopen('config.ini','wt');
fprintf(fid,'Profile_AD9910A=%d\n',Profile_AD9910A);
fprintf(fid,'Profile_AD9910B=%d\n',Profile_AD9910B);
fprintf(fid,'chip_length_AD9910A=%d\n',chip_length_AD9910A);
fprintf(fid,'chip_length_AD9910B=%d\n',chip_length_AD9910B);
fprintf(fid,'IF_SELECT_TX1=%d\n',IF_SELECT_TX1);
fprintf(fid,'IF_SELECT_TX2=%d\n',IF_SELECT_TX2);
fprintf(fid,'IF_SELECT_TX3=%d\n',IF_SELECT_TX3);
fprintf(fid,'IF_SELECT_PROBE=%d\n',IF_SELECT_PROBE);
fprintf(fid,'IO_UPDATE_rate=%d\n',IO_UPDATE_rate);
fprintf(fid,'TX_ON1=%d\n',TX_ON1);
fprintf(fid,'TX_ON2=%d\n',TX_ON2);
fprintf(fid,'TX_ON3=%d\n',TX_ON3);
fprintf(fid,'PROBE_ON=%d\n',PROBE_ON);
fprintf(fid,'TX_LO_TR=%d\n',TX_LO_TR);
fprintf(fid,'ANT_SAMPLE_SELECT=%d\n',ANT_SAMPLE_SELECT);
fprintf(fid,'ATTN_TX1=%d\n',ATTN_TX1);
fprintf(fid,'ATTN_TX2=%d\n',ATTN_TX2);
fprintf(fid,'ATTN_TX3=%d\n',ATTN_TX3);
fprintf(fid,'ATTN_RX1=%d\n',ATTN_RX1);
fprintf(fid,'ATTN_RX2=%d\n',ATTN_RX2);
fprintf(fid,'ATTN_RX3=%d\n',ATTN_RX3);
fprintf(fid,'ATTN_RX4=%d\n',ATTN_RX4);
fprintf(fid,'AD9910_Set_aux_dac_A=%d\n',AD9910_Set_aux_dac_A);
fprintf(fid,'AD9910_Set_aux_dac_B=%d\n',AD9910_Set_aux_dac_B);
fprintf(fid,'Number_of_buffers=%d\n',Number_of_buffers);
fprintf(fid,'Buffer_length=%d\n',Buffer_length);
fprintf(fid,'FIFO_length=%d\n',FIFO_length);
fprintf(fid,'MODE=%d\n',MODE);
fclose(fid);
%-------------------------------------------------
% Read file parameters
%-------------------------------------------------
fid = fopen(ResultsFile,'r');
Samples = fread(fid,SIZE*2,'double');
fclose(fid);
if (length(Samples) ~= SIZE*2)
    error('Sampled file is incorrect. Size mismatch.');
end;
Samples = Samples/2^15;
eval(['cd ' CurrentDir]);
%--------------------------------------------------
%               Processing file
%--------------------------------------------------
x_A = Samples(1:SIZE);
x_B = Samples(SIZE+1:2*SIZE);
buffer_A = reshape(x_A,PCIE_BUFFSIZE*4,PCIE_NUMBER_PULSES);
buffer_B = reshape(x_B,PCIE_BUFFSIZE*4,PCIE_NUMBER_PULSES);
buffer_H_left_I = buffer_A(1+2:2:2*PCIE_BUFFSIZE,:);
buffer_H_left_Q = buffer_A(2+2:2:2*PCIE_BUFFSIZE,:);
buffer_V_left_I = buffer_A(2*PCIE_BUFFSIZE+1+2:2:end,:);
buffer_V_left_Q = buffer_A(2*PCIE_BUFFSIZE+2+2:2:end,:);     
buffer_H_right_I = buffer_B(1+2:2:2*PCIE_BUFFSIZE,:);
buffer_H_right_Q = buffer_B(2+2:2:2*PCIE_BUFFSIZE,:);
buffer_V_right_I = buffer_B(2*PCIE_BUFFSIZE+1+2:2:end,:);
buffer_V_right_Q = buffer_B(2*PCIE_BUFFSIZE+2+2:2:end,:);
