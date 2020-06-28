public class Dinoszaurusz implements Entity {
  private double elet = 150.0D;
  
  private boolean tamed = false;
  
  public double getHP() {
    return this.elet;
  }
  
  public boolean getTamed() {
    return this.tamed;
  }
  
  public void setTamed(boolean b) {
    this.tamed = b;
  }
  
  public void incHP(double r) {
    if (this.elet + r <= 150.0D) {
      this.elet += r;
      return;
    } 
    this.elet = 150.0D;
  }
  
  public void decHP(double r) {
    if (this.elet - r >= 0.0D) {
      this.elet -= r;
      return;
    } 
    this.elet = 0.0D;
  }
  
  public String toString() {
    return "Dinoszaurusz: " + Math.round(this.elet) + " élet," + (this.tamed ? " idomított. " : " idomítatlan.");
  }
}
