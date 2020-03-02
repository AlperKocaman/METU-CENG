public class HardTire extends Tire {

    public HardTire() {
        this.speed = 275;
        this.degradation = 0;
    }

    public void tick(TrackFeature f) {
        /*The tire will degrade at each feature of the track. Moreover the amount it degrades depends on tire type (soft,
        medium, hard), feature type (high speed turn, low speed turn, straight) and the feature’s roughness value. Tire
        degradation value should start from 0 and increase at each tick method call by the following amount.
        degradation+ = feature type multiplier ∗ feature roughness ∗ tire type multiplier */

        double currDegradation = f.getFeatureTypeMultiplier() * f.getRoughness();
        this.degradation += currDegradation;

        /* Additionally, the speed of the tire should decrease at each tick method call by the following amount.
        speed− = min(75, degradation) ∗ 0.25
        Also when the tire speed drops below 100 it should not decrease more. For example, when the tire speed is 103
        and after a tick its speed drops to 98, it should stay 98. In other words, a tire shouldn’t lose speed when its speed
        is already below 100.*/

        if(this.getSpeed() >= 100) {
            this.speed -= Math.min(75, this.getDegradation())*0.25;
        }
    }


    public Tire pitStop() {
        return new SoftTire();
    }
}
