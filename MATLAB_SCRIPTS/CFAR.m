function [R, D, c] = CFAR( RDM, RDM_mask, num_buffers, buffer_length)
k = 25;
taqrget_count = 0;
D = zeros(1,100);
R = zeros(1,100);

    for i = 0:num_buffers                                     % # buffers 
  
        for j = 0:buffer_length * 2                           % buffer length 
          
            % check if RD value is above TH
             if RDM(i,j) > ((RDM_mask(i,j) + 1) * k)
			 max = RDM(i,j);
			 doppler_idx = i;
			 range_idx = j;
			
% 			 * ------------------------------------------------------
% 			 *  target cluster detected
% 			 *  search for the peak value within the given radius
% 			 * ------------------------------------------------------
			 
                for n = j+1:j + radius
                    if ( RDM(i,j) > max ) && ( RDM(i,j) > (((RDM_mask(i,j) + 1) * k)))
				
                        max = RDM(i,j);
                        doppler_idx = i;
                        range_idx = n;
                    end
                end
                j = j + radius;
		
% 			 * ------------------------------------------------------
% 			 *  Update targets
% 			 * ------------------------------------------------------
                D(taqrget_count) = doppler_idx;
                R(taqrget_count)   = range_idx;
                target_count = target_count + 1;
             end
          
        end % col loop
    end % row loop
      
      c = taqrget_count;

end

