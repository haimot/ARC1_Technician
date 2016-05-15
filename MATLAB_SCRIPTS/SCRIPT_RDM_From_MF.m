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
    Doppler      = (-floor(PCIE_NUMBER_PULSES/2):-floor(PCIE_NUMBER_PULSES/2) + PCIE_NUMBER_PULSES-1)/PCIE_NUMBER_PULSES * IO_UPDATE_rate;
    %Range        = (0:PCIE_BUFFSIZE-2)/Fs*3e8/2;
    Range = RANGE_samples - 1;
    %--------------------------------------------------
    %     Match filter due transmited filter
    %--------------------------------------------------
    profile_0 = [];
    profile_1 = [1 1 1 1 1 -1 -1 1 1 -1 1 -1 1];
    profile_2 = [1 1 1 1 1 1 1 1 1 1 1 1 1];
    profile_3 = [1 1 1 1 1 1 1 1 1];
    profile_4 = [1 1 1 1 1 1 1 ];
    profile_5 = [1 1 1 1 1];
    profile_6 = [1 1 1];
    profile_7 = [1];
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
    MatchedFilter   = Matched_sig + 1j*Matched_sig;
    %--------------------------------------------------
    %     Start form IO_UPDATE
    %--------------------------------------------------
    %--------------------------------------------------
    %     Match filter due transmited filter
    %--------------------------------------------------
    profile_0 = [];
    profile_1 = [1 1 1 1 1 -1 -1 1 1 -1 1 -1 1];
    profile_2 = [1 1 1 1 1 1 1 1 1 1 1 1 1];
    profile_3 = [1 1 1 1 1 1 1 1 1];
    profile_4 = [1 1 1 1 1 1 1 ];
    profile_5 = [1 1 1 1 1];
    profile_6 = [1 1 1];
    profile_7 = [1];
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
    MatchedFilter   = Matched_sig + 1j*Matched_sig;
    %----------------------------------------
    %  Matched filter
    %----------------------------------------
    TGT_H_left_I_mf  = buffer_H_left_I;
    TGT_H_left_Q_mf  = buffer_H_left_Q;
    TGT_V_left_I_mf  = buffer_V_left_I;
    TGT_V_left_Q_mf  = buffer_V_left_Q;
    TGT_H_right_I_mf =buffer_H_right_I;
    TGT_H_right_Q_mf =buffer_H_right_Q;
    TGT_V_right_I_mf = buffer_V_right_I;
    TGT_V_right_Q_mf = buffer_V_right_Q;
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
    TGT_H_left_window   = zeros(Range,PCIE_NUMBER_PULSES);
    TGT_V_left_window   = zeros(Range,PCIE_NUMBER_PULSES);
    TGT_H_right_window  = zeros(Range,PCIE_NUMBER_PULSES);
    TGT_V_right_window  = zeros(Range,PCIE_NUMBER_PULSES);
    
    CAF_H_left  = zeros(Range,PCIE_NUMBER_PULSES);
    CAF_V_left  = zeros(Range,PCIE_NUMBER_PULSES);
    CAF_H_right = zeros(Range,PCIE_NUMBER_PULSES);
    CAF_V_right = zeros(Range,PCIE_NUMBER_PULSES);
    for p = 1:Range,
        if (1)          % Windowing
            TGT_H_left_window(p,:) = TGT_H_left_mf(p,:).*((1+1j)*kaiser(PCIE_NUMBER_PULSES,12)');
            TGT_V_left_window(p,:) = TGT_V_left_mf(p,:).*((1+1j)*kaiser(PCIE_NUMBER_PULSES,12)');
            TGT_H_right_window(p,:) = TGT_H_right_mf(p,:).*((1+1j)*kaiser(PCIE_NUMBER_PULSES,12)');
            TGT_V_right_window(p,:) = TGT_V_right_mf(p,:).*((1+1j)*kaiser(PCIE_NUMBER_PULSES,12)');
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
    CAF_H_left_abs  = abs(CAF_H_left);
    CAF_V_left_abs  = abs(CAF_V_left);
    CAF_H_right_abs = abs(CAF_H_right);
    CAF_V_right_abs = abs(CAF_V_right);
    %----------------------------------------------
    % Plotting
    %----------------------------------------------
 Fig_RDM= figure('units','normalized','outerposition',[0 0 1 1]);
    set(Fig_RDM,'WindowStyle','docked')
    subplot(221)
    mesh(20*log10(CAF_H_left_abs))
    hold on;
    view(70,32)
    xlabel('Buffer #');
    ylabel('range [m]')
    title('H left')
   
    
 subplot(222)
    mesh(20*log10(CAF_V_left_abs))
    hold on;
    view(70,32)
    xlabel('Buffer #');
    ylabel('range [m]')
    title('H right')
  
  subplot(223)
    mesh(20*log10(CAF_H_right_abs))
    hold on;
    view(70,32)
    xlabel('Buffer #');
    ylabel('range [m]')
    title('V left')
    
    
  subplot(224)
    mesh(20*log10(CAF_V_right_abs))
    hold on;
    view(70,32)
    xlabel('Buffer #');
    ylabel('range [m]')
    title('V right')
    
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
