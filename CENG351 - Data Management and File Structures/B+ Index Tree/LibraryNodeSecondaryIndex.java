import java.util.ArrayList;

public class LibraryNodeSecondaryIndex extends LibraryNode
{
	private ArrayList<Integer> keys;
	private ArrayList<Integer> years;
	private ArrayList<LibraryNode> children;	
	
	public LibraryNodeSecondaryIndex(LibraryNode parent) 
	{
		super(parent);
		keys = new ArrayList<Integer>();
		years = new ArrayList<Integer>();
		children = new ArrayList<LibraryNode>();
		this.type = LibraryNodeType.Internal;
	}
	
	public LibraryNodeSecondaryIndex(LibraryNode parent, ArrayList<Integer> years, ArrayList<Integer> keys, ArrayList<LibraryNode> children) 
	{
		super(parent);
		this.years = years;
		this.keys = keys;
		this.children = children;
		this.type = LibraryNodeType.Internal;
	}
	
	// GUI Methods - Do not modify
	public ArrayList<LibraryNode> getAllChildren()
	{
		return this.children;
	}
	
	public LibraryNode getChildrenAt(Integer index) {
		
		return this.children.get(index);
	}
	
	public Integer keyCount()
	{
		return this.keys.size();
	}
	public Integer keyAtIndex(Integer index)
	{
		if(index >= this.keyCount() || index < 0)
		{
			return -1;
		}
		else
		{
			return this.keys.get(index);			
		}
	}
	
	public Integer yearAtIndex(Integer index)
	{
		if(index >= this.keyCount() || index < 0)
		{
			return -1;
		}
		else
		{
			return this.years.get(index);			
		}
	}
	
	
	// Extra functions if needed

	public void addLeaf( LibraryNodeLeaf newLeaf1 , LibraryNodeLeaf newLeaf2 , Integer number , Integer key) {

		int i=0 , j=0 ;

		do { 


			if( years.get(i) < number ) {i++ ; continue ;}

			if( (int)years.get(i) == number  ){

				if(key > keys.get(i)){

					i++ ; continue ;
				}
			}

			break ;

		} while (i < this.years.size() );

		this.years.add(i,number) ;

		this.keys.add(i,key) ;

		do {

			if( j == i) {

				this.children.remove(i) ;

				this.children.add(i , newLeaf1 ) ;

				this.children.add(i+1 , newLeaf2 ) ;

				break ;
			}

			j++ ;

		} while ( j < this.years.size() );

		return ;
 }

 public LibraryNode addPindex( LibraryNodeLeaf newLeaf1 , LibraryNodeLeaf newLeaf2 , LibraryNode parent ) {

	 int moveup , moveup_year , i,j;

	 ArrayList<Integer> keys1 = new ArrayList<Integer>() ;

	 ArrayList<Integer> keys2 = new ArrayList<Integer>() ;

	 ArrayList<Integer> years1 = new ArrayList<Integer>() ;

	 ArrayList<Integer> years2 = new ArrayList<Integer>() ;

	 ArrayList<LibraryNode> children1 = new ArrayList<LibraryNode>() ;

	 ArrayList<LibraryNode> children2 = new ArrayList<LibraryNode>() ;

	 i=0 ;j=0;

		do {

			if(newLeaf2.bookAtIndex(0).year() > ((LibraryNodeSecondaryIndex)parent).yearAtIndex(i) ) {

			 i++ ;

			 continue ;

			 }

			 else if( newLeaf2.bookAtIndex(0).year() == (int)((LibraryNodeSecondaryIndex)parent).yearAtIndex(i)) {

			 	if( newLeaf2.bookAtIndex(0).key() > (int)((LibraryNodeSecondaryIndex)parent).keyAtIndex(i)){
			 		i++ ; continue ;
			 	}
			 }

			 break ;

		} while (i < 2*LibraryNode.order) ;

		if(i < LibraryNode.order) {

			for(j=0 ; j < LibraryNode.order -1; j++) {

				keys1.add(((LibraryNodeSecondaryIndex)parent).keyAtIndex(j) ) ;
			}

			keys1.add(i , newLeaf2.bookAtIndex(0).key()) ;

			for(;j< 2*LibraryNode.order;j++){

				keys2.add(((LibraryNodeSecondaryIndex)parent).keyAtIndex(j) ) ;
			}

		}

		else{

			for(j=0 ; j< LibraryNode.order ; j++){

				keys1.add(((LibraryNodeSecondaryIndex)parent).keyAtIndex(j) ) ;
			}

			for( ; j < 2*LibraryNode.order ; j++) {

				keys2.add(((LibraryNodeSecondaryIndex)parent).keyAtIndex(j) ) ;
			}

			keys2.add(i-LibraryNode.order , newLeaf2.bookAtIndex(0).key() ) ;
	 }

		if(i < LibraryNode.order) {

			for(j=0 ; j < LibraryNode.order -1; j++) {

				years1.add(((LibraryNodeSecondaryIndex)parent).yearAtIndex(j) ) ;
			}

			years1.add(i , newLeaf2.bookAtIndex(0).year()) ;

			for(;j< 2*LibraryNode.order;j++){

				years2.add(((LibraryNodeSecondaryIndex)parent).yearAtIndex(j) ) ;
			}

		}

		else{

			for(j=0 ; j< LibraryNode.order ; j++){

				years1.add(((LibraryNodeSecondaryIndex)parent).yearAtIndex(j) ) ;
			}

			for( ; j < 2*LibraryNode.order ; j++) {

				years2.add(((LibraryNodeSecondaryIndex)parent).yearAtIndex(j) ) ;
			}

			years2.add(i-LibraryNode.order , newLeaf2.bookAtIndex(0).year() ) ;
	 	}

	 moveup = keys2.get(0) ;

	 keys2.remove(0) ;

	 moveup_year = years2.get(0) ;

	 years2.remove(0) ;

	 if(i< LibraryNode.order) {

		 for(j=0 ; j< LibraryNode.order ; j++) {

			 children1.add(j , this.children.get(j)) ;
		 }
		 children1.remove(i) ;

		 children1.add(i , newLeaf1 ) ;

		 children1.add(i +1 , newLeaf2 ) ;

		 for( ; j <= 2*LibraryNode.order ; j++){

			 children2.add(j-LibraryNode.order , this.children.get(j) ) ;
		 }
	 }

	 else if( i == LibraryNode.order ) {

		 for(j = 0 ; j<LibraryNode.order ; j++) {

			 children1.add(j , this.children.get(j) ) ;
		 }

		 children1.add(j,newLeaf1) ;

		 children2.add(0 , newLeaf2 ) ;

		 j++ ;

		 for( ; j<=2*order ; j++){

			 children2.add( j-LibraryNode.order , this.children.get(j) ) ;
		 }
	 }

	 else{

		 for(j=0 ; j <= LibraryNode.order ; j++) {

			 children1.add( j , this.children.get(j) ) ;
		 }

		 for( ; j <=2*LibraryNode.order ; j++){

			 children2.add(j-LibraryNode.order-1 , this.children.get(j) ) ;
		 }

		 children2.remove(i-LibraryNode.order-1) ;

		 children2.add(i-LibraryNode.order-1 , newLeaf1) ;

		 children2.add(i-LibraryNode.order , newLeaf2) ;
	 }

	 if(parent.getParent() == null) {

		ArrayList<Integer> keys3 = new ArrayList<Integer>() ;

		ArrayList<Integer> years3 = new ArrayList<Integer>() ;

		keys3.add(moveup) ; years3.add(moveup_year) ; 

		ArrayList<LibraryNode> children3 = new ArrayList<LibraryNode>() ;

		LibraryNodeSecondaryIndex newPindex1 = new LibraryNodeSecondaryIndex( null , years1 , keys1 , children1) ;

		LibraryNodeSecondaryIndex newPindex2 = new LibraryNodeSecondaryIndex( null , years2 ,keys2 , children2) ;

		children3.add(newPindex1) ; children3.add(newPindex2) ;

		LibraryNodeSecondaryIndex newPindex3 = new LibraryNodeSecondaryIndex( null , years3 ,keys3 , children3) ;

		newPindex1.setParent(newPindex3) ;  newPindex2.setParent(newPindex3) ;

		for(j=0 ; j < children1.size() ; j++)
			(children1.get(j)).setParent(newPindex1) ;

		for(j=0 ; j < children2.size() ; j++)
			(children2.get(j)).setParent(newPindex2) ;

		return newPindex3;
 	}

	else {

		LibraryNodeSecondaryIndex parent2 = ( ( LibraryNodeSecondaryIndex ) (parent.getParent() ) ) ;

		LibraryNodeSecondaryIndex newPindex1 = new LibraryNodeSecondaryIndex( null , years1 , keys1 , children1) ;

		LibraryNodeSecondaryIndex newPindex2 = new LibraryNodeSecondaryIndex( null , years2 , keys2 , children2) ;

		for(j=0 ; j < children1.size() ; j++)
			(children1.get(j)).setParent(newPindex1) ;

		for(j=0 ; j < children2.size() ; j++)
			(children2.get(j)).setParent(newPindex2) ;

		if( parent2.keyCount() != 2 *LibraryNode.order){

			for(j = 0 ; j < parent2.keyCount() ; j++){

				if(moveup_year > parent2.yearAtIndex(j)) ;

				else break ;
			}

			parent2.children.remove(j) ;

			parent2.keys.add(j , moveup) ;

			parent2.years.add(j , moveup_year) ;

			parent2.children.add(j , newPindex1) ;

			parent2.children.add(j+1 , newPindex2) ;

			newPindex1.setParent(parent2) ;  newPindex2.setParent(parent2) ;

			return null ;			

		}

		else{

			return addPindex2( newPindex1 , newPindex2 , parent2 , moveup , moveup_year) ;
		}


	}

	}


	public LibraryNode addPindex2( LibraryNodeSecondaryIndex newPindex1 , LibraryNodeSecondaryIndex newPindex2 , LibraryNodeSecondaryIndex parent , Integer moveup , Integer moveup_year) {

		int i = 0 , j = 0 ;

		ArrayList<Integer> keys1 = new ArrayList<Integer>() ;

	 	ArrayList<Integer> keys2 = new ArrayList<Integer>() ;

	 	ArrayList<Integer> years1 = new ArrayList<Integer>() ;

	 	ArrayList<Integer> years2 = new ArrayList<Integer>() ;

	 	ArrayList<LibraryNode> children1 = new ArrayList<LibraryNode>() ;

	 	ArrayList<LibraryNode> children2 = new ArrayList<LibraryNode>() ;

		while(true){

			for(i = 0 ; i < parent.keyCount() ; i++ ) {

				if(moveup_year > parent.yearAtIndex(i)) continue ;

				else if(moveup_year == (int)parent.yearAtIndex(i)){

					if(moveup > (int)parent.keyAtIndex(i) ) continue ;
				} 

				break ;
			}

			if( i < LibraryNode.order ) {

				for(j = 0 ; j < LibraryNode.order -1 ; j++){

					keys1.add(j , parent.keyAtIndex(j)) ;
				}

				for(; j < 2*LibraryNode.order ; j++){

					keys2.add(j-LibraryNode.order +1, parent.keyAtIndex(j)) ;
				}

				keys1.add(i , moveup ) ;
			

			}

			else{

				for(j = 0 ; j < LibraryNode.order ; j++){

					keys1.add(j , parent.keyAtIndex(j)) ;
				}

				for(; j < 2*LibraryNode.order ; j++){

					keys2.add(j-LibraryNode.order , parent.keyAtIndex(j)) ;
				}

				keys2.add(i - LibraryNode.order , moveup ) ;
			}

			
			if( i < LibraryNode.order ) {

				for(j = 0 ; j < LibraryNode.order -1 ; j++){

					years1.add(j , parent.yearAtIndex(j)) ;
				}

				for(; j < 2*LibraryNode.order ; j++){

					years2.add(j-LibraryNode.order +1, parent.yearAtIndex(j)) ;
				}

				years1.add(i , moveup_year ) ;
			

			}

			else{

				for(j = 0 ; j < LibraryNode.order ; j++){

					years1.add(j , parent.yearAtIndex(j)) ;
				}

				for(; j < 2*LibraryNode.order ; j++){

					years2.add(j-LibraryNode.order , parent.yearAtIndex(j)) ;
				}

				years2.add(i - LibraryNode.order , moveup_year ) ;
			}



			if(i < LibraryNode.order){

				for(j = 0 ; j < LibraryNode.order; j++){

					children1.add(j , parent.getChildrenAt(j) ) ;
				}

				for( ; j <= 2*LibraryNode.order;j++){

					children2.add(j - LibraryNode.order , parent.getChildrenAt(j) ) ;
				}



				children1.remove(i) ;

				children1.add(i , newPindex1) ;

				children1.add(i+1 , newPindex2) ;
			}

			else if (i == LibraryNode.order){

				for(j = 0 ; j < LibraryNode.order; j++){

					children1.add(j , parent.getChildrenAt(j) ) ;
				}

				children1.add(j , newPindex1) ;

				j++ ;

				children2.add(0 , newPindex2) ;

				for( ; j <= 2*LibraryNode.order;j++){

					children2.add(j - LibraryNode.order , parent.getChildrenAt(j) ) ;
				}

			}

			else{

				for(j=0 ; j <= LibraryNode.order ; j++){

					children1.add(j , parent.getChildrenAt(j) ) ;
				}

				for( ; j <= 2*LibraryNode.order ; j++ ){

					children2.add(j - LibraryNode.order - 1 , parent.getChildrenAt(j) ) ;
				}

				children2.remove(i-LibraryNode.order-1) ;

		 		children2.add(i-LibraryNode.order-1 , newPindex1) ;

		 		children2.add(i-LibraryNode.order , newPindex2) ;


			}

			LibraryNodeSecondaryIndex parent2 = ( ( LibraryNodeSecondaryIndex ) (parent.getParent() ) ) ;

			if( parent2 == null ) {

				ArrayList<Integer> keys3 = new ArrayList<Integer>() ;

				ArrayList<Integer> years3 = new ArrayList<Integer>() ;

				moveup = keys2.get(0) ; moveup_year = years2.get(0) ;

				keys2.remove(0) ; years2.remove(0) ;

				keys3.add(moveup) ; years3.add(moveup_year) ;

				ArrayList<LibraryNode> children3 = new ArrayList<LibraryNode>() ;

				LibraryNodeSecondaryIndex newPindex3 = new LibraryNodeSecondaryIndex( null , years1 , keys1 , children1) ;

				LibraryNodeSecondaryIndex newPindex4 = new LibraryNodeSecondaryIndex( null , years2 , keys2 , children2) ;

				children3.add(newPindex3) ; children3.add(newPindex4) ;

				LibraryNodeSecondaryIndex newPindex5 = new LibraryNodeSecondaryIndex( null , years3 , keys3 , children3) ;

				newPindex3.setParent(newPindex5) ;  newPindex4.setParent(newPindex5) ;

				for(j=0 ; j < children1.size() ; j++)
					(children1.get(j)).setParent(newPindex3) ;

				for(j=0 ; j < children2.size() ; j++)
						(children2.get(j)).setParent(newPindex4) ;

				return newPindex5;

			}

			else if(parent2.keyCount() != 2 *LibraryNode.order){

				moveup = keys2.get(0) ; moveup_year = years2.get(0) ;

				keys2.remove(0) ; years2.remove(0) ;

				LibraryNodeSecondaryIndex newPindex3 = new LibraryNodeSecondaryIndex( null , years1 ,keys1 , children1) ;

				LibraryNodeSecondaryIndex newPindex4 = new LibraryNodeSecondaryIndex( null , years2 ,keys2 , children2) ;

				for(j=0 ; j < children1.size() ; j++)
					(children1.get(j)).setParent(newPindex3) ;

				for(j=0 ; j < children2.size() ; j++)
					(children2.get(j)).setParent(newPindex4) ;

				for(j = 0 ; j < parent2.keyCount() ; j++){

					if(moveup_year > parent2.yearAtIndex(j)) ;

					else break ;
				}

					parent2.children.remove(j) ;

					parent2.keys.add(j , moveup) ;

					parent2.years.add(j , moveup_year) ;

					parent2.children.add(j , newPindex3) ;

					parent2.children.add(j+1 , newPindex4) ;

					newPindex3.setParent(parent2) ;  newPindex4.setParent(parent2) ;

					return null ;			

			}

			else{

				moveup = keys2.get(0) ; moveup_year = years2.get(0) ;

				keys2.remove(0) ; years2.remove(0) ; 

				LibraryNodeSecondaryIndex newPindex3 = new LibraryNodeSecondaryIndex( null ,years1, keys1 , children1) ;

				LibraryNodeSecondaryIndex newPindex4 = new LibraryNodeSecondaryIndex( null ,years2, keys2 , children2) ;

				for(j=0 ; j < children1.size() ; j++)
					(children1.get(j)).setParent(newPindex3) ;

				for(j=0 ; j < children2.size() ; j++)
					(children2.get(j)).setParent(newPindex4) ;

				return addPindex2( newPindex3 , newPindex4 , parent2 , moveup , moveup_year) ;
			}


		}
	}




}
