package ceng.ceng351.musicdb;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;

import ceng.ceng351.musicdb.QueryResult.ArtistNameNumberOfSongsResult;
import ceng.ceng351.musicdb.QueryResult.ArtistNameSongNameGenreRatingResult;
import ceng.ceng351.musicdb.QueryResult.TitleReleaseDateRatingResult;
import ceng.ceng351.musicdb.QueryResult.UserIdUserNameNumberOfSongsResult;

public class MUSICDB implements IMUSICDB{
	private static String user = "e2169589"; // TODO: Your userName
    private static String password = "4328b2d0"; //  TODO: Your password
    private static String host = "144.122.71.57"; // host name
    private static String database = "db2169589"; // TODO: Your database name
    private static int port = 8084; // port
    
    private static Connection con = null;

	@Override
	public void initialize() {
		// TODO Auto-generated method stub
		String url = "jdbc:mysql://" + host + ":" + port + "/" + database;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            con =  DriverManager.getConnection(url, user, password);
        } 
        catch (SQLException | ClassNotFoundException e) {
            e.printStackTrace();
        } 
	}

	@Override
	public int createTables() {
		// TODO Auto-generated method stub

        int numberofTablesInserted = 0;

        String queryCreateUserTable = "create table user (" + 
                                                                   "userID int not null," + 
                                                                   "userName varchar(60)," + 
                                                                   "email varchar(30)," +
                                                                   "password varchar(30)," +
                                                                   "primary key (userID))";

        String queryCreateSongTable = "create table song (" + 
                                                                   "songID int not null," + 
                                                                   "songName varchar(60)," + 
                                                                   "genre varchar(30)," +
                                                                   "rating double," +
                                                                   "artistID int," +
                                                                   "albumID int,"+
                                                                   "primary key (songID),"+
                                                                   "foreign key (artistID) references artist(artistID),"+
                                                                   "foreign key (albumID) references album(albumID))";
                                                                   

        String queryCreateArtistTable = "create table artist (" + 
                                                                   "artistID int not null," + 
                                                                   "artistName varchar(60),"+
                                                                   "primary key (artistID))";
                                                                   

        String queryCreateAlbumTable = "create table album (" + 
                                                                   "albumID int not null," + 
                                                                   "title varchar(60)," + 
                                                                   "albumGenre varchar(30)," +
                                                                   "albumRating double," +
                                                                   "releaseDate date," +
                                                                   "artistID int," +
                                                                   "primary key (albumID)," +
                                                                   "foreign key (artistID) references artist(artistID))";
                                                                   

        String queryCreateListenTable = "create table listen (" + 
                                                                   "userID int not null," + 
                                                                   "songID int not null," + 
                                                                   "lastListenTime  timestamp," +
                                                                   "listenCount int," +
                                                                   "primary key (userID,songID),"+
                                                                   "foreign key (userID) references user(userID),"+
                                                                   "foreign key (songID) references song(songID)"+
                                                                   "on delete cascade)"; 
                                                                                                   

        try {
            
            Statement statement = con.createStatement();

            //User Table
            statement.executeUpdate(queryCreateUserTable);
            numberofTablesInserted++;

            //close
            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        try {
            
            Statement statement = con.createStatement();

            //Song Table
            statement.executeUpdate(queryCreateArtistTable);
            numberofTablesInserted++;

            //close
            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        try {
            
            Statement statement = con.createStatement();

            //artist Table
            statement.executeUpdate(queryCreateAlbumTable);
            numberofTablesInserted++;

            //close
            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        try {
            
            Statement statement = con.createStatement();

            //Album Table
            statement.executeUpdate(queryCreateSongTable);
            numberofTablesInserted++;

            //close
            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        try {
            
            Statement statement = con.createStatement();

            //Listen Table
            statement.executeUpdate(queryCreateListenTable);
            numberofTablesInserted++;

            //close
            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return numberofTablesInserted;
	}

	@Override
	public int dropTables() {
		
        int numberofTablesDropped = 0;

        String queryDropUserTable = "drop table if exists user";
        String queryDropSongTable = "drop table if exists song";
        String queryDropArtistTable = "drop table if exists artist";
        String queryDropAlbumTable = "drop table if exists album";
        String queryDropListenTable = "drop table if exists listen";


        try {
            Statement statement = con.createStatement();

            //User
            statement.executeUpdate(queryDropListenTable);
            numberofTablesDropped++;

            //close
            statement.close();

        } catch (SQLException e) {
            e.printStackTrace();
        }

        try {
            Statement statement = con.createStatement();

            //Song
            statement.executeUpdate(queryDropUserTable);
            numberofTablesDropped++;

            //close
            statement.close();

        } catch (SQLException e) {
            e.printStackTrace();
        }

        try {
            Statement statement = con.createStatement();

            //Artist
            statement.executeUpdate(queryDropSongTable);
            numberofTablesDropped++;

            //close
            statement.close();

        } catch (SQLException e) {
            e.printStackTrace();
        }

        try {
            Statement statement = con.createStatement();

            //Album
            statement.executeUpdate(queryDropAlbumTable);
            numberofTablesDropped++;

            //close
            statement.close();

        } catch (SQLException e) {
            e.printStackTrace();
        }

        try {
            Statement statement = con.createStatement();

            //Listen
            statement.executeUpdate(queryDropArtistTable);
            numberofTablesDropped++;

            //close
            statement.close();

        } catch (SQLException e) {
            e.printStackTrace();
        }

        return numberofTablesDropped ;
	}

	@Override
	public int insertAlbum(Album[] albums) {
		// TODO Auto-generated method stub

        int numberofRowsInserted = 0;
        int i = 0;

        while( i<albums.length ) {

            String query = "insert into album values (\"" + 
                            albums[i].getAlbumID()+ "\",\"" + 
                            albums[i].getTitle() + "\",\"" + 
                            albums[i].getAlbumGenre() + "\",\"" + 
                            albums[i].getAlbumRating() + "\",\"" +
                            albums[i].getReleaseDate() + "\",\"" + 
                            albums[i].getArtistID() + "\")";

            try {
                Statement st = con.createStatement();
                st.executeUpdate(query);
                numberofRowsInserted++ ;

                //Close
                st.close();

            } catch (SQLException e) {
                e.printStackTrace(); 
            }

            i++ ;

        }

		return numberofRowsInserted ;
	}

	@Override
	public int insertArtist(Artist[] artists) {
		// TODO Auto-generated method stub

        int numberofRowsInserted = 0;
        int i = 0;

        while( i<artists.length ) {

            String query = "insert into artist values (\"" + 
                            artists[i].getArtistID()+ "\",\"" +  
                            artists[i].getArtistName() + "\")";

            try {
                Statement st = con.createStatement();
                st.executeUpdate(query);
                numberofRowsInserted++ ;

                //Close
                st.close();

            } catch (SQLException e) {
                e.printStackTrace(); 
            }

            i++ ;

        }

        return numberofRowsInserted ;
	}

	@Override
	public int insertSong(Song[] songs) {
		// TODO Auto-generated method stub

        int numberofRowsInserted = 0;
        int i = 0;

        while( i<songs.length ) {

            String query = "insert into song values (\"" + 
                            songs[i].getSongID()+ "\",\"" +
                            songs[i].getSongName()+ "\",\"" +
                            songs[i].getGenre()+ "\",\"" +
                            songs[i].getRating()+ "\",\"" +
                            songs[i].getArtistID()+ "\",\"" +  
                            songs[i].getAlbumID() + "\")";

            try {
                Statement st = con.createStatement();
                st.executeUpdate(query);
                numberofRowsInserted++ ;

                //Close
                st.close();

            } catch (SQLException e) {
                e.printStackTrace(); 
                }
            

            i++ ;

        }

        return numberofRowsInserted ;
	}

	@Override
	public int insertUser(User[] users) {
		// TODO Auto-generated method stub

        int numberofRowsInserted = 0;
        int i = 0;

        while( i<users.length ) {

            String query = "insert into user values (\"" + 
                            users[i].getUserID()+ "\",\"" +
                            users[i].getUserName()+ "\",\"" +
                            users[i].getEmail()+ "\",\"" +  
                            users[i].getPassword() + "\")";

            try {
                Statement st = con.createStatement();
                st.executeUpdate(query);
                numberofRowsInserted++ ;

                //Close
                st.close();

            } catch (SQLException e) {
                e.printStackTrace();   
                }
            

            i++ ;

        }

        return numberofRowsInserted ;
	}

	@Override
	public int insertListen(Listen[] listens) {
		// TODO Auto-generated method stub

        int numberofRowsInserted = 0;
        int i = 0;

        while( i < listens.length ) {

            String query = "insert into listen values (\"" + 
                            listens[i].getUserID()+ "\",\"" +
                            listens[i].getSongID()+ "\",\"" +
                            listens[i].getLastListenTime()+ "\",\"" +  
                            listens[i].getListenCount() + "\")";

            try {
                Statement st = con.createStatement();
                st.executeUpdate(query);
                numberofRowsInserted++ ;

                //Close
                st.close();

            } catch (SQLException e) {
                e.printStackTrace(); 
                }
            

            i++ ;

        }

        return numberofRowsInserted ;
	}

	@Override
	public ArtistNameSongNameGenreRatingResult[] getHighestRatedSongs() {
		// TODO Auto-generated method stub
		
		ArrayList<ArtistNameSongNameGenreRatingResult> rlist = new ArrayList<ArtistNameSongNameGenreRatingResult>(); 
		ArtistNameSongNameGenreRatingResult r[] ;
		ArtistNameSongNameGenreRatingResult r_new ;
		ResultSet rs ;
		
		String query = "select A.artistName,S.songName,S.genre,S.rating "+
				   	   "from song S,artist A "+
				       "where A.artistID = S.artistID and S.rating = (select max(rating) from song ) order by A.artistName ;" ;

		
		try {
            Statement st = con.createStatement();
            rs = st.executeQuery(query);
          
            while( rs.next() ) {
	
	            String r_artistName= rs.getString("artistName");
	            String r_songName = rs.getString("songName");
	            String r_genre = rs.getString("genre");
	            double r_rating = rs.getDouble("rating");
	            
	            r_new = new ArtistNameSongNameGenreRatingResult(r_artistName, r_songName, r_genre, r_rating);
	            
	            rlist.add(r_new) ;
	
            }
	            //Close
	            st.close();
	        } catch (SQLException e) {
	            e.printStackTrace();
	        }
		
		r = new ArtistNameSongNameGenreRatingResult[rlist.size()];
		r = rlist.toArray(r);

        return r;
	}

	@Override
	public TitleReleaseDateRatingResult getMostRecentAlbum(String artistName) {
		// TODO Auto-generated method stub
		
		TitleReleaseDateRatingResult r = null ;
		ResultSet rs ;
		
		String query = "select A.title, A.releaseDate, A.albumrating "+
					   "from album A,artist B "+
					   "where A.artistID = B.artistID and B.artistName =\"" +
					   artistName +
					   "\" and A.releaseDate = (	select max(releaseDate) "+
					   "from album A2,artist B2 "+
					   "where A2.artistID = B2.artistID and B2.artistName =\""+
					   artistName +
					   "\");" ;
        
        try {
            Statement st = con.createStatement();
            rs = st.executeQuery(query);	
           
            rs.next();

            String r_title= rs.getString("title");
            String r_date = rs.getString("releaseDate");
            double r_rating = rs.getDouble("albumRating");
            
            r = new TitleReleaseDateRatingResult(r_title, r_date, r_rating);

            //Close
            st.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return r;

	}

	@Override
	public ArtistNameSongNameGenreRatingResult[] getCommonSongs(String userName1, String userName2) {
		// TODO Auto-generated method stub

		ArrayList<ArtistNameSongNameGenreRatingResult> rlist = new ArrayList<ArtistNameSongNameGenreRatingResult>(); 
		ArtistNameSongNameGenreRatingResult r[] ;
		ArtistNameSongNameGenreRatingResult r_new ;
		ResultSet rs ;

		String query = "select A.artistName , S.songName , S.genre , S.rating " +
					"from artist A, song S " + 
		   	   "where S.artistID = A.artistID and S.songID in " +
				"(select distinct L.songID from listen L "+
		   	   "where L.songID in (select L2.songID from user U2,listen L2 "+
		   	   "where U2.userID = L2.userID and U2.userName = \""+
		   	   userName1 +
		   	   "\") and L.songID in (select L3.songID from user U3,listen L3 "+
		   	   " where U3.userID = L3.userID and U3.userName =\""+
		   	   userName2 +
		   	   "\")) order by S.rating desc ;";
		   	   
		try {
    		Statement st = con.createStatement();
    		rs = st.executeQuery(query);
  
	    	while( rs.next()) {
	    			
		        String r_artistName= rs.getString("artistName");
		        String r_songName = rs.getString("songName");
		        String r_genre = rs.getString("genre");
		        double r_rating = rs.getDouble("rating");
	        
		        r_new = new ArtistNameSongNameGenreRatingResult(r_artistName, r_songName, r_genre, r_rating);
		        rlist.add(r_new) ;
		
	    }
        //Close
        st.close();
		} catch (SQLException e) {
        e.printStackTrace();
		}

		r = new ArtistNameSongNameGenreRatingResult[rlist.size()];
		r = rlist.toArray(r);

		return r;
		
	}

	@Override
	public ArtistNameNumberOfSongsResult[] getNumberOfTimesSongsListenedByUser(String userName) {
		// TODO Auto-generated method stub
		
		ArrayList<ArtistNameNumberOfSongsResult> rlist = new ArrayList<ArtistNameNumberOfSongsResult>(); 
		ArtistNameNumberOfSongsResult r[] ;
		ArtistNameNumberOfSongsResult r_new ;
		ResultSet rs ;
		
		String query = "select A.artistName,sum(L.listenCount) as scount "+
				   	   "from listen L , user U ,song S ,artist A "+
				   	   "where L.userID = U.userID and U.userName = \""+
				   	   userName +
				   	   "\" and S.songID = L.songID and S.artistID = A.artistID "+
				       "group by A.artistID,A.artistName "+
				   	   "order by A.artistName ;" ;

		
		try {
            Statement st = con.createStatement();
            rs = st.executeQuery(query);
          
            while( rs.next() ) {
	
	            String r_artistName= rs.getString("artistName");
	            int r_number = rs.getInt("scount");
	            
	            r_new = new ArtistNameNumberOfSongsResult(r_artistName, r_number);
	            
	            rlist.add(r_new) ;
	
            }
	            //Close
	            st.close();
	        } catch (SQLException e) {
	            e.printStackTrace();
	        }
		
		r = new ArtistNameNumberOfSongsResult[rlist.size()];
		r = rlist.toArray(r);

        return r;

	}

	@Override
	public User[] getUsersWhoListenedAllSongs(String artistName) {
		// TODO Auto-generated method stub
		
		ArrayList<User> rlist = new ArrayList<User>(); 
		User r[] ;
		User r_new ;
		ResultSet rs ;
		
		String query = "select U.userID,U.userName,U.email,U.password "+
			   	   "from user U "+
			   	   "where not exists(select S.songID "+
			   	   "from song S,artist A "+
			   	   "where S.artistID = A.artistID and A.artistName = \"" +
			   	   artistName +
			   	   "\" and "+
			       "not exists(select L.songID "+
			       "from listen L "+
			       "where L.userID = U.userID and L.songID = S.songID)) "+
			   	   "order by U.userID ;" ;

		
		try {
            Statement st = con.createStatement();
            rs = st.executeQuery(query);
          
            while( rs.next() ) {         
	
	            int r_userID= rs.getInt("userID");
	            String r_userName = rs.getString("userName");
	            String r_email = rs.getString("email");
	            String r_password = rs.getString("password");
            	
            	
	            
	            r_new = new User(r_userID, r_userName, r_email, r_password);
	            
	            rlist.add(r_new) ;
	
            }
	            //Close
	            st.close();
	        } catch (SQLException e) {
	            e.printStackTrace();
	        }
		
		r = new User[rlist.size()];
		r = rlist.toArray(r);

        return r;
	}

	@Override
	public UserIdUserNameNumberOfSongsResult[] getUserIDUserNameNumberOfSongsNotListenedByAnyone() {
		// TODO Auto-generated method stub
		
		ArrayList<UserIdUserNameNumberOfSongsResult> rlist = new ArrayList<UserIdUserNameNumberOfSongsResult>(); 
		UserIdUserNameNumberOfSongsResult r[] ;
		UserIdUserNameNumberOfSongsResult r_new ;
		ResultSet rs ;

		
		String query = "select u.userID,u.userName,count(*) as scount "+
				"from user u,listen l3 "+
				"where l3.songID in(select l.songID from listen l "+
				"where l.userID = u.userID and l.songID not in( "+
				"select l2.songID from listen l2 "+
				"where l2.userID != u.userID)) "+
				" group by u.userID,u.userName "+
				" order by u.userID ;" ;

		
		try {
            Statement st = con.createStatement();
            rs = st.executeQuery(query);
          
            while( rs.next() ) {
	
	            int r_userID= rs.getInt("userID");
	            String r_userName = rs.getString("userName");
	            int r_number= rs.getInt("scount");
	            
	            r_new = new UserIdUserNameNumberOfSongsResult( r_userID , r_userName , r_number);
	            
	            rlist.add(r_new) ;
	
            }
	            //Close
	            st.close();
	        } catch (SQLException e) {
	            e.printStackTrace();
	        }
		
		r = new UserIdUserNameNumberOfSongsResult[rlist.size()];
		r = rlist.toArray(r);

        return r;
		
	}

	@Override
	public Artist[] getArtistSingingPopGreaterAverageRating(double rating) {
		// TODO Auto-generated method stub
		
		ArrayList<Artist> rlist = new ArrayList<Artist>(); 
		Artist r[] ;
		Artist r_new ;
		ResultSet rs ;
		
		String query = "select a3.artistID,a3.artistName from artist a3 where a3.artistID in "+
				"(select a.artistID from song s , artist a where a.artistID = s.artistID and s.genre = \"pop\") and "+
				"a3.artistID in( select a2.artistID from artist a2 where "+
				rating +
				" <= (select avg(s2.rating) from song s2 where s2.artistID = a2.artistID group by s2.artistID)) "+
				" order by a3.artistID ;" ;

		
		try {
            Statement st = con.createStatement();
            rs = st.executeQuery(query);
          
            while( rs.next() ) {     
	
	            int r_artID= rs.getInt("artistID");
	            String r_artName = rs.getString("artistName");
	            
	            r_new = new Artist( r_artID , r_artName );
	            
	            rlist.add(r_new) ;
	
            }
	            //Close
	            st.close();
	        } catch (SQLException e) {
	            e.printStackTrace();
	        }
		
		r = new Artist[rlist.size()];
		r = rlist.toArray(r);

        return r;
	}

	@Override
	public Song[] retrieveLowestRatedAndLeastNumberOfListenedSongs() {
		// TODO Auto-generated method stub
		
		ArrayList<Song> rlist = new ArrayList<Song>(); 
		Song r[] ;
		Song r_new ;
		ResultSet rs ;
		
		String query = "select s.songID , s.songName , s.rating , s.genre , s.artistID , s.albumID "+
				"from song s where s.songID in "+
				"(select s2.songID from song s2,listen l2 where s2.genre = \"pop\" and l2.songID = s2.songID and "+
				"s2.rating = (select min(s3.rating) from song s3 where s3.genre = \"pop\") "+
				"group by s2.songID "+
				"having sum(l2.listenCount) <= all (select sum(l2.listenCount) from song s2,listen l2 where s2.genre = \"pop\" and l2.songID = s2.songID and "+
				   	   "s2.rating = (select min(s3.rating) from song s3 where s3.genre = \"pop\") "+
				       "group by s2.songID )) "+
				   	   "order by s.songID ;" ;

		
		try {
            Statement st = con.createStatement();
            rs = st.executeQuery(query);
          
            while( rs.next() ) {
	
	            int r_songID= rs.getInt("songID");
	            String r_songName = rs.getString("songName");
	            double r_rating = rs.getDouble("rating");
	            String r_genre = rs.getString("genre");
	            int r_artID = rs.getInt("artistID") ;
	            int r_albumID = rs.getInt("albumID") ;
	            
	            r_new = new Song(r_songID, r_songName , r_genre , r_rating , r_artID , r_albumID);
	            
	            rlist.add(r_new) ;
	
            }
	            //Close
	            st.close();
	        } catch (SQLException e) {
	            e.printStackTrace();
	        }
		
		r = new Song[rlist.size()];
		r = rlist.toArray(r);

        return r;
	}

	@Override
	public int multiplyRatingOfAlbum(String releaseDate) {
		// TODO Auto-generated method stub
		
		int result = 0 ;
		
		String query = "UPDATE album A "+
					   "SET A.albumRating=A.albumRating*1.5 "+
					   "where A.releaseDate > \"" +
					   releaseDate +
					   "\";" ;
        
        try {
            Statement st = con.createStatement();
            result = st.executeUpdate(query);	

            st.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return result;

	}

	@Override
	public Song deleteSong(String songName) {
		// TODO Auto-generated method stub
		
		Song song = null ;
		ResultSet rs ;
		
		String query = "select * "+
					   "from song S "+
					   "where S.songName = \"" +
					   songName +
					   "\";" ;
        
        try {
            Statement st = con.createStatement();
            rs = st.executeQuery(query);	

            rs.next();

            int s_ID= rs.getInt("songID");
            String s_name = rs.getString("songName");
            String s_genre = rs.getString("genre") ;
            Double s_rating = rs.getDouble("rating");
            int s_artistID = rs.getInt("artistID");
            int s_albumID = rs.getInt("albumID");
            
            
            
            song = new Song(s_ID, s_name, s_genre, s_rating, s_artistID, s_albumID);

            //Close
            st.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        
        query = "delete from song "+
				   "where songName = \"" +
				   songName +
				   "\";" ;
        
        try {
            Statement st = con.createStatement();
            st.executeUpdate(query);	

            //Close
            st.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        
        return song;
		
	}

}


