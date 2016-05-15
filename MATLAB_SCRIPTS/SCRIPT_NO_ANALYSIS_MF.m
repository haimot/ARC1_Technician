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
%SERVICE_READ_SCRIPT_DATA_FULL_LENGTH;
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
    
    t = (OFFSET_samples:OFFSET_samples+size(buffer_H_right_I,1)-1);
    
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
