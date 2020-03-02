`timescale 1ns / 1ps
module FUNCROM (input [3:0] romAddress, output reg[4:0] romData);

	wire [4:0]register2[0:15] ;
	
	integer i,decimal_num2=4'b0000;
	
	assign register2[0] = 5'b00000;
	assign register2[1] = 5'b00010;
	assign register2[2] = 5'b00100;
	assign register2[3] = 5'b00111;
	assign register2[4] = 5'b01010;
	assign register2[5] = 5'b01011;
	assign register2[6] = 5'b01101;
	assign register2[7] = 5'b01110;
	assign register2[8] = 5'b10001;
	assign register2[9] = 5'b10010;
	assign register2[10] = 5'b10100;
	assign register2[11] = 5'b10111;
	assign register2[12] = 5'b11001;
	assign register2[13] = 5'b11010;
	assign register2[14] = 5'b11110;
	assign register2[15] = 5'b11111;
	
	always@( romAddress )
	
	begin
	
		decimal_num2 = (8*romAddress[3])+(4*romAddress[2])+(2*romAddress[1])+(romAddress[0]);
			
		for(i = 0; i < 3'b101 ; i = i+1)
			
			begin

				romData[i] = register2[decimal_num2][i];
				
			end
			
	end
		
endmodule
																						
module FUNCRAM (input mode,input [3:0] ramAddress, input [4:0] dataIn,input op, input [1:0] arg,  input CLK, output reg [8:0] dataOut);
/*Write your code here*/

	reg[8:0]register1[0:15] ;
	
	reg result[8:0];
	
	integer j=4'b0000 ,decimal_num=4'b0000 ,arg_plugged=9'b000000000;
	
	integer c0,c1,c2,c3,c4;

	initial begin
	
		result[6] = 1'b0;
		result[7] = 1'b0;

		register1[0] = 9'b000000000;
		register1[1] = 9'b000000000;
		register1[2] = 9'b000000000;
		register1[3] = 9'b000000000;
		register1[4] = 9'b000000000;
		register1[5] = 9'b000000000;
		register1[6] = 9'b000000000;
		register1[7] = 9'b000000000;
		register1[8] = 9'b000000000;
		register1[9] = 9'b000000000;
		register1[10] = 9'b000000000;
		register1[11] = 9'b000000000;
		register1[12] = 9'b000000000;
		register1[13] = 9'b000000000;
		register1[14] = 9'b000000000;
		register1[15] = 9'b000000000;
		
	end
	
	always @(ramAddress or mode)
	
		begin
	
		if(mode == 1'b0) //read mode
	
			begin
			
				decimal_num = (8*ramAddress[3])+(4*ramAddress[2])+(2*ramAddress[1])+(ramAddress[0]);
				
				for(j=0;j < 4'b1001;j=j+1)
		
				dataOut[j] = register1[decimal_num][j];
		
			end
			
		end
		
	always@( posedge CLK )
	
		begin
		
		if(mode == 1'b1) //write mode
		
			begin
			
				decimal_num = (8*ramAddress[3])+(4*ramAddress[2])+(2*ramAddress[1])+(ramAddress[0]);
			
				if(dataIn[0]== 0) c0 = 1'b1;
				else c0 = -1;
				
				if(dataIn[1]== 0) c1 = 1'b1;
				else c1 = -1;
				
				if(dataIn[2]== 0) c2 = 1'b1;
				else c2 = -1;
				
				if(dataIn[3]== 0) c3 = 1'b1;
				else c3 = -1;
				
				if(dataIn[4]== 0) c4 = 1'b1;
				else c4 = -1;
					
				if(op == 1'b1) //derivative
				
					begin
					
					c0 = c1;
					c1 = 2*c2;
					c2 = 3*c3;
					c3 = (4*c4);
					c4 = 0;
					
					end
	
				if((arg[1] == 0) & (arg[0] == 0)) begin
		
					arg_plugged = (16*c4) + (8*c3) + (4*c2) + (2*c1)+ c0; end
			
				else if((arg[1] == 1) & (arg[0] == 1)) begin
		
					arg_plugged = (16*c4) - (8*c3) + (4*c2) - (2*c1)+ c0; end
	
				else if((arg[1] == 0) & (arg[0] == 1)) begin
		
					arg_plugged = c4 + c3 + c2 + c1+ c0; end
			
				else	begin
		
					arg_plugged = c4 - c3 + c2 - c1 + c0; end	
				
				if(op == 1'b0) //modulo
				
					begin
					
						arg_plugged = arg_plugged % 7;

						if(arg_plugged < 1'b0)
						
							arg_plugged = arg_plugged + 7;
			
					end
				
				if(arg_plugged < 0) begin
					
					register1[decimal_num] = (-1)*arg_plugged;
					register1[decimal_num][8] = 1'b1;
					
					end
					
				else register1[decimal_num] = arg_plugged;
		
			end
		
		end
	
endmodule


module FUNCMEMORY(input mode, input [6:0] memInput, input CLK, output wire [8:0] result);
	/*Don't edit this module*/
	wire [4:0]  romData;

	FUNCROM RO(memInput[6:3], romData);
	FUNCRAM RA(mode, memInput[6:3], romData, memInput[2],memInput[1:0], CLK, result);

endmodule
