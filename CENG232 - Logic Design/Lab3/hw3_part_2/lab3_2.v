			`timescale 1ns / 1ps 
module lab3_2(
			input[4:0] word,
			input CLK, 
			input selection,
			input mode,
			output reg [7:0] hipsterians1,
			output reg [7:0] hipsterians0,
			output reg [7:0] nerdians1,
			output reg [7:0] nerdians0,
			output reg warning
    );

	initial begin
		hipsterians0=0;
		nerdians0=0;
		hipsterians1=0;
		nerdians1=0;
		warning=0;
	end
   //Modify the lines below to implement your design .
	
	always@(posedge CLK )
		
		if(selection == 1'b0) 
		
			begin
			
			if(((word[0] == word[1]) & (word[0] == 1'b0)) | ((word[1] == word[2]) & (word[1] == 1'b0)) | ((word[2] == word[3]) & (word[2] == 1'b0)) |
			
				((word[3] == word[4]) & (word[4] == 1'b0))) 
		
				begin
				
				if(mode == 1'b1) 
				
					begin 
					
					if(hipsterians0 == 1'd9)
					
						begin 
						
						if(hipsterians1 == 1'b0)
						
							begin
							
							hipsterians0 = 1'b0;
		
							hipsterians1 = 1'b1;
							
							end
						
						else
						
							begin
						
							hipsterians0 = 1'b0;
						
							hipsterians1 = 1'd2;
		
							end
							
						end
						
					else if((hipsterians1 == 1'd2)&(hipsterians0 == 1'b0))		
		
						begin
						
						hipsterians1 = 1'b0;
						
						hipsterians0 = 1'b0; 
						
						end
						
					else

						begin
						
						hipsterians0 = hipsterians0 + 1'b1;
						
						hipsterians1 = hipsterians1 + 1'b1;

						end
						
					end
					
				else 
				
					begin 
					
					if((hipsterians0 == 1'b0)&(hipsterians1 == 1'b0));
					
					else
					
						begin
							
						hipsterians0 = hipsterians0 + 1'b1;
						
						hipsterians1 = hipsterians1 + 1'b1;
							
						end
						
					end
						
				end			
				
				else warning = 1'b1 ;
				
				end
				
			else

				begin
				
				if(((word[0] == word[1]) & (word[0] == 1'b1)) | ((word[1] == word[2]) & (word[1] == 1'b1)) | ((word[2] == word[3]) & (word[2] == 1'b1)) |
			
				((word[3] == word[4]) & (word[4] == 1'b1))) 
		
				begin
				
				if(mode == 1'b1) 
				
					begin 
					
					if(nerdians0 == 1'd9)
					
						begin 
						
						if(nerdians1 == 1'b0)
						
							begin
							
							nerdians0 = 1'b0;
		
							nerdians1 = 1'b1;
							
							end
						
						else
						
							begin
						
							nerdians0 = 1'b0;
						
							nerdians1 = 1'd2;
		
							end
							
						end
						
					else if((nerdians1 == 1'd2)&(nerdians0 == 1'b0))		
		
						begin
						
						nerdians1 = 1'b0;
						
						nerdians0 = 1'b0; 
						
						end
						
					else

						begin
						
						nerdians0 = nerdians0 + 1'b1;
						
						nerdians1 = nerdians1 + 1'b1;

						end
						
					end
					
				else 
				
					begin 
					
					if((nerdians0 == 1'b0)&(nerdians1 == 1'b0));
					
					else
					
						begin
							
						nerdians0 = nerdians0 + 1'b1;
						
						nerdians1 = nerdians1 + 1'b1;
							
						end
						
					end
						
				end			
				
				else warning = 1'b1 ;
				
				end		
				
endmodule


