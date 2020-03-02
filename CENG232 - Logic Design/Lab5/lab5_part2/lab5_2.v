`timescale 1ns / 1ps

module Elevator(input CLK,
					input [1:0] mode,
					input [3:0] request,
					output reg[3:0] currentFloor1,
					output reg[3:0] currentFloor2,
					output reg doorOpen1, 
					output reg doorOpen2, 
					output reg [3:0] listingLeds,
					output reg listBusy,
					output reg state);

//Write your code below

	reg [3:0] pool [0:7] ;
	reg [3:0] temp1 ;
	reg [3:0] temp2 ;
	
	reg check ;
	
	integer i_list ,i_del;

initial begin
	currentFloor1[3:0] = 1;
	currentFloor2[3:0] = 1;
	doorOpen1=1;
	doorOpen2=1;
	listingLeds=4'b0000;
	listBusy = 0;
	state = 0;
	
	pool[0] = 4'b0000;
	pool[1] = 4'b0000;
	pool[2] = 4'b0000;
	pool[3] = 4'b0000;
	pool[4] = 4'b0000;
	pool[5] = 4'b0000;
	pool[6] = 4'b0000;
	pool[7] = 4'b0000;
	check   = 1'b0   ;
	i_list  = 0      ; 
	i_del   = 0      ; 
	
end

always@ ( posedge CLK) 

	begin // begin of always block
	
	if( mode == 2'b00)
	
		begin // begin of add mode
		
		if( pool[0] == 4'b0000 ) pool[0] = request ;
		
		else if ( pool[0] == request ) check = 1'b1 ;
		
		else if(( pool[1] == 4'b0000 ) & ( check == 0 )) pool[1] = request ; 
		
		else if( pool[1] == request ) check = 1'b1 ;

		else if(( pool[2] == 4'b0000 ) & ( check == 0 )) pool[2] = request ; 
		
		else if( pool[2] == request ) check = 1'b1 ;
		
		else if(( pool[3] == 4'b0000 ) & ( check == 0 )) pool[3] = request ; 
		
		else if( pool[3] == request ) check = 1'b1 ;
		
		else if(( pool[4] == 4'b0000 ) & ( check == 0 )) pool[4] = request ; 
		
		else if( pool[4] == request ) check = 1'b1 ;
		
		else if(( pool[5] == 4'b0000 ) & ( check == 0 )) pool[5] = request ; 
		
		else if( pool[5] == request ) check = 1'b1 ;
		
		else if(( pool[6] == 4'b0000 ) & ( check == 0 )) pool[6] = request ; 
		
		else if( pool[6] == request ) check = 1'b1 ;
		
		else if(( pool[7] == 4'b0000 ) & ( check == 0 )) pool[7] = request ; 
		
		else if( pool[7] == request ) check = 1'b1 ;
		
		check = 1'b0 ;
		
		end // end of add mode
	
	if( mode == 2'b01)
	
		begin // begin of list block
		
		listBusy = 1'b1 ;
		
		if( pool[i_list] != 4'b0000 ) 
		
			begin
			
			listingLeds = pool[i_list] ;

			i_list = i_list +1;

			end
			
		else 
		
			begin
			
			listBusy = 1'b0 ;
			
			i_list = 0 ;
			
			end
			
		end // end of list block
		
	if ( mode == 2'b10)  

		begin // begin of delete mode 

			if ( pool[0] == request ) begin i_del = 0 ; check = 1'b1 ; end
			
				else if ( pool[1] == request ) begin i_del = 1 ; check = 1'b1 ; end
			
				else if ( pool[2] == request ) begin i_del = 2 ; check = 1'b1 ; end
			
				else if ( pool[3] == request ) begin i_del = 3 ; check = 1'b1 ; end
			
				else if ( pool[4] == request ) begin i_del = 4 ; check = 1'b1 ; end
			
				else if ( pool[5] == request ) begin i_del = 5 ; check = 1'b1 ; end
			
				else if ( pool[6] == request ) begin i_del = 6 ; check = 1'b1 ; end
			
				else if ( pool[7] == request ) begin i_del = 7 ; check = 1'b1 ; end
			
			if( check == 1'b1 )
			
				begin
				
				if( i_del == 0) begin
				
					pool[0] = pool[1];pool[1] = pool[2];pool[2] = pool[3];pool[3] = pool[4];
					pool[4] = pool[5];pool[5] = pool[6];pool[6] = pool[7];pool[7] = 4'b0000;  end
				
				if( i_del == 1) begin
				
					pool[1] = pool[2];pool[2] = pool[3];pool[3] = pool[4];pool[4] = pool[5];
					pool[5] = pool[6];pool[6] = pool[7];pool[7] = 4'b0000;  end
				
				if( i_del == 2) begin
				
					pool[2] = pool[3];pool[3] = pool[4];pool[4] = pool[5];
					pool[5] = pool[6];pool[6] = pool[7];pool[7] = 4'b0000;  end
				
				if( i_del == 3) begin
				
					pool[3] = pool[4];pool[4] = pool[5];pool[5] = pool[6];pool[6] = pool[7];pool[7] = 4'b0000;  end
				
				if( i_del == 4) begin
				
					pool[4] = pool[5];pool[5] = pool[6];pool[6] = pool[7];pool[7] = 4'b0000;  end
				
				if( i_del == 5) begin
				
					pool[5] = pool[6];pool[6] = pool[7];pool[7] = 4'b0000;  end
				
				if( i_del == 6) begin
				
					pool[6] = pool[7];pool[7] = 4'b0000;  end
				
				if( i_del == 7) begin
				pool[7] = 4'b0000;  end
				
				end
				
			check = 1'b0 ;

			i_del = 0 ;	
			
		end //end of delete mode
	
	if( mode == 2'b11)
	
		begin // begin of work mode
		
		state = 1'b1 ;
		
		if(( pool[0] != 4'b0000 ) & ( doorOpen1 == 1'b1 ))
		
			begin
				
				temp1 = pool[0];pool[0] = pool[1];pool[1] = pool[2];pool[2] = pool[3];pool[3] = pool[4];
				pool[4] = pool[5];pool[5] = pool[6];pool[6] = pool[7];pool[7] = 4'b0000; 
			
			end
			
		if(( pool[0] != 4'b0000 ) & ( doorOpen2 == 1'b1 ))
		
			begin
				
				temp2 = pool[0];pool[0] = pool[1];pool[1] = pool[2];pool[2] = pool[3];pool[3] = pool[4];
				pool[4] = pool[5];pool[5] = pool[6];pool[6] = pool[7];pool[7] = 4'b0000; 
			
			end		
			
		doorOpen1 = 1'b0 ;
		doorOpen2 = 1'b0 ;

		if( currentFloor1 < temp1 ) currentFloor1 = currentFloor1 +1 ;
		
			else if ( currentFloor1 == temp1 ) ;

			else currentFloor1 = currentFloor1 -1 ;
		
		if( currentFloor2 < temp2 ) currentFloor2 = currentFloor2 +1 ;
		
			else if( currentFloor2 == temp2 ) ;

			else currentFloor2 = currentFloor2 -1 ;
			
		if ( currentFloor1 == temp1 ) doorOpen1 = 1'b1 ;
		
		if ( currentFloor2 == temp2 ) doorOpen2 = 1'b1 ;
			
		if (( pool[0] == 4'b0000) & ( doorOpen1 == 1'b1 ) & ( doorOpen2 == 1'b1 )) state = 1'b0 ;	
		
		end // end of work mode
		
	end //  end of always block

endmodule