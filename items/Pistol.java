package items;


public class Pistol extends GepFegyver {
    public Pistol() {
        this.rate = 2;
        this.minDMG = 15.0;
        this.maxDMG = 20.0;
    }


    @Override
    public String toString() {
        return "pisztoly";
    }
}
