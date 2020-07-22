package items;


public class RocketLauncher extends GepFegyver {
    public RocketLauncher () {
        this.rate = 1;
        this.minDMG = 90.0;
        this.maxDMG = 120.0;
    }


    @Override
    public String toString() {
        return "rocketlauncher";
    }
}
