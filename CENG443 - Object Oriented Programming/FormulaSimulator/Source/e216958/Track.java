import java.util.ArrayList;

public class Track {

    private String trackName;
    private ArrayList<TrackFeature> featureList;
    private boolean isClockwise;
    // addded featureIndex to keep the last element returned from featureList
    private int featureIndex;

    public Track() {
        this.trackName = null;
        this.featureList = null;
        this.isClockwise = false;
        this.featureIndex = 0;
    }

    public Track(String trackName, ArrayList<TrackFeature> featureList, boolean isClockwise) {
        this.trackName = trackName;
        this.featureList = featureList;
        this.isClockwise = isClockwise;
        this.featureIndex = 0;
    }

    public String getTrackName() {
        return trackName;
    }

    public void setTrackName(String trackName) {
        this.trackName = trackName;
    }

    public ArrayList<TrackFeature> getFeatureList() {
        return featureList;
    }

    public void setFeatureList(ArrayList<TrackFeature> featureList) {
        this.featureList = featureList;
    }

    public boolean isClockwise() {
        return isClockwise;
    }

    public void setClockwise(boolean clockwise) {
        isClockwise = clockwise;
    }

    public int getTrackLength() {
        int trackLength = 0;
        for(TrackFeature feature : featureList){
            trackLength += feature.getDistance();
        }

        return trackLength;
    }

    public TrackFeature getNextFeature() {
        if(featureIndex == featureList.size()){
            featureIndex = 0;
        }
        return featureList.get(featureIndex++);
    }

    public void addFeature(TrackFeature feature) {
        featureList.add(feature);
    }

    public boolean isValidTrack() {
        if(featureList.get(0).getTurnDirection() != TurnDirection.STRAIGHT){
            return false;
        }
        else if(featureList.get(featureList.size()-1).getTurnDirection() != TurnDirection.STRAIGHT){
            return false;
        }
        int counter=0;
        for (TrackFeature feature : featureList) {
            if (feature.getTurnDirection() == TurnDirection.LEFT)
                counter--;
            else if (feature.getTurnDirection() == TurnDirection.RIGHT)
                counter++;
        }
        if(isClockwise())
            return counter == 4;
        else
            return counter == (-4);
    }
}
