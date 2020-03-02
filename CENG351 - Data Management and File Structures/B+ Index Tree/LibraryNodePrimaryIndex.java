import java.util.ArrayList;

public class LibraryNodePrimaryIndex extends LibraryNode
{
	private ArrayList<Integer> keys;
	private ArrayList<LibraryNode> children;

	public LibraryNodePrimaryIndex(LibraryNode parent)
	{
		super(parent);
		keys = new ArrayList<Integer>();
		children = new ArrayList<LibraryNode>();
		this.type = LibraryNodeType.Internal;
	}

	public LibraryNodePrimaryIndex(LibraryNode parent, ArrayList<Integer> keys, ArrayList<LibraryNode> children)
	{
		super(parent);
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

	// Extra functions if needed

	public void addLeaf( LibraryNodeLeaf newLeaf1 , LibraryNodeLeaf newLeaf2 , Integer number ) {

		int i=0 , j=0 ;

		do {

			if( keys.get(i) < number ) i++ ;

			else break ;

		} while (i < this.keys.size() );

		this.keys.add(i,number) ;

		do {

			if( j == i) {

				this.children.remove(i) ;

				this.children.add(i , newLeaf1 ) ;

				this.children.add(i+1 , newLeaf2 ) ;

				break ;
			}

			j++ ;

		} while ( j < this.keys.size() );

		return ;
 }

 public LibraryNode addPindex( LibraryNodeLeaf newLeaf1 , LibraryNodeLeaf newLeaf2 , LibraryNode parent ) {

	 int moveup ,i,j;

	 ArrayList<Integer> keys1 = new ArrayList<Integer>() ;

	 ArrayList<Integer> keys2 = new ArrayList<Integer>() ;

	 ArrayList<LibraryNode> children1 = new ArrayList<LibraryNode>() ;

	 ArrayList<LibraryNode> children2 = new ArrayList<LibraryNode>() ;

	 i=0 ;j=0;

		do {

			if(newLeaf2.bookAtIndex(0).key() > ((LibraryNodePrimaryIndex)parent).keyAtIndex(i) ) {

			 i++ ;

			 continue ;

			 }

			 break ;

		} while (i < 2*LibraryNode.order) ;

		if(i < LibraryNode.order) {

			for(j=0 ; j < LibraryNode.order -1; j++) {

				keys1.add(((LibraryNodePrimaryIndex)parent).keyAtIndex(j) ) ;
			}

			keys1.add(i , newLeaf2.bookAtIndex(0).key()) ;

			for(;j< 2*LibraryNode.order;j++){

				keys2.add(((LibraryNodePrimaryIndex)parent).keyAtIndex(j) ) ;
			}

		}

		else{

			for(j=0 ; j< LibraryNode.order ; j++){

				keys1.add(((LibraryNodePrimaryIndex)parent).keyAtIndex(j) ) ;
			}

			for( ; j < 2*LibraryNode.order ; j++) {

				keys2.add(((LibraryNodePrimaryIndex)parent).keyAtIndex(j) ) ;
			}

			keys2.add(i-LibraryNode.order , newLeaf2.bookAtIndex(0).key() ) ;
	 }

	 moveup = keys2.get(0) ;

	 keys2.remove(0) ;

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

		keys3.add(moveup) ;

		ArrayList<LibraryNode> children3 = new ArrayList<LibraryNode>() ;

		LibraryNodePrimaryIndex newPindex1 = new LibraryNodePrimaryIndex( null , keys1 , children1) ;

		LibraryNodePrimaryIndex newPindex2 = new LibraryNodePrimaryIndex( null , keys2 , children2) ;

		children3.add(newPindex1) ; children3.add(newPindex2) ;

		LibraryNodePrimaryIndex newPindex3 = new LibraryNodePrimaryIndex( null , keys3 , children3) ;

		newPindex1.setParent(newPindex3) ;  newPindex2.setParent(newPindex3) ;

		for(j=0 ; j < children1.size() ; j++)
			(children1.get(j)).setParent(newPindex1) ;

		for(j=0 ; j < children2.size() ; j++)
			(children2.get(j)).setParent(newPindex2) ;

		return newPindex3;
 	}

	else {

		LibraryNodePrimaryIndex parent2 = ( ( LibraryNodePrimaryIndex ) (parent.getParent() ) ) ;

		LibraryNodePrimaryIndex newPindex1 = new LibraryNodePrimaryIndex( null , keys1 , children1) ;

		LibraryNodePrimaryIndex newPindex2 = new LibraryNodePrimaryIndex( null , keys2 , children2) ;

		for(j=0 ; j < children1.size() ; j++)
			(children1.get(j)).setParent(newPindex1) ;

		for(j=0 ; j < children2.size() ; j++)
			(children2.get(j)).setParent(newPindex2) ;

		if( parent2.keyCount() != 2 *LibraryNode.order){

			for(j = 0 ; j < parent2.keyCount() ; j++){

				if(moveup > parent2.keyAtIndex(j)) ;

				else break ;
			}

			parent2.children.remove(j) ;

			parent2.keys.add(j , moveup) ;

			parent2.children.add(j , newPindex1) ;

			parent2.children.add(j+1 , newPindex2) ;

			newPindex1.setParent(parent2) ;  newPindex2.setParent(parent2) ;

			return null ;			

		}

		else{

			return addPindex2( newPindex1 , newPindex2 , parent2 , moveup) ;
		}


	}

	}

	public LibraryNode addPindex2( LibraryNodePrimaryIndex newPindex1 , LibraryNodePrimaryIndex newPindex2 , LibraryNodePrimaryIndex parent , Integer moveup) {

		int i = 0 , j = 0 ;

		ArrayList<Integer> keys1 = new ArrayList<Integer>() ;

	 	ArrayList<Integer> keys2 = new ArrayList<Integer>() ;

	 	ArrayList<LibraryNode> children1 = new ArrayList<LibraryNode>() ;

	 	ArrayList<LibraryNode> children2 = new ArrayList<LibraryNode>() ;

		while(true){

			for(i = 0 ; i < parent.keyCount() ; i++ ) {

				if(moveup > parent.keyAtIndex(i)) ;

				else break ;
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

			LibraryNodePrimaryIndex parent2 = ( ( LibraryNodePrimaryIndex ) (parent.getParent() ) ) ;

			if( parent2 == null ) {

				ArrayList<Integer> keys3 = new ArrayList<Integer>() ;

				moveup = keys2.get(0) ;

				keys2.remove(0) ;

				keys3.add(moveup) ;

				ArrayList<LibraryNode> children3 = new ArrayList<LibraryNode>() ;

				LibraryNodePrimaryIndex newPindex3 = new LibraryNodePrimaryIndex( null , keys1 , children1) ;

				LibraryNodePrimaryIndex newPindex4 = new LibraryNodePrimaryIndex( null , keys2 , children2) ;

				children3.add(newPindex3) ; children3.add(newPindex4) ;

				LibraryNodePrimaryIndex newPindex5 = new LibraryNodePrimaryIndex( null , keys3 , children3) ;

				newPindex3.setParent(newPindex5) ;  newPindex4.setParent(newPindex5) ;

				for(j=0 ; j < children1.size() ; j++)
					(children1.get(j)).setParent(newPindex3) ;

				for(j=0 ; j < children2.size() ; j++)
						(children2.get(j)).setParent(newPindex4) ;

				return newPindex5;

			}

			else if(parent2.keyCount() != 2 *LibraryNode.order){

				moveup = keys2.get(0) ;

				keys2.remove(0) ;

				LibraryNodePrimaryIndex newPindex3 = new LibraryNodePrimaryIndex( null , keys1 , children1) ;

				LibraryNodePrimaryIndex newPindex4 = new LibraryNodePrimaryIndex( null , keys2 , children2) ;

				for(j=0 ; j < children1.size() ; j++)
					(children1.get(j)).setParent(newPindex3) ;

				for(j=0 ; j < children2.size() ; j++)
					(children2.get(j)).setParent(newPindex4) ;

				for(j = 0 ; j < parent2.keyCount() ; j++){

					if(moveup > parent2.keyAtIndex(j)) ;

					else break ;
				}

					parent2.children.remove(j) ;

					parent2.keys.add(j , moveup) ;

					parent2.children.add(j , newPindex3) ;

					parent2.children.add(j+1 , newPindex4) ;

					newPindex3.setParent(parent2) ;  newPindex4.setParent(parent2) ;

					return null ;			

			}

			else{

				moveup = keys2.get(0) ;

				keys2.remove(0) ;

				LibraryNodePrimaryIndex newPindex3 = new LibraryNodePrimaryIndex( null , keys1 , children1) ;

				LibraryNodePrimaryIndex newPindex4 = new LibraryNodePrimaryIndex( null , keys2 , children2) ;

				for(j=0 ; j < children1.size() ; j++)
					(children1.get(j)).setParent(newPindex3) ;

				for(j=0 ; j < children2.size() ; j++)
					(children2.get(j)).setParent(newPindex4) ;

				return addPindex2( newPindex3 , newPindex4 , parent2 , moveup) ;
			}


		}
	}

}
