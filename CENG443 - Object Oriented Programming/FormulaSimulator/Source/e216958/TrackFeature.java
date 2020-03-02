public abstract class TrackFeature {

  protected int featureNo;
  protected TurnDirection turnDirection;
  protected double distance;
  protected double roughness;

  public int getFeatureNo() {
    return featureNo;
  }

  public double getRoughness() {
    return roughness;
  }

  public double getDistance() {
    return distance;
  }

  public TurnDirection getTurnDirection() {
    return turnDirection;
  }

  abstract public double getFeatureTypeMultiplier();

}
