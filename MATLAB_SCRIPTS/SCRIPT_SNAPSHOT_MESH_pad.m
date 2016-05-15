%----------------------------------------------
%   SCRIPT_TARGETS
%
%
%   1 - Matched filter in time
%   2 - Histograms
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
    SERVICE_READ_SCRIPT_DATA2;
    %==================================================
    %==================================================
    %
    %
    %               Processing data
    %
    %
    %==================================================
    %==================================================
    %--------------------------------------------------
    %     Match filter due transmited filter
    %--------------------------------------------------
    FRAME_start = 1;
%     profile_0 = [];
%     profile_1 = [1 1 1 1 1 -1 -1 1 1 -1 1 -1 1];
%     profile_2 = [1 1 1 1 1 1 1 1 1 1 1 1 1];
%     profile_3 = [1 1 1 1 1 1 1 1 1];
%     profile_4 = [1 1 1 1 1 1 1 ];
%     profile_5 = [1 1 1 1 1];
%     profile_6 = [1 1 1];
%     profile_7 = [1];
%     switch (Profile_AD9910A)
%         case 0,
%             signal = profile_0;
%         case 1,
%             signal = profile_1;
%             FRAME_start = 1;
%         case 2,
%             signal = profile_2;
%         case 3,
%             signal = profile_3;
%         case 4,
%             signal = profile_4;
%         case 5,
%             signal = profile_5;
%         case 6,
%             signal = profile_6;
%         case 7,
%             signal = profile_7;
%             FRAME_start = 1;
%     end;
%     chip_length     = chip_length_AD9910A;
%     samples_Number  = length(signal) * Fs * chip_length *4/0.6*1e-9;
%     Matched_sig     = signal(round(linspace(1,length(signal),samples_Number)));
%     MatchedFilter   = Matched_sig + 1j*Matched_sig;
    %--------------------------------------------------
    %     Start form IO_UPDATE
    %--------------------------------------------------
    FRAME_samples = RANGE_samples; %FRAME_distance*2/3e8*Fs
    
    t = (0: FRAME_samples-2);
    
%     TGT_H_left_I = buffer_H_left_I(FRAME_start:FRAME_samples-1,:);
%     TGT_H_left_Q = buffer_H_left_Q(FRAME_start:FRAME_samples-1,:);
%     TGT_V_left_I = buffer_V_left_I(FRAME_start:FRAME_samples-1,:);
%     TGT_V_left_Q = buffer_V_left_Q(FRAME_start:FRAME_samples-1,:);
%     TGT_H_right_I = buffer_H_right_I(FRAME_start:FRAME_samples-1,:);
%     TGT_H_right_Q = buffer_H_right_Q(FRAME_start:FRAME_samples-1,:);
%     TGT_V_right_I = buffer_V_right_I(FRAME_start:FRAME_samples-1,:);
%     TGT_V_right_Q = buffer_V_right_Q(FRAME_start:FRAME_samples-1,:);
    %--------------------------------------------------
    %     Zero blind intervea;
    %--------------------------------------------------
%     TGT_H_left_I(1:20,:) = 0;
%     TGT_H_left_Q(1:20,:) = 0;
%     TGT_V_left_I(1:20,:) = 0;
%     TGT_V_left_Q(1:20,:) = 0;
%     TGT_H_right_I(1:20,:) = 0;
%     TGT_H_right_Q(1:20,:) = 0;
%     TGT_V_right_I(1:20,:) = 0;
%     TGT_V_right_Q(1:20,:) = 0;
    %----------------------------------------
    %  Matched filter
    %----------------------------------------
%     TGT_H_left_I_mf  = filter(fliplr(Matched_sig),1,TGT_H_left_I);
%     TGT_H_left_Q_mf  = filter(fliplr(Matched_sig),1,TGT_H_left_Q);
%     TGT_V_left_I_mf  = filter(fliplr(Matched_sig),1,TGT_V_left_I);
%     TGT_V_left_Q_mf  = filter(fliplr(Matched_sig),1,TGT_V_left_Q);
%     TGT_H_right_I_mf = filter(fliplr(Matched_sig),1,TGT_H_right_I);
%     TGT_H_right_Q_mf = filter(fliplr(Matched_sig),1,TGT_H_right_Q);
%     TGT_V_right_I_mf = filter(fliplr(Matched_sig),1,TGT_V_right_I);
%     TGT_V_right_Q_mf = filter(fliplr(Matched_sig),1,TGT_V_right_Q);
    %----------------------------------------
    %   ABS mesh
    %----------------------------------------
    TGT_H_left_mf  = buffer_H_left_I + 1j*buffer_H_left_Q;
    TGT_V_left_mf  = buffer_V_left_I + 1j*buffer_V_left_Q;
    TGT_H_right_mf = buffer_H_right_I + 1j*buffer_H_right_Q;
    TGT_V_right_mf = buffer_V_right_I + 1j*buffer_V_right_Q;
    
%     TGT_H_left_mf  = abs(TGT_H_left_mf);
%     TGT_V_left_mf  = abs(TGT_V_left_mf);
%     TGT_H_right_mf  = abs(TGT_H_right_mf);
%     TGT_V_right_mf  = abs(TGT_V_right_mf);
    %----------------------------------------
    %   ABS average
    %----------------------------------------
%     TGT_H_left_mf_mean = sqrt(mean(TGT_H_left_I_mf,2).^2+mean(TGT_H_left_Q_mf,2).^2);
%     TGT_V_left_mf_mean = sqrt(mean(TGT_V_left_I_mf,2).^2+mean(TGT_V_left_Q_mf,2).^2);
%     TGT_H_right_mf_mean = sqrt(mean(TGT_H_right_I_mf,2).^2+mean(TGT_H_right_Q_mf,2).^2);
%     TGT_V_right_mf_mean = sqrt(mean(TGT_V_right_I_mf,2).^2+mean(TGT_V_right_Q_mf,2).^2);
    %----------------------------------------
    %   Plotting: 
    %----------------------------------------
    %----------------------------------------
    %   mesh dB scale
    %----------------------------------------
%     Fig_TGT_MESH= figure('units','normalized','outerposition',[0 0 1 1]);
%     set(Fig_TGT_MESH,'WindowStyle','docked')
%     mesh(1:Number_of_buffers,t,20*log10(TGT_H_left_mf))
%     hold on;
%     plot3(ones(1,length(t)),t,20*log10(TGT_H_left_mf_mean)+40,'linewidth',2,'Color','k')
%     view(124,52)
%     xlabel('Buffer #');
%     ylabel('range [m]')
%     title('H left')
%     eval(['cd ' ResultsDir]);
%     saveas(Fig_TGT_MESH,'TGT_mesh_dB_H_left.fig' ,'fig');
%     eval(['cd ' CurrentDir]);
% 
% 
%     
%     Fig_TGT_MESH= figure('units','normalized','outerposition',[0 0 1 1]);
%     set(Fig_TGT_MESH,'WindowStyle','docked')
%     mesh(1:Number_of_buffers,t,20*log10(TGT_V_left_mf))
%     hold on;
%     plot3(ones(1,length(t)),t,20*log10(TGT_V_left_mf_mean)+40,'linewidth',2,'Color','k')
%     view(124,52)
%     xlabel('Buffer #');
%     ylabel('range [m]')
%     title('V left')
%     eval(['cd ' ResultsDir]);
%     saveas(Fig_TGT_MESH,'TGT_mesh_dB_V_left.fig' ,'fig');
%     eval(['cd ' CurrentDir]);
% 
%     
%     
%     Fig_TGT_MESH= figure('units','normalized','outerposition',[0 0 1 1]);
%     set(Fig_TGT_MESH,'WindowStyle','docked')
%     mesh(1:Number_of_buffers,t,20*log10(TGT_H_right_mf))
%     hold on;
%     plot3(ones(1,length(t)),t,20*log10(TGT_H_right_mf_mean)+40,'linewidth',2,'Color','k')
%     view(124,52)
%     xlabel('Buffer #');
%     ylabel('range [m]')
%     title('H right')
%     eval(['cd ' ResultsDir]);
%     saveas(Fig_TGT_MESH,'TGT_mesh_dB_H_right.fig' ,'fig');
%     eval(['cd ' CurrentDir]);
% 
%     
%     
%     Fig_TGT_MESH= figure('units','normalized','outerposition',[0 0 1 1]);
%     set(Fig_TGT_MESH,'WindowStyle','docked')
%     mesh(1:Number_of_buffers,t,20*log10(TGT_V_right_mf))
%     hold on;
%     plot3(ones(1,length(t)),t,20*log10(TGT_V_right_mf_mean)+40,'linewidth',2,'Color','k')
%     view(124,52)
%     xlabel('Buffer #');
%     ylabel('range [m]')
%     title('V right')
%     eval(['cd ' ResultsDir]);
%     saveas(Fig_TGT_MESH,'TGT_mesh_dB_V_right.fig' ,'fig');
%     eval(['cd ' CurrentDir]);
 Fig_TGT_MESH= figure('units','normalized','outerposition',[0 0 1 1]);
    set(Fig_TGT_MESH,'WindowStyle','docked')
    subplot(221)
    noise_floor_mat = TGT_H_left_mf(FRAME_samples-20-1:FRAME_samples-1,1:20);
    noise_floor_emp = 10*log10(var(noise_floor_mat(:)));
    signal_strength_emp = 20*log10(max(max(abs(TGT_H_left_mf(:)))));
    mesh(Number_of_buffers / 2 :-1:-Number_of_buffers / 2 + 1,t,20*log10(abs(TGT_H_left_mf)))
    hold on;
%    plot3(ones(1,length(t)),t,20*log10(TGT_H_left_mf_mean)+40,'linewidth',2,'Color','k')
%     view(70,32)
%     view(180,0)
    view(-224,32)
    xlabel('Doppler Bin');
    ylabel('Range Sample')
    zlabel('Magnitude [dB]');
     title({'H left';['Noise floor = ' num2str(noise_floor_emp) ' [dB]'];['Signal strength = ' num2str(signal_strength_emp) ' [dB]']});
    axis([-inf inf -inf inf -120 10 ])
   
    
 subplot(222)
     noise_floor_mat = TGT_H_right_mf(FRAME_samples-20-1:FRAME_samples-1,1:20);
    noise_floor_emp = 10*log10(var(noise_floor_mat(:)));
    signal_strength_emp = 20*log10(max(max(abs(TGT_H_right_mf(:)))));
    mesh(Number_of_buffers / 2 :-1:-Number_of_buffers / 2 + 1,t,20*log10(abs(TGT_H_right_mf)))
    hold on;
%     plot3(ones(1,length(t)),t,20*log10(TGT_H_right_mf_mean)+40,'linewidth',2,'Color','k')
%     view(70,32)
%     view(180,0)
    view(-224,32)
    xlabel('Doppler Bin');
    ylabel('Range Sample')
    zlabel('Magnitude [dB]');
     title({'H right';['Noise floor = ' num2str(noise_floor_emp) ' [dB]'];['Signal strength = ' num2str(signal_strength_emp) ' [dB]']});
    axis([-inf inf -inf inf -120 10 ])
  
  subplot(223)
      noise_floor_mat = TGT_V_left_mf(FRAME_samples-20-1:FRAME_samples-1,1:20);
     noise_floor_emp = 10*log10(var(noise_floor_mat(:)));
    signal_strength_emp = 20*log10(max(max(abs(TGT_V_left_mf(:)))));
    mesh(Number_of_buffers / 2 :-1:-Number_of_buffers / 2 + 1,t,20*log10(abs(TGT_V_left_mf)))
    hold on;
%     plot3(ones(1,length(t)),t,20*log10(TGT_V_left_mf_mean)+40,'linewidth',2,'Color','k')
%     view(70,32)
%     view(180,0)
    view(-224,32)
    xlabel('Doppler Bin');
    ylabel('Range Sample')
    zlabel('Magnitude [dB]');
     title({'V left';['Noise floor = ' num2str(noise_floor_emp) ' [dB]'];['Signal strength = ' num2str(signal_strength_emp) ' [dB]']});
    axis([-inf inf -inf inf -120 10 ])
    
    
  subplot(224)
    noise_floor_mat = TGT_V_right_mf(FRAME_samples-20-1:FRAME_samples-1,1:20);
    noise_floor_emp = 10*log10(var(noise_floor_mat(:)));
    signal_strength_emp = 20*log10(max(max(abs(TGT_V_right_mf(:)))));
    mesh(Number_of_buffers / 2 :-1:-Number_of_buffers / 2 + 1,t,20*log10(abs(TGT_V_right_mf)))
    hold on;
%     plot3(ones(1,length(t)),t,20*log10(TGT_V_right_mf_mean)+40,'linewidth',2,'Color','k')
%     view(70,32)
%     view(180,0)
    view(-224,32)
    xlabel('Doppler Bin');
    ylabel('Range Sample')
    zlabel('Magnitude [dB]');
     title({'V right';['Noise floor = ' num2str(noise_floor_emp) ' [dB]'];['Signal strength = ' num2str(signal_strength_emp) ' [dB]']});
    axis([-inf inf -inf inf -120 10 ])
    eval(['cd ' ResultsDir]);
    saveas(Fig_TGT_MESH,'TGT_mesh_dB.fig' ,'fig');
    saveas(Fig_TGT_MESH,'TGT_mesh_dB.jpg' ,'jpg');
    eval(['cd ' CurrentDir]);
    
% ----------------------------------------------
% DC from RDM
% ----------------------------------------------
% s = linspace(-50e6/2,50e6/2,FRAME_samples - 1);
% 
%     TGT_H_left_mf_IQ  = buffer_H_left_I + 1j*buffer_H_left_Q;
%     TGT_V_left_mf_IQ = buffer_V_left_I + 1j*buffer_V_left_Q;
%     TGT_H_right_mf_IQ = buffer_H_right_I + 1j*buffer_H_right_Q;
%     TGT_V_right_mf_IQ = buffer_V_right_I + 1j*buffer_V_right_Q;
% 
% Fig_DC = figure('units','normalized','outerposition',[0 0 1 1]);
% set(Fig_DC,'WindowStyle','docked')
% 
% subplot(221)
% plot(s,abs(fftshift(fft((TGT_H_left_mf_IQ(:,257)))))); 
% grid on;
% xlabel('Frequency [Hz]');
% ylabel('Amplitude')
% title('H left')
% axis([-30e6 30e6 -inf 0.5])
% 
% subplot(222)
% plot(s,abs(fftshift(fft((TGT_H_right_mf_IQ(:,257)))))); 
% grid on;
% xlabel('Frequency [Hz]');
% ylabel('Amplitude')
% title('H right')
% axis([-30e6 30e6 -inf 0.5])
% 
% subplot(223)
% plot(s,abs(fftshift(fft((TGT_V_left_mf_IQ(:,257)))))); 
% grid on;
% xlabel('Frequency [Hz]');
% ylabel('Amplitude')
% title('V left')
% axis([-30e6 30e6 -inf 0.5])
% 
% subplot(224)
% plot(s,abs(fftshift(fft((TGT_V_right_mf_IQ(:,257)))))); 
% grid on;
% xlabel('Frequency [Hz]');
% ylabel('Amplitude')
% title('V right')
% 
% Fig_DC = figure('units','normalized','outerposition',[0 0 1 1]);
% set(Fig_DC,'WindowStyle','docked')
% 
% subplot(221)
% plot(s,real(TGT_H_left_mf_IQ(:,256))*32768,s,imag(TGT_H_left_mf_IQ(:,257))*32768); 
% grid on;
% xlabel('Frequency [Hz]');
% ylabel('Amplitude')
% title('H left')
% axis([-30e6 30e6 -inf 0.5])
% 
% subplot(222)
% plot(s,real(TGT_H_right_mf_IQ(:,256))*32768,s,imag(TGT_H_right_mf_IQ(:,257))*32768); 
% grid on;
% xlabel('Frequency [Hz]');
% ylabel('Amplitude')
% title('H right')
% axis([-30e6 30e6 -inf 0.5])
% 
% subplot(223)
% plot(s,real(TGT_V_left_mf_IQ(:,256))*32768,s,imag(TGT_V_left_mf_IQ(:,257))*32768); 
% 
% grid on;
% xlabel('Frequency [Hz]');
% ylabel('Amplitude')
% title('V left')
% axis([-30e6 30e6 -inf 0.5])
% 
% subplot(224)
% plot(s,real(TGT_V_right_mf_IQ(:,256))*32768,s,imag(TGT_V_right_mf_IQ(:,257))*32768); 
% 
% grid on;
% xlabel('Frequency [Hz]');
% ylabel('Amplitude')
% title('V right')
% axis([-30e6 30e6 -inf 0.5])
    
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % loate target and clculate AOA
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%     ArrayConst = 2*pi*0.2*980e6/3e8;
%     
%     [sample,buffer_num]=find(20*log10(abs(TGT_H_left_mf))==max(max(20*log10(abs(TGT_H_left_mf)))));
%     
%     % calculate phase
%     phaseH_left = atan2(-buffer_H_left_Q(sample,buffer_num), buffer_H_left_I(sample,buffer_num));
%     phaseV_left = atan2(-buffer_V_left_Q(sample,buffer_num), buffer_V_left_I(sample,buffer_num));
%     phaseH_right = atan2(-buffer_H_right_Q(sample,buffer_num), buffer_H_right_I(sample,buffer_num));
%     phaseV_right = atan2(-buffer_V_right_Q(sample,buffer_num), buffer_V_right_I(sample,buffer_num));
%      
%     % calculate phase diff  H_L - H_R in degrees
%     diff_H =  abs(phaseH_left) - abs(phaseH_right);
%     DOA_H = asin(diff_H/ArrayConst)/pi*180;
%     
%     % calculate phase diff  V_L - V_R in degrees
%     diff_V =  abs(phaseV_left) - abs(phaseV_right);
%     DOA_V = asin(diff_V/ArrayConst)/pi*180;
%     
%     target = figure;
%      % Create textbox
%     annotation(target,'textbox',...
%    [0.0035714285714272 0.89047619047619 0.46507142857143  0.0590476190476239],...
%     'String',{'Range[M] =' , sample, 'buffer# =' , buffer_num},...
%     'FitBoxToText','off', ...
%     'LineStyle','none');
%     % Create textbox
%     annotation(target,'textbox',...
%    [0.0035714285714272  0.79047619047619 0.332928571428572 0.0761904761904847],...
%     'String',{'Phase diff H =' , diff_H, 'phase diff V=' , diff_V},...
%     'FitBoxToText','off', ...
%     'LineStyle','none');
% % Create textbox
% annotation(target,'textbox',...
%      [0.0035714285714272 0.69047619047619 0.39507142857143 0.0690476190476239],...
%     'String',{' HLQ =', buffer_H_left_Q(sample,buffer_num), ' HLI =', buffer_H_left_I(sample,buffer_num),...
%     ' VLQ =', buffer_V_left_Q(sample,buffer_num), ' VLI =', buffer_V_left_I(sample,buffer_num),...
%     ' HRQ =', buffer_H_right_Q(sample,buffer_num), ' HRI =', buffer_H_right_I(sample,buffer_num),...
%     ' VRQ =', buffer_V_right_Q(sample,buffer_num), ' VRI =', buffer_V_right_I(sample,buffer_num)},...
%     'FitBoxToText','off', ...
%     'LineStyle','none');
    
    
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % target in doppler and range axis
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    %
    %   meshing max region
    %
    width = 30;%15;
    
     Fig_MAX_MESH= figure('units','normalized','outerposition',[0 0 1 1]);
    set(Fig_MAX_MESH,'WindowStyle','docked')
    subplot(1,4,1)
    [sample,buffer_num]=find(20*log10(abs(TGT_H_left_mf))==max(max(20*log10(abs(TGT_H_left_mf)))));
   bar(sample(1) - width:sample(1) + width,20*log10(abs(TGT_H_left_mf(sample(1) - width:sample(1) + width,buffer_num))),'BaseValue',-120)
%     mesh(width:-1:-width,-width:width,20*log10(TGT_H_left_mf(sample(1) - width: sample(1) + width,buffer_num(1) - width:buffer_num(1) + width)))
    hold on;
%    plot3(ones(1,length(t)),t,20*log10(TGT_H_left_mf_mean)+40,'linewidth',2,'Color','k')
%     view(90,0)
%     xlabel('Doppler Bin');
    xlabel('Range Sample');
    ylabel('Magnitude [dB]');
    grid on;
    title(['H left'])
%     text(2, -width + 1 ,2 ,['Max Doppler:' num2str(-(buffer_num(1) - (Number_of_buffers/2) - 1)) ]);
%     text(2, -width + 1 ,7, ['Max Range:' num2str(sample(1))]);
    axis([-inf inf -120 10 ])
   
    
 subplot(1,4,2)
     [sample,buffer_num]=find(20*log10(abs(TGT_H_right_mf))==max(max(20*log10(abs(TGT_H_right_mf)))));
       bar(sample(1) - width:sample(1) + width,20*log10(abs(TGT_H_right_mf(sample(1) - width:sample(1) + width,buffer_num))),'BaseValue',-120)
%    mesh(width:-1:-width,-width:width,20*log10(TGT_H_right_mf(sample(1) - width: sample(1) + width,buffer_num(1) - width:buffer_num(1) + width)))
    hold on;
%     plot3(ones(1,length(t)),t,20*log10(TGT_H_right_mf_mean)+40,'linewidth',2,'Color','k')
%     view(90,0)
%     xlabel('Doppler Bin');
    xlabel('Range Sample');
    ylabel('Magnitude [dB]');
    title(['H right'])
    grid on;
%     text(2, -width + 1 ,2 ,['Max Doppler:' num2str(-(buffer_num(1) - (Number_of_buffers/2) - 1)) ]);
%     text(2, -width + 1 ,7, ['Max Range:' num2str(sample(1))]);
    axis([-inf inf -120 10 ])
  
  subplot(1,4,3)
     [sample,buffer_num]=find(20*log10(abs(TGT_V_left_mf))==max(max(20*log10(abs(TGT_V_left_mf)))));
      bar(sample(1) - width:sample(1) + width,20*log10(abs(TGT_V_left_mf(sample(1) - width:sample(1) + width,buffer_num))),'BaseValue',-120)
%      mesh(width:-1:-width,-width:width,20*log10(TGT_V_left_mf(sample(1) - width: sample(1) + width,buffer_num(1) - width:buffer_num(1) + width)))
    hold on;
%     plot3(ones(1,length(t)),t,20*log10(TGT_V_left_mf_mean)+40,'linewidth',2,'Color','k')
%     view(90,0)
%     xlabel('Doppler Bin');
grid on;
    xlabel('Range Sample');
    ylabel('Magnitude [dB]');
    title(['V left'])
%     text(2, -width + 1 ,2 ,['Max Doppler:' num2str(-(buffer_num(1) - (Number_of_buffers/2) - 1)) ]);
%     text(2, -width + 1 ,7, ['Max Range:' num2str(sample(1))]);
    axis([-inf inf -120 10 ])
    
    
  subplot(1,4,4)
   [sample,buffer_num]=find(20*log10(abs(TGT_V_right_mf))==max(max(20*log10(abs(TGT_V_right_mf)))));
   bar(sample(1) - width:sample(1) + width,20*log10(abs(TGT_V_right_mf(sample(1) - width:sample(1) + width,buffer_num))),'BaseValue',-120)
%     mesh(width:-1:-width,-width:width,20*log10(TGT_V_right_mf(sample(1) - width: sample(1) + width,buffer_num(1) - width:buffer_num(1) + width)))
    hold on;
%     plot3(ones(1,length(t)),t,20*log10(TGT_V_right_mf_mean)+40,'linewidth',2,'Color','k')
%     view(90,0)
%     xlabel('Doppler Bin');
grid on;
    xlabel('Range Sample');
    ylabel('Magnitude [dB]');
    title(['V right'])
%     text(2, -width + 1 ,2 ,['Max Doppler:' num2str(-(buffer_num(1) - (Number_of_buffers/2) - 1)) ]);
%     text(2, -width + 1 ,7, ['Max Range:' num2str(sample(1))]);
    axis([-inf inf -120 10 ])
    eval(['cd ' ResultsDir]);
    saveas(Fig_MAX_MESH,'MAX_mesh_dB.fig' ,'fig');
    saveas(Fig_MAX_MESH,'MAX_mesh_dB.jpg' ,'jpg');
    eval(['cd ' CurrentDir]);
    
    width = 50;
    % side way
    Fig_MAX_SIDE_MESH= figure('units','normalized','outerposition',[0 0 1 1]);
    set(Fig_MAX_SIDE_MESH,'WindowStyle','docked')
    subplot(1,4,1)
    [sample,buffer_num]=find(20*log10(abs(TGT_H_left_mf))==max(max(20*log10(abs(TGT_H_left_mf)))));
     bar(width:-1:-width,20*log10(abs(TGT_H_left_mf(sample(1),buffer_num - width : buffer_num + width))),'BaseValue',-120)
%     mesh(width:-1:-width,-width:width,20*log10(TGT_H_left_mf(sample(1) - width: sample(1) + width,buffer_num(1) - width:buffer_num(1) + width)))
    hold on;
    grid on;
%    plot3(ones(1,length(t)),t,20*log10(TGT_H_left_mf_mean)+40,'linewidth',2,'Color','k')
%     view(0,0)
    xlabel('Doppler Bin');
%     ylabel('Range Sample');
    ylabel('Magnitude [dB]');
    title(['H left'])
%     text(2, -width + 1 ,2 ,['Max Doppler:' num2str(-(buffer_num(1) - (Number_of_buffers/2) - 1)) ]);
%     text(2, -width + 1 ,7, ['Max Range:' num2str(sample(1))]);
    axis([-inf inf -120 10 ])
   
    
 subplot(1,4,2)
     [sample,buffer_num]=find(20*log10(abs(TGT_H_right_mf))==max(max(20*log10(abs(TGT_H_right_mf)))));
          bar(width:-1:-width,20*log10(abs(TGT_H_right_mf(sample(1),buffer_num - width : buffer_num + width))),'BaseValue',-120)
%    mesh(width:-1:-width,-width:width,20*log10(TGT_H_right_mf(sample(1) - width: sample(1) + width,buffer_num(1) - width:buffer_num(1) + width)))
    hold on;
    grid on;
%     plot3(ones(1,length(t)),t,20*log10(TGT_H_right_mf_mean)+40,'linewidth',2,'Color','k')
%     view(0,0)
    xlabel('Doppler Bin');
%     ylabel('Range Sample');
    ylabel('Magnitude [dB]');
    title(['H right'])
%     text(2, -width + 1 ,2 ,['Max Doppler:' num2str(-(buffer_num(1) - (Number_of_buffers/2) - 1)) ]);
%     text(2, -width + 1 ,7, ['Max Range:' num2str(sample(1))]);
    axis([-inf inf -120 10 ])
  
  subplot(1,4,3)
     [sample,buffer_num]=find(20*log10(abs(TGT_V_left_mf))==max(max(20*log10(abs(TGT_V_left_mf)))));
        bar(width:-1:-width,20*log10(abs(TGT_V_left_mf(sample(1),buffer_num - width : buffer_num + width))),'BaseValue',-120)
%      mesh(width:-1:-width,-width:width,20*log10(TGT_V_left_mf(sample(1) - width: sample(1) + width,buffer_num(1) - width:buffer_num(1) + width)))
    hold on;
    grid on;
%     plot3(ones(1,length(t)),t,20*log10(TGT_V_left_mf_mean)+40,'linewidth',2,'Color','k')
%     view(0,0)
    xlabel('Doppler Bin');
%     ylabel('Range Sample');
    ylabel('Magnitude [dB]');
    title(['V left'])
%     text(2, -width + 1 ,2 ,['Max Doppler:' num2str(-(buffer_num(1) - (Number_of_buffers/2) - 1)) ]);
%     text(2, -width + 1 ,7, ['Max Range:' num2str(sample(1))]);
    axis([-inf inf -120 10 ])
    
    
  subplot(1,4,4)
   [sample,buffer_num]=find(20*log10(abs(TGT_V_right_mf))==max(max(20*log10(abs(TGT_V_right_mf)))));
           bar(width:-1:-width,20*log10(abs(TGT_V_right_mf(sample(1),buffer_num - width : buffer_num + width))),'BaseValue',-120)
%     mesh(width:-1:-width,-width:width,20*log10(TGT_V_right_mf(sample(1) - width: sample(1) + width,buffer_num(1) - width:buffer_num(1) + width)))
    hold on;
    grid on;
%     plot3(ones(1,length(t)),t,20*log10(TGT_V_right_mf_mean)+40,'linewidth',2,'Color','k')
%     view(0,0)
    xlabel('Doppler Bin');
%     ylabel('Range Sample');
    ylabel('Magnitude [dB]');
    title(['V right'])
%     text(2, -width + 1 ,2 ,['Max Doppler:' num2str(-(buffer_num(1) - (Number_of_buffers/2) - 1)) ]);
%     text(2, -width + 1 ,7, ['Max Range:' num2str(sample(1))]);
    axis([-inf inf -120 10 ])
    eval(['cd ' ResultsDir]);
    saveas(Fig_MAX_SIDE_MESH,'MAX_side_mesh_dB.fig' ,'fig');
    saveas(Fig_MAX_SIDE_MESH,'MAX_side_mesh_dB.jpg' ,'jpg');
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
