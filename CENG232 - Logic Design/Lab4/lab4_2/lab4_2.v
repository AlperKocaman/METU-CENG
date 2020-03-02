`timescale 1ns / 1ps

module lab4_2(
	input[3:0] userID, 
	input CLK, 
	input team,
	input [1:0] mode,
	output reg  [7:0] numPlyLP,
	output reg  [7:0] numPlyCF,
	output reg  teamWng,
	output reg capWngLP,
	output reg capWngCF,
	output reg findRes,
	output reg [3:0] listOut,
	output reg  listMode
    );
//Write your code below

	reg [3:0] memLP[0:4];
	reg [3:0] memCF[0:4];
	
	reg [2:0]i;
	reg [2:0]numLP;
	reg [2:0]numCF;
	
	initial begin
	
		memLP[4] = 4'b0000;
		memLP[3] = 4'b0000;
		memLP[2] = 4'b0000;
		memLP[1] = 4'b0000;
		memLP[0] = 4'b0000;
		
		memCF[4] = 4'b0000;
		memCF[3] = 4'b0000;
		memCF[2] = 4'b0000;
		memCF[1] = 4'b0000;
		memCF[0] = 4'b0000;
		
		i = 3'b100;
		numLP = 3'b000;
		numCF = 3'b000;
		findRes = 1'b0;
		listMode = 1'b0;
		
	end
	
	always@(posedge CLK)
	
	begin
	
	teamWng = 1'b0;
	
	findRes = 1'b0;
	
	listMode = 1'b0;
	
	if((numLP == 1'b0) | (numLP == 3'b101)) begin
	
		capWngLP = 1'b1; end

	if((numCF == 1'b0) | (numCF == 3'b101)) begin
	
		capWngCF = 1'b1; end				
		
		
	if((mode[1] == 1'b0) & (mode[0] == 1'b0)) // logout mode
	
		begin
		
		i = 3'b100;
	
			if(userID[3] == 1'b0)
			
				begin
				
					if(userID == memLP[4])
						
						begin
						
							memLP[4] = 4'b0000;
						
							numLP = numLP -1 ;
						
						end
						
					if(userID == memLP[3])
						
						begin
						
							memLP[3] = 4'b0000;
						
							numLP = numLP -1 ;
						
						end
						
						if(userID == memLP[2])
						
						begin
						
							memLP[2] = 4'b0000;
						
							numLP = numLP -1 ;
						
						end
						
						if(userID == memLP[1])
						
						begin
						
							memLP[1] = 4'b0000;
						
							numLP = numLP -1 ;
						
						end
						
						if(userID == memLP[0])
						
						begin
						
							memLP[0] = 4'b0000;
						
							numLP = numLP -1 ;
						
						end
	
				end	
	
			if(userID[3] == 1'b1)
			
				begin
				
					if(userID == memCF[4])
						
						begin
						
							memCF[4] = 4'b0000;
						
							numCF = numCF -1 ;
						
						end
						
					if(userID == memCF[3])
						
						begin
						
							memCF[3] = 4'b0000;
						
							numCF = numCF -1 ;
						
						end
						
						if(userID == memCF[2])
						
						begin
						
							memCF[2] = 4'b0000;
						
							numCF = numCF -1 ;
						
						end
						
						if(userID == memCF[1])
						
						begin
						
							memCF[1] = 4'b0000;
						
							numCF = numCF -1 ;
						
						end
						
						if(userID == memCF[0])
						
						begin
						
							memCF[0] = 4'b0000;
						
							numCF = numCF -1 ;
						
						end
	
				end		
	
		end
	
	if((mode[1] == 1'b0) & (mode[0] == 1'b1)) //login mode
	
		begin
		
		i = 3'b100;
		
		if(userID[3] != team)
		
			begin
			
				teamWng = 1'b1;
				
			end
			
		else if(((team == 1'b0) & (numLP == 3'b101)) | (team == 1'b1) & (numCF == 3'b101))
		
			begin
				
				teamWng = 1'b1;	
				
			end
		
		else if((team == 1'b0) & ((userID == memLP[4]) | (userID == memLP[3]) | (userID == memLP[2]) | (userID == memLP[1]) | (userID == memLP[0])));
		
		else if((team == 1'b1) & ((userID == memCF[4]) | (userID == memCF[3]) | (userID == memCF[2]) | (userID == memCF[1]) | (userID == memCF[0])));	
			
		else

			begin
			
				if(team == 1'b0)
				
					begin
			
						if(memLP[4] == {1'b0,1'b0,1'b0,1'b0})
						
							begin
							
							memLP[4][0] = userID[0];
							memLP[4][1] = userID[1];
							memLP[4][2] = userID[2];
							memLP[4][3] = userID[3];
							
							numLP = numLP +1;
							
							end
							
						else if(memLP[3] == {1'b0,1'b0,1'b0,1'b0})
						
							begin
							
							memLP[3][0] = userID[0];
							memLP[3][1] = userID[1];
							memLP[3][2] = userID[2];
							memLP[3][3] = userID[3];
							
							numLP = numLP +1;
							
							end
							
						else if(memLP[2] == {1'b0,1'b0,1'b0,1'b0})
						
							begin
							
							memLP[2][0] = userID[0];
							memLP[2][1] = userID[1];
							memLP[2][2] = userID[2];
							memLP[2][3] = userID[3];
							
							numLP = numLP +1;
							
							end
							
						else if(memLP[1] == {1'b0,1'b0,1'b0,1'b0})
						
							begin
							
							memLP[1][0] = userID[0];
							memLP[1][1] = userID[1];
							memLP[1][2] = userID[2];
							memLP[1][3] = userID[3];
							
							numLP = numLP +1;
							
							end
							
						else if(memLP[0] == {1'b0,1'b0,1'b0,1'b0})
						
							begin
							
							memLP[0][0] = userID[0];
							memLP[0][1] = userID[1];
							memLP[0][2] = userID[2];
							memLP[0][3] = userID[3];
							
							numLP = numLP +1;
							
							end	
				
	
					end//end of team 0
					
				if(team == 1'b1)
				
					begin
					
						if(memCF[4] == 4'b0000)
						
							begin
							
							memCF[0][0] = userID[0];
							memCF[0][1] = userID[1];
							memCF[0][2] = userID[2];
							memCF[0][3] = userID[3];
							
							numCF = numCF +1;
							
							end
							
						else if(memCF[3] == 4'b0000)
						
							begin
							
							memCF[3] = userID;
							
							numCF = numCF +1;
							
							end
							
						else if(memCF[2] == 4'b0000)
						
							begin
							
							memCF[2] = userID;
							
							numCF = numCF +1;
							
							end
							
						else if(memCF[1] == 4'b0000)
						
							begin
							
							memCF[1] = userID;
							
							numCF = numCF +1;
							
							end
							
						else if(memCF[0] == 4'b0000)
						
							begin
							
							memCF[0] = userID;
							
							numCF = numCF +1;
							
							end
	
				end//end of team 1
			
			end //end of writing mode
			
		end //end of login mode

	if((mode[1] == 1'b1) & (mode[0] == 1'b0)) //find mode

		begin
	
		i = 3'b100;

			if(userID[3] == 1'b0)
			
				begin
				
					if((userID == memLP[4]) | (userID == memLP[3]) | (userID == memLP[2]) | (userID == memLP[1]) | (userID == memLP[0]))
					
						begin
		
							findRes = 1'b1;
						
						end
						
					else findRes = 1'b0;
		
				end//end of team 0
				
			if(userID[3] == 1'b1)	
				
				begin
				
					if((userID == memCF[4]) | (userID == memCF[3]) | (userID == memCF[2]) | (userID == memCF[1]) | (userID == memCF[0]))
					
						begin
		
							findRes = 1'b1;
						
						end
						
					else findRes = 1'b0;
				
				end//end of team 1
	
		end//end of find mode
		
	if((mode[1] == 1'b1) & (mode[0] == 1'b1)) //list mode
	
		begin
		
			listMode = 1'b1;
		
			if(team == 1'b0)
		
				begin
		
					listOut = memLP[i];
		
					i = i - 1;	
		
				end
		
			if(team == 1'b1)
		
				begin
		
					listOut = memCF[i];
		
					i = i - 1;	
		
				end	
		
		end//end of list mode
	
	end //end of always block

endmodule
