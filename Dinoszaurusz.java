public class Dinoszaurusz implements Entity {
  private int id;
  
  private double elet;
  
  private boolean alive;
  
  private boolean tamed;
  
  public Dinoszaurusz(int id) {
    this.id = id;
    this.alive = true;
    this.elet = 150.0D;
    this.tamed = false;
  }
  
  public int getId() {
    return this.id;
  }
  
  public boolean isAlive() {
    return this.alive;
  }
  
  public void setTamed(boolean b) {
    this.tamed = b;
  }
  
  public boolean getTamed() {
    return this.tamed;
  }
  
  public void decHP(double r) {
    if (this.elet - r >= 0.0D) {
      this.elet -= r;
    } else {
      this.elet = 0.0D;
      this.alive = false;
    } 
  }
  
  public void incHP(double r) {
    if (this.elet + r <= 150.0D) {
      this.elet += r;
    } else {
      this.elet = 150.0D;
    } 
    this.alive = true;
  }
  
  public double getHP() {
    return this.elet;
  }
  
  public String toString() {
    return "Dinoszaurusz: " + Math.round(this.elet) + " élet," + (this.tamed ? " idomított. " : " idomítatlan. ");
  }
}
