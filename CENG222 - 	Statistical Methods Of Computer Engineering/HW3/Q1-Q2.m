i = 1;
j = 1;
num_of_minion = 0;    %keeps the number of minions which have the property  (W > 2*S) in one set and is reset before every new minion set
estimated_minion = 0; %ratio of num_of_minion with N to find percentage of these minion sets 
estimated_total = 0;  %ratio of total weights and N in order to find avearage weight
num_of_trial = 0;     % number of minion sets that have 6 or more minions with the property W > 2*S
total_weight = 0;     %keeps the total minion weight		
N = 38416;            %number of monte carlo trials to reach correct result within given precision 			

for i=1 : N

	rand_poiss = poissrnd(20,1);   %number of minions that are caught within 5 hours

	for j=1 : rand_poiss

		w = rand;   %these w,s and v are generated random 
		s = rand;   %numbers in order to      	
         	v = rand;   %apply rejection method
        
		W = ( 35 - 0) * w; %35  is b 
		S = ( 35 - 0) * s; %0   is a
        	Y = (1/exp(1))*v;  %1/e is c	
				   %these are coefficients of rejection algorithm	 	

		while(( Y>W ) || ( Y>S ))
			
			%this is the area that generated randoms are not usable,
			%and they are should be changed.
 				
			w = rand;
			s = rand;
	        	v = rand;

			W = ( 35 - 0) * w;
			S = ( 35 - 0) * s;
        		Y = (1/exp(1))*v;

		end				  	

		if(W > 2*S)

			num_of_minion = num_of_minion +1;

		end

		total_weight = total_weight + W;	

	end
	
	if(num_of_minion > 6)

		num_of_trial = num_of_trial + 1; 

	end	
		
	num_of_minion = 0;
	j = 0;

end

estimated_minion = num_of_trial/N 

estimated_total = total_weight/N


