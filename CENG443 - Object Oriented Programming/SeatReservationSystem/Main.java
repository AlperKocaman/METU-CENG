import java.util.ArrayList;                     // for arraylist usage
import java.util.Scanner;                       // for input taking from StdIn
import java.util.concurrent.ExecutorService;    // for thread pool and shutdown method
import java.util.concurrent.Executors;          // for execute() method which accepts an object of the Runnable interface

/**
 * This is the main class of the  seat reservation system with multiple users acting at the same time(multithreaded).
 * @author AlperKOCAMAN
 */

public class Main {

    /**
     * "main" method which starts execution.
     * This method takes input given by user which defines seat grid, number of users and requested seats by each user.
     * User threads are created within this method as well.
     * Lastly, it waits all created threads and prints the state of the seats to StdOut.
     * @param args
     */

    public static void main(String[] args){

        int i, j;
        Scanner scanner = new Scanner(System.in);

        int rows = scanner.nextInt(); // takes number n into rows
        int cols = scanner.nextInt(); // takes number m into cols

        ArrayList<ArrayList<Seat>> grid = new ArrayList<>(); // at the end, all seats are stored in this 2D arraylist

        for(i=0 ; i < rows ; ++i){
            ArrayList<Seat> seatsRow = new ArrayList<>(); // for storing one row of the seat grid

            for(j=0 ; j < cols ; ++j){
                Seat seat = new Seat(); // creating new empty seat with default constructor
                seatsRow.add(seat);     // add this seat to the row arraylist
            }
            grid.add(seatsRow);         // add row arraylist to the grid
        }

        int userNumber = scanner.nextInt(); // takes number of users
        scanner.nextLine(); // skips the \n character

        ArrayList<Runnable> usersList = new ArrayList<>(); // all user thread will be kept here

        for (i=0 ; i<userNumber ; ++i){
            String impLine = scanner.nextLine();                    //take the input line
            String[] userInfo = impLine.split(" ", 2);   // split input line into two part, first keeps name and second keeps requested seats
            String[] userSeats = userInfo[1].split(" ");      // split the requested seats part into all seats
            ArrayList<Seat> requestedSeatList = new ArrayList<>();  // user will check the seats via this ArrayList<Seat>

            for(j=0 ; j<userSeats.length ; ++j){
                int rowValue = (int)(userSeats[j].charAt(0)) - ((int)'A');          // in order to get row value
                int colValue = Character.getNumericValue(userSeats[j].charAt(1));   // in order to get column value
                requestedSeatList.add(grid.get(rowValue).get(colValue));            // add the seat in the grid to the user's requested seat list
            }
            Runnable user = new User(userInfo[0], requestedSeatList, userInfo[1]);  // creates user threads by using user class which implements Runnable inteface
            usersList.add(user);
        }

        ExecutorService executorService = Executors.newFixedThreadPool(userNumber); // thread are kept in the executorService
                                                                                    // this thread pool will have threads at most number of users
        Logger.InitLogger(); // starts the Logger for timing issues

        for (Runnable currentUser: usersList) {
            executorService.execute(currentUser); // starts execution of the user threads
        }

        executorService.shutdown(); // executor should be shutted down since new request should not come to it.

        while (!executorService.isTerminated()); // wait for other threads in order to finish their jobs correctly
                                                 // this code shares the same logic with Thread.join() method
                                                 // awaitTermination method exists for executor services as well

        /* For printing the status of the seats in the seat grid*/
        for(i=0 ; i<rows ; ++i){

            for(j=0; j<cols ; ++j){

                Seat tempSeat = grid.get(i).get(j);
                char isTaken;
                if(!tempSeat.getAvailability()){
                    isTaken = 'T';
                    System.out.print("T:" + tempSeat.getReservedUser() + " ");
                }
                else{
                    isTaken = 'E';
                    System.out.print("E:" + "      ");
                }
            }
            System.out.print("\n");
        }
    }
}
