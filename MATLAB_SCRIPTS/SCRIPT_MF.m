%----------------------------------------------
%   SCRIPT_MF
%
%   Alon Slapak     17.11.2014
%
%   1 - Mathced filter
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
    %SERVICE_READ_SCRIPT_DATA;
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
    %----------------------------------------
    %   Magnitude
    %----------------------------------------
    TGT_H_left_mf_abs  = abs(TGT_H_left_mf);
    TGT_V_left_mf_abs  = abs(TGT_V_left_mf);
    TGT_H_right_mf_abs = abs(TGT_H_right_mf);
    TGT_V_right_mf_abs = abs(TGT_V_right_mf);
    %----------------------------------------------
    % Plotting
    %----------------------------------------------
 Fig_MF= figure('units','normalized','outerposition',[0 0 1 1]);
    set(Fig_MF,'WindowStyle','docked')
    subplot(221)
    mesh(10*log10(TGT_H_left_mf_abs + eps))
    hold on;
    view(70,32)
    xlabel('Buffer #');
    ylabel('range [m]')
    title('H left')
   
    
 subplot(222)
    mesh(10*log10(TGT_H_right_mf_abs + eps))
    hold on;
    view(70,32)
    xlabel('Buffer #');
    ylabel('range [m]')
    title('H right')
  
  subplot(223)
    mesh(10*log10(TGT_V_left_mf_abs + eps))
    hold on;
    view(70,32)
    xlabel('Buffer #');
    ylabel('range [m]')
    title('V left')
    
    
  subplot(224)
    mesh(10*log10(TGT_V_right_mf_abs + eps))
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
