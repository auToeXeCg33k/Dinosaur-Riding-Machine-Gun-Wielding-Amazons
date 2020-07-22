package entities;

public class Dinoszaurusz implements Entity {
    private double elet;
    private boolean tamed;


    public Dinoszaurusz () {
        this.elet = 150.0;
        this.tamed = false;
    }


    @Override
    public double getHP() {
        return this.elet;
    }
    public boolean getTamed () {
        return tamed;
    }


    public void setTamed (boolean b) {
        this.tamed = b;
    }


    @Override
    public void incHP(double r) {
        if (elet + r <= 150.0) {
            elet += r;
            return;
        }
        elet = 150.0;
    }
    @Override
    public void decHP(double r) {
        if (elet - r >= 0.0) {
            elet -= r;
            return;
        }
        elet = 0.0;
    }


    @Override
    public String toString() {
        return "Dinoszaurusz(" + Math.round(this.elet) + (this.tamed ? "HP, idomított)" : "HP, idomítatlan)");
    }
}
