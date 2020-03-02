i = 1;
N = 1000;
estimateds = 0;
real_estimate = 0;

for i = 1 : N
	
	a = exprnd(2);
	b = normrnd(0,1);
	c = b;
	if (b < 0)
		c = -1 * b;

	end 

	estimateds = estimateds + mean((a+2*b)/(1+c));

end

real_estimate = estimateds / 1000

	 
