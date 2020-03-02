import java.util.ArrayList; // for arraylist usage

/**
 * This is the user class of the seat reservation system.
 * userName is used for storing the name of the user.
 * requestedSeatList is used for storing all seats that this user wants.
 * requestedSeatString is used for Logger class methods
 * shouldRetry is used for whether this user can try again to reserve seats or not
 */

public class User implements Runnable {

    private final String userName;
    private final ArrayList<Seat> requestedSeatList;
    private final String requestedSeatString;
    private boolean shouldRetry = true;

    /**
     * Constructor method of the user class
     * @param userName
     * @param requestedSeatList
     * @param requestedSeatString
     */

    public User(String userName, ArrayList<Seat> requestedSeatList, String requestedSeatString) {
        this.userName = userName;
        this.requestedSeatList = requestedSeatList;
        this.requestedSeatString = requestedSeatString;
    }

    /**
     * This is the method that user threads execute on it.
     * Firstly, for every requested seat, user checks whether it is available or not via reserveSeatTemporarily method.
     * If this method returns that user can reserve this requested seat tempporarily, user continues to check other requested seats.
     * If all seats are checked and all of them are available, then canReserve flag will be true and user will reserve seats unless database error occurs.
     * If one of the seats are not available, then user remove the temporary reservation on previous seats.
     * If one of the seats are reserved completely,than user sees that he/she can't reserve his/her requests and will not try again later.(both shouldRetry and canReserve will become false)
     * If one of the seats are reserved temporarily, just canReserve flag will become false but user will try again later.
     */

    @Override
    public void run() {

        while (shouldRetry) {
            int i;
            boolean canReserve = false;
            for (i=0 ; i<requestedSeatList.size() ; ++i) {
                seatState canReserveSeat = null;
                try {
                    canReserveSeat = requestedSeatList.get(i).reserveSeatTemporarily(this.userName);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                if(canReserveSeat != seatState.Available) {

                    for(i=i-1 ; i>=0 ; --i) {
                        requestedSeatList.get(i).undoReservation(this.userName);
                    }
                    if(canReserveSeat == seatState.PerminantlyReserved) {
                        Logger.LogFailedReservation(this.userName, this.requestedSeatString, System.nanoTime(),
                                "Failed due to unavailable seats");
                        shouldRetry = false;
                        canReserve = false;
                        break;
                    }
                    else {
                        canReserve = false;
                        Thread.yield();
                        break;
                    }
                }
                canReserve = true;
            }

            if(canReserve) {
                if (Math.random() >= 0.1) {

                    for (i=0 ; i<requestedSeatList.size() ; ++i) {
                        requestedSeatList.get(i).reserveSeat(this.userName);
                    }
                    try {
                        Thread.sleep(50);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }

                    shouldRetry = false;
                    Logger.LogSuccessfulReservation(this.userName, this.requestedSeatString, System.nanoTime(), "Succesfully reserved");
                }
                else {
                    for(i=0 ; i<requestedSeatList.size() ; ++i) {
                        requestedSeatList.get(i).undoReservation(this.userName);
                    }
                    Logger.LogDatabaseFailiure(this.userName, this.requestedSeatString, System.nanoTime(), "Database error");
                    try {
                        Thread.sleep(100);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        }
    }
}
