public class Car {

    private int carNo;
    private String driverName;
    private double totalTime;
    private Tire tire;

    public Car() {
        this.carNo = 0;
        this.driverName = null;
        this.totalTime = 0.0;
        this.tire = null;
    }

    public Car(String driverName, int carNo, Tire tire) {
        this.driverName = driverName;
        this.carNo = carNo;
        this.tire = tire;
        this.totalTime = 0.0;
    }

    public Tire getTire() {
        return tire;
    }

    public void setTire(Tire tire) {
        this.tire = tire;
    }

    public String getDriverName() {
        return driverName;
    }

    public void setDriverName(String driverName) {
        this.driverName = driverName;
    }

    public int getCarNo() {
        return carNo;
    }

    public void setCarNo(int carNo) {
        this.carNo = carNo;
    }

    public double getTotalTime() {
        return totalTime;
    }

    public void tick(TrackFeature feature) {
        /*For each track feature the track has, this method will be called.
        It needs to update the totalTime, and then call the currentTire.tick(f)*/

        /* At each tick cars will go through a single track feature. Time spent at a track feature is calculated by dividing
        the feature’s distance by the car’s tire’s current speed and adding a random value between 0 and 1:
        time spent = feature distance/tire s peed() + Random(0, 1.0)*/
        this.totalTime += feature.getDistance() / this.getTire().getSpeed() + Math.random();

        /* As cars go around the track their tires will degrade and when the tire degradation value goes over 70, cars
        will perform a pit stop. At the pit stop cars will put on brand new tires, but they will change their tire types
        according to the following table. The pit stop will also cost them 25 seconds.Tire degradation calculation should be
        performed after a car clears a feature. That is, first Car’s tick method should be called, then Tire’s tick method should be called.*/

        this.getTire().tick(feature);
        if(this.getTire().getDegradation() > 70){
            this.totalTime += 25;
            Tire newTire = this.getTire().pitStop();
            this.setTire(newTire);
        }
    }
}
