public class Straight extends TrackFeature {

    public Straight(int turnNo, TurnDirection direction, double distance, double roughness) {
        this.featureNo = turnNo;
        this.turnDirection = direction;
        this.distance = distance;
        this.roughness = roughness;
    }

    public double getFeatureTypeMultiplier() {
        return 1;
    }
}
