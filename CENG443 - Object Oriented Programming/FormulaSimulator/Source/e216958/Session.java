import java.util.ArrayList;

public class Session {

    private Track track;
    private ArrayList<Team> teamList;
    private int totalLaps;

    private ArrayList<Double> timeTable = new ArrayList<>();
    private ArrayList<Car> carTable = new ArrayList<>();
    private Team winningTeam;

    //TODO : setter/getter for these added private fields were not added here since there is no need for accessing or setting these fields from outside of this class!

    public Session() {
        this.track = null;
        this.teamList = null;
        this.totalLaps = 0;
    }

    public Session(Track track, ArrayList<Team> teamList, int totalLaps) {
        this.track = track;
        this.teamList = teamList;
        this.totalLaps = totalLaps;
    }

    public Track getTrack() {
        return track;
    }

    public void setTrack(Track track) {
        this.track = track;
    }

    public ArrayList<Team> getTeamList() {
        return teamList;
    }

    public void setTeamList(ArrayList<Team> teamList) {
        this.teamList = teamList;
    }

    public int getTotalLaps() {
        return totalLaps;
    }

    public void setTotalLaps(int totalLaps) {
        this.totalLaps = totalLaps;
    }

    public void simulate() {
        /* This method simulates the race until it’s over. This method should check
        the validity of the track before starting the simulation and if the track is not valid it should return
        without simulating the race.*/

        if(!this.track.isValidTrack()){
            System.out.println("Track is invalid.Simulation aborted!");
            return;
        }

        System.out.println("Track is valid.Starting simulation on " + this.track.getTrackName() +" for " + this.getTotalLaps() + " laps.");

        int i,j,k;
        int totalTrackFeatureNum = this.track.getFeatureList().size()*this.totalLaps;
        for (i = 0; i<totalTrackFeatureNum ; ++i){

            TrackFeature feature = this.track.getNextFeature();

            for(j = 0; j< this.getTeamList().size() ; ++j){

                Team currentTeam = this.getTeamList().get(j);

                for(k = 0; k<currentTeam.getCarList().size(); k++){

                    currentTeam.getCarList().get(k).tick(feature);
                }
            }
        }

        for(Team team: this.getTeamList()){

            for(Car car: team.getCarList()){

                double currentCarTime = car.getTotalTime();

                for(i = 0; i<this.timeTable.size() ; ++i){

                    if(currentCarTime < timeTable.get(i)){
                        break;
                    }
                }

                timeTable.add(i,currentCarTime);
                carTable.add(i,car);

                if(i == 0){
                    winningTeam = team;
                }
            }
        }

        this.printWinnerTeam();
        this.printTimingTable();
    }

    public String printWinnerTeam() {
        /* In the pdf, this function is stated as public "void" printWinnerTeam() and this is the logical one, I took in this way*/
        /* Team Williams wins.Red, Blue and White flags are waving everywhere.*/
        System.out.print("Team " + this.winningTeam.getName() + " wins.");
        String[] colors = this.winningTeam.getTeamColors();
        int colorLength = colors.length;
        for (int i=0; i < colorLength ; ++i) {
            if(colorLength - i == 1)
                System.out.print(colors[i]);
            else if(colorLength - i == 2)
                System.out.print(colors[i] + " and ");
            else
                System.out.print(colors[i] + ", ");
        }
        System.out.print(" flags are waving everywhere.\n");
        /* everything printed here, no need to return something*/
        return null;
    }

    private String printTimingTable() {
        /* In the pdf, this function is stated as public "void" printTimingTable() and this is the logical one, I took in this way*/
        for (Car car: this.carTable){

            Double time = car.getTotalTime();
            int hour = (int) (time/3600);
            time -= hour*3600;
            int minute = (int) (time/60);
            time -= minute*60;
            double sec = time;

            String h = (hour<10?"0":"") + hour;
            String m = (minute<10?"0":"") + minute;
            String s = (sec<10?"0":"") + sec;
            s = s.substring(0,6);

            System.out.println(car.getDriverName()+"("+ car.getCarNo()+"):  "+
                    h+":"+m+":"+s);
        }
        /* everything printed here, no need to return something*/
        return null;
    }
}
