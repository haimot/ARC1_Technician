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
   
    %......................................
    %   Time domain
    %......................................
    FigTSS = figure('units','normalized','outerposition',[0 0 1 1]);
    set(FigTSS,'WindowStyle','docked')
      t = (0:length(buffer_H_right_I)-1);
    subplot(221)
    plot(t,buffer_H_left_I',t,buffer_H_left_Q')
    S1 = sprintf('H-Left I');
    S2 = sprintf('H-Left Q');
    legend(S1,S2);legend('boxoff','Orientation','horizontal')
    xlabel('[Samples]')
    % S0 = sprintf('H-Left: Vpp = %1.2f',max(max(abs([buffer_H_left_I buffer_H_left_Q]))));
    % title(S0)
    axis([-inf inf -0.06 0.06])
    grid on
    
    t = (0:length(buffer_H_right_I)-1);
    subplot(223)
    plot(t,buffer_H_right_I',t,buffer_H_right_Q')
    S1 = sprintf('H-Right I');
    S2 = sprintf('H-Right Q');
    legend(S1,S2);legend('boxoff','Orientation','horizontal')
    xlabel('[Samples]')
    % S0 = sprintf('H-Right: Vpp = %1.2f',max(max(abs([buffer_H_right_I buffer_H_right_Q]))));
    % title(S0)
    axis([-inf inf -0.06 0.06])
    grid on

    t = (0:length(buffer_H_right_I)-1);
    subplot(222)
    plot(t,buffer_V_left_I',t,buffer_V_left_Q')
    S1 = sprintf('V-Left I');
    S2 = sprintf('V-Left Q');
    legend(S1,S2);legend('boxoff','Orientation','horizontal')
    xlabel('[Samples]')
    % S0 = sprintf('V-Left: Vpp = %1.2f',max(max(abs([buffer_V_left_I buffer_V_left_Q]))));
    % title(S0)
    axis([-inf inf -0.06 0.06])
    grid on
    
    t = (0:length(buffer_H_right_I)-1);
    subplot(224)
    plot(t,buffer_V_right_I',t,buffer_V_right_Q')
    S1 = sprintf('V-Right I');
    S2 = sprintf('V-Right Q');
    legend(S1,S2);legend('boxoff','Orientation','horizontal')
    xlabel('[Samples]')
    % S0 = sprintf('V-Right: Vpp = %1.2f',max(max(abs([buffer_V_right_I buffer_V_right_Q]))));
    % title(S0)
    axis([-inf inf -0.06 0.06])
    grid on
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
