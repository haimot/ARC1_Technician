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
%     Doppler      = (-floor(PCIE_NUMBER_PULSES/2):-floor(PCIE_NUMBER_PULSES/2) + PCIE_NUMBER_PULSES-1)/PCIE_NUMBER_PULSES * 2 * IO_UPDATE_rate;
    Doppler      = (-floor(PCIE_NUMBER_PULSES/2):-floor(PCIE_NUMBER_PULSES/2) + PCIE_NUMBER_PULSES-1)/PCIE_NUMBER_PULSES * IO_UPDATE_rate;
    Range        = (0:PCIE_BUFFSIZE-2)/Fs*3e8/2;
    
    CAF_H_left  = buffer_H_left_I  + 1j * buffer_H_left_Q;
    CAF_V_left  = buffer_V_left_I  + 1j * buffer_V_left_Q;
    CAF_H_right = buffer_H_right_I + 1j * buffer_H_right_Q;
    CAF_V_right = buffer_V_right_I + 1j * buffer_V_right_Q;
    
    %----------------------------------------------
    % Plotting
    %----------------------------------------------
    Fig_CAF = figure('units','normalized','outerposition',[0 0 1 1]);
    set(Fig_CAF,'WindowStyle','docked')
    mesh(Doppler,Range,10*log10(abs(CAF_H_right+eps)));
    xlabel('Velocity [m/sec]')
    ylabel('Range [m]')
    title ('CAF H left')
    view(90,-8)
    eval(['cd ' ResultsDir]);
    saveas(Fig_CAF,'CAF_H_left.fig' ,'fig');
    eval(['cd ' CurrentDir]);
    
    Fig_CAF = figure('units','normalized','outerposition',[0 0 1 1]);
    set(Fig_CAF,'WindowStyle','docked')
    mesh(Doppler,Range,10*log10(abs(CAF_V_right+eps)));
    xlabel('Velocity [m/sec]')
    ylabel('Range [m]')
    title ('CAF V left')
    view(90,-8)
    eval(['cd ' ResultsDir]);
    saveas(Fig_CAF,'CAF_V_left.fig' ,'fig');
    eval(['cd ' CurrentDir]);
    
%     Fig_CAF = figure('units','normalized','outerposition',[0 0 1 1]);
%     set(Fig_CAF,'WindowStyle','docked')
%     mesh(Doppler,Range,10*log10(abs(CAF_H_right)));
%     xlabel('Velocity [m/sec]')
%     ylabel('Range [m]')
%     title ('CAF H right')
%     view(0,52)
%     eval(['cd ' ResultsDir]);
%     saveas(Fig_CAF,'CAF_H_right.fig' ,'fig');
%     eval(['cd ' CurrentDir]);
%     
%     Fig_CAF = figure('units','normalized','outerposition',[0 0 1 1]);
%     set(Fig_CAF,'WindowStyle','docked')
%     mesh(Doppler,Range,10*log10(abs(CAF_V_right)));
%     xlabel('Velocity [m/sec]')
%     ylabel('Range [m]')
%     title ('CAF V right')
%     view(0,52)
%     eval(['cd ' ResultsDir]);
%     saveas(Fig_CAF,'CAF_V_right.fig' ,'fig');
%     eval(['cd ' CurrentDir]);
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
