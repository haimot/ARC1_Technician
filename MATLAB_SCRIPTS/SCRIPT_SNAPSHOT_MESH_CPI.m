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
    FRAME_samples = Buffer_length; %FRAME_distance*2/3e8*Fs
    
    t = (0:FRAME_samples-2);
    
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
    
    TGT_H_left_mf  = abs(TGT_H_left_mf);
    TGT_V_left_mf  = abs(TGT_V_left_mf);
    TGT_H_right_mf  = abs(TGT_H_right_mf);
    TGT_V_right_mf  = abs(TGT_V_right_mf);
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
    mesh(1:Number_of_buffers,t,20*log10(TGT_H_left_mf))
    hold on;
%    plot3(ones(1,length(t)),t,20*log10(TGT_H_left_mf_mean)+40,'linewidth',2,'Color','k')
    view(70,32)
    xlabel('Doppler Bin');
    ylabel('Range Bin')
    title('H left')
    axis([-inf inf -inf inf -80 10 ])
   
    
 subplot(222)
    mesh(1:Number_of_buffers,t,20*log10(TGT_H_right_mf))
    hold on;
%     plot3(ones(1,length(t)),t,20*log10(TGT_H_right_mf_mean)+40,'linewidth',2,'Color','k')
    view(70,32)
    xlabel('Doppler Bin');
    ylabel('Range Bin')
    title('H right')
    axis([-inf inf -inf inf -80 10 ])
  
  subplot(223)
    mesh(1:Number_of_buffers,t,20*log10(TGT_V_left_mf))
    hold on;
%     plot3(ones(1,length(t)),t,20*log10(TGT_V_left_mf_mean)+40,'linewidth',2,'Color','k')
    view(70,32)
    xlabel('Doppler Bin');
    ylabel('Range Bin')
    title('V left')
    axis([-inf inf -inf inf -80 10 ])
    
    
  subplot(224)
    mesh(1:Number_of_buffers,t,20*log10(TGT_V_right_mf))
    hold on;
%     plot3(ones(1,length(t)),t,20*log10(TGT_V_right_mf_mean)+40,'linewidth',2,'Color','k')
    view(70,32)
    xlabel('Doppler Bin');
    ylabel('Range Bin')
    title('V right')
    axis([-inf inf -inf inf -80 10 ])
    eval(['cd ' ResultsDir]);
    saveas(Fig_TGT_MESH,'TGT_mesh_dB.fig' ,'fig');
    saveas(Fig_TGT_MESH,'TGT_mesh_dB.jpg' ,'jpg');
    eval(['cd ' CurrentDir]);

    %
    %   meshing max region
    %
     Fig_MAX_MESH= figure('units','normalized','outerposition',[0 0 1 1]);
    set(Fig_MAX_MESH,'WindowStyle','docked')
    subplot(1,4,1)
    [sample,buffer_num]=my_max_matrix(20*log10(TGT_H_left_mf));
    mesh(-4:4,-4:4,20*log10(TGT_H_left_mf(sample(1) - 4: sample(1) + 4,buffer_num(1) - 4:buffer_num(1) + 4)))
    hold on;
%    plot3(ones(1,length(t)),t,20*log10(TGT_H_left_mf_mean)+40,'linewidth',2,'Color','k')
    view(90,0)
    xlabel('Doppler Bin');
    ylabel('Range Bin')
    title(['H left,' 'Max Doppler Bin:' num2str(buffer_num(1)) ',Max Range Bin:' num2str(sample(1))])
    axis([-inf inf -inf inf -80 10 ])
   
    
 subplot(1,4,2)
     [sample,buffer_num]=my_max_matrix(20*log10(TGT_H_right_mf));
   mesh(-4:4,-4:4,20*log10(TGT_H_right_mf(sample(1) - 4: sample(1) + 4,buffer_num(1) - 4:buffer_num(1) + 4)))
    hold on;
%     plot3(ones(1,length(t)),t,20*log10(TGT_H_right_mf_mean)+40,'linewidth',2,'Color','k')
    view(90,0)
    xlabel('Doppler Bin');
    ylabel('Range Bin')
    title(['H right,' 'Max Doppler Bin:' num2str(buffer_num(1)) ',Max Range Bin:' num2str(sample(1))])
    axis([-inf inf -inf inf -80 10 ])
  
  subplot(1,4,3)
     [sample,buffer_num]=my_max_matrix(20*log10(TGT_V_left_mf));
     mesh(-4:4,-4:4,20*log10(TGT_V_left_mf(sample(1) - 4: sample(1) + 4,buffer_num(1) - 4:buffer_num(1) + 4)))
    hold on;
%     plot3(ones(1,length(t)),t,20*log10(TGT_V_left_mf_mean)+40,'linewidth',2,'Color','k')
    view(90,0)
    xlabel('Doppler Bin');
    ylabel('Range Bin')
    title(['V left,' 'Max Doppler Bin:' num2str(buffer_num(1)) ',Max Range Bin:' num2str(sample(1))])
    axis([-inf inf -inf inf -80 10 ])
    
    
  subplot(1,4,4)
   [sample,buffer_num]=my_max_matrix(20*log10(TGT_V_right_mf));
    mesh(-4:4,-4:4,20*log10(TGT_V_right_mf(sample(1) - 4: sample(1) + 4,buffer_num(1) - 4:buffer_num(1) + 4)))
    hold on;
%     plot3(ones(1,length(t)),t,20*log10(TGT_V_right_mf_mean)+40,'linewidth',2,'Color','k')
    view(90,0)
    xlabel('Doppler Bin');
    ylabel('Range Bin')
    title(['V right,' 'Max Doppler Bin:' num2str(buffer_num(1)) ',Max Range Bin:' num2str(sample(1))])
    axis([-inf inf -inf inf -80 10 ])
    eval(['cd ' ResultsDir]);
    saveas(Fig_MAX_MESH,'MAX_mesh_dB.fig' ,'fig');
    saveas(Fig_MAX_MESH,'MAX_mesh_dB.jpg' ,'jpg');
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
