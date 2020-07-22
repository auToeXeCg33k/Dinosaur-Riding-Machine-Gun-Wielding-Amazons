package items;


public class MiniGun extends GepFegyver {
    public MiniGun () {
        this.rate = 30;
        this.minDMG = 1.5;
        this.maxDMG = 5.0;
    }


    @Override
    public String toString() {
        return "minigun";
    }
}
