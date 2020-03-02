public class LowSpeedTurn extends TrackFeature {

    public LowSpeedTurn(int turnNo, TurnDirection direction, double distance, double roughness) {
        // DONE
        this.featureNo = turnNo;
        this.turnDirection = direction;
        this.distance = distance;
        this.roughness = roughness;
    }

    public double getFeatureTypeMultiplier() {
        return 1.3;
    }
}
