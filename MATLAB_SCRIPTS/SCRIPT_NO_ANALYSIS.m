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
%     SERVICE_READ_SCRIPT_DATA_ONLY;
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
    S0 = sprintf('Right-H: Vpp = %1.2f',2*max(max(sqrt(buffer_H_right_I.^2+buffer_H_right_Q.^2))));
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
    
    R1 = 60;
    R2 = 80;
     ArrayConst = 2*pi*0.2*980e6/3e8;
    
    HLI = mean(mean(buffer_H_left_I(R1:R2,:)));
    HLQ = mean(mean(buffer_H_left_Q(R1:R2,:)));
    HRI = mean(mean(buffer_H_right_I(R1:R2,:)));
    HRQ = mean(mean(buffer_H_right_Q(R1:R2,:)));
    
    VLI = mean(mean(buffer_V_left_I(R1:R2,:)));
    VLQ = mean(mean(buffer_V_left_Q(R1:R2,:)));
    VRI = mean(mean(buffer_V_right_I(R1:R2,:)));
    VRQ = mean(mean(buffer_V_right_Q(R1:R2,:)));
    
     phaseH_left = atan2(-HLQ, HLI);
    phaseV_left = atan2(-VLQ, VLI);
    phaseH_right = atan2(-HRQ, HRI);
    phaseV_right = atan2(-VRQ, VRI);
     
    % calculate phase diff  H_L - H_R in degrees
    diff_H =  abs(phaseH_left) - abs(phaseH_right);
    DOA_H = asin(diff_H/ArrayConst)/pi*180;
    
    % calculate phase diff  V_L - V_R in degrees
    diff_V =  abs(phaseV_left) - abs(phaseV_right);
    DOA_V = asin(diff_V/ArrayConst)/pi*180;
    
    % calculate phase diff  H_L - V_L in degrees
    diff_L =  abs(phaseH_left) - abs(phaseV_left);
    DOA_L = asin(diff_L/ArrayConst)/pi*180;
    
    % calculate phase diff  H_R - V_R in degrees
    diff_R =  abs(phaseH_right) - abs(phaseV_right);
    DOA_R = asin(diff_R/ArrayConst)/pi*180;
    
    diff_array = [ diff_H, diff_V, diff_L, diff_R ];
    AoA_array = [ DOA_H, DOA_V, DOA_L, DOA_R ];
    
    
    % Create textbox
    annotation(FigPULSE,'textbox',...
   [0.0035714285714272  0.79047619047619 0.332928571428572 0.0761904761904847],...
    'String',{'Phase diff H =' , diff_H, 'phase diff V=' , diff_V,...
    'Phase diff L =' , diff_L, 'phase diff R=' , diff_R},...
    'FitBoxToText','off', ...
    'LineStyle','none');
% % Create textbox
% annotation(target,'textbox',...
%      [0.0035714285714272 0.69047619047619 0.39507142857143 0.0690476190476239],...
%     'String',{' HLQ =', HLQ, ' HLI =', HLI,...
%     ' VLQ =', VLQ, ' VLI =', VLQ,...
%     ' HRQ =',HRQ, ' HRI =', HRI,...
%     ' VRQ =', VRQ, ' VRI =', VRI},...
%     'FitBoxToText','off', ...
%     'LineStyle','none');
    
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
