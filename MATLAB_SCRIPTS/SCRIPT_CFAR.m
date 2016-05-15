%----------------------------------------------
%   SCRIPT_CAF_DSP
%
%   Ronen Globinsky     10.2.2015
%
%   1 - filter RD map using detection kernel
%
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
    Doppler      = (-floor(PCIE_NUMBER_PULSES/2):-floor(PCIE_NUMBER_PULSES/2) + PCIE_NUMBER_PULSES-1)/PCIE_NUMBER_PULSES * IO_UPDATE_rate;
    Range        = (0:PCIE_BUFFSIZE-2)/Fs*3e8/2;
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
    %----------------------------------------------
    % CFAR
    %----------------------------------------------
    k = 25;
    % create 2D kernel
%    h = zeros(35,15);
%     h([1:15, 21:35], 8) = 1/72;
%     h(15:21, [1:3, 13:15]) = 1/72;
%     h([1:14, 22:35], 8) = 1/70;
%     h(15:21, [1:3, 13:15]) = 1/70;
    
    h = zeros(15,15);
     h(6:10, [1:3, 13:15]) = 1/30;
   
    % filter RDM - calculate TH
    CAF_H_left_filtered = filter2(h', abs(CAF_H_left)); 
    CAF_V_left_filtered = filter2(h', abs(CAF_V_left)); 
    CAF_H_right_filtered = filter2(h', abs(CAF_H_right)); 
    CAF_V_right_filtered = filter2(h', abs(CAF_V_right)); 
   
    % find targets > TH*k
    [R_H_left,D_H_left] = find(abs(CAF_H_left) > CAF_H_left_filtered * k);
    [R_V_left,D_V_left] = find(abs(CAF_V_left) > CAF_V_left_filtered * k);
    [R_H_right,D_H_right] = find(abs(CAF_H_right) > CAF_H_right_filtered * k);
    [R_V_right,D_V_right] = find(abs(CAF_V_right) > CAF_V_right_filtered * k);
    
    % get centeroid of target in range[m], doppler shift[Hz]
    %    [R, D, c] = CFAR( abs(CAF_H_left), CAF_H_left_filtered, PCIE_NUMBER_PULSES, CPI_LENGTH);
    
    R_H_left  = subclust(R_H_left,3)/Fs*3e8/2;
    R_V_left  = subclust(R_V_left,3)/Fs*3e8/2;
    R_H_right  = subclust(R_H_right,3)/Fs*3e8/2;
    R_V_right  = subclust(R_V_right,3)/Fs*3e8/2;
    
    D_H_left   = (subclust(D_H_left,3) - floor(PCIE_NUMBER_PULSES/2) - 1)/PCIE_NUMBER_PULSES * IO_UPDATE_rate * 1000;
    D_V_left   = (subclust(D_V_left,3) - floor(PCIE_NUMBER_PULSES/2) - 1)/PCIE_NUMBER_PULSES * IO_UPDATE_rate * 1000;
    D_H_right  = (subclust(D_H_right,3) - floor(PCIE_NUMBER_PULSES/2) - 1)/PCIE_NUMBER_PULSES * IO_UPDATE_rate * 1000;
    D_V_right  = (subclust(D_V_right,3) - floor(PCIE_NUMBER_PULSES/2) - 1)/PCIE_NUMBER_PULSES * IO_UPDATE_rate * 1000;
       
    %----------------------------------------------
    % Plotting
    %----------------------------------------------
    % show 2D filter kernel
     image(256*h);
    
    target = figure;
    % Create textbox
annotation(target,'textbox',...
   [0.0259999999999996 0.890476190476193 0.332928571428572 0.0761904761904847],...
    'String',{'Range[m] [H_L, V_L, H_R , V_R]=' , [R_H_left; R_V_left; R_H_right; R_V_right]},...
    'FitBoxToText','off', ...
    'LineStyle','none');

% Create textbox
annotation(target,'textbox',...
     [0.0245714285714272 0.646666666666672 0.39507142857143 0.0690476190476239],...
    'String',{'Doppler[Hz] [H_L, V_L, H_R , V_R]=', [D_H_left; D_V_left; D_H_right; D_V_right]},...
    'FitBoxToText','off', ...
    'LineStyle','none');

    
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
    Error_message = err.message;
    Error_line = err.stack.line;
end
