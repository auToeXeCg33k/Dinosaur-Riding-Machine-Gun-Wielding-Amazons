package items;


public abstract class GepFegyver implements Item {
    protected double minDMG;
    protected double maxDMG;
    protected int rate;


    public double getDMG() {
        java.util.Random rand = new java.util.Random();
        double dmg = 0.0;
        for (int i = 0; i < rate; i++) {
            dmg += (this.maxDMG-this.minDMG)* rand.nextDouble() + this.minDMG;
        }
        return dmg;
    }
}