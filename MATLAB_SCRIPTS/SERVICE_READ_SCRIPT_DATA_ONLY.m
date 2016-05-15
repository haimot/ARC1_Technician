%----------------------------------------------
%   SERVICE_READ_SCRIPT_DATA
%
%
%   Read samples file
%   
%   Alon Slapak17.11.2014
%
%   Improvements:
%
%
%----------------------------------------------

%-------------------------------------------------
% Parameters
%-------------------------------------------------
PCIE_NUMBER_PULSES  = 1;
PCIE_BUFFSIZE       = 1024;
SIZE                = PCIE_BUFFSIZE*PCIE_NUMBER_PULSES*4;
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
%            Read first buffer from file
%--------------------------------------------------
x_A = Samples(1:SIZE);
x_B = Samples(SIZE+1:2*SIZE);
buffer_A = reshape(x_A,PCIE_BUFFSIZE*4,PCIE_NUMBER_PULSES);
buffer_B = reshape(x_B,PCIE_BUFFSIZE*4,PCIE_NUMBER_PULSES);
buffer_H_left_I = buffer_A(1+4:4:end,:);
buffer_H_left_Q = buffer_A(2+4:4:end,:);
buffer_V_left_I = buffer_A(3+4:4:end,:);
buffer_V_left_Q = buffer_A(4+4:4:end,:);
buffer_H_right_I = buffer_B(1+4:4:end,:);
buffer_H_right_Q = buffer_B(2+4:4:end,:);
buffer_V_right_I = buffer_B(3+4:4:end,:);
buffer_V_right_Q = buffer_B(4+4:4:end,:);
