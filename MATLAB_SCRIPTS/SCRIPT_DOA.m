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
    
    
    t = (0:size(buffer_H_right_I,1)-1);
    
    Buf_H_left = buffer_H_left_I + 1j*buffer_H_left_Q;
    Buf_V_left = buffer_V_left_I + 1j*buffer_V_left_Q;
    Buf_H_right = buffer_H_right_I + 1j*buffer_H_right_Q;
    Buf_V_right = buffer_V_right_I + 1j*buffer_V_right_Q;
    
    [~,kkk] = find(abs(Buf_H_right') > max(max(abs(Buf_H_right)))*0.5);
    TGT1 = floor(mean(kkk(1:PCIE_NUMBER_PULSES)))+10;
    TGT2 = floor(mean(kkk(end-PCIE_NUMBER_PULSES+1:end)))-7;
    
    TGT1 = 110;
    TGT2 = 125;
    
    Epsilon = 0.05;
    
    FigDOA = figure('units','normalized','outerposition',[0 0 1 1]);
    set(FigDOA,'WindowStyle','docked')
    
    phaseH_left = atan2(-buffer_H_left_Q, buffer_H_left_I + Epsilon);
    subplot(421)
    plot(t,buffer_H_left_I',t,buffer_H_left_Q')
    legend('I_1','Q_1','Orientation','horizontal');legend('boxoff')
    xlabel('[Samples]')
    S0 = sprintf('H Left: Vpp = %1.2f',2*max(max(sqrt(buffer_H_left_I.^2+buffer_H_left_Q.^2))));
    S1 = sprintf(' Phase = %1.2f', mean(mean(phaseH_left(TGT1:TGT2,:))));
    title([S0 S1])
    axis([-inf inf -1 1])
    grid on
    
    subplot(423)
    plot(t,phaseH_left)
    
    phaseV_left = atan2(-buffer_V_left_Q, buffer_V_left_I + Epsilon);
    subplot(422)
    plot(t,buffer_V_left_I',t,buffer_V_left_Q')
    legend('I_2','Q_2','Orientation','horizontal');legend('boxoff')
    xlabel('[Samples]')
    S0 = sprintf('V Left: Vpp = %1.2f',2*max(max(sqrt(buffer_V_left_I.^2+buffer_V_left_Q.^2))));
    S1 = sprintf(' Phase = %1.2f', mean(mean(phaseV_left(TGT1:TGT2,:))));
    title([S0 S1])
    axis([-inf inf -1 1])
    grid on
    
    subplot(424)
    plot(t,phaseV_left)
    
    phaseH_right = atan2(-buffer_H_right_Q, buffer_H_right_I + Epsilon);
    subplot(425)
    plot(t,buffer_H_right_I',t,buffer_H_right_Q')
    legend('I_1','Q_1','Orientation','horizontal');legend('boxoff')
    xlabel('[Samples]')
    S0 = sprintf('H RIght: Vpp = %1.2f',2*max(max(sqrt(buffer_H_right_I.^2+buffer_H_right_Q.^2))));
    S1 = sprintf(' Phase = %1.2f', mean(mean(phaseH_right(TGT1:TGT2,:))));
    title([S0 S1])
    axis([-inf inf -1 1])
    grid on
    
    subplot(427)
    plot(t,phaseH_right)
    
    phaseV_right = atan2(-buffer_V_right_Q, buffer_V_right_I + Epsilon);
    subplot(426)
    plot(t,buffer_V_right_I',t,buffer_V_right_Q')
    legend('I_2','Q_2','Orientation','horizontal');legend('boxoff')
    xlabel('[Samples]')
    S0 = sprintf('V Right: Vpp = %1.2f',2*max(max(sqrt(buffer_V_right_I.^2+buffer_V_right_Q.^2))));
    S1 = sprintf(' Phase = %1.2f', mean(mean(phaseV_right(TGT1:TGT2,:))));
    title([S0 S1])
    axis([-inf inf -1 1])
    grid on
    
    subplot(428)
    plot(t,phaseV_right)
    
    eval(['cd ' ResultsDir]);
    saveas(FigDOA,'DOA.fig' ,'fig');
    eval(['cd ' CurrentDir]);
    
    %----------------------------------------
    % DOA
    %----------------------------------------
    ArrayConst = 2*pi*0.2*980e6/3e8;
    
    %Theta = mean(phaseH_left(TGT1:TGT2,:) - phaseH_right(TGT1:TGT2,:),2);
    
    mean_Hleft_Q = mean(mean(-buffer_H_left_Q(TGT1:TGT2,:)));
    mean_Hleft_I = mean(mean(buffer_H_left_I(TGT1:TGT2,:)));
    mean_Hright_Q = mean(mean(-buffer_H_right_Q(TGT1:TGT2,:)));
    mean_Hright_I = mean(mean(buffer_H_right_I(TGT1:TGT2,:)));
    
    mean_phaseH_left = mean(mean(phaseH_left(TGT1:TGT2,:)));
    mean_phaseH_right = mean(mean(phaseH_right(TGT1:TGT2,:)));
    
    diff =  mean_phaseH_left - mean_phaseH_right;
    if abs(diff) < ArrayConst
        Theta = diff;
    else
        Theta = diff - sign(diff)*pi;
    end
    
    disp(mean_Hleft_Q)
    disp(mean_Hleft_I)
    disp(mean_Hright_Q)
    disp(mean_Hright_I)
    disp(mean_phaseH_left)
    disp(mean_phaseH_right)
    disp(mean(Theta)/pi*180)
    disp(asin(mean(Theta)/ArrayConst)/pi*180)
    
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
