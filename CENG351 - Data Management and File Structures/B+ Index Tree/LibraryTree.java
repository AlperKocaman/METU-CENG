import java.util.ArrayList;
public class LibraryTree {

	public LibraryNode primaryRoot;		//root of the primary B+ tree
	public LibraryNode secondaryRoot;	//root of the secondary B+ tree
	public LibraryTree(Integer order)
	{
		LibraryNode.order = order;
		primaryRoot = new LibraryNodeLeaf(null);
		primaryRoot.level = 0;
		secondaryRoot = new LibraryNodeLeaf(null);
		secondaryRoot.level = 0;
	}

	public void addBook(CengBook book) {

		// add methods to fill both primary and secondary tree

		int i = 0 , j = 0 ;

		if(primaryRoot.getType() == LibraryNodeType.Leaf) {

			if(((LibraryNodeLeaf)primaryRoot).bookCount() < 2*LibraryNode.order){

				do {

					if(((LibraryNodeLeaf)primaryRoot).bookKeyAtIndex(i) == -1){

						( (LibraryNodeLeaf)primaryRoot).addBook(i , book) ;

						i = 0 ;

						break ;
					}

					if( (book.key()) > ( (LibraryNodeLeaf)primaryRoot).bookKeyAtIndex(i) ) {

						i++ ;

						continue ;

					}

					( (LibraryNodeLeaf)primaryRoot).addBook(i , book) ;

					i = 0 ;

					break ;

				} while ( i != 2*LibraryNode.order ) ;

			}

			else{

				do{

					if( (book.key()) > ( (LibraryNodeLeaf)primaryRoot).bookKeyAtIndex(i) ) i++ ;

					else break ;

				} while( i != 2*LibraryNode.order ) ;

				ArrayList<LibraryNode> _children = new ArrayList<LibraryNode>() ;

				ArrayList<Integer> _keys = new ArrayList<Integer>() ;

				LibraryNodePrimaryIndex primary_root ;

				primary_root = new LibraryNodePrimaryIndex( null , _keys , _children ) ;

				ArrayList<CengBook> list1 = new ArrayList<CengBook>();

				ArrayList<CengBook> list2 = new ArrayList<CengBook>();

				if(i < LibraryNode.order ) {

					for(j=0 ; j < LibraryNode.order -1 ; j++ ) {

						list1.add(((LibraryNodeLeaf)primaryRoot).bookAtIndex(j)) ;
					}

					list1.add( i , book) ;

					for( ; j != 2*LibraryNode.order ; j++){

						list2.add(((LibraryNodeLeaf)primaryRoot).bookAtIndex(j)) ;
					}

				}

				else {

					for(j=0 ; j < LibraryNode.order  ; j++ ) {

						list1.add(((LibraryNodeLeaf)primaryRoot).bookAtIndex(j)) ;
					}

					for( ; j != 2*LibraryNode.order ; j++){

						list2.add(((LibraryNodeLeaf)primaryRoot).bookAtIndex(j)) ;
					}

					list2.add( i-LibraryNode.order , book) ;

				}

				LibraryNodeLeaf newLeaf1 ; LibraryNodeLeaf newLeaf2 ;

				newLeaf1 = new LibraryNodeLeaf(primary_root , list1 ) ;

				newLeaf2 = new LibraryNodeLeaf(primary_root , list2 ) ;

				_children.add(newLeaf1) ; _children.add(newLeaf2) ;

				_keys.add(list2.get(0).key()) ;

				primary_root = new LibraryNodePrimaryIndex( null , _keys , _children ) ;

				primaryRoot = primary_root ;

			}

		}

		else{

			LibraryNode traverse ;

			traverse = primaryRoot ;

			i = 0 ; j = 0 ;

			while(traverse.getType() != LibraryNodeType.Leaf){

				do {

					if( ((LibraryNodePrimaryIndex)traverse).keyAtIndex(i) == -1 ){

						traverse = ((LibraryNodePrimaryIndex)traverse).getChildrenAt(i) ;

						i = 0 ;

						break ;
					}

					else if(book.key() > ((LibraryNodePrimaryIndex)traverse).keyAtIndex(i)) {

						i++ ;

						continue ;
					}

					traverse = ((LibraryNodePrimaryIndex)traverse).getChildrenAt(i) ;

					i = 0 ;

					break ;

				} while ( i <= ((LibraryNodePrimaryIndex)traverse).keyCount() );

			}

			if(((LibraryNodeLeaf)traverse).bookCount() < 2*LibraryNode.order){

				do {

					if(((LibraryNodeLeaf)traverse).bookKeyAtIndex(i) == -1){

						( (LibraryNodeLeaf)traverse).addBook(i , book) ;

						i = 0 ;

						break ;
					}

					if( (book.key()) > ( (LibraryNodeLeaf)traverse).bookKeyAtIndex(i) ) {

						i++ ;

						continue ;

					}

					( (LibraryNodeLeaf)traverse).addBook(i , book) ;

					i = 0 ;

					break ;

				} while ( i != 2*LibraryNode.order ) ;

			}

			else{

					LibraryNode parent = traverse.getParent() ;

					do{

						if( (book.key()) > ( (LibraryNodeLeaf)traverse).bookKeyAtIndex(i) ) i++ ;

						else break ;

					} while( i != 2*LibraryNode.order ) ;

					ArrayList<CengBook> list1 = new ArrayList<CengBook>();

					ArrayList<CengBook> list2 = new ArrayList<CengBook>();

					if(i < LibraryNode.order ) {

						for(j=0 ; j < LibraryNode.order -1 ; j++ ) {

							list1.add(((LibraryNodeLeaf)traverse).bookAtIndex(j)) ;
						}

						list1.add( i , book) ;

						for( ; j != 2*LibraryNode.order ; j++){

							list2.add(((LibraryNodeLeaf)traverse).bookAtIndex(j)) ;
						}

					}

					else {

						for(j=0 ; j < LibraryNode.order  ; j++ ) {

							list1.add(((LibraryNodeLeaf)traverse).bookAtIndex(j)) ;
						}

						for( ; j != 2*LibraryNode.order ; j++){

							list2.add(((LibraryNodeLeaf)traverse).bookAtIndex(j)) ;
						}

						list2.add( i-LibraryNode.order , book) ;

					}

					LibraryNodeLeaf newLeaf1 = new LibraryNodeLeaf(null , list1) ;

					LibraryNodeLeaf newLeaf2 = new LibraryNodeLeaf(null , list2) ;



					if(((LibraryNodePrimaryIndex)parent).keyCount() != 2*LibraryNode.order ){

						newLeaf1.setParent(parent) ; newLeaf2.setParent(parent) ;

						((LibraryNodePrimaryIndex)parent).addLeaf(newLeaf1,newLeaf2,list2.get(0).key()) ;

					}

					else{

						LibraryNode temp = new LibraryNode(null) ;

						temp = ((LibraryNodePrimaryIndex)parent).addPindex( newLeaf1 , newLeaf2 , parent) ;

						if( temp != null)
							primaryRoot = temp ;
					}
			}
		}



	i = 0 ; j = 0 ;

	if(secondaryRoot.getType() == LibraryNodeType.Leaf) {

		if(((LibraryNodeLeaf)secondaryRoot).bookCount() < 2*LibraryNode.order){

			do {		

				if(((LibraryNodeLeaf)secondaryRoot).bookYearAtIndex(i) == null){

					( (LibraryNodeLeaf)secondaryRoot).addBook(i , book) ;

					i = 0 ;

					break ;
				}

				int bookyear = book.year() ; int indexyear = ((LibraryNodeLeaf)secondaryRoot).bookYearAtIndex(i) ;

				if( book.year() > ( (LibraryNodeLeaf)secondaryRoot).bookYearAtIndex(i) ) {

					i++ ;

					continue ;

				}

				//else if( book.year() == ((LibraryNodeLeaf)secondaryRoot).bookYearAtIndex(i) ){

				if( indexyear == bookyear ){

					if(book.key() > ((LibraryNodeLeaf)secondaryRoot).bookKeyAtIndex(i) ) {

						i++ ; continue ; }

				}

				( (LibraryNodeLeaf)secondaryRoot).addBook(i , book) ;

				i = 0 ;

				break ;

			} while ( i != 2*LibraryNode.order ) ;

		}

		else{

			do{
				if( ((LibraryNodeLeaf)secondaryRoot).bookYearAtIndex(i) == null) break ;

				int bookyear = book.year() ; int indexyear = ((LibraryNodeLeaf)secondaryRoot).bookYearAtIndex(i) ;

				if( (book.year()) > ( (LibraryNodeLeaf)secondaryRoot).bookYearAtIndex(i) ) {i++ ; continue ;}

				if( bookyear == indexyear) {

					if(book.key() > ( (LibraryNodeLeaf)secondaryRoot).bookKeyAtIndex(i) ) 

						{i++ ; continue ;}

					else break ;

				}

				break ;

			} while( i != 2*LibraryNode.order ) ;

			ArrayList<LibraryNode> _children = new ArrayList<LibraryNode>() ;

			ArrayList<Integer> _keys = new ArrayList<Integer>() ;

			ArrayList<Integer> _years = new ArrayList<Integer>() ;

			LibraryNodeSecondaryIndex secondary_root ;

			secondary_root = new LibraryNodeSecondaryIndex( null , _years ,_keys , _children ) ;

			ArrayList<CengBook> list1 = new ArrayList<CengBook>();

			ArrayList<CengBook> list2 = new ArrayList<CengBook>();

			if(i < LibraryNode.order ) {

				for(j=0 ; j < LibraryNode.order -1 ; j++ ) {

					list1.add(((LibraryNodeLeaf)secondaryRoot).bookAtIndex(j)) ;
				}

				list1.add( i , book) ;

				for( ; j != 2*LibraryNode.order ; j++){

					list2.add(((LibraryNodeLeaf)secondaryRoot).bookAtIndex(j)) ;
				}

			}

			else {

				for(j=0 ; j < LibraryNode.order  ; j++ ) {

					list1.add(((LibraryNodeLeaf)secondaryRoot).bookAtIndex(j)) ;
				}

				for( ; j != 2*LibraryNode.order ; j++){

					list2.add(((LibraryNodeLeaf)secondaryRoot).bookAtIndex(j)) ;
				}

				list2.add( i-LibraryNode.order , book) ;

			}

			LibraryNodeLeaf newLeaf1 ; LibraryNodeLeaf newLeaf2 ;

			newLeaf1 = new LibraryNodeLeaf(secondary_root , list1 ) ;

			newLeaf2 = new LibraryNodeLeaf(secondary_root , list2 ) ;

			_children.add(newLeaf1) ; _children.add(newLeaf2) ;

			_keys.add(list2.get(0).key()) ;

			_years.add(list2.get(0).year()) ;

			secondary_root = new LibraryNodeSecondaryIndex( null , _years , _keys , _children ) ;

			secondaryRoot = secondary_root ;

		}

	}

	else{

		LibraryNode traverse ;

		traverse = secondaryRoot ;

		i = 0 ; j = 0 ;

		while(traverse.getType() != LibraryNodeType.Leaf){

			do {

				if( ((LibraryNodeSecondaryIndex)traverse).yearAtIndex(i) == -1 ){

					traverse = ((LibraryNodeSecondaryIndex)traverse).getChildrenAt(i) ;

					i = 0 ;

					break ;
				}

				else if(book.year() > ((LibraryNodeSecondaryIndex)traverse).yearAtIndex(i)) {

					i++ ;

					continue ;
				}

				int bookyear = book.year() ; int indexyear = ((LibraryNodeSecondaryIndex)traverse).yearAtIndex(i) ;

				if( indexyear == bookyear ){

					if(book.key() > ((LibraryNodeSecondaryIndex)traverse).keyAtIndex(i) ) {

					i++ ; continue ; }

				}

				traverse = ((LibraryNodeSecondaryIndex)traverse).getChildrenAt(i) ;

				i = 0 ;

				break ;

			} while ( i <= ((LibraryNodeSecondaryIndex)traverse).keyCount() );

		}

		if(((LibraryNodeLeaf)traverse).bookCount() < 2*LibraryNode.order){

			do {

				if(((LibraryNodeLeaf)traverse).bookYearAtIndex(i) == null){

					( (LibraryNodeLeaf)traverse).addBook(i , book) ;

					i = 0 ;

					break ;
				}

				if( (book.year()) > ( (LibraryNodeLeaf)traverse).bookYearAtIndex(i) ) {

					i++ ;

					continue ;

				}

				int bookyear = book.year() ; int indexyear = ((LibraryNodeLeaf)traverse).bookYearAtIndex(i) ;

				if( indexyear == bookyear ){

					if(book.key() > ((LibraryNodeLeaf)traverse).bookKeyAtIndex(i) ) {

						i++ ; continue ; }

				}

				( (LibraryNodeLeaf)traverse).addBook(i , book) ;

				i = 0 ;

				break ;

			} while ( i != 2*LibraryNode.order ) ;

		} 

		else{

				LibraryNode parent = traverse.getParent() ;

				do{

					if( (book.year()) > (int)((LibraryNodeLeaf)traverse).bookYearAtIndex(i) ) {i++ ; continue ;}

					int bookyear = book.year() ; int indexyear = ((LibraryNodeLeaf)traverse).bookYearAtIndex(i) ;

					if( indexyear == bookyear ){

						if(book.key() > ((LibraryNodeLeaf)traverse).bookKeyAtIndex(i) ) {

						i++ ; continue ; }

				}

					break ;

				} while( i != 2*LibraryNode.order ) ;

				ArrayList<CengBook> list1 = new ArrayList<CengBook>();

				ArrayList<CengBook> list2 = new ArrayList<CengBook>();

				if(i < LibraryNode.order ) {

					for(j=0 ; j < LibraryNode.order -1 ; j++ ) {

						list1.add(((LibraryNodeLeaf)traverse).bookAtIndex(j)) ;
					}

					list1.add( i , book) ;

					for( ; j != 2*LibraryNode.order ; j++){

						list2.add(((LibraryNodeLeaf)traverse).bookAtIndex(j)) ;
					}

				}

				else {

					for(j=0 ; j < LibraryNode.order  ; j++ ) {

						list1.add(((LibraryNodeLeaf)traverse).bookAtIndex(j)) ;
					}

					for( ; j != 2*LibraryNode.order ; j++){

						list2.add(((LibraryNodeLeaf)traverse).bookAtIndex(j)) ;
					}

					list2.add( i-LibraryNode.order , book) ;

				}

				LibraryNodeLeaf newLeaf1 = new LibraryNodeLeaf(null , list1) ;

				LibraryNodeLeaf newLeaf2 = new LibraryNodeLeaf(null , list2) ;

				if(((LibraryNodeSecondaryIndex)parent).keyCount() != 2*LibraryNode.order ){

					newLeaf1.setParent(parent) ; newLeaf2.setParent(parent) ;

					((LibraryNodeSecondaryIndex)parent).addLeaf(newLeaf1,newLeaf2,list2.get(0).year() , list2.get(0).key()) ;

				}

				else{

					LibraryNode temp = new LibraryNode(null) ;

					temp = ((LibraryNodeSecondaryIndex)parent).addPindex( newLeaf1 , newLeaf2 , parent) ;

					if( temp != null)
						secondaryRoot = temp ;
				}
		}

		
	}

	return  ;
	}

	public CengBook searchBook(Integer key) {

		// add methods to find the book with the searched key in primary B+ tree
		// return value will not be tested, just print as the specicifications say

		LibraryNode traverse ;

		traverse = primaryRoot ;

		int i = 0 , j = 0 ;

		while(traverse.getType() != LibraryNodeType.Leaf){

			System.out.println("<index>") ;

			for(j=0 ; j < ((LibraryNodePrimaryIndex)traverse).keyCount(); j++)
				System.out.println(((LibraryNodePrimaryIndex)traverse).keyAtIndex(j)) ;							

			do {

				if( ((LibraryNodePrimaryIndex)traverse).keyAtIndex(i) == -1 ){

					traverse = ((LibraryNodePrimaryIndex)traverse).getChildrenAt(i) ;

					i = 0 ;

					break ;
				}

				else if(key >= ((LibraryNodePrimaryIndex)traverse).keyAtIndex(i)) {

					i++ ;

					continue ;
				}

				traverse = ((LibraryNodePrimaryIndex)traverse).getChildrenAt(i) ;

				i = 0 ;

				break ;

			} while ( i <= ((LibraryNodePrimaryIndex)traverse).keyCount() );

			System.out.println("</index>") ;
		}

		for( j = 0 ; j < ((LibraryNodeLeaf)traverse).bookCount() ; j++ ) {

			 if( ((LibraryNodeLeaf)traverse).bookKeyAtIndex(j) == key ) {

			 	CengBook tempBook = ((LibraryNodeLeaf)traverse).bookAtIndex(j) ;
	
				String name = tempBook.name();
				String author = tempBook.author();
				Integer year = tempBook.year();

			 	System.out.println("<data>") ;

			 	System.out.println("<record>" +key+"|"+year+"|"+name+"|"+author +"</record>" ) ;

			 	System.out.println("</data>" ) ;

			 	return null ;
			 }
		}

		System.out.println("No match for "+ key) ;

		return null;
		}


	public void printPrimaryLibrary() {

		// add methods to print the primary B+ tree in Depth-first order

		printHelper(primaryRoot) ;

	}

	public void printSecondaryLibrary() {

		// add methods to print the secondary B+ tree in Depth-first order

		printHelper2(secondaryRoot) ;

	}

	// Extra functions if needed

	private void printHelper(LibraryNode traverse) {

		int i = 0 , j = 0 ;

		if(traverse.getType() == LibraryNodeType.Leaf) {

			System.out.println("<data>") ;

			for( j = 0 ; j < ((LibraryNodeLeaf)traverse).bookCount() ; j++ ) {

				CengBook tempBook = ((LibraryNodeLeaf)traverse).bookAtIndex(j) ;
		
				Integer key = tempBook.key() ;
				String name = tempBook.name();
				String author = tempBook.author();
				Integer year = tempBook.year();

			 	System.out.println("<record>" +key+"|"+year+"|"+name+"|"+author +"</record>" ) ;

			}

			System.out.println("</data>" ) ;

			return ;

		}

		System.out.println("<index>") ;

		for(j=0 ; j < ((LibraryNodePrimaryIndex)traverse).keyCount(); j++)
			System.out.println(((LibraryNodePrimaryIndex)traverse).keyAtIndex(j)) ;	

		System.out.println("</index>") ;

		while(i <= ((LibraryNodePrimaryIndex)traverse).keyCount() ) {
			
			printHelper( ((LibraryNodePrimaryIndex)traverse).getChildrenAt(i) );
			
			i++ ;
		}

	}

	private void printHelper2(LibraryNode traverse) {

		int i = 0 , j = 0 ;

		if(traverse.getType() == LibraryNodeType.Leaf) {

			System.out.println("<data>") ;

			for( j = 0 ; j < ((LibraryNodeLeaf)traverse).bookCount() ; j++ ) {

				CengBook tempBook = ((LibraryNodeLeaf)traverse).bookAtIndex(j) ;
		
				Integer key = tempBook.key() ;
				String name = tempBook.name();
				String author = tempBook.author();
				Integer year = tempBook.year();

			 	System.out.println("<record>" +key+"|"+year+"|"+name+"|"+author +"</record>" ) ;

			}

			System.out.println("</data>" ) ;

			return ;

		}

		System.out.println("<index>") ;

		for(j=0 ; j < ((LibraryNodeSecondaryIndex)traverse).keyCount(); j++){
			
			System.out.println(((LibraryNodeSecondaryIndex)traverse).yearAtIndex(j)+"|"+((LibraryNodeSecondaryIndex)traverse).keyAtIndex(j)) ;
	
		}

		System.out.println("</index>") ;

		while(i <= ((LibraryNodeSecondaryIndex)traverse).keyCount() ) {
			
			printHelper2( ((LibraryNodeSecondaryIndex)traverse).getChildrenAt(i) );
			
			i++ ;
		}

	}

}
