package items;

public class GepKatana extends GepFegyver {
    public GepKatana() {
        this.rate = 3;
        this.minDMG = 20.0;
        this.maxDMG = 30.0;
    }


    @Override
    public String toString() {
        return "gépkatana";
    }
}

