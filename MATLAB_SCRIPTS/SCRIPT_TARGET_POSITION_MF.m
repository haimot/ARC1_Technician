%----------------------------------------------
%   SCRIPT_TARGET_POSITION
%
%
%   1 - Pulse in time
%   2 - timing and I&Q histograms
%   3 - SNR visualization
%
%   Improvements:
%   17.5.2015:     Based on pulse test, but taking the maximum as an indication.
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
    SERVICE_READ_SCRIPT_DATA;
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
    abs_H_left = 10 * log10(  abs(buffer_H_left_I + 1j * buffer_H_left_Q)  + eps );
    plot(t,abs_H_left')
    %plot(t,buffer_H_left_I',t,buffer_H_left_Q')
    legend('I_1','Q_1','Orientation','horizontal');legend('boxoff')
    xlabel('[Samples]')
    S0 = sprintf('CHA_1: Vpp = %1.2f',2*max(max(sqrt(buffer_H_left_I.^2+buffer_H_left_Q.^2))));
    [~,max_db_H_left] = max(abs_H_left(:,1));
    mean_sample(1,4) = mean(abs_H_left(max_db_H_left,:));
    mean_sample(1,5) = mean(abs_H_left(max_db_H_left + 1,:));
    mean_sample(1,6) = mean(abs_H_left(max_db_H_left + 2,:));
    mean_sample(1,7) = mean(abs_H_left(max_db_H_left + 3,:));
    mean_sample(1,3) = mean(abs_H_left(max_db_H_left - 1,:));
    mean_sample(1,2) = mean(abs_H_left(max_db_H_left - 2,:));
    mean_sample(1,1) = mean(abs_H_left(max_db_H_left - 3,:));
    title(S0)
    axis([-inf inf -60 0])
   % axis([-inf inf -1 1])
    grid on
    
    subplot(222)
    abs_V_left = 10 * log10(  abs(buffer_V_left_I + 1j * buffer_V_left_Q) + eps );
    plot(t,abs_V_left')
    %plot(t,buffer_V_left_I',t,buffer_V_left_Q')
    legend('I_2','Q_2','Orientation','horizontal');legend('boxoff')
    xlabel('[Samples]')
    S0 = sprintf('CHA_2: Vpp = %1.2f',2*max(max(sqrt(buffer_V_left_I.^2+buffer_V_left_Q.^2))));
    [~,max_db_V_left] = max(abs_V_left(:,1));
   mean_sample(3,4) = mean(abs_V_left(max_db_V_left,:));
    mean_sample(3,5) = mean(abs_V_left(max_db_V_left + 1,:));
    mean_sample(3,6) = mean(abs_V_left(max_db_V_left + 2,:));
    mean_sample(3,7) = mean(abs_V_left(max_db_V_left + 3,:));
    mean_sample(3,3) = mean(abs_V_left(max_db_V_left - 1,:));
    mean_sample(3,2) = mean(abs_V_left(max_db_V_left - 2,:));
    mean_sample(3,1) = mean(abs_V_left(max_db_V_left - 3,:));
    title(S0)
    axis([-inf inf -60 0])
  %  axis([-inf inf -1 1])
    grid on
    
    subplot(223)
    abs_H_right = 10 * log10(  abs(buffer_H_right_I + 1j * buffer_H_right_Q) + eps );
    plot(t,abs_H_right')
    %plot(t,buffer_H_right_I',t,buffer_H_right_Q')
    legend('I_1','Q_1','Orientation','horizontal');legend('boxoff')
    xlabel('[Samples]')
    S0 = sprintf('CHB_1: Vpp = %1.2f',2*max(max(sqrt(buffer_H_right_I.^2+buffer_H_right_Q.^2))));
    [~,max_db_H_right] = max(abs_H_right(:,1));
    mean_sample(2,4) = mean(abs_H_right(max_db_H_right,:));
    mean_sample(2,5) = mean(abs_H_right(max_db_H_right + 1,:));
    mean_sample(2,6) = mean(abs_H_right(max_db_H_right + 2,:));
    mean_sample(2,7) = mean(abs_H_right(max_db_H_right + 3,:));
    mean_sample(2,3) = mean(abs_H_right(max_db_H_right - 1,:));
    mean_sample(2,2) = mean(abs_H_right(max_db_H_right - 2,:));
    mean_sample(2,1) = mean(abs_H_right(max_db_H_right - 3,:));
    title(S0)
    axis([-inf inf -60 0])
%    axis([-inf inf -1 1])
    grid on
    
    subplot(224)
    abs_V_right = 10 * log10(  abs(buffer_V_right_I + 1j * buffer_V_right_Q)  + eps );
    plot(t,abs_V_right')
    %plot(t,buffer_V_right_I',t,buffer_V_right_Q')
    legend('I_2','Q_2','Orientation','horizontal');legend('boxoff')
    xlabel('[Samples]')
    S0 = sprintf('CHB_2: Vpp = %1.2f',2*max(max(sqrt(buffer_V_right_I.^2+buffer_V_right_Q.^2))));
   [~,max_db_V_right] = max(abs_V_right(:,1));
    mean_sample(4,4) = mean(abs_V_right(max_db_V_right,:));
    mean_sample(4,5) = mean(abs_V_right(max_db_V_right + 1,:));
    mean_sample(4,6) = mean(abs_V_right(max_db_V_right + 2,:));
    mean_sample(4,7) = mean(abs_V_right(max_db_V_right + 3,:));
    mean_sample(4,3) = mean(abs_V_right(max_db_V_right - 1,:));
    mean_sample(4,2) = mean(abs_V_right(max_db_V_right - 2,:));
    mean_sample(4,1) = mean(abs_V_right(max_db_V_right - 3,:));
    title(S0)
    axis([-inf inf -60 0])
  %  axis([-inf inf -1 1])
    grid on
    
    eval(['cd ' ResultsDir]);
    saveas(FigPULSE,'Pulses' ,'fig');
    saveas(FigPULSE,'Pulses' ,'jpg');
    eval(['cd ' CurrentDir]);
    %-------------------------------------------------
    %    Sinc analysis - Range
    %-------------------------------------------------
    FigSYNC1 = figure('units','normalized','outerposition',[0 0 1 1]);
    set(FigSYNC1,'WindowStyle','docked')
   
    for k = 1:4,
        switch k,
            case 1
                temp = abs(buffer_H_left_I.^2 + buffer_H_left_Q.^2);
                sig_name = 'H left';
            case 2
                temp = abs(buffer_H_right_I.^2 + buffer_H_right_Q.^2);
                sig_name = 'H right';
            case 3
                temp = abs(buffer_V_left_I.^2 + buffer_V_left_Q.^2);
                sig_name = 'V left';
            case 4
                temp = abs(buffer_V_right_I.^2 + buffer_V_right_Q.^2);
                sig_name = 'V right';
        end;
        [~,estimated_range] = max(temp);
        subplot(2,2,k)
       hist(estimated_range - 1);
        E_hist = mean(estimated_range) - 1;
        var_hist = std(estimated_range);
        range_mean_var(k,1) = E_hist;
        range_mean_var(k,2) = var_hist;
        axis tight
        xlabel('estimated range [samples]')
        title([sig_name '  E = ' num2str(E_hist) ' std =  ' num2str(var_hist)] )
    end;
    
    eval(['cd ' ResultsDir]);
    saveas(FigSYNC1,'Amplitude_SYNC' ,'fig');
    saveas(FigSYNC1,'Amplitude_SYNC' ,'jpg');
    eval(['cd ' CurrentDir]);
    %-------------------------------------------------
    %    Sinc analysis - Phase I/Q
    %-------------------------------------------------
    FigSYNC2 = figure('units','normalized','outerposition',[0 0 1 1]);
    set(FigSYNC2,'WindowStyle','docked')
    
    for k = 1:8,
        switch k,
            case 1
                sig_name = 'H left I';
                temp = buffer_H_left_I;
            case 2
                sig_name = 'H left Q';
                 temp = buffer_H_left_Q;
            case 3
                sig_name = 'H right I';
                temp = buffer_H_right_I;
            case 4
                sig_name = 'H right Q';
                temp = buffer_H_right_Q;
            case 5
                sig_name = 'V left I';
                temp = buffer_V_left_I;
            case 6
                sig_name = 'V left Q';
                temp = buffer_V_left_Q;
            case 7
                sig_name = 'V right I';
                temp = buffer_V_right_I;
            case 8
                sig_name = 'V right Q';
                temp = buffer_V_right_Q;
        end;
        for p = 1:PCIE_NUMBER_PULSES,
            IQ(p,k) = temp(estimated_range(p), p);
            IQ(p,k) = floor(IQ(p,k)*1000)/1000;       % resolution of 3 digits.
        end;
        
        subplot(2,4,k);
        hist(IQ(:,k));
        E_hist_IQ = mean(IQ(:,k));
        var_hist_IQ = std(IQ(:,k));
        IQ_mean_var_temp(k,1) = E_hist_IQ;
        IQ_mean_var_temp(k,2) = var_hist_IQ;
        axis([-inf inf -inf inf]);
        xlabel('estimated amplitude')
        %title(sig_name)
        title([sig_name '  E = ' num2str(E_hist_IQ) ' std =  ' num2str(var_hist_IQ)] )
    end;
    IQ_complex(:,1) = IQ(:,1) + 1j*IQ(:,2);
    IQ_complex(:,2) = IQ(:,3) + 1j*IQ(:,4);
    IQ_complex(:,3) = IQ(:,5) + 1j*IQ(:,6);
    IQ_complex(:,4) = IQ(:,7) + 1j*IQ(:,8);
    IQ_Phase = angle(IQ_complex);
    IQ_complex_mean_var(1,1) = mean( IQ_Phase(:,1));
    IQ_complex_mean_var(1,2) = std( IQ_Phase(:,1));
    IQ_complex_mean_var(2,1) = mean( IQ_Phase(:,2));
    IQ_complex_mean_var(2,2) = std( IQ_Phase(:,2));
    IQ_complex_mean_var(3,1) = mean( IQ_Phase(:,3));
    IQ_complex_mean_var(3,2) = std( IQ_Phase(:,3));
    IQ_complex_mean_var(4,1) = mean( IQ_Phase(:,4));
    IQ_complex_mean_var(4,2) = std( IQ_Phase(:,4));
    IQ_mean_var(1,1) = IQ_mean_var_temp(1,1);
    IQ_mean_var(1,2) = IQ_mean_var_temp(1,2);
    IQ_mean_var(1,3) = IQ_mean_var_temp(2,1);
    IQ_mean_var(1,4) = IQ_mean_var_temp(2,2);
    IQ_mean_var(2,1) = IQ_mean_var_temp(3,1);
    IQ_mean_var(2,2) = IQ_mean_var_temp(3,2);
    IQ_mean_var(2,3) = IQ_mean_var_temp(4,1);
    IQ_mean_var(2,4) = IQ_mean_var_temp(4,2);
    IQ_mean_var(3,1) = IQ_mean_var_temp(5,1);
    IQ_mean_var(3,2) = IQ_mean_var_temp(5,2);
    IQ_mean_var(3,3) = IQ_mean_var_temp(6,1);
    IQ_mean_var(3,4) = IQ_mean_var_temp(6,2);
    IQ_mean_var(4,1) = IQ_mean_var_temp(7,1);
    IQ_mean_var(4,2) = IQ_mean_var_temp(7,2);
    IQ_mean_var(4,3) = IQ_mean_var_temp(8,1);
    IQ_mean_var(4,4) = IQ_mean_var_temp(8,2);
     IQ_HL = sqrt(IQ(:,1).^2+IQ(:,2).^2);
     IQ_HR = sqrt(IQ(:,3).^2+IQ(:,4).^2);
     IQ_VL = sqrt(IQ(:,5).^2+IQ(:,6).^2);
     IQ_VR = sqrt(IQ(:,7).^2+IQ(:,8).^2);
     abs_mean_var(1,1) = mean(IQ_HL);
     abs_mean_var(1,2) = std(IQ_HL);
     abs_mean_var(2,1) = mean(IQ_HR);
     abs_mean_var(2,2) = std(IQ_HR);
     abs_mean_var(3,1) = mean(IQ_VL);
     abs_mean_var(3,2) = std(IQ_VL);
     abs_mean_var(4,1) = mean(IQ_VR);
     abs_mean_var(4,2) = std(IQ_VR);
    eval(['cd ' ResultsDir]);
    saveas(FigSYNC2,'Amplitude_histograms' ,'fig');
    saveas(FigSYNC2,'Amplitude_histograms' ,'jpg');
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
    Npeaks = 30;
    for k = 1:2:8,
        [temp_PKS,temp_LOCS] = findpeaks(10*log10(abs(H(k,StartFindPeaks:end)).^2+abs(H(k+1,StartFindPeaks:end)).^2),'NPEAKS',Npeaks,'MINPEAKDISTANCE',37);
        if (length(temp_PKS) == Npeaks)
            PKS(k,:)    = temp_PKS;
            LOCS(k,:)   = temp_LOCS;
            LOCS(k,:) = LOCS(k,:) + StartFindPeaks -1;
            [P1(k,:),INDs(k,:)]  = sort(PKS(k,:),'descend');
            L1(k,:) = LOCS(k,INDs(k,:));
            SFDR(k) = P1(k,1)-P1(k,2);
            SNR(k) = P1(k,1)-max(P1(k,12:30));
        end;
    end;
    %     %......................................
    %     %                        H
    %     %.......................................
    %     FigPULSE_H = figure('units','normalized','outerposition',[0 0 1 1]);
    %     set(FigPULSE_H,'WindowStyle','docked')
    %     %......................................
    %     %          Frequency domain
    %     %......................................
    %     subplot(241)
    %     plot(W,10*log10(abs(H(1,:)).^2+abs(H(2,:)).^2))
    %     for k = 1:6,
    %         hold on;
    %         plot(W(L1(1,k+1)),P1(1,k+1),'*');
    %         text(W(L1(1,k+1)),P1(1,k+1)+10,num2str(k));
    %     end;
    %     hold on
    %     line([W(1) W(end)],[mean(max(P1(1,12:30))) mean(max(P1(1,12:30)))],'LineStyle','--','Color','r');
    %     xlabel('[Hz]')
    %     ylabel('dB')
    %     S0 = sprintf('H-Left: SNR %2.1f SFDR %2.1f',mean(SNR(1)),mean(SFDR(1)));
    %     title(S0)
    %     xlabel('[Hz]')
    %     ylabel('dB')
    %     grid on
    %     axis([-inf,inf,-140, 0])
    %
    %     subplot(243)
    %     plot(W,10*log10(abs(H(5,:)).^2+abs(H(6,:)).^2))
    %     for k = 1:6,
    %         hold on;
    %         plot(W(L1(5,k+1)),P1(5,k+1),'*');
    %         text(W(L1(5,k+1)),P1(5,k+1)+10,num2str(k));
    %     end;
    %     hold on
    %     line([W(1) W(end)],[mean(max(P1(5,12:30))) mean(max(P1(5,12:30)))],'LineStyle','--','Color','r');
    %     S0 = sprintf('H-Right: SNR %2.1f SFDR %2.1f',mean(SNR(5)),mean(SFDR(5)));
    %     title(S0)
    %     xlabel('[Hz]')
    %     ylabel('dB')
    %     grid on
    %     axis([-inf,inf, -140, 0])
    %     %......................................
    %     %   Time domain
    %     %......................................
    %     t = (0:length(buffer_H_right_I)-1);
    %     subplot(425)
    %     plot(t,buffer_H_left_I',t,buffer_H_left_Q')
    %     S1 = sprintf('H-Left I');
    %     S2 = sprintf('H-Left Q');
    %     legend(S1,S2);legend('boxoff','Orientation','horizontal')
    %     xlabel('[Samples]')
    %     % S0 = sprintf('H-Left: Vpp = %1.2f',max(max(abs([buffer_H_left_I buffer_H_left_Q]))));
    %     % title(S0)
    %     axis([-inf inf -1 1])
    %     grid on
    %
    %     t = (0:length(buffer_H_right_I)-1);
    %     subplot(426)
    %     plot(t,buffer_H_right_I',t,buffer_H_right_Q')
    %     S1 = sprintf('H-Right I');
    %     S2 = sprintf('H-Right Q');
    %     legend(S1,S2);legend('boxoff','Orientation','horizontal')
    %     xlabel('[Samples]')
    %     % S0 = sprintf('H-Right: Vpp = %1.2f',max(max(abs([buffer_H_right_I buffer_H_right_Q]))));
    %     % title(S0)
    %     axis([-inf inf -1 1])
    %     grid on
    %
    %     subplot(427)
    %     plot(t,20*log10(abs(buffer_H_left_I')),t,20*log10(abs(buffer_H_left_Q')))
    %     S1 = sprintf('H-Left I');
    %     S2 = sprintf('H-Left Q');
    %     legend(S1,S2);legend('boxoff','Orientation','horizontal')
    %     xlabel('[Samples]')
    %     ylabel('[dB]')
    %     % S0 = sprintf('H-Left: Vpp = %1.2f',max(max(abs([buffer_H_left_I buffer_H_left_Q]))));
    %     % title(S0)
    %     axis([-inf,inf, -90, 0])
    %     grid on
    %
    %     subplot(428)
    %     plot(t,20*log10(abs(buffer_H_right_I')),t,20*log10(abs(buffer_H_right_Q')))
    %     S1 = sprintf('H-Right I');
    %     S2 = sprintf('H-Right Q');
    %     legend(S1,S2);legend('boxoff','Orientation','horizontal')
    %     xlabel('[Samples]')
    %     ylabel('[dB]')
    %     % S0 = sprintf('H-Right: Vpp = %1.2f',max(max(abs([buffer_H_right_I buffer_H_right_Q]))));
    %     % title(S0)
    %     axis([-inf,inf, -90, 0])
    %     grid on
    %     %......................................
    %     %   Histograms
    %     %......................................
    %     x = linspace(-0.02,0.02,1000);
    %     subplot(442);
    %     hist(buffer_H_left_I(:,1),x)
    %     xlabel('magnitude [V]');
    %     title(['H-Left I: s.d. = ' num2str(std(buffer_H_left_I(:,1))) ' [V]']);
    %     subplot(446);
    %     hist(buffer_H_left_Q(:,1),x)
    %     xlabel('magnitude [V]');
    %     title(['H-Left Q: s.d. = ' num2str(std(buffer_H_left_Q(:,1))) ' [V]']);
    %     subplot(444);
    %     hist(buffer_H_right_I(:,1),x)
    %     xlabel('magnitude [V]');
    %     title(['H-Right I: s.d. = ' num2str(std(buffer_H_right_I(:,1))) ' [V]']);
    %     subplot(448);
    %     hist(buffer_H_right_Q(:,1),x)
    %     xlabel('magnitude [V]');
    %     title(['H-Right Q: s.d. = ' num2str(std(buffer_H_right_Q(:,1))) ' [V]']);
    %
    %
    %     eval(['cd ' ResultsDir]);
    %     saveas(FigPULSE_H,'Pulse-H' ,'fig');
    %     saveas(FigPULSE_H,'Pulse-H' ,'jpg');
    %     eval(['cd ' CurrentDir]);
    %
    %     %......................................
    %     %                        V
    %     %.......................................
    %     FigPULSE_V = figure('units','normalized','outerposition',[0 0 1 1]);
    %     set(FigPULSE_V,'WindowStyle','docked')
    %     %......................................
    %     %   Frequency domain
    %     %......................................
    %     subplot(241)
    %     plot(W,10*log10(abs(H(3,:)).^2+abs(H(4,:)).^2))
    %     for k = 1:6,
    %         hold on;
    %         plot(W(L1(3,k+1)),P1(3,k+1),'*');
    %         text(W(L1(3,k+1)),P1(3,k+1)+10,num2str(k));
    %     end;
    %     hold on
    %     line([W(1) W(end)],[mean(max(P1(3,12:30))) mean(max(P1(3,12:30)))],'LineStyle','--','Color','r');
    %     xlabel('[Hz]')
    %     ylabel('dB')
    %     S0 = sprintf('V-Left: SNR %2.1f SFDR %2.1f',mean(SNR(3)),mean(SFDR(3)));
    %     title(S0)
    %     xlabel('[Hz]')
    %     ylabel('dB')
    %     grid on
    %     axis([-inf,inf,-140, 0])
    %
    %     subplot(243)
    %     plot(W,10*log10(abs(H(7,:)).^2+abs(H(8,:)).^2))
    %     for k = 1:6,
    %         hold on;
    %         plot(W(L1(7,k+1)),P1(7,k+1),'*');
    %         text(W(L1(7,k+1)),P1(7,k+1)+10,num2str(k));
    %     end;
    %     hold on
    %     line([W(1) W(end)],[mean(max(P1(7,12:30))) mean(max(P1(7,12:30)))],'LineStyle','--','Color','r');
    %     xlabel('[Hz]')
    %     ylabel('dB')
    %     S0 = sprintf('V-Right: SNR %2.1f SFDR %2.1f',mean(SNR(7)),mean(SFDR(7)));
    %     title(S0)
    %     xlabel('[Hz]')
    %     ylabel('dB')
    %     grid on
    %     axis([-inf,inf,-140, 0])
    %
    %     %......................................
    %     %   Time domain
    %     %......................................
    %     t = (0:length(buffer_H_right_I)-1);
    %     subplot(425)
    %     plot(t,buffer_V_left_I',t,buffer_V_left_Q')
    %     S1 = sprintf('V-Left I');
    %     S2 = sprintf('V-Left Q');
    %     legend(S1,S2);legend('boxoff','Orientation','horizontal')
    %     xlabel('[Samples]')
    %     % S0 = sprintf('V-Left: Vpp = %1.2f',max(max(abs([buffer_V_left_I buffer_V_left_Q]))));
    %     % title(S0)
    %     axis([-inf inf -1 1])
    %     grid on
    %
    %     t = (0:length(buffer_H_right_I)-1);
    %     subplot(426)
    %     plot(t,buffer_V_right_I',t,buffer_V_right_Q')
    %     S1 = sprintf('V-Right I');
    %     S2 = sprintf('V-Right Q');
    %     legend(S1,S2);legend('boxoff','Orientation','horizontal')
    %     xlabel('[Samples]')
    %     % S0 = sprintf('V-Right: Vpp = %1.2f',max(max(abs([buffer_V_right_I buffer_V_right_Q]))));
    %     % title(S0)
    %     axis([-inf inf -1 1])
    %     grid on
    %
    %     subplot(427)
    %     plot(t,20*log10(abs(buffer_V_left_I')),t,20*log10(abs(buffer_V_left_Q')))
    %     S1 = sprintf('V-Left I');
    %     S2 = sprintf('V-Left Q');
    %     legend(S1,S2);legend('boxoff','Orientation','horizontal')
    %     xlabel('[Samples]')
    %     ylabel('[dB]')
    %     % S0 = sprintf('V-Left: Vpp = %1.2f',max(max(abs([buffer_V_left_I buffer_V_left_Q]))));
    %     % title(S0)
    %     axis([-inf,inf, -90, 0])
    %     grid on
    %
    %     subplot(428)
    %     plot(t,20*log10(abs(buffer_V_right_I')),t,20*log10(abs(buffer_V_right_Q')))
    %     S1 = sprintf('V-Right I');
    %     S2 = sprintf('V-Right Q');
    %     legend(S1,S2);legend('boxoff','Orientation','horizontal')
    %     xlabel('[Samples]')
    %     ylabel('[dB]')
    %     % S0 = sprintf('V-Right: Vpp = %1.2f',max(max(abs([buffer_V_right_I buffer_V_right_Q]))));
    %     % title(S0)
    %     axis([-inf,inf, -90, 0])
    %     grid on
    %
    %     %......................................
    %     %   Histograms
    %     %......................................
    %     x = linspace(-0.02,0.02,1000);
    %     subplot(442);
    %     hist(buffer_V_left_I(:,1),x)
    %     xlabel('magnitude [V]');
    %     title(['V-Left I: s.d. = ' num2str(std(buffer_V_left_I(:,1))) ' [V]']);
    %     subplot(446);
    %     hist(buffer_V_left_Q(:,1),x)
    %     xlabel('magnitude [V]');
    %     title(['V-Left Q: s.d. = ' num2str(std(buffer_V_left_Q(:,1))) ' [V]']);
    %     subplot(444);
    %     hist(buffer_V_right_I(:,1),x)
    %     xlabel('magnitude [V]');
    %     title(['V-Right I: s.d. = ' num2str(std(buffer_V_right_I(:,1))) ' [V]']);
    %     subplot(448);
    %     hist(buffer_V_right_Q(:,1),x)
    %     xlabel('magnitude [V]');
    %     title(['V-Right Q: s.d. = ' num2str(std(buffer_V_right_Q(:,1))) ' [V]']);
    %
    %     eval(['cd ' ResultsDir]);
    %     saveas(FigPULSE_V,'Pulse-V' ,'fig');
    %     saveas(FigPULSE_V,'Pulse-V' ,'jpg')
    %     eval(['cd ' CurrentDir]);
    
    res_matrix = range_mean_var;
    res_matrix = horzcat(res_matrix,IQ_mean_var);
    res_matrix = horzcat(res_matrix,abs_mean_var);
    res_matrix = horzcat(res_matrix,IQ_complex_mean_var);
    res_matrix = horzcat(res_matrix,mean_sample);
    
    
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
