package items;


public class ShotGun extends GepFegyver {
    public ShotGun() {
        this.rate = 1;
        this.minDMG = 50.0;
        this.maxDMG = 75.0;
    }


    @Override
    public String toString() {
        return "shotgun";
    }
}
