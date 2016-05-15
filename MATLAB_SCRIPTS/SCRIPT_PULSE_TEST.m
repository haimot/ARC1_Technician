%----------------------------------------------
%   SCRIPT_PULSE_TEST
%
%
%   1 - Pulse in time
%   2 - timing and I&Q histograms
%   3 - SNR visualization
%
%   Improvements:
%   17.11.2014:     Add using SERVICE_READ_SCRIPT_DATA for reading data.
%
%----------------------------------------------
try
    %==================================================
    %==================================================
    %
    %
    %               Read data
    %
    %
    %==================================================
    %==================================================
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
    
    %----------------------------------------
    % DC correction
    %----------------------------------------
    buffer_H_left_I = buffer_H_left_I - mean(mean(buffer_H_left_I(512:end,:)));
    buffer_H_left_Q = buffer_H_left_Q - mean(mean(buffer_H_left_Q(512:end,:)));
    buffer_V_left_I = buffer_V_left_I - mean(mean(buffer_V_left_I(512:end,:)));
    buffer_V_left_Q = buffer_V_left_Q - mean(mean(buffer_V_left_Q(512:end,:)));
    buffer_H_right_I = buffer_H_right_I - mean(mean(buffer_H_right_I(512:end,:)));
    buffer_H_right_Q = buffer_H_right_Q - mean(mean(buffer_H_right_Q(512:end,:)));
    buffer_V_right_I = buffer_V_right_I - mean(mean(buffer_V_right_I(512:end,:)));
    buffer_V_right_Q = buffer_V_right_Q - mean(mean(buffer_V_right_Q(512:end,:)));
    
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
    S0 = sprintf('Left-H: Vpp = %1.2f',2*max(max(sqrt(buffer_H_left_I.^2+buffer_H_left_Q.^2))));
    title(S0)
    axis([-inf inf -1 1])
    grid on
    
    subplot(223)
    plot(t,buffer_V_left_I',t,buffer_V_left_Q')
    legend('I_2','Q_2','Orientation','horizontal');legend('boxoff')
    xlabel('[Samples]')
    S0 = sprintf('Left-V: Vpp = %1.2f',2*max(max(sqrt(buffer_V_left_I.^2+buffer_V_left_Q.^2))));
    title(S0)
    axis([-inf inf -1 1])
    grid on
    
    subplot(222)
    plot(t,buffer_H_right_I',t,buffer_H_right_Q')
    legend('I_1','Q_1','Orientation','horizontal');legend('boxoff')
    xlabel('[Samples]')
    S0 = sprintf('RIght-H: Vpp = %1.2f',2*max(max(sqrt(buffer_H_right_I.^2+buffer_H_right_Q.^2))));
    title(S0)
    axis([-inf inf -1 1])
    grid on
    
    subplot(224)
    plot(t,buffer_V_right_I',t,buffer_V_right_Q')
    legend('I_2','Q_2','Orientation','horizontal');legend('boxoff')
    xlabel('[Samples]')
    S0 = sprintf('Right-V: Vpp = %1.2f',2*max(max(sqrt(buffer_V_right_I.^2+buffer_V_right_Q.^2))));
    title(S0)
    axis([-inf inf -1 1])
    grid on
    
    eval(['cd ' ResultsDir]);
    saveas(FigPULSE,'Pulses' ,'fig');
    saveas(FigPULSE,'Pulses' ,'jpg');
    eval(['cd ' CurrentDir]);
    %     %-------------------------------------------------
    %     %    Sinc analysis - Range
    %     %-------------------------------------------------
    %     Sync_left = zeros(PCIE_NUMBER_PULSES,8);
    %     Sync_right = zeros(PCIE_NUMBER_PULSES,8);
    %     Sync = zeros(PCIE_NUMBER_PULSES,8);
    %     IQ = zeros(PCIE_NUMBER_PULSES,8);
    %     for k = 1:8,
    %         switch k,
    %             case 1
    %                 temp = buffer_H_left_I;
    %             case 2
    %                 temp = buffer_H_left_Q;
    %             case 3
    %                 temp = buffer_V_left_I;
    %             case 4
    %                 temp = buffer_V_left_Q;
    %             case 5
    %                 temp = buffer_H_right_I;
    %             case 6
    %                 temp = buffer_H_right_Q;
    %             case 7
    %                 temp = buffer_V_right_I;
    %             case 8
    %                 temp = buffer_V_right_Q;
    %         end;
    %         [~,kkk] = find(abs(temp') >= max(max(abs(temp)))*0.5);
    %         if (size(kkk,1) >= PCIE_NUMBER_PULSES),
    %             Sync_left(:,k)  =  kkk(1:PCIE_NUMBER_PULSES);
    %             Sync_right(:,k) =  kkk(end-PCIE_NUMBER_PULSES+1:end);
    %
    %         else
    %             Sync_left(:,k) = ones(PCIE_NUMBER_PULSES,1);
    %             Sync_right(:,k) = ones(PCIE_NUMBER_PULSES,1);
    %         end;
    %         Sync(:,k) = 0.5*(Sync_right(:,k) + Sync_left(:,k));
    %         for p = 1:PCIE_NUMBER_PULSES,
    %             IQ(p,k) = temp(floor(Sync(p,k)),p);
    %             IQ(p,k) = floor(IQ(p,k)*1000)/1000;       % resolution of 3 digits.
    %         end;
    %
    %     end;
    %
    %     FigSYNC1 = figure('units','normalized','outerposition',[0 0 1 1]);
    %     set(FigSYNC1,'WindowStyle','docked')
    %
    %     subplot(2,4,1)
    %     hist(Sync(:,1));
    %     axis([-inf inf -inf inf])
    %     title('Left-H I')
    %     subplot(2,4,2)
    %     hist(Sync(:,2));
    %     axis([-inf inf -inf inf])
    %     title('Left-H Q')
    %     subplot(2,4,3)
    %     hist(Sync(:,3));
    %     axis([-inf inf -inf inf])
    %     title('Left-V I')
    %     subplot(2,4,4)
    %     hist(Sync(:,4));
    %     axis([-inf inf -inf inf])
    %     title('Left-V Q')
    %     subplot(2,4,5)
    %     hist(Sync(:,5));
    %     axis([-inf inf -inf inf])
    %     title('Right-H I')
    %     subplot(2,4,6)
    %     hist(Sync(:,6));
    %     axis([-inf inf -inf inf])
    %     title('Right-H Q')
    %     subplot(2,4,7)
    %     hist(Sync(:,7));
    %     axis([-inf inf -inf inf])
    %     title('Right-V I')
    %     subplot(2,4,8)
    %     hist(Sync(:,8));
    %     axis([-inf inf -inf inf])
    %     title('Right-V Q')
    %
    %     eval(['cd ' ResultsDir]);
    %     saveas(FigSYNC1,'Amplitude_SYNC' ,'fig');
    %     saveas(FigSYNC1,'Amplitude_SYNC' ,'jpg');
    %     eval(['cd ' CurrentDir]);
    %     %-------------------------------------------------
    %     %    Sinc analysis - Phase I/Q
    %     %-------------------------------------------------
    %     FigSYNC2 = figure('units','normalized','outerposition',[0 0 1 1]);
    %     set(FigSYNC2,'WindowStyle','docked')
    %
    %     for k = 1:8,
    %         subplot(2,4,k);
    %         hist(IQ(:,k));
    %         axis([-inf inf -inf inf]);
    %         switch k,
    %             case 1
    %                 title('Left-H I');
    %             case 2
    %                 title('Left-H Q')
    %             case 3
    %                 title('Left-V I')
    %             case 4
    %                 title('Left-V Q')
    %             case 5
    %                 title('Right-H I')
    %             case 6
    %                 title('Right-H Q')
    %             case 7
    %                 title('Right-V I')
    %             case 8
    %                 title('Right-V Q')
    %         end;
    %     end;
    %     eval(['cd ' ResultsDir]);
    %     saveas(FigSYNC2,'Amplitude_histograms' ,'fig');
    %     saveas(FigSYNC2,'Amplitude_histograms' ,'jpg');
    %     eval(['cd ' CurrentDir]);
    %----------------------------------------
    %  General Plotting - Frequency domain
    %----------------------------------------
    FFT_BUF_SIZE = 1023;
    my_window = window(@chebwin,FFT_BUF_SIZE,60)*2;
    
    NFFT = FFT_BUF_SIZE;
    delta_W = Fs/NFFT;
    W = -floor(Fs/2) +(0:delta_W:delta_W * (NFFT-1));
    
    H = zeros(8,NFFT);
    for k = 1:PCIE_NUMBER_PULSES,
        H(1,:) =  H(1,:)  + transpose(fftshift(fft((buffer_H_left_I(1:FFT_BUF_SIZE,k).*my_window),NFFT)));
        H(2,:) = H(2,:)  +  transpose(fftshift(fft((buffer_H_left_Q(1:FFT_BUF_SIZE,k).*my_window),NFFT)));
        H(3,:) = H(3,:)  +  transpose(fftshift(fft((buffer_V_left_I(1:FFT_BUF_SIZE,k).*my_window),NFFT)));
        H(4,:) = H(4,:)  +  transpose(fftshift(fft((buffer_H_right_I(1:FFT_BUF_SIZE,k).*my_window),NFFT)));
        H(5,:) = H(5,:)  +  transpose(fftshift(fft((buffer_H_right_I(1:FFT_BUF_SIZE,k).*my_window),NFFT)));
        H(6,:) = H(6,:)  +  transpose(fftshift(fft((buffer_H_right_Q(1:FFT_BUF_SIZE,k).*my_window),NFFT)));
        H(7,:) = H(7,:)  +  transpose(fftshift(fft((buffer_V_right_I(1:FFT_BUF_SIZE,k).*my_window),NFFT)));
        H(8,:) = H(8,:)  +  transpose(fftshift(fft((buffer_V_right_Q(1:FFT_BUF_SIZE,k).*my_window),NFFT)));
    end;
    
    %     NFFT = 2048;
    
    %     [H(1,:),W] = freqz(buffer_H_left_I(1:FFT_BUF_SIZE,1).*my_window,1,NFFT,Fs);
    %     [H(2,:),W] = freqz(buffer_H_left_Q(1:FFT_BUF_SIZE,1).*my_window,1,NFFT,Fs);
    %     [H(3,:),W] = freqz(buffer_V_left_I(1:FFT_BUF_SIZE,1).*my_window,1,NFFT,Fs);
    %     [H(4,:),W] = freqz(buffer_V_left_Q(1:FFT_BUF_SIZE,1).*my_window,1,NFFT,Fs);
    %     [H(5,:),W] = freqz(buffer_H_right_I(1:FFT_BUF_SIZE,1).*my_window,1,NFFT,Fs);
    %     [H(6,:),W] = freqz(buffer_H_right_Q(1:FFT_BUF_SIZE,1).*my_window,1,NFFT,Fs);
    %     [H(7,:),W] = freqz(buffer_V_right_I(1:FFT_BUF_SIZE,1).*my_window,1,NFFT,Fs);
    %     [H(8,:),W] = freqz(buffer_V_right_Q(1:FFT_BUF_SIZE,1).*my_window,1,NFFT,Fs);
    
%     for k = 2:PCIE_NUMBER_PULSES,
%         H(1,:) = H(1,:) + transpose(freqz(buffer_H_left_I(1:FFT_BUF_SIZE,k).*my_window,1,NFFT,Fs));
%         H(2,:) = H(2,:) + transpose(freqz(buffer_H_left_Q(1:FFT_BUF_SIZE,k).*my_window,1,NFFT,Fs));
%         H(3,:) = H(3,:) + transpose(freqz(buffer_V_left_I(1:FFT_BUF_SIZE,k).*my_window,1,NFFT,Fs));
%         H(4,:) = H(4,:) + transpose(freqz(buffer_V_left_Q(1:FFT_BUF_SIZE,k).*my_window,1,NFFT,Fs));
%         H(5,:) = H(5,:) + transpose(freqz(buffer_H_right_I(1:FFT_BUF_SIZE,k).*my_window,1,NFFT,Fs));
%         H(6,:) = H(6,:) + transpose(freqz(buffer_H_right_Q(1:FFT_BUF_SIZE,k).*my_window,1,NFFT,Fs));
%         H(7,:) = H(7,:) + transpose(freqz(buffer_V_right_I(1:FFT_BUF_SIZE,k).*my_window,1,NFFT,Fs));
%         H(8,:) = H(8,:) + transpose(freqz(buffer_V_right_Q(1:FFT_BUF_SIZE,k).*my_window,1,NFFT,Fs));
%     end;
    H(1,:) = H(1,:)/FFT_BUF_SIZE*2/PCIE_NUMBER_PULSES;
    H(2,:) = H(2,:)/FFT_BUF_SIZE*2/PCIE_NUMBER_PULSES;
    H(3,:) = H(3,:)/FFT_BUF_SIZE*2/PCIE_NUMBER_PULSES;
    H(4,:) = H(4,:)/FFT_BUF_SIZE*2/PCIE_NUMBER_PULSES;
    H(5,:) = H(5,:)/FFT_BUF_SIZE*2/PCIE_NUMBER_PULSES;
    H(6,:) = H(6,:)/FFT_BUF_SIZE*2/PCIE_NUMBER_PULSES;
    H(7,:) = H(7,:)/FFT_BUF_SIZE*2/PCIE_NUMBER_PULSES;
    H(8,:) = H(8,:)/FFT_BUF_SIZE*2/PCIE_NUMBER_PULSES;
    %----------------------------------------------------------
    % Alon 26.7.2015 delete me
    %----------------------------------------------------------
    for k = 1:8,
        H(k,:) = medfilt1(  H(k,:) , 15);
    end;
    
    
    %----------------------------------------------------------
    % Alon 26.7.2015 delete me
    %----------------------------------------------------------
    StartFindPeaks = 1;
    
    SFDR = zeros(1,8);
    SNR = zeros(1,8);
    Npeaks = 30;
    for k = 1:2:8,
        [temp_PKS,temp_LOCS] = findpeaks(10*log10(abs(H(k,StartFindPeaks:end)).^2+abs(H(k+1,StartFindPeaks:end)).^2),'NPEAKS',Npeaks,'MINPEAKDISTANCE',37);
        PKS = ones(8,Npeaks);
        LOCS = ones(8,Npeaks);
        P1 = ones(8,Npeaks);
        L1 = ones(8,Npeaks);
        INDs = ones(8,Npeaks);
        
        PKS(k,1:length(temp_PKS))    = temp_PKS;
        LOCS(k,1:length(temp_LOCS))   = temp_LOCS;
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
    axis([-inf,inf,-140, -60])
    
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
    axis([-inf,inf, -140, -60])
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
    
    
    eval(['cd ' ResultsDir]);
    saveas(FigPULSE_H,'Pulse-H' ,'fig');
    saveas(FigPULSE_H,'Pulse-H' ,'jpg');
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
    axis([-inf,inf,-140, -60])
    
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
    axis([-inf,inf,-140, -60])
    
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
    
    eval(['cd ' ResultsDir]);
    saveas(FigPULSE_V,'Pulse-V' ,'fig');
    saveas(FigPULSE_V,'Pulse-V' ,'jpg')
    eval(['cd ' CurrentDir]);
    
    %......................................
    %
    %   Pulse shape
    %
    %......................................
    %     width = 5;
    %     buffer_H_left = sqrt(abs((buffer_H_left_I.^2 +buffer_H_left_Q.^2)));
    %     buffer_H_right = sqrt(abs((buffer_H_right_I.^2 +buffer_H_right_Q.^2)));
    %     buffer_V_left = sqrt(abs((buffer_V_left_I.^2 +buffer_V_left_Q.^2)));
    %     buffer_V_right = sqrt(abs((buffer_V_right_I.^2 +buffer_V_right_Q.^2)));
    %
    %
    %     [~,pulse_postion_H_left_ind] = max(buffer_H_left);
    %     [~,pulse_postion_H_right_ind] = max(buffer_H_right);
    %     [~,pulse_postion_V_left_ind] = max(buffer_V_left);
    %     [~,pulse_postion_V_right_ind] = max(buffer_V_right);
    %
    %
    %     pulse_postion_H_left = round(mean(pulse_postion_H_left_ind));
    %     pulse_postion_H_right = round(mean(pulse_postion_H_right_ind));
    %     pulse_postion_V_left = round(mean(pulse_postion_V_left_ind));
    %     pulse_postion_V_right = round(mean(pulse_postion_V_right_ind));
    %
    %
    %     pulse_H_left = buffer_H_left(pulse_postion_H_left - width:pulse_postion_H_left + width,:);
    %     pulse_H_right = buffer_H_right(pulse_postion_H_right - width:pulse_postion_H_right + width,:);
    %     pulse_V_left = buffer_V_left(pulse_postion_V_left - width:pulse_postion_V_left + width,:);
    %     pulse_V_right = buffer_V_right(pulse_postion_V_right - width:pulse_postion_V_right + width,:);
    %
    % %     pulse_H_left_avg = mean(pulse_H_left,2);
    % %     pulse_H_right_avg = mean(pulse_H_right,2);
    % %     pulse_V_left_avg = mean(pulse_V_left,2);
    % %     pulse_V_right_avg = mean(pulse_V_right,2);
    %
    %     pulse_H_left_avg = pulse_H_left(:,1);
    %     pulse_H_right_avg = pulse_H_right(:,1);
    %     pulse_V_left_avg = pulse_V_left(:,1);
    %     pulse_V_right_avg = pulse_V_right(:,1);
    %
    %     t = -5:0.1:5.9;
    %     %[curve, gof] = fit(pulse_H_left_avg,(-width:width)', 'poly2');
    %     curve_H_left_avg = interp(pulse_H_left_avg, 10);
    %     curve_V_left_avg = interp(pulse_V_left_avg, 10);
    %     curve_H_right_avg = interp(pulse_H_right_avg, 10);
    %     curve_V_right_avg = interp(pulse_V_right_avg, 10);
    %
    %     FigPULSE_shape = figure;
    %
    %     subplot(221);
    %     plot(-width:width,20*log10(pulse_H_left_avg),'ko');
    %     hold on
    %     grid on
    %     plot(t, 20*log10(curve_H_left_avg), 'r');
    %     xlabel('Range Sample # (1 sample = 3 meter)')
    %     ylabel('Magnitude [dB]');
    %     title(['Pulse at H left  max:' num2str(pulse_postion_H_left)]);
    %
    %     subplot(222);
    %     plot(-width:width,20*log10(pulse_H_right_avg),'ko');
    %     hold on
    %     grid on
    %     plot(t,20*log10( curve_H_right_avg), 'r');
    %     xlabel('Range Sample # (1 sample = 3 meter)')
    %     ylabel('Magnitude [dB]');
    %     title(['Pulse at H right  max:' num2str(pulse_postion_H_right)] );
    %
    %     subplot(223);
    %     plot(-width:width,20*log10(pulse_V_left_avg),'ko');
    %     hold on
    %     grid on
    %     plot(t, 20*log10(curve_V_left_avg), 'r');
    %     xlabel('Range Sample # (1 sample = 3 meter)')
    %     ylabel('Magnitude [dB]');
    %     title(['Pulse at V left  max:'  num2str(pulse_postion_V_left)]);
    %
    %     subplot(224);
    %     plot(-width:width,20*log10(pulse_V_right_avg),'ko');
    %     hold on
    %     grid on
    %     plot(t, 20*log10(curve_V_right_avg), 'r');
    %     xlabel('Range Sample # (1 sample = 3 meter)')
    %     ylabel('Magnitude [dB]');
    %     title(['Pulse at V right  max:' num2str(pulse_postion_V_right)]);
    %
    %     eval(['cd ' ResultsDir]);
    %     saveas(FigPULSE_shape,'Pulse_shape' ,'fig');
    %     saveas(FigPULSE_shape,'Pulse_shape' ,'jpg')
    %     eval(['cd ' CurrentDir]);
    
    FigJohn = figure;
    
    subplot(221)
    plot(t,20*log10(abs(buffer_H_left_I')))
    S1 = sprintf('H-Left I');
    xlabel('[Samples]')
    ylabel('[dB]')
    title(S1)
    axis([120,140, -65, -30])
    grid on
    
    subplot(222)
    plot(t,20*log10(abs(buffer_H_left_Q')))
    S1 = sprintf('H-left Q');
    legend(S1,S2);legend('boxoff','Orientation','horizontal')
    xlabel('[Samples]')
    ylabel('[dB]')
    title(S1)
     axis([120,140, -65, -30])
    grid on
    
    subplot(223)
    plot(t,20*log10(abs(buffer_V_left_I')))
    S1 = sprintf('V-Left I');
    xlabel('[Samples]')
    ylabel('[dB]')
    title(S1)
    axis([120,140, -65, -30])
    grid on
    
    subplot(224)
    plot(t,20*log10(abs(buffer_V_left_Q')))
    S1 = sprintf('V-left Q');
    legend(S1,S2);legend('boxoff','Orientation','horizontal')
    xlabel('[Samples]')
    ylabel('[dB]')
    title(S1)
     axis([120,140, -65, -30])
    grid on
    
     eval(['cd ' ResultsDir]);
    saveas(FigJohn,'FigJohn_left' ,'fig');
    saveas(FigJohn,'FigJohn_left' ,'jpg')
    eval(['cd ' CurrentDir]);
    
     FigJohn = figure;
    
    subplot(221)
    plot(t,20*log10(abs(buffer_H_right_I')))
    S1 = sprintf('H-right I');
    xlabel('[Samples]')
    ylabel('[dB]')
    title(S1)
    axis([120,140, -65, -30])
    grid on
    
    subplot(222)
    plot(t,20*log10(abs(buffer_H_right_Q')))
    S1 = sprintf('H-right Q');
    legend(S1,S2);legend('boxoff','Orientation','horizontal')
    xlabel('[Samples]')
    ylabel('[dB]')
    title(S1)
     axis([120,140, -65, -30])
    grid on
    
    subplot(223)
    plot(t,20*log10(abs(buffer_V_right_I')))
    S1 = sprintf('V-right I');
    xlabel('[Samples]')
    ylabel('[dB]')
    title(S1)
    axis([120,140, -65, -30])
    grid on
    
    subplot(224)
    plot(t,20*log10(abs(buffer_V_right_Q')))
    S1 = sprintf('V-right Q');
    legend(S1,S2);legend('boxoff','Orientation','horizontal')
    xlabel('[Samples]')
    ylabel('[dB]')
    title(S1)
     axis([120,140, -65, -30])
    grid on
    
     eval(['cd ' ResultsDir]);
    saveas(FigJohn,'FigJohn_right' ,'fig');
    saveas(FigJohn,'FigJohn_right' ,'jpg')
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
