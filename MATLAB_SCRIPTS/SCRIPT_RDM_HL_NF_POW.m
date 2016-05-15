%----------------------------------------------
%   SCRIPT_CAF
%
%   Alon Slapak     17.11.2014
%
%   1 - Range-Doppler map
%
%   Improvements:
%   17.11.2014:     Add using SERVICE_READ_SCRIPT_DATA for reading data.
%
%----------------------------------------------
% try
%==================================================
%==================================================
%
%
%               Read data
%
%
%==================================================
%==================================================
%----------------------------------------
%  Matched filter
%----------------------------------------
% clear all
% Fs                  = 50e6;
% Buffer_length       = 1024;
% Number_of_buffers   = 512;
% PCIE_NUMBER_PULSES  = Number_of_buffers;
% IO_UPDATE_rate      = 5;
% PCIE_BUFFSIZE       = Buffer_length;
% Profile_AD9910A     = 7;
% chip_length_AD9910A = 9;
% 
% G = 1e-2;
% Gs = 1;
% buffer_H_left_I  = G * randn(Buffer_length,Number_of_buffers);
% buffer_H_left_Q  = G * randn(Buffer_length,Number_of_buffers);
% buffer_V_left_I  = G * randn(Buffer_length,Number_of_buffers);
% buffer_V_left_Q  = G * randn(Buffer_length,Number_of_buffers);
% buffer_H_right_I = G * randn(Buffer_length,Number_of_buffers);
% buffer_H_right_Q = G * randn(Buffer_length,Number_of_buffers);
% buffer_V_right_I = G * randn(Buffer_length,Number_of_buffers);
% buffer_V_right_Q = G * randn(Buffer_length,Number_of_buffers);
% 
% buffer_H_left_I(300,:) = Gs * real(exp(1j*2*pi/(IO_UPDATE_rate * 1000) * 1000 * (0:Number_of_buffers-1)));
% buffer_H_left_Q(300,:) = Gs * imag(exp(1j*2*pi/(IO_UPDATE_rate * 1000) * 1000 * (0:Number_of_buffers-1)));
% buffer_V_left_I(300,:) = Gs * real(exp(1j*2*pi/(IO_UPDATE_rate * 1000) * 500 * (0:Number_of_buffers-1)));
% buffer_V_left_Q(300,:) = Gs * imag(exp(1j*2*pi/(IO_UPDATE_rate * 1000) * 500* (0:Number_of_buffers-1)));
% buffer_H_right_I(300,:) = Gs * real(exp(1j*2*pi/(IO_UPDATE_rate * 1000) * 0 * (0:Number_of_buffers-1)));
% buffer_H_right_Q(300,:) = Gs * imag(exp(1j*2*pi/(IO_UPDATE_rate * 1000) * 0 * (0:Number_of_buffers-1)));
% buffer_V_right_I(300,:) = Gs * real(exp(1j*2*pi/(IO_UPDATE_rate * 1000) * 9.5 * 5000/512 * (0:Number_of_buffers-1)));
% buffer_V_right_Q(300,:) = Gs * imag(exp(1j*2*pi/(IO_UPDATE_rate * 1000) * 9.5 * 5000/512 * (0:Number_of_buffers-1)));
% 
% buffer_H_left_I(301,:) = Gs * real(exp(1j*2*pi/(IO_UPDATE_rate * 1000) * 1000 * (0:Number_of_buffers-1)));
% buffer_H_left_Q(301,:) = Gs * imag(exp(1j*2*pi/(IO_UPDATE_rate * 1000) * 1000 * (0:Number_of_buffers-1)));
% buffer_V_left_I(301,:) = Gs * real(exp(1j*2*pi/(IO_UPDATE_rate * 1000) * 500 * (0:Number_of_buffers-1)));
% buffer_V_left_Q(301,:) = Gs * imag(exp(1j*2*pi/(IO_UPDATE_rate * 1000) * 500* (0:Number_of_buffers-1)));
% buffer_H_right_I(301,:) = Gs * real(exp(1j*2*pi/(IO_UPDATE_rate * 1000) * 0 * (0:Number_of_buffers-1)));
% buffer_H_right_Q(301,:) = Gs * imag(exp(1j*2*pi/(IO_UPDATE_rate * 1000) * 0 * (0:Number_of_buffers-1)));
% buffer_V_right_I(301,:) = Gs * real(exp(1j*2*pi/(IO_UPDATE_rate * 1000) * 9.5* 5000/512 * (0:Number_of_buffers-1)));
% buffer_V_right_Q(301,:) = Gs * imag(exp(1j*2*pi/(IO_UPDATE_rate * 1000) * 9.5* 5000/512 * (0:Number_of_buffers-1)));

    SERVICE_READ_SCRIPT_DATA_FULL_LENGTH;
%==================================================
%==================================================
%
%
%               Processing data
%
%
%==================================================
%==================================================
Doppler      = (-floor(PCIE_NUMBER_PULSES/2):-floor(PCIE_NUMBER_PULSES/2) + PCIE_NUMBER_PULSES-1)/PCIE_NUMBER_PULSES * IO_UPDATE_rate;
Range        = (0:PCIE_BUFFSIZE-2)/Fs*3e8/2;
%--------------------------------------------------
%     Match filter due transmited filter
%--------------------------------------------------
profile_0 = [];
profile_1 = [1 1 1 1 1 -1 -1 1 1 -1 1 -1 1];
profile_2 = [1 1 1 1 1  1  1 1 1  1 1  1 1];
profile_3 = [0 0 0 0 1  1  1 1 1  1 1  1 1];
profile_4 = [0 0 0 0 0  0  1 1 1  1 1  1 1];
profile_5 = [0 0 0 0 0  0  0 0 1  1 1  1 1];
profile_6 = [0 0 0 0 0  0  0 0 0  0 1  1 1];
profile_7 = [0 0 0 0 0  0  0 0 0  0 0  0 1];
switch (Profile_AD9910A)
    case 0,
        signal = profile_0;
    case 1,
        signal = profile_1;
    case 2,
        signal = profile_2;
    case 3,
        signal = profile_3;
    case 4,
        signal = profile_4;
    case 5,
        signal = profile_5;
    case 6,
        signal = profile_6;
    case 7,
        signal = profile_7;
end;
chip_length     = chip_length_AD9910A;
samples_Number  = length(signal) * Fs * chip_length *4/0.6*1e-9;
Matched_sig     = signal(round(linspace(1,length(signal),samples_Number)));
% Matched_sig = Matched_sig/sum(Matched_sig);
Matched_sig = 1;

 %----------------------------------------
 % DC correction
 %----------------------------------------
%     buffer_H_left_I = buffer_H_left_I - mean(mean(buffer_H_left_I(512:end,:)));
%     buffer_H_left_Q = buffer_H_left_Q - mean(mean(buffer_H_left_Q(512:end,:)));
%     buffer_V_left_I = buffer_V_left_I - mean(mean(buffer_V_left_I(512:end,:)));
%     buffer_V_left_Q = buffer_V_left_Q - mean(mean(buffer_V_left_Q(512:end,:)));
%     buffer_H_right_I = buffer_H_right_I - mean(mean(buffer_H_right_I(512:end,:)));
%     buffer_H_right_Q = buffer_H_right_Q - mean(mean(buffer_H_right_Q(512:end,:)));
%     buffer_V_right_I = buffer_V_right_I - mean(mean(buffer_V_right_I(512:end,:)));
%     buffer_V_right_Q = buffer_V_right_Q - mean(mean(buffer_V_right_Q(512:end,:)));
    
%----------------------------------------
%  Matched filter
%----------------------------------------
TGT_H_left_I_mf  = filter(fliplr(Matched_sig),1,buffer_H_left_I);
TGT_H_left_Q_mf  = filter(fliplr(Matched_sig),1,buffer_H_left_Q);
TGT_V_left_I_mf  = filter(fliplr(Matched_sig),1,buffer_V_left_I);
TGT_V_left_Q_mf  = filter(fliplr(Matched_sig),1,buffer_V_left_Q);
TGT_H_right_I_mf = filter(fliplr(Matched_sig),1,buffer_H_right_I);
TGT_H_right_Q_mf = filter(fliplr(Matched_sig),1,buffer_H_right_Q);
TGT_V_right_I_mf = filter(fliplr(Matched_sig),1,buffer_V_right_I);
TGT_V_right_Q_mf = filter(fliplr(Matched_sig),1,buffer_V_right_Q);
%----------------------------------------
%  CPI
%----------------------------------------
TGT_H_left_mf  = TGT_H_left_I_mf  + 1j * TGT_H_left_Q_mf;
TGT_V_left_mf  = TGT_V_left_I_mf  + 1j * TGT_V_left_Q_mf;
TGT_H_right_mf = TGT_H_right_I_mf + 1j * TGT_H_right_Q_mf;
TGT_V_right_mf = TGT_V_right_I_mf + 1j * TGT_V_right_Q_mf;
%----------------------------------------------
% RDM
%----------------------------------------------
TGT_H_left_window   = zeros(PCIE_BUFFSIZE-1,PCIE_NUMBER_PULSES);
TGT_V_left_window   = zeros(PCIE_BUFFSIZE-1,PCIE_NUMBER_PULSES);
TGT_H_right_window  = zeros(PCIE_BUFFSIZE-1,PCIE_NUMBER_PULSES);
TGT_V_right_window  = zeros(PCIE_BUFFSIZE-1,PCIE_NUMBER_PULSES);

CAF_H_left  = zeros(PCIE_BUFFSIZE-1,PCIE_NUMBER_PULSES);
CAF_V_left  = zeros(PCIE_BUFFSIZE-1,PCIE_NUMBER_PULSES);
CAF_H_right = zeros(PCIE_BUFFSIZE-1,PCIE_NUMBER_PULSES);
CAF_V_right = zeros(PCIE_BUFFSIZE-1,PCIE_NUMBER_PULSES);
for p = 1:PCIE_BUFFSIZE-1,
    if (1)          % Windowing
        wnd = kaiser(PCIE_NUMBER_PULSES,45)';
        wnd = wnd/sum(wnd)*length(wnd)/sqrt(2);
        TGT_H_left_window(p,:) = TGT_H_left_mf(p,:).*(wnd);
        TGT_V_left_window(p,:) = TGT_V_left_mf(p,:).*(wnd);
        TGT_H_right_window(p,:) = TGT_H_right_mf(p,:).*(wnd);
        TGT_V_right_window(p,:) = TGT_V_right_mf(p,:).*(wnd);
    else
        TGT_H_left_window(p,:) = TGT_H_left_mf(p,:);
        TGT_V_left_window(p,:) = TGT_V_left_mf(p,:);
        TGT_H_right_window(p,:) = TGT_H_right_mf(p,:);
        TGT_V_right_window(p,:) = TGT_V_right_mf(p,:);
    end;
    CAF_H_left(p,:) = fftshift(fft(TGT_H_left_window(p,:)));
    CAF_V_left(p,:) = fftshift(fft(TGT_V_left_window(p,:)));
    CAF_H_right(p,:) = fftshift(fft(TGT_H_right_window(p,:)));
    CAF_V_right(p,:) = fftshift(fft(TGT_V_right_window(p,:)));
end;
%----------------------------------------
%   Magnitude
%----------------------------------------
% B = fir1(50,0.20);
% CAF_H_left = filter(B,1,CAF_H_left);
% CAF_V_left = filter(B,1,CAF_V_left);
% CAF_H_right = filter(B,1,CAF_H_right);
% CAF_V_right = filter(B,1,CAF_V_right);

CAF_H_left_abs  = abs(CAF_H_left)/Buffer_length * 2 + eps;
CAF_V_left_abs  = abs(CAF_V_left)/Buffer_length * 2+ eps;
CAF_H_right_abs = abs(CAF_H_right)/Buffer_length * 2+ eps;
CAF_V_right_abs = abs(CAF_V_right)/Buffer_length * 2+ eps;

% CAF_H_left_I  = real(CAF_H_left)/Buffer_length * 2 + eps;
% CAF_H_left_Q  = imag(CAF_H_left)/Buffer_length * 2 + eps;

%----------------------------------------------
% Plotting
%----------------------------------------------

% %----------------------------------------------
% % DC from RDM
% %----------------------------------------------
% s = linspace(-50e6/2,50e6/2,1023);
% 
% Fig_DC = figure('units','normalized','outerposition',[0 0 1 1]);
% set(Fig_DC,'WindowStyle','docked')
% 
% subplot(221)
% plot(s,abs(fftshift(fft((CAF_H_left(:,257)))))); 
% grid on;
% xlabel('Frequency [Hz]');
% ylabel('Amplitude')
% title('H left')
% axis([-30e6 30e6 -inf 80])
% 
% subplot(222)
% plot(s,abs(fftshift(fft((CAF_H_right(:,257)))))); 
% grid on;
% xlabel('Frequency [Hz]');
% ylabel('Amplitude')
% title('H right')
% axis([-30e6 30e6 -inf 80])
% 
% subplot(223)
% plot(s,abs(fftshift(fft((CAF_V_left(:,257)))))); 
% grid on;
% xlabel('Frequency [Hz]');
% ylabel('Amplitude')
% title('V left')
% axis([-30e6 30e6 -inf 80])
% 
% subplot(224)
% plot(s,abs(fftshift(fft((CAF_V_right(:,257)))))); 
% grid on;
% xlabel('Frequency [Hz]');
% ylabel('Amplitude')
% title('V right')
% axis([-30e6 30e6 -inf 80])

%----------------------------------------------
%  NF & Power
%----------------------------------------------
noise_floor_mat = CAF_H_left(Buffer_length-20-1:Buffer_length-1,1:20)/Buffer_length * 2;
noise_floor_emp = 10*log10(var(noise_floor_mat(:)));
signal_strength_emp = 20*log10(max(max(abs(CAF_H_left(:))/Buffer_length * 2)));

%----------------------------------------------
%  RDM
%----------------------------------------------
Fig_RDM = figure('units','normalized','outerposition',[0 0 1 1]);
set(Fig_RDM,'WindowStyle','docked')
% subplot(221)
mesh(Doppler,Range,20*log10(CAF_H_left_abs))
hold on;
% view(70,32)
% view(90,0)
view(180,0)
xlabel('Doppler kHz');
ylabel('range [m]')
% title('H left')
title({'H Left';['Noise floor = ' num2str(noise_floor_emp) ' [dB]'];['Signal strength = ' num2str(signal_strength_emp) ' [dB]']});
axis([-inf inf -inf inf -90 10])

% subplot(222)
% mesh(Doppler,Range,20*log10(CAF_H_right_abs))
% hold on;
% view(70,32)
% view(90,0)
% xlabel('Doppler kHz');
% ylabel('range [m]')
% title('H right')
% axis([-inf inf -inf inf -100 10])
% 
% subplot(223)
% mesh(Doppler,Range,20*log10( CAF_V_left_abs))
% hold on;
% view(70,32)
% view(90,0)
% xlabel('Doppler kHz');
% ylabel('range [m]')
% title('V left')
% axis([-inf inf -inf inf -100 10])
% 
% subplot(224)
% mesh(Doppler,Range,20*log10(CAF_V_right_abs))
% hold on;
% view(70,32)
% view(90,0)
% xlabel('Doppler kHz');
% ylabel('range [m]')
% title('V right')
% axis([-inf inf -inf inf -100 10])

    eval(['cd ' ResultsDir]);
    saveas(Fig_RDM,'RDM' ,'fig');
    saveas(Fig_RDM,'RDM' ,'jpg')
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
% catch err
%     Error_message = err.message
%     Error_line = err.stack.line
% end
