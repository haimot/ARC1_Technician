%----------------------------------------------
%   SCRIPT DOA
%
%   Alon Slapak
%   21/10/2014
%
%   1 - Calculate DOA paramters
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
        if (0)          % Windowing
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
%     k = 10;
%     % create 2D kernel
% %     h = zeros(35,15);
% %     h([1:15, 21:35], 8) = 1/72;
% %     h(15:21, [1:3, 13:15]) = 1/72;
% %     h([1:14, 22:35], 8) = 1/70;
% %     h(15:21, [1:3, 13:15]) = 1/70;
%     
%      h = zeros(15,15);
%      h(5:11, [1:3, 13:15]) = 1/42;
%    
%     % filter RDM - calculate TH
%     CAF_H_left_filtered = filter2(h', abs(CAF_H_left)); 
%     CAF_V_left_filtered = filter2(h', abs(CAF_V_left)); 
%     CAF_H_right_filtered = filter2(h', abs(CAF_H_right)); 
%     CAF_V_right_filtered = filter2(h', abs(CAF_V_right)); 
%    
%     % find targets > TH*k
%     [R_H_left,D_H_left] = find(abs(CAF_H_left) > CAF_H_left_filtered * k);
%     [R_V_left,D_V_left] = find(abs(CAF_V_left) > CAF_V_left_filtered * k);
%     [R_H_right,D_H_right] = find(abs(CAF_H_right) > CAF_H_right_filtered * k);
%     [R_V_right,D_V_right] = find(abs(CAF_V_right) > CAF_V_right_filtered * k);
%     
%     % get centeroid of target in range[m], doppler shift[Hz]
%     %    [R, D, c] = CFAR( abs(CAF_H_left), CAF_H_left_filtered, PCIE_NUMBER_PULSES, CPI_LENGTH);
%     
%     R_H_left  = subclust(R_H_left,3);
%     R_V_left  = subclust(R_V_left,3);
%     R_H_right  = subclust(R_H_right,3);
%     R_V_right  = subclust(R_V_right,3);
%     
%     D_H_left   = subclust(D_H_left,3);
%     D_V_left   = subclust(D_V_left,3);
%     D_H_right  = subclust(D_H_right,3);
%     D_V_right  = subclust(D_V_right,3);
    [R_H_left,D_H_left] =  my_max_matrix( abs(CAF_H_left));
    [R_V_left,D_V_left] = my_max_matrix( abs(CAF_V_left));
    [R_H_right,D_H_right] = my_max_matrix( abs(CAF_H_right));
   [R_V_right,D_V_right] = my_max_matrix( abs(CAF_V_right));
    %----------------------------------------
    % Range & Doppler
    %----------------------------------------
    Range_T = R_H_left;%( R_H_left - OFFSET_samples ) * 3e8 / ( 50e6 * 2 );
    Doppler_T = D_H_left;%(D_H_left - 1 - floor (  Number_of_buffers / 2 )) * ( 3e8 / Number_of_buffers ) * IO_UPDATE_rate * ( 1000 / 980e6 );
    
    
    %----------------------------------------
    % DOA
    %----------------------------------------
    Epsilon = 0.05;
    ArrayConst = 2*pi*0.2*980e6/3e8;
    
    % get target values
%     H_left_Q = buffer_H_left_Q(R_H_left, D_H_left + 1);
%     H_left_I = buffer_H_left_I(R_H_left, D_H_left + 1);
%     V_left_Q = buffer_V_left_Q(R_V_left, D_V_left + 1);
%     V_left_I = buffer_V_left_I(R_V_left, D_V_left + 1);
%     H_right_Q = buffer_H_right_Q(R_H_right, D_H_right + 1);
%     H_right_I = buffer_H_right_I(R_H_right ,D_H_right + 1);
%     V_right_Q = buffer_V_right_Q(R_V_right, D_V_right + 1);
%     V_right_I = buffer_V_right_I(R_V_right, D_V_right + 1);

    H_left_Q = buffer_H_left_Q(R_H_left, D_H_left + 1);
    H_left_I = buffer_H_left_I(R_H_left, D_H_left + 1);
    V_left_Q = buffer_V_left_Q(R_H_left, D_H_left + 1);
    V_left_I = buffer_V_left_I(R_H_left, D_H_left + 1);
    H_right_Q = buffer_H_right_Q(R_H_left, D_H_left + 1);
    H_right_I = buffer_H_right_I(R_H_left ,D_H_left + 1);
    V_right_Q = buffer_V_right_Q(R_H_left, D_H_left + 1);
    V_right_I = buffer_V_right_I(R_H_left, D_H_left + 1);
    
    % calculate phase
    phaseH_left = atan2(-H_left_Q, H_left_I + Epsilon);
    phaseV_left = atan2(-V_left_Q, V_left_I + Epsilon);
    phaseH_right = atan2(-H_right_Q, H_right_I + Epsilon);
    phaseV_right = atan2(-V_right_Q, V_right_I + Epsilon);
     
    % calculate phase diff  H_L - H_R in degrees
    diff_H =  abs(phaseH_left) - abs(phaseH_right);
    DOA_H = asin(diff_H/ArrayConst)/pi*180;
    
    % calculate phase diff  V_L - V_R in degrees
    diff_V =  abs(phaseV_left) - abs(phaseV_right);
    DOA_V = asin(diff_V/ArrayConst)/pi*180;
    
    %----------------------------------------
    % polarization
    %----------------------------------------

    % calculate ratio V/H left and right
    IQ_H_L = complex(H_left_I, H_left_Q);
    IQ_V_L = complex(V_left_I, V_left_Q);
    IQ_H_R = complex(H_right_I, H_right_Q);
    IQ_V_R = complex(V_right_I, V_right_Q);
    
    % calculate polarization ratio
    ratio_L = IQ_H_L / IQ_V_L;
    ratio_R = IQ_H_R / IQ_V_R;
    % calculate phase H-V left and right
    phase_diff_L = atan2(-imag(ratio_L), real(ratio_L));
    phase_diff_R = atan2(-imag(ratio_R), real(ratio_R));

    % estimated polarization angle left and right
    mag_ratio_L = abs(ratio_L);
    mag_ratio_R = abs(ratio_R);

    mag_ratio_square_L = mag_ratio_L^2;
    numerator_L = 1 - mag_ratio_square_L;
    denominator_L = sqrt(1 + mag_ratio_square_L + 2 * sin(phase_diff_L)) * sqrt(1 + mag_ratio_square_L - 2 * sin(phase_diff_L));
    Pol_L = 0.5 * acos(numerator_L/(denominator_L + eps));
    Pol_L = Pol_L / pi * 180;

    mag_ratio_square_R = mag_ratio_R^2;
    numerator_R = 1 - mag_ratio_square_R;
    denominator_R = sqrt(1 + mag_ratio_square_R + 2 * sin(phase_diff_R)) * sqrt(1 + mag_ratio_square_R - 2 * sin(phase_diff_R));
    Pol_R = 0.5 * acos(numerator_R/(denominator_R + eps));
    Pol_R = Pol_R / pi * 180;

    %----------------------------------------------
    % Plotting
    %----------------------------------------------
    
    target = figure;
    
        % Create textbox
annotation(target,'textbox',...
   [0.0035714285714272 0.89047619047619 0.46507142857143  0.0590476190476239],...
    'String',{'Range[M] =' , Range_T, 'Doppler[m/s] =' , Doppler_T},...
    'FitBoxToText','off', ...
    'LineStyle','none');
    
    % Create textbox
annotation(target,'textbox',...
   [0.0035714285714272  0.79047619047619 0.332928571428572 0.0761904761904847],...
    'String',{'DOA H[deg] =' , DOA_H, 'DOA V[deg] =' , DOA_V},...
    'FitBoxToText','off', ...
    'LineStyle','none');

% Create textbox
annotation(target,'textbox',...
     [0.0035714285714272 0.69047619047619 0.39507142857143 0.0690476190476239],...
    'String',{' Polarization angle L[deg] =', Pol_L, ' Polarization angle R[deg] =', Pol_R},...
    'FitBoxToText','off', ...
    'LineStyle','none');
    
%Fig_RDM= figure('units','normalized','outerposition',[0 0 1 1]);
 %   set(Fig_RDM,'WindowStyle','docked')
 set(target,'WindowStyle','docked')
    subplot(221)
    mesh(10*log10(abs(CAF_H_left)+eps))
    hold on;
    view(70,32)
    xlabel('Buffer #');
    ylabel('range [m]')
    title('H left')
   
    
 subplot(222)
    mesh(10*log10(abs(CAF_V_left)+eps))
    hold on;
    view(70,32)
    xlabel('Buffer #');
    ylabel('range [m]')
    title('H right')
  
  subplot(223)
    mesh(10*log10(abs(CAF_H_right)+eps))
    hold on;
    view(70,32)
    xlabel('Buffer #');
    ylabel('range [m]')
    title('V left')
    
    
  subplot(224)
    mesh(10*log10(abs(CAF_V_right)+eps))
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
