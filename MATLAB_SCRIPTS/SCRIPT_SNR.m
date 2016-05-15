%----------------------------------------------
%   SCRIPT SNR
%
%
%   1 - SNR + SFDR test
%   2 - Pulse test
%   3 - CAF
%
%----------------------------------------------
figure;
plot(rand(1,50));
%-------------------------------------------------
% Extruct MAIN_config_message values
%-------------------------------------------------
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
%   Loading SAMPLES file
%-------------------------------------------------
[MP] = textread(ResultsFile,'%4c');
M = hex2dec(char(MP));
if (length(M)~=SIZE*2)
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
%   Move files to Experiment directory
%-------------------------------------------------
% system(['copy ' ResultsFile ' .\' ResultsDir '\' ExpDir]);
% system(['copy ' SavedConfigFile ' .\' ResultsDir '\' ExpDir]);
% eval(['cd ' CurrentDir]);
% 
% S = ['cd(''' CurrentDir ''')'];
% eval(S);
% fid = fopen(['.\' ConfigDir '\' ConfigFile],'wt');
% fprintf(fid,'%s\n',titleconfig);
% fprintf(fid,'Profile_AD9910A=%d\n',Profile_AD9910A);
% fprintf(fid,'Profile_AD9910B=%d\n',Profile_AD9910B);
% fprintf(fid,'chip_length_AD9910A=%d\n',chip_length_AD9910A);
% fprintf(fid,'chip_length_AD9910B=%d\n',chip_length_AD9910B);
% fprintf(fid,'IF_SELECT_TX1=%d\n',IF_SELECT_TX1);
% fprintf(fid,'IF_SELECT_TX2=%d\n',IF_SELECT_TX2);
% fprintf(fid,'IF_SELECT_TX3=%d\n',IF_SELECT_TX3);
% fprintf(fid,'IO_UPDATE_rate=%d\n',IO_UPDATE_rate);
% fprintf(fid,'TX_ON1=%d\n',TX_ON1);
% fprintf(fid,'TX_ON2=%d\n',TX_ON2);
% fprintf(fid,'TX_ON3=%d\n',TX_ON3);
% fprintf(fid,'TX_LO_TR=%d\n',TX_LO_TR);
% fprintf(fid,'SAMPLE_SEL=%d\n',SAMPLE_SEL);
% fprintf(fid,'SAMPLE_ON_OFF=%d\n',SAMPLE_ON_OFF);
% fprintf(fid,'ATTN_TX1=%d\n',ATTN_TX1);
% fprintf(fid,'ATTN_TX2=%d\n',ATTN_TX2);
% fprintf(fid,'ATTN_TX3=%d\n',ATTN_TX3);
% fprintf(fid,'ATTN_RX1=%d\n',ATTN_RX1);
% fprintf(fid,'ATTN_RX2=%d\n',ATTN_RX2);
% fprintf(fid,'ATTN_RX3=%d\n',ATTN_RX3);
% fprintf(fid,'ATTN_RX4=%d\n',ATTN_RX4);
% fprintf(fid,'AD9910_Set_aux_dac_A=%d\n',AD9910_Set_aux_dac_A);
% fprintf(fid,'AD9910_Set_aux_dac_B=%d\n',AD9910_Set_aux_dac_B);
% fprintf(fid,'Number_of_buffers=%d\n',Number_of_buffers);
% fprintf(fid,'Buffer_length=%d\n',Buffer_length);
% fprintf(fid,'FIFO_length=%d\n',FIFO_length);
% fprintf(fid,'MODE=%d\n',1);
% fclose(fid);
%--------------------------------------------------
%               Processing file
%--------------------------------------------------
x_A = M(1:SIZE);
x_B = M(SIZE+1:2*SIZE);
x_A = x_A - 2^16*(x_A>(2^15-1));
x_B = x_B - 2^16*(x_B>(2^15-1));
x_A = x_A/2^15;
x_B = x_B/2^15;
buffer_A = reshape(x_A,PCIE_BUFFSIZE*4,PCIE_NUMBER_PULSES);
buffer_B = reshape(x_B,PCIE_BUFFSIZE*4,PCIE_NUMBER_PULSES);
buffer_H_left_I = buffer_A(4+4:4:end,:);
buffer_H_left_Q = buffer_A(3+4:4:end,:);
buffer_V_left_I = buffer_A(2+4:4:end,:);
buffer_V_left_Q = buffer_A(1+4:4:end,:);
buffer_H_right_I = buffer_B(4+4:4:end,:);
buffer_H_right_Q = buffer_B(3+4:4:end,:);
buffer_V_right_I = buffer_B(2+4:4:end,:);
buffer_V_right_Q = buffer_B(1+4:4:end,:);

Buf_A_1 = buffer_H_left_I + 1j*buffer_H_left_Q;
Buf_A_2 = buffer_V_left_I + 1j*buffer_V_left_Q;
Buf_B_1 = buffer_H_right_I + 1j*buffer_H_right_Q;
Buf_B_2 = buffer_V_right_I + 1j*buffer_V_right_Q;

% %----------------------------------------------
% %   HALF-BAND FILTER COEFFICIENTS. pp. 39 in AD6655 datasheet
% %----------------------------------------------
HB_FIR = zeros(1,19);
HB_FIR( 1) = 0.0008049;
HB_FIR(19) = 0.0008049;
HB_FIR( 3) = -0.0059023;
HB_FIR(17) = -0.0059023;
HB_FIR( 5) = 0.0239182;
HB_FIR(15) = 0.0239182;
HB_FIR( 7) = -0.0755024;
HB_FIR(13) = -0.0755024;
HB_FIR( 9) = 0.3066864;
HB_FIR(11) = 0.3066864;
HB_FIR(10) = 0.5;
%----------------------------------------------
%   FIXED-COEFFICIENT FIR FILTER. pp. 39-40 in AD6655 datasheet
%----------------------------------------------
FC_FIR( 1) = 0.0001826;
FC_FIR( 2) = 0.0006824;
FC_FIR( 3) = 0.0009298;
FC_FIR( 4) = 0.0000458;
FC_FIR( 5) = -0.0012689;
FC_FIR( 6) = -0.0008345;
FC_FIR( 7) = 0.0011806;
FC_FIR( 8) = 0.0011387;
FC_FIR( 9) = -0.0018439;
FC_FIR(10) = -0.0024557;
FC_FIR(11) = 0.0018063;
FC_FIR(12) = 0.0035825;
FC_FIR(13) = -0.0021510;
FC_FIR(14) = -0.0056810;
FC_FIR(15) = 0.0017405;
FC_FIR(16) = 0.0078602;
FC_FIR(17) = -0.0013437;
FC_FIR(18) = -0.0110626;
FC_FIR(19) = -0.0000229;
FC_FIR(20) = 0.0146618;
FC_FIR(21) = 0.0018959;
FC_FIR(22) = -0.0195594;
FC_FIR(23) = -0.0053153;
FC_FIR(24) = 0.0255623;
FC_FIR(25) = 0.0104036;
FC_FIR(26) = -0.0341468;
FC_FIR(27) = -0.0192165;
FC_FIR(28) = 0.0471258;
FC_FIR(29) = 0.0354118;
FC_FIR(30) = -0.0728111;
FC_FIR(31) = -0.0768890;
FC_FIR(32) = 0.1607208;
FC_FIR(33) = 0.4396725;
FC_FIR = [FC_FIR fliplr(FC_FIR)];
%==================================================
%==================================================
%
%
%               Processing data
%           SNR + SFDR - External sine wave
%
%==================================================
%==================================================
w  = window(@blackmanharris,PCIE_BUFFSIZE-1);
w = w/rms(w);

y_I1_A = buffer_H_left_I(:,1).*w;
y_Q1_A = buffer_H_left_Q(:,1).*w;
y_I2_A = buffer_V_left_I(:,1).*w;
y_Q2_A = buffer_V_left_Q(:,1).*w;

y_I1_B = buffer_H_right_I(:,1).*w;
y_Q1_B = buffer_H_right_Q(:,1).*w;
y_I2_B = buffer_V_right_I(:,1).*w;
y_Q2_B = buffer_V_right_Q(:,1).*w;

[H(1,:),W1] = freqz(y_I1_A/PCIE_BUFFSIZE*2,1,NFFT,Fs);
[H(2,:),W2] = freqz(y_Q1_A/PCIE_BUFFSIZE*2,1,NFFT,Fs);
[H(3,:),W3] = freqz(y_I2_A/PCIE_BUFFSIZE*2,1,NFFT,Fs);
[H(4,:),W4] = freqz(y_Q2_A/PCIE_BUFFSIZE*2,1,NFFT,Fs);
[H(5,:),W5] = freqz(y_I1_B/PCIE_BUFFSIZE*2,1,NFFT,Fs);
[H(6,:),W6] = freqz(y_Q1_B/PCIE_BUFFSIZE*2,1,NFFT,Fs);
[H(7,:),W7] = freqz(y_I2_B/PCIE_BUFFSIZE*2,1,NFFT,Fs);
[H(8,:),W8] = freqz(y_Q2_B/PCIE_BUFFSIZE*2,1,NFFT,Fs);

for k = 1:8,
    [PKS(k,:),LOCS(k,:)] = findpeaks(20*log10(abs(H(k,:))),'NPEAKS',30,'SORTSTR','descend');
    [P1(k,:),INDs(k,:)]  = sort(PKS(k,:),'descend');
    L1(k,:) = LOCS(k,INDs(k,:));
    SFDR(k) = P1(k,1)-P1(k,2);
    SNR(k) = P1(k,1)-max(P1(k,12:30));
end;
%\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
%
%  Plotting
%
%\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
FigSNR = figure('units','normalized','outerposition',[0 0 1 1])
set(FigSNR,'WindowStyle','docked')

subplot(221)
plot(W1,20*log10(abs(H(1,:))),W3,20*log10(abs(H(2,:))),W5,20*log10(abs(H(3,:))),W7,20*log10(abs(H(4,:))))
for k = 1:6,
    hold on;
    plot(W1(L1(1,k+1)),P1(1,k+1),'*');
    text(W1(L1(1,k+1)),P1(1,k+1)+10,num2str(k));
end;
hold on
line([W1(1) W1(end)],[mean(max(P1(1:4,12:30))) mean(max(P1(1:4,12:30)))],'LineStyle','--','Color','r');
xlabel('[Hz]')
ylabel('dB')
S0 = sprintf('CHA: SNR %2.1f SFDR %2.1f',mean(SNR(1:4)),mean(SFDR(1:4)));
title(S0)
S1 = sprintf('CHA_1 I: SNR %2.1f SFDR %2.1f', SNR(1), SFDR(1));
S2 = sprintf('CHA_1 Q: SNR %2.1f SFDR %2.1f', SNR(2), SFDR(2));
S3 = sprintf('CHA_2 I: SNR %2.1f SFDR %2.1f', SNR(3), SFDR(3));
S4 = sprintf('CHA_2 Q: SNR %2.1f SFDR %2.1f', SNR(4), SFDR(4));
legend(S1,S2,S3,S4);legend('boxoff')
grid on
axis([-inf,inf,-140, 0])

subplot(222)
plot(W2,20*log10(abs(H(5,:))),W4,20*log10(abs(H(6,:))),W6,20*log10(abs(H(7,:))),W8,20*log10(abs(H(8,:))))
for k = 1:6,
    hold on;
    plot(W1(L1(5,k+1)),P1(5,k+1),'*');
    text(W1(L1(5,k+1)),P1(5,k+1)+10,num2str(k));
end;
hold on
line([W1(1) W1(end)],[mean(max(P1(5:8,12:30))) mean(max(P1(5:8,12:30)))],'LineStyle','--','Color','r');
xlabel('[Hz]')
ylabel('dB')
S0 = sprintf('CHB: SNR %2.1f SFDR %2.1f',mean(SNR(5:8)),mean(SFDR(5:8)));
title(S0)
S1 = sprintf('CHB_1 I: SNR %2.1f SFDR %2.1f', SNR(5), SFDR(5));
S2 = sprintf('CHB_1 Q: SNR %2.1f SFDR %2.1f', SNR(6), SFDR(6));
S3 = sprintf('CHB_2 I: SNR %2.1f SFDR %2.1f', SNR(7), SFDR(7));
S4 = sprintf('CHB_2 Q: SNR %2.1f SFDR %2.1f', SNR(8), SFDR(8));
legend(S1,S2,S3,S4);legend('boxoff')
grid on
axis([-inf,inf, -140, 0])

t = (0:length(buffer_H_right_I)-1)*1/Fs;
subplot(223)
plot(t,buffer_H_left_I,t,buffer_H_left_Q,t,buffer_V_left_I,t,buffer_V_left_Q)
legend('I_1','Q_1','I_2','Q_2','Orientation','horizontal');legend('boxoff')
xlabel('time [Sec]')
S0 = sprintf('CHA: Vpp = %1.2f',2*max(max([buffer_H_left_I buffer_H_left_Q buffer_V_left_I buffer_H_left_Q])));
title(S0)
axis([-inf inf -1 1])
grid on

subplot(224)
plot(t,buffer_H_right_I,t,buffer_H_right_Q,t,buffer_V_right_I,t,buffer_V_right_Q)
legend('I_1','Q_1','I_2','Q_2','Orientation','horizontal');legend('boxoff')
xlabel('time [Sec]')
S0 = sprintf('CHB: Vpp = %1.2f',2*max(max([buffer_H_right_I buffer_H_right_Q buffer_V_right_I buffer_H_right_Q])));
title(S0)
axis([-inf inf -1 1])
grid on
eval(['cd ' ResultsDir '\' ExpDir]);
saveas(FigSNR,'SNR.fig','fig');


