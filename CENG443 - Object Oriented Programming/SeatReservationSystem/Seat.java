import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.ReentrantLock;

/**
 * Seat class of the seat reservation system.
 * lock is used to ensure only one user thread is executing inside of the critical sedtions.
 * isAvaliable field declares if this seat reserved or not.
 * temporarilyReversed field declares that if there is a user controlled this seat before.
 * reservedUser field is used to store name of the user who reserved this seat.
 */

public class Seat {

    ReentrantLock lock = new ReentrantLock();
    private  boolean isAvailable;
    private boolean temporarilyReserved;
    private  String reservedUser;

    /**
     * default constructor method of the seat(no need to supply constructor since other fields are not known at the time of seat object creation)
     */

    public Seat() {
        this.isAvailable = true;
        this.temporarilyReserved = false;
    }

    /**
     * main method uses this method
     * @return : isAvailable
     */

    public boolean getAvailability(){
        return  isAvailable;
    }

    /**
     * main method uses this method
     * @return : reservedUser
     */

    public String getReservedUser(){
        return reservedUser;
    }

    /**
     * Critical method which provides concurrency of the application.
     * If seat is not available, then user sees that no need to try again.
     * If user sees that this seat is available now, looks whether it is checked by other users.
     * If this seat is temporarily unavailable, user sees that he/she can try again, however can't do anything currently.
     * If this seat temporarily available as well, user locks this seat temporarily.
     * The user than checks other requested seats by himself/herself.
     * If all requested seats are available, than user completely reserves this seat.
     * If other requested seats are not available, this user cancels the temporary reservation.
     * @param userName
     * @return
     * @throws InterruptedException
     */

    public seatState reserveSeatTemporarily(String userName) throws InterruptedException {

        if(lock.tryLock(50, TimeUnit.MILLISECONDS)) {
            try {
                if (this.isAvailable) {
                    if (!this.temporarilyReserved) {
                        this.temporarilyReserved = true;
                        this.reservedUser = userName;
                        return seatState.Available;
                    } else {
                        return seatState.TemporarilyReserved;
                    }
                }
                else {
                    return seatState.PerminantlyReserved;
                }
            }
            finally {
                lock.unlock();
            }
        }
        else{
            return seatState.TemporarilyReserved;
        }
    }

    /**
     * This method is used when user is decided to comletely reserve this seat.
     * @param userName
     */
    public void reserveSeat(String userName){
        lock.lock();
        if(userName.equals(reservedUser)){
            this.isAvailable = false;
        }
        lock.unlock();
    }

    /**
     * When all of the requested seats are not available and current user is decided to remove temporary reservation.
     * @param userName
     */
    public void undoReservation(String userName){
        lock.lock();
        if(userName.equals(this.reservedUser) ) {
            this.temporarilyReserved = false;
            this.reservedUser = "";
        }
        lock.unlock();
    }
}
