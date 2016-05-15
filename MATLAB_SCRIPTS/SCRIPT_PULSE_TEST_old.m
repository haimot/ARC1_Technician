%----------------------------------------------
%   SCRIPT SNR
%
%
%   1 - SNR + SFDR test
%   2 - Pulse test
%   3 - CAF
%
%----------------------------------------------
try
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
IO_UPDATE_rate = MAIN_config_message(8);
TX_ON1 = MAIN_config_message(9);
TX_ON2 = MAIN_config_message(10);
TX_ON3 = MAIN_config_message(11);
TX_LO_TR = MAIN_config_message(12);
SAMPLE_SEL = MAIN_config_message(13);
SAMPLE_ON_OFF = MAIN_config_message(14);
ATTN_TX1 = MAIN_config_message(15);
ATTN_TX2 = MAIN_config_message(16);
ATTN_TX3 = MAIN_config_message(17);
ATTN_RX1 = MAIN_config_message(18);
ATTN_RX2 = MAIN_config_message(19);
ATTN_RX3 = MAIN_config_message(20);
ATTN_RX4 = MAIN_config_message(21);
AD9910_Set_aux_dac_A = MAIN_config_message(22);
AD9910_Set_aux_dac_B = MAIN_config_message(23);
Number_of_buffers = MAIN_config_message(24);
Buffer_length = MAIN_config_message(25);
FIFO_length = MAIN_config_message(26);
IO_UPDATE_OFF = MAIN_config_message(27);
MODE = MAIN_config_message(28);
%-------------------------------------------------
% Parameters
%-------------------------------------------------
PCIE_NUMBER_PULSES  = Number_of_buffers;
PCIE_BUFFSIZE       = Buffer_length;
SIZE                = PCIE_BUFFSIZE*PCIE_NUMBER_PULSES*4;
Fs                  = 50e6;
NFFT                = 2048;
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
%    rearranging SAMPLES from workspace
%-------------------------------------------------
M = double(Samples);
if (length(M) ~= SIZE*2)
    error('Sampled file is incorrect. Size mismatch.');
end;
%-------------------------------------------------
% Experiment directory
%-------------------------------------------------
if exist('.\expNum.mat','file'),
    load expNum;
    expNum = expNum+1;
    save expNum expNum;
else
    expNum = 1;
    save expNum expNum;
end;
ExpDir = ['Exp_' num2str(expNum)];
if ~exist(ExpDir,'dir'),
    eval(['mkdir ' ExpDir]);
end;
%-------------------------------------------------
%   Save SAMPLES file
%-------------------------------------------------
eval(['cd ' ResultsDir '\' ExpDir])
save('Samples','M','-mat');
eval(['cd ' CurrentDir]);
%-------------------------------------------------
%   Save SENSOR data
%-------------------------------------------------
eval(['cd ' ResultsDir '\' ExpDir])
fid = fopen('SESNOR.dat','wt');
fprintf(fid,'YAW = %f\n',SENSOR_DATA(1));
fprintf(fid,'PITCH = %f\n',SENSOR_DATA(2));
fprintf(fid,'ROLL = %f\n',SENSOR_DATA(3));
fprintf(fid,'Latitude = %f\n',SENSOR_DATA(4));
fprintf(fid,'Longitude = %f\n',SENSOR_DATA(5));
fprintf(fid,'Altitude = %f\n',SENSOR_DATA(6));
fprintf(fid,'VelocityX = %f\n',SENSOR_DATA(7));
fprintf(fid,'VelocityY = %f\n',SENSOR_DATA(8));
fprintf(fid,'VelocityZ = %f\n',SENSOR_DATA(9));
fprintf(fid,'AccelX = %f\n',SENSOR_DATA(10));
fprintf(fid,'AccelY = %f\n',SENSOR_DATA(11));
fprintf(fid,'AccelZ = %f\n',SENSOR_DATA(12));
fprintf(fid,'AngularRateX = %f\n',SENSOR_DATA(13));
fprintf(fid,'AngularRateY = %f\n',SENSOR_DATA(14));
fprintf(fid,'AngularRateZ = %f\n',SENSOR_DATA(15));
fprintf(fid,'time = %f\n',SENSOR_DATA(16));
fprintf(fid,'AttUncertainty = %f\n',SENSOR_DATA(17));
fprintf(fid,'PosUncertainty = %f\n',SENSOR_DATA(18));
fprintf(fid,'VelUncertainty = %f\n',SENSOR_DATA(19));
fprintf(fid,'ROW_YAW = %f\n',SENSOR_DATA(20));
fprintf(fid,'ROW_PITCH = %f\n',SENSOR_DATA(21));
fprintf(fid,'ROW_ROLL = %f\n',SENSOR_DATA(22));
fclose(fid);
eval(['cd ' CurrentDir]);
%-------------------------------------------------
%   Save parameters file
%-------------------------------------------------
eval(['cd ' ResultsDir '\' ExpDir])
fid = fopen('config.ini','wt');
fprintf(fid,'Profile_AD9910A=%d\n',Profile_AD9910A);
fprintf(fid,'Profile_AD9910B=%d\n',Profile_AD9910B);
fprintf(fid,'chip_length_AD9910A=%d\n',chip_length_AD9910A);
fprintf(fid,'chip_length_AD9910B=%d\n',chip_length_AD9910B);
fprintf(fid,'IF_SELECT_TX1=%d\n',IF_SELECT_TX1);
fprintf(fid,'IF_SELECT_TX2=%d\n',IF_SELECT_TX2);
fprintf(fid,'IF_SELECT_TX3=%d\n',IF_SELECT_TX3);
fprintf(fid,'IO_UPDATE_rate=%d\n',IO_UPDATE_rate);
fprintf(fid,'TX_ON1=%d\n',TX_ON1);
fprintf(fid,'TX_ON2=%d\n',TX_ON2);
fprintf(fid,'TX_ON3=%d\n',TX_ON3);
fprintf(fid,'TX_LO_TR=%d\n',TX_LO_TR);
fprintf(fid,'SAMPLE_SEL=%d\n',SAMPLE_SEL);
fprintf(fid,'SAMPLE_ON_OFF=%d\n',SAMPLE_ON_OFF);
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
eval(['cd ' CurrentDir]);
%--------------------------------------------------
%               Processing file
%--------------------------------------------------
x_A = M(1:SIZE);
x_B = M(SIZE+1:2*SIZE);
x_A = x_A/2^15;
x_B = x_B/2^15;
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

%==================================================
%==================================================
%
%
%               Processing data
%
%
%==================================================
%==================================================

%----------------------------------------
%  General Plotting - Time domain
%----------------------------------------
FigPULSE = figure('units','normalized','outerposition',[0 0 1 1]);
set(FigPULSE,'WindowStyle','docked')

t = (0:size(buffer_H_right_I,1)-1);

subplot(221)
plot(t,buffer_H_left_I',t,buffer_H_left_Q')
legend('I_1','Q_1','Orientation','horizontal');legend('boxoff')
xlabel('[Samples]')
S0 = sprintf('CHA_1: Vpp = %1.2f',2*max(max(sqrt(buffer_H_left_I.^2+buffer_H_left_Q.^2))));
title(S0)
axis([-inf inf -1 1])
grid on

subplot(222)
plot(t,buffer_V_left_I',t,buffer_V_left_Q')
legend('I_2','Q_2','Orientation','horizontal');legend('boxoff')
xlabel('[Samples]')
S0 = sprintf('CHA_2: Vpp = %1.2f',2*max(max(sqrt(buffer_V_left_I.^2+buffer_V_left_Q.^2))));
title(S0)
axis([-inf inf -1 1])
grid on

subplot(223)
plot(t,buffer_H_right_I',t,buffer_H_right_Q')
legend('I_1','Q_1','Orientation','horizontal');legend('boxoff')
xlabel('[Samples]')
S0 = sprintf('CHB_1: Vpp = %1.2f',2*max(max(sqrt(buffer_H_right_I.^2+buffer_H_right_Q.^2))));
title(S0)
axis([-inf inf -1 1])
grid on

subplot(224)
plot(t,buffer_V_right_I',t,buffer_V_right_Q')
legend('I_2','Q_2','Orientation','horizontal');legend('boxoff')
xlabel('[Samples]')
S0 = sprintf('CHB_2: Vpp = %1.2f',2*max(max(sqrt(buffer_V_right_I.^2+buffer_V_right_Q.^2))));
title(S0)
axis([-inf inf -1 1])
grid on

eval(['cd ' ResultsDir '\' ExpDir])
saveas(FigPULSE,'Pulses.fig' ,'fig');
eval(['cd ' CurrentDir]);
%-------------------------------------------------
%    Sinc analysis - Range
%-------------------------------------------------
Sync_left = zeros(PCIE_NUMBER_PULSES,8);
Sync_right = zeros(PCIE_NUMBER_PULSES,8);
Sync = zeros(PCIE_NUMBER_PULSES,8);
IQ = zeros(PCIE_NUMBER_PULSES,8);
for k = 1:8,
    switch k,
        case 1
            temp = buffer_H_left_I;
        case 2
            temp = buffer_H_left_Q;
        case 3
            temp = buffer_V_left_I;
        case 4
            temp = buffer_V_left_Q;
        case 5
            temp = buffer_H_right_I;
        case 6
            temp = buffer_H_right_Q;
        case 7
            temp = buffer_V_right_I;
        case 8
            temp = buffer_V_right_Q;
    end;
    [~,kkk] = find(abs(temp') >= max(max(abs(temp)))*0.5);
    if (size(kkk,1) >= PCIE_NUMBER_PULSES),
        Sync_left(:,k)  =  kkk(1:PCIE_NUMBER_PULSES);
        Sync_right(:,k) =  kkk(end-PCIE_NUMBER_PULSES+1:end);
        
    else
        Sync_left(:,k) = ones(PCIE_NUMBER_PULSES,1);
        Sync_right(:,k) = ones(PCIE_NUMBER_PULSES,1);
    end;
    Sync(:,k) = 0.5*(Sync_right(:,k) + Sync_left(:,k));
    for p = 1:PCIE_NUMBER_PULSES,
        IQ(p,k) = temp(floor(Sync(p,k)),p);
        IQ(p,k) = floor(IQ(p,k)*1000)/1000;       % resolution of 3 digits.
    end;
    
end;

FigSYNC1 = figure('units','normalized','outerposition',[0 0 1 1]);
set(FigSYNC1,'WindowStyle','docked')

subplot(2,4,1)
hist(Sync(:,1));
axis([-inf inf -inf inf])
title('CH_A I1')
subplot(2,4,2)
hist(Sync(:,2));
axis([-inf inf -inf inf])
title('CH_A Q1')
subplot(2,4,3)
hist(Sync(:,3));
axis([-inf inf -inf inf])
title('CH_A I2')
subplot(2,4,4)
hist(Sync(:,4));
axis([-inf inf -inf inf])
title('CH_A Q2')
subplot(2,4,5)
hist(Sync(:,5));
axis([-inf inf -inf inf])
title('CH_B I1')
subplot(2,4,6)
hist(Sync(:,6));
axis([-inf inf -inf inf])
title('CH_B Q1')
subplot(2,4,7)
hist(Sync(:,7));
axis([-inf inf -inf inf])
title('CH_B I2')
subplot(2,4,8)
hist(Sync(:,8));
axis([-inf inf -inf inf])
title('CH_B Q2')

eval(['cd ' ResultsDir '\' ExpDir])
saveas(FigSYNC1,'Amplitude_SYNC.fig' ,'fig');
eval(['cd ' CurrentDir]);
%-------------------------------------------------
%    Sinc analysis - Phase I/Q
%-------------------------------------------------
FigSYNC2 = figure('units','normalized','outerposition',[0 0 1 1]);
set(FigSYNC2,'WindowStyle','docked')

for k = 1:8,
    subplot(2,4,k);
    hist(IQ(:,k));
    axis([-inf inf -inf inf]);
    switch k,
        case 1
            title('CH_A I1');
        case 2
            title('CH_A Q1')
        case 3
            title('CH_A I2')
        case 4
            title('CH_A Q2')
        case 5
            title('CH_B I1')
        case 6
            title('CH_B Q1')
        case 7
            title('CH_B I2')
        case 8
            title('CH_B Q2')
    end;
end;
eval(['cd ' ResultsDir '\' ExpDir])
saveas(FigSYNC2,'Amplitude_histograms.fig' ,'fig');
eval(['cd ' CurrentDir]);
%----------------------------------------
%  General Plotting - Frequency domain
%----------------------------------------
[H(1,:),W] = freqz(buffer_H_left_I(:,1)/PCIE_BUFFSIZE*2,1,NFFT,Fs);
[H(2,:),W] = freqz(buffer_H_left_Q(:,1)/PCIE_BUFFSIZE*2,1,NFFT,Fs);
[H(3,:),W] = freqz(buffer_V_left_I(:,1)/PCIE_BUFFSIZE*2,1,NFFT,Fs);
[H(4,:),W] = freqz(buffer_V_left_Q(:,1)/PCIE_BUFFSIZE*2,1,NFFT,Fs);
[H(5,:),W] = freqz(buffer_H_right_I(:,1)/PCIE_BUFFSIZE*2,1,NFFT,Fs);
[H(6,:),W] = freqz(buffer_H_right_Q(:,1)/PCIE_BUFFSIZE*2,1,NFFT,Fs);
[H(7,:),W] = freqz(buffer_V_right_I(:,1)/PCIE_BUFFSIZE*2,1,NFFT,Fs);
[H(8,:),W] = freqz(buffer_V_right_Q(:,1)/PCIE_BUFFSIZE*2,1,NFFT,Fs);
StartFindPeaks = 1;

SFDR = zeros(1,8);
SNR = zeros(1,8);
for k = 1:2:8,
    [PKS(k,:),LOCS(k,:)] = findpeaks(10*log10(abs(H(k,StartFindPeaks:end)).^2+abs(H(k+1,StartFindPeaks:end)).^2),'NPEAKS',30,'MINPEAKDISTANCE',37);
    LOCS(k,:) = LOCS(k,:) + StartFindPeaks -1;
    [P1(k,:),INDs(k,:)]  = sort(PKS(k,:),'descend');
    L1(k,:) = LOCS(k,INDs(k,:));
    SFDR(k) = P1(k,1)-P1(k,2);
    SNR(k) = P1(k,1)-max(P1(k,12:30));
end;
%......................................
%                        H
%.......................................
FigPULSE_H = figure('units','normalized','outerposition',[0 0 1 1]);
set(FigPULSE_H,'WindowStyle','docked')
%......................................
%          Frequency domain
%......................................
subplot(241)
plot(W,10*log10(abs(H(1,:)).^2+abs(H(2,:)).^2))
for k = 1:6,
    hold on;
    plot(W(L1(1,k+1)),P1(1,k+1),'*');
    text(W(L1(1,k+1)),P1(1,k+1)+10,num2str(k));
end;
hold on
line([W(1) W(end)],[mean(max(P1(1,12:30))) mean(max(P1(1,12:30)))],'LineStyle','--','Color','r');
xlabel('[Hz]')
ylabel('dB')
S0 = sprintf('H-Left: SNR %2.1f SFDR %2.1f',mean(SNR(1)),mean(SFDR(1)));
title(S0)
xlabel('[Hz]')
ylabel('dB')
grid on
axis([-inf,inf,-140, 0])

subplot(243)
plot(W,10*log10(abs(H(5,:)).^2+abs(H(6,:)).^2))
for k = 1:6,
    hold on;
    plot(W(L1(5,k+1)),P1(5,k+1),'*');
    text(W(L1(5,k+1)),P1(5,k+1)+10,num2str(k));
end;
hold on
line([W(1) W(end)],[mean(max(P1(5,12:30))) mean(max(P1(5,12:30)))],'LineStyle','--','Color','r');
S0 = sprintf('H-Right: SNR %2.1f SFDR %2.1f',mean(SNR(5)),mean(SFDR(5)));
title(S0)
xlabel('[Hz]')
ylabel('dB')
grid on
axis([-inf,inf, -140, 0])
%......................................
%   Time domain
%......................................
t = (0:length(buffer_H_right_I)-1);
subplot(425)
plot(t,buffer_H_left_I',t,buffer_H_left_Q')
S1 = sprintf('H-Left I');
S2 = sprintf('H-Left Q');
legend(S1,S2);legend('boxoff','Orientation','horizontal')
xlabel('[Samples]')
% S0 = sprintf('H-Left: Vpp = %1.2f',max(max(abs([buffer_H_left_I buffer_H_left_Q]))));
% title(S0)
axis([-inf inf -1 1])
grid on

t = (0:length(buffer_H_right_I)-1);
subplot(426)
plot(t,buffer_H_right_I',t,buffer_H_right_Q')
S1 = sprintf('H-Right I');
S2 = sprintf('H-Right Q');
legend(S1,S2);legend('boxoff','Orientation','horizontal')
xlabel('[Samples]')
% S0 = sprintf('H-Right: Vpp = %1.2f',max(max(abs([buffer_H_right_I buffer_H_right_Q]))));
% title(S0)
axis([-inf inf -1 1])
grid on

subplot(427)
plot(t,20*log10(abs(buffer_H_left_I')),t,20*log10(abs(buffer_H_left_Q')))
S1 = sprintf('H-Left I');
S2 = sprintf('H-Left Q');
legend(S1,S2);legend('boxoff','Orientation','horizontal')
xlabel('[Samples]')
ylabel('[dB]')
% S0 = sprintf('H-Left: Vpp = %1.2f',max(max(abs([buffer_H_left_I buffer_H_left_Q]))));
% title(S0)
axis([-inf,inf, -90, 0])
grid on

subplot(428)
plot(t,20*log10(abs(buffer_H_right_I')),t,20*log10(abs(buffer_H_right_Q')))
S1 = sprintf('H-Right I');
S2 = sprintf('H-Right Q');
legend(S1,S2);legend('boxoff','Orientation','horizontal')
xlabel('[Samples]')
ylabel('[dB]')
% S0 = sprintf('H-Right: Vpp = %1.2f',max(max(abs([buffer_H_right_I buffer_H_right_Q]))));
% title(S0)
axis([-inf,inf, -90, 0])
grid on
%......................................
%   Histograms
%......................................
x = linspace(-0.02,0.02,1000);
subplot(442);
hist(buffer_H_left_I(:,1),x)
xlabel('magnitude [V]');
title(['H-Left I: s.d. = ' num2str(std(buffer_H_left_I(:,1))) ' [V]']);
subplot(446);
hist(buffer_H_left_Q(:,1),x)
xlabel('magnitude [V]');
title(['H-Left Q: s.d. = ' num2str(std(buffer_H_left_Q(:,1))) ' [V]']);
subplot(444);
hist(buffer_H_right_I(:,1),x)
xlabel('magnitude [V]');
title(['H-Right I: s.d. = ' num2str(std(buffer_H_right_I(:,1))) ' [V]']);
subplot(448);
hist(buffer_H_right_Q(:,1),x)
xlabel('magnitude [V]');
title(['H-Right Q: s.d. = ' num2str(std(buffer_H_right_Q(:,1))) ' [V]']);


eval(['cd ' ResultsDir '\' ExpDir])
saveas(FigPULSE_H,'Pulse-H.fig' ,'fig');
eval(['cd ' CurrentDir]);

%......................................
%                        V
%.......................................
FigPULSE_V = figure('units','normalized','outerposition',[0 0 1 1]);
set(FigPULSE_V,'WindowStyle','docked')
%......................................
%   Frequency domain
%......................................
subplot(241)
plot(W,10*log10(abs(H(3,:)).^2+abs(H(4,:)).^2))
for k = 1:6,
    hold on;
    plot(W(L1(3,k+1)),P1(3,k+1),'*');
    text(W(L1(3,k+1)),P1(3,k+1)+10,num2str(k));
end;
hold on
line([W(1) W(end)],[mean(max(P1(3,12:30))) mean(max(P1(3,12:30)))],'LineStyle','--','Color','r');
xlabel('[Hz]')
ylabel('dB')
S0 = sprintf('V-Left: SNR %2.1f SFDR %2.1f',mean(SNR(3)),mean(SFDR(3)));
title(S0)
xlabel('[Hz]')
ylabel('dB')
grid on
axis([-inf,inf,-140, 0])

subplot(243)
plot(W,10*log10(abs(H(7,:)).^2+abs(H(8,:)).^2))
for k = 1:6,
    hold on;
    plot(W(L1(7,k+1)),P1(7,k+1),'*');
    text(W(L1(7,k+1)),P1(7,k+1)+10,num2str(k));
end;
hold on
line([W(1) W(end)],[mean(max(P1(7,12:30))) mean(max(P1(7,12:30)))],'LineStyle','--','Color','r');
xlabel('[Hz]')
ylabel('dB')
S0 = sprintf('V-Right: SNR %2.1f SFDR %2.1f',mean(SNR(7)),mean(SFDR(7)));
title(S0)
xlabel('[Hz]')
ylabel('dB')
grid on
axis([-inf,inf,-140, 0])

%......................................
%   Time domain
%......................................
t = (0:length(buffer_H_right_I)-1);
subplot(425)
plot(t,buffer_V_left_I',t,buffer_V_left_Q')
S1 = sprintf('V-Left I');
S2 = sprintf('V-Left Q');
legend(S1,S2);legend('boxoff','Orientation','horizontal')
xlabel('[Samples]')
% S0 = sprintf('V-Left: Vpp = %1.2f',max(max(abs([buffer_V_left_I buffer_V_left_Q]))));
% title(S0)
axis([-inf inf -1 1])
grid on

t = (0:length(buffer_H_right_I)-1);
subplot(426)
plot(t,buffer_V_right_I',t,buffer_V_right_Q')
S1 = sprintf('V-Right I');
S2 = sprintf('V-Right Q');
legend(S1,S2);legend('boxoff','Orientation','horizontal')
xlabel('[Samples]')
% S0 = sprintf('V-Right: Vpp = %1.2f',max(max(abs([buffer_V_right_I buffer_V_right_Q]))));
% title(S0)
axis([-inf inf -1 1])
grid on

subplot(427)
plot(t,20*log10(abs(buffer_V_left_I')),t,20*log10(abs(buffer_V_left_Q')))
S1 = sprintf('V-Left I');
S2 = sprintf('V-Left Q');
legend(S1,S2);legend('boxoff','Orientation','horizontal')
xlabel('[Samples]')
ylabel('[dB]')
% S0 = sprintf('V-Left: Vpp = %1.2f',max(max(abs([buffer_V_left_I buffer_V_left_Q]))));
% title(S0)
axis([-inf,inf, -90, 0])
grid on

subplot(428)
plot(t,20*log10(abs(buffer_V_right_I')),t,20*log10(abs(buffer_V_right_Q')))
S1 = sprintf('V-Right I');
S2 = sprintf('V-Right Q');
legend(S1,S2);legend('boxoff','Orientation','horizontal')
xlabel('[Samples]')
ylabel('[dB]')
% S0 = sprintf('V-Right: Vpp = %1.2f',max(max(abs([buffer_V_right_I buffer_V_right_Q]))));
% title(S0)
axis([-inf,inf, -90, 0])
grid on

%......................................
%   Histograms
%......................................
x = linspace(-0.02,0.02,1000);
subplot(442);
hist(buffer_V_left_I(:,1),x)
xlabel('magnitude [V]');
title(['V-Left I: s.d. = ' num2str(std(buffer_V_left_I(:,1))) ' [V]']);
subplot(446);
hist(buffer_V_left_Q(:,1),x)
xlabel('magnitude [V]');
title(['V-Left Q: s.d. = ' num2str(std(buffer_V_left_Q(:,1))) ' [V]']);
subplot(444);
hist(buffer_V_right_I(:,1),x)
xlabel('magnitude [V]');
title(['V-Right I: s.d. = ' num2str(std(buffer_V_right_I(:,1))) ' [V]']);
subplot(448);
hist(buffer_V_right_Q(:,1),x)
xlabel('magnitude [V]');
title(['V-Right Q: s.d. = ' num2str(std(buffer_V_right_Q(:,1))) ' [V]']);

eval(['cd ' ResultsDir '\' ExpDir])
saveas(FigPULSE_V,'Pulse-V.fig' ,'fig');
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
